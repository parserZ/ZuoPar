#ifndef __ZUOPAR_APP_SEQUENCE_LABELER_PIPE_H__
#define __ZUOPAR_APP_SEQUENCE_LABELER_PIPE_H__

#include "types/sequence_instance.h"
#include "engine/token_alphabet.h"
#include "app/seqlabeler/opt.h"
#include "app/seqlabeler/weight.h"
#include "app/seqlabeler/decoder.h"
#include "app/seqlabeler/learner.h"

namespace ZuoPar {
namespace SequenceLabeler {

namespace eg = ZuoPar::Engine;
namespace fe = ZuoPar::FrontEnd;

class Pipe {
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
  Pipe(const fe::TestOption& opts);

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
  void build_output(const State& source, SequenceInstance& output);

protected:
  //! The supported modes.
  enum PipeMode { kPipeLearn, kPipeTest };

  //! Use to specify if perform training.
  PipeMode mode;

  //! The path to the reference file.
  std::string reference_path;

  //! The path to the model file.
  std::string model_path;

  //!
  std::string input_path;

  //!
  std::string output_path;

  //! The size of the beam.
  int beam_size;

  //! The display.
  int display_interval;

  //! The pointer to the weights instances which is pointwise averaged
  //! perceptron model.
  Weight* weight;

  //! The parameter learner.
  Learner* learner;

  //! The learning algorithm.
  Learner::LearningAlgorithm algorithm;

  //! The early update flag.
  bool early_update;

  //! The pointer to the decoder.
  Decoder* decoder;

  //! The alphabets of attributes.
  eg::TokenAlphabet attributes_alphabet;

  //! The alphabets of postags.
  eg::TokenAlphabet tags_alphabet;

  //! The dataset.
  std::vector<SequenceInstance> dataset;
};


} //  end for namespace sequencelabeler
} //  end for namespace zuopar

#endif  //  end for __ZUOPAR_APP_SEQUENCE_LABELER_PIPE_H__
