#include <iostream>
#include <cstring>  // strcmp
#include <boost/program_options.hpp>
#include "utils/logging.h"
#include "experimental/hc_search/arceager/opt.h"
#include "experimental/hc_search/arceager/opt_utils.h"
#include "experimental/hc_search/arceager/pipe.h"

#define __EXE__ "experimental/hc_arceager_depparser"

namespace fe = ZuoPar::FrontEnd;
namespace hc = ZuoPar::Experimental::HCSearchDependencyParser;
namespace po = boost::program_options;

/**
 * Perform the learning process of ZuoPar::arceager dependency parser.
 *
 *  @param[in]  argc  The number of arguments.
 *  @param[in]  argv  The arguments.
 *  @return     int   The status of running learning.
 */
int learn_phase_one(int argc, char** argv) {
  std::string usage = "Training component of ZuoPar::HC-search arceager depparser phase(1).\n";
  usage += "Author: Yijia Liu (oneplus.lau@gmail.com).\n\n";
  usage += "Usage: " __EXE__ " learn-phase-one [options]\n";
  usage += "OPTIONS";

  po::options_description optparser = hc::build_phase_one_learn_optparser(usage);

  if (argc == 1) {
    std::cerr << optparser << std::endl;
    return 1;
  }

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, optparser), vm);

  hc::LearnOneOption opts;
  if (!hc::parse_phase_one_learn_option(vm, opts)) {
    std::cerr << optparser << std::endl;
    return 1;
  }

  hc::Pipe pipe(opts);
  pipe.run();
  return 0;
}

int learn_phase_two(int argc, char** argv) {
  std::string usage = "Training component of ZuoPar::HC-search arceager depparser phase(2).\n";
  usage += "Author: Yijia Liu (oneplus.lau@gmail.com).\n\n";
  usage += "Usage: " __EXE__ " learn-phase-two [options]\n";
  usage += "OPTIONS";

  po::options_description optparser = hc::build_phase_two_learn_optparser(usage);
  if (argc == 1) {
    std::cerr << optparser << std::endl;
    return 1;
  }
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, optparser), vm);

  hc::LearnTwoOption opts;
  if (!hc::parse_phase_two_learn_option(vm, opts)) {
    std::cerr << optparser << std::endl;
    return 1;
  }

  hc::Pipe pipe(opts);
  pipe.run();
  return 0;
}

int evaluate(int argc, char** argv) {
  std::string usage = "Evaluating component of ZuoPar::HC-search arceager dependency parser.\n";
  usage += "Author: Yijia Liu (oneplus.lau@gmail.com).\n\n";
  usage += "Usage: " __EXE__ " test [options]\n";
  usage += "OPTIONS";

  po::options_description optparser = hc::build_evaluate_optparser(usage);
  if (argc == 1) {
    std::cerr << optparser << std::endl;
    return 1;
  }

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, optparser), vm);
  hc::EvaluateOption opts;
  if (!hc::parse_evaluate_option(vm, opts)) {
    std::cerr << optparser << std::endl;
    return 1;
  }
  hc::Pipe pipe(opts);
  pipe.run();
  return 0;
}

/**
 * Perform the testing process of ZuoPar::arceager dependency parser.
 *
 *  @param[in]  argc  The number of arguments.
 *  @param[in]  argv  The arguments.
 *  @return     int   The status of running test.
 */
int test(int argc, char** argv) {
  std::string usage = "Testing component of ZuoPar::HC-search arceager dependency parser.\n";
  usage += "Author: Yijia Liu (oneplus.lau@gmail.com).\n\n";
  usage += "Usage: " __EXE__ " test [options]\n";
  usage += "OPTIONS";

  po::options_description optparser = hc::build_test_optparser(usage);

  if (argc == 1) {
    std::cerr << optparser << std::endl;
    return 1;
  }

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, optparser), vm);

  hc::TestOption opts;
  if (!hc::parse_test_option(vm, opts)) {
    std::cerr << optparser << std::endl;
    return 1;
  }
  hc::Pipe pipe(opts);
  pipe.run();

  return 0;
}

int main(int argc, char** argv) {
  std::string usage = "ZuoPar::HC-search arceager dependency parser.\n";
  usage += "Author: Yijia Liu (oneplus.lau@gmail.com).\n\n";
  usage += "Usage: " __EXE__;
  usage += " [learn-phase-one|learn-phase-two|evaluate|test] [options]";

  if (argc == 1) {
    std::cerr << usage << std::endl;
    return 1;
  } else if (strcmp(argv[1], "learn-phase-one") == 0) {
    learn_phase_one(argc- 1, argv+ 1);
  } else if (strcmp(argv[1], "learn-phase-two") == 0) {
    learn_phase_two(argc- 1, argv+ 1);
  } else if (strcmp(argv[1], "evaluate") == 0) {
    evaluate(argc- 1, argv+ 1);
  } else if (strcmp(argv[1], "test") == 0) {
    test(argc- 1, argv+ 1);
  } else {
    std::cerr << "Unknown mode: " << argv[1] << std::endl;
    std::cerr << usage << std::endl;
    return 1;
  }

  return 0;
}