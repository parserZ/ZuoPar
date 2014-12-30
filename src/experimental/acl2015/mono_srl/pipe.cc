#include <iostream>
#include <fstream>
#include <algorithm>
#include "utils/logging.h"
#include "utils/io/stream.h"
#include "utils/io/dataset/semchunks.h"
#include "utils/io/instance/semchunks.h"
#include "experimental/acl2015/mono_srl/action_utils.h"
#include "experimental/acl2015/mono_srl/pipe.h"

namespace ZuoPar {
namespace Experimental {
namespace ACL2015 {
namespace MonoSRL {

namespace eg = ZuoPar::Engine;
namespace fe = ZuoPar::FrontEnd;

Pipe::Pipe(const fe::LearnOption& opts)
  : weight(0), decoder(0), learner(0), fe::CommonPipeConfigure(opts) {
  if (load_model(opts.model_path)) {
    _INFO << "report: model is loaded.";
  } else {
    _INFO << "report: model is not loaded.";
  }
}

Pipe::Pipe(const TestOption& opts)
  : weight(0), decoder(0), learner(0),
  fe::CommonPipeConfigure(static_cast<const fe::TestOption&>(opts)) {
  if (opts.output_format == "semchunks") {
    output_format = kSemanticChunks;
  } else {
    output_format = kCoNLL2005;
  }
  if (load_model(opts.model_path)) {
    _INFO << "report: model is loaded.";
  } else {
    _INFO << "report: model is not loaded.";
  }
}

bool
Pipe::load_model(const std::string& model_path) {
  weight = new Weight;
  std::ifstream mfs(model_path);

  if (!mfs.good()) {
    _WARN << "pipe: model doesn't exists.";
    return false;
  }

  if (!forms_alphabet.load(mfs)) {
    _WARN << "pipe: failed to load forms alphabet.";
    return false;
  }

  if (!postags_alphabet.load(mfs)) {
    _WARN << "pipe: failed to load postags alphabet.";
    return false;
  }

  if (!senses_alphabet.load(mfs)) {
    _WARN << "pie: failed to load senses alphabet.";
    return false;
  }

  if (!tags_alphabet.load(mfs)) {
    _WARN << "pipe: failed to load tags alphabet.";
    return false;
  }

  if (!weight->load(mfs)) {
    _WARN << "pipe: failed to load weight.";
    return false;
  }

  return true;
}

bool
Pipe::setup() {
  namespace ioutils = ZuoPar::IO;

  dataset.clear();
  if (mode == kPipeLearn) {
    std::ifstream ifs(reference_path.c_str());
    if (!ifs.good()) {
      _ERROR << "#: failed to open reference file.";
      _ERROR << "#: training halt";
      return false;
    }
    _INFO << "report: loading dataset from reference file.";
    ioutils::read_semchunks_dataset(ifs, dataset, forms_alphabet,
        postags_alphabet, senses_alphabet, tags_alphabet, true);
    _INFO << "report: dataset is loaded from reference file.";
  } else {
    // not implemented.
    std::ifstream ifs(input_path.c_str());
    if (!ifs.good()) {
      _ERROR << "#: failed to open input file.";
      _ERROR << "#: testing halt";
      return false;
    }
    ioutils::read_semchunks_dataset(ifs, dataset, forms_alphabet,
        postags_alphabet, senses_alphabet, tags_alphabet, true);
  }
  _INFO << "report: " << dataset.size() << " instance(s) is loaded.";
  _INFO << "report: " << forms_alphabet.size() << " form(s) is detected.";
  _INFO << "report: " << postags_alphabet.size() << " postag(s) is detected.";
  _INFO << "report: " << senses_alphabet.size() << " sense(s) is detected.";
  _INFO << "report: " << tags_alphabet.size() << " tag(s) is detected.";

  return true;
}

void
Pipe::run() {
  namespace ioutils = ZuoPar::IO;
  if (!setup()) {
    return;
  }

  decoder = new Decoder(tags_alphabet.size(), tags_alphabet.encode("V"),
      beam_size, early_update, weight);

  if (mode == kPipeLearn) {
    learner = new Learner(weight, this->algorithm);
  }
  size_t N = dataset.size();
  size_t m = 1;
  std::ostream* os = (mode == kPipeLearn ? NULL: ioutils::get_ostream(output_path.c_str()));
  for (size_t n = 0; n < N; ++ n) {
    const SemanticChunks& instance = dataset[n];
    SemanticChunks output;
    output.forms = instance.forms;
    output.postags = instance.postags;
    output.senses = instance.senses;

    //ioutils::write_semchunks_instance(std::cout, instance, forms_alphabet,
    //    postags_alphabet, senses_alphabet, tags_alphabet);

    for (size_t i = 0; i < instance.nr_predicates(); ++ i, ++ m) {
      MonoSemanticChunks mono_semchunks(instance.forms,
          instance.postags,
          instance.senses,
          instance.semchunks[i]);

      // calculate the oracle transition actions.
      std::vector<Action> actions;
      if (mode == kPipeLearn) {
        ActionUtils::get_oracle_actions(mono_semchunks, actions);
      }

      int max_nr_actions = instance.size();
      State init_state(&mono_semchunks);
      Decoder::const_decode_result_t result = decoder->decode(init_state,
          actions, max_nr_actions);

      if (mode == kPipeLearn) {
        learner->set_timestamp(m);
        learner->learn(result.first, result.second);
      } else {
        build_output((*result.first), output);
      }
    }

    if ((n+ 1)% display_interval == 0) {
      _INFO << "pipe: processed #" << (n+ 1) << " instances.";
    }

    if (mode != kPipeLearn) {
      if (output_format == kSemanticChunks) {
        ioutils::write_semchunks_instance((*os), output, forms_alphabet,
            postags_alphabet, senses_alphabet, tags_alphabet);
      } else {
        ioutils::write_props_instance((*os), output, forms_alphabet,
            postags_alphabet, senses_alphabet, tags_alphabet);
      }
    }
  }
  _INFO << "pipe: processed #" << N << " instances.";

  if (mode == kPipeLearn) {
    learner->set_timestamp(m);
    learner->flush();

    std::ofstream mfs(model_path);
    if (!mfs.good()) {
      _WARN << "pipe: failed to save model.";
    } else {
      forms_alphabet.save(mfs);
      postags_alphabet.save(mfs);
      senses_alphabet.save(mfs);
      tags_alphabet.save(mfs);
      weight->save(mfs);
      _INFO << "pipe: model saved to " << model_path;
    }
  }
}

void
Pipe::build_output(const State& source, SemanticChunks& output) {
  SemanticChunks::predicate_t predicate;
  predicate.first = source.ref->predicate.first;
  for (const State* p = &source; p->previous; p = p->previous) {
    tag_t tag;

    if (ActionUtils::is_O(p->last_action)) {
      predicate.second.push_back(0);
    } else if (ActionUtils::is_B(p->last_action, tag)) {
      predicate.second.push_back(kSemanticChunkBeginTag+ tag);
    } else if (ActionUtils::is_I(p->last_action, tag)) {
      predicate.second.push_back(kSemanticChunkInterTag+ tag);
    }

  }
  std::reverse(predicate.second.begin(), predicate.second.end());
  output.semchunks.push_back(predicate);
}

} //  namespace monosrl
} //  namespace acl2015
} //  namespace sequencelabeler
} //  namespace zuopar
