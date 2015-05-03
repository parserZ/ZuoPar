#ifndef __ZUOPAR_DEPPARSER_NN_CLASSIFIER_H__
#define __ZUOPAR_DEPPARSER_NN_CLASSIFIER_H__

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <armadillo>
#include <boost/bind/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/lockfree/queue.hpp>
#include "types/common.h"
#include "app/depparser/nn/dataset.h"
#include "app/depparser/nn/opt.h"

namespace ZuoPar {
namespace DependencyParser {
namespace NeuralNetwork {

class Cost {
public:
  typedef std::vector<std::vector<int> > history_t;

  floatval_t loss;
  floatval_t accuracy;
  arma::mat grad_W1;
  arma::vec grad_b1;
  arma::mat grad_W2;
  arma::mat grad_E;
  history_t dropout_histories;

  Cost();

  void emplace(const floatval_t& loss,
      const floatval_t& accuracy,
      const arma::mat& grad_W1,
      const arma::vec& grad_b1,
      const arma::mat& grad_W2,
      const arma::mat& grad_E,
      const history_t& dropout_histories
      );

  void merge(const Cost& other, bool debug = false);
};

class NeuralNetworkClassifier {
private:
  // The weight group.
  arma::mat W1;         // Mat: hidden_layer_size X (nr_feature_types * embedding_size)
  arma::mat W2;         // Mat: nr_classes X hidden_layer_size
  arma::mat E;          // Mat: nr_objects X embedding_size
  arma::vec b1;         // Vec: hidden_layer_size

  arma::mat grad_W1;
  arma::vec grad_b1;
  arma::mat grad_W2;
  arma::mat grad_E;

  arma::mat eg2W1;
  arma::mat eg2W2;
  arma::mat eg2E;
  arma::vec eg2b1;

  floatval_t loss;
  floatval_t accuracy;

  // Precomputed matrix
  arma::mat saved;      // Mat: encoder.size() X hidden_layer_size
  arma::mat grad_saved; // Mat: encoder.size() X hidden_layer_size

  Cost cost;  // The cost in each iteration

  // The configuration
  size_t embedding_size;      //! The size of the embedding.
  size_t hidden_layer_size;   //! The size of the hidden layer
  size_t nr_objects;          //! The sum of forms, postags and deprels
  size_t nr_feature_types;    //! The number of feature types
  size_t nr_classes;          //! The number of classes

  size_t batch_size;
  size_t nr_threads;
  bool fix_embeddings;
  bool debug;
  floatval_t dropout_probability;
  floatval_t lambda;
  floatval_t ada_eps;
  floatval_t ada_alpha;

  const Dataset* dataset;
  std::unordered_map<int, size_t> precomputation_id_encoder;

  bool initialized;
  size_t cursor;
public:
  NeuralNetworkClassifier();

  /**
   * Initialize the neural network
   *
   *  @param[in]  nr_forms        The size of vocabulary.
   *  @param[in]  nr_postags      The size of postags.
   *  @param[in]  nr_labels       The size of label set.
   *  @param[in]  nr_tokens       (?)
   *  @param[in]  embedding_size  The size of embeddings
   *  @param[in]  hidden_size     The size of hidden layer
   */
  void initialize(int nr_forms, int nr_postags, int nr_deprels,
      const LearnOption& opt,
      const std::vector< std::vector<floatval_t> >& embeddings,
      const Dataset* dataset,
      const std::vector<int>& precomputed_features
      );

  /**
   * Calculate scores for the given features.
   *
   *  @param[in]  features  The features
   *  @param[out] retval    The calculated score
   */
  void score(const std::vector<int>& attributes, std::vector<floatval_t>& retval);

  void info();
  //!
  void compute_ada_gradient_step();

  //!
  void initialize_gradient_histories();

  void take_ada_gradient_step();

  //!
  floatval_t get_cost();

  //!
  floatval_t get_accuracy();

  /**
   * Collect the indices from samples and put them into a set.
   *
   *  @param[in]  samples The samples
   *  @param[out] retval  The set of indicies
   */
  void get_precomputed_features(std::vector<Sample>::const_iterator& begin,
      std::vector<Sample>::const_iterator& end,
      std::unordered_set<int>& retval);

  void precomputing();

  void precomputing(const std::unordered_set<int>& candidates);

  void compute_gradient(std::vector<Sample>::const_iterator& begin,
      std::vector<Sample>::const_iterator& end,
      size_t batch_size);

  void compute_saved_gradient(
      const std::unordered_set<int>& precomputed_indices);

  void add_l2_regularization();

  void save(std::ofstream& mfs);

  void load(std::ifstream& mfs);
};

} //  namespace neuralnetwork
} //  namespace dependencyparser
} //  namespace zuopar

#endif  //  end for __ZUOPAR_DEPPARSER_NN_CLASSIFIER_H__
