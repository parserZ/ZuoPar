#ifndef __ZUOPAR_EXPERIMENTAL_ACL2015_MONO_SRL_PIPE_H__
#define __ZUOPAR_EXPERIMENTAL_ACL2015_MONO_SRL_PIPE_H__

#include "types/semchunks.h"
#include "frontend/common_pipe_cfg.h"
#include "engine/token_alphabet.h"
#include "experimental/acl2015/mono_srl/opt.h"
#include "experimental/acl2015/mono_srl/weight.h"
#include "experimental/acl2015/mono_srl/decoder.h"
#include "experimental/acl2015/mono_srl/learner.h"

namespace ZuoPar {
namespace Experimental {
namespace ACL2015 {
namespace MonoSRL {

namespace eg = ZuoPar::Engine;
namespace fe = ZuoPar::FrontEnd;

class Pipe : fe::CommonPipeConfigure {
public:
  /**
   * The learning mode constructor.
   *
   *  @param[in]  opts  The learning options.
   */
  Pipe(const fe::LearnOption& opts);

  /**
   * The testing mode constructor.
   *
   *  @param[in]  opts  The testing options.
   */
  Pipe(const TestOption& opts);

  /**
   * Perform learning or testing according to the configuration.
   */
  void run();

protected:
  bool setup();

  /**
   * Load model from the specified path.
   *
   *  @param[in]  model_path  The path to the model.
   */
  bool load_model(const std::string& model_path);

  /**
   * Build the dependency output for the state chain which ends with the source
   * state.
   *
   *  @param[in]  source  The last state in state chain.
   *  @param[out] output  The output dependency parse.
   */
  void build_output(const State& source, SemanticChunks& output);

protected:
  enum OutputFormat {
    kSemanticChunks,
    kCoNLL2005
  };

  OutputFormat output_format;

  //! The pointer to the weights instances which is pointwise averaged
  //! perceptron model.
  Weight* weight;

  //! The parameter learner.
  Learner* learner;

  //! The pointer to the decoder.
  Decoder* decoder;

  //! The alphabet of attributes.
  eg::TokenAlphabet forms_alphabet;

  //! The alphabet of postags.
  eg::TokenAlphabet postags_alphabet;

  //! The alphabet of senses.
  eg::TokenAlphabet senses_alphabet;

  //! The alphabet of semantic chunks.
  eg::TokenAlphabet tags_alphabet;

  //! The dataset.
  std::vector<SemanticChunks> dataset;
};

} //  namespace monosrl
} //  namespace acl2015
} //  namespace experimental
} //  namespace zuopar

#endif  //  end for __ZUOPAR_EXPERIMENTAL_ACL2015_MONO_SRL_PIPE_H__
