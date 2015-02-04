#ifndef __ZUOPAR_EXPERIMENTAL_HCSEARCH_ARCEAGER_ACTION_H__
#define __ZUOPAR_EXPERIMENTAL_HCSEARCH_ARCEAGER_ACTION_H__

#include <iostream>
#include <boost/assert.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/functional/hash.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "types/common.h"
#include "system/action/abstract_action.h"

namespace ZuoPar {
namespace Experimental {
namespace HCSearchDependencyParser {

class Action: public AbstractAction {
public:
  enum {
    kNone = 0,  //! Placeholder for illegal action.
    kShift,     //! The index of shift action.
    kReduce,    //! The index of reduce action.
    kLeftArc,   //! The index of arc left action.
    kRightArc   //! The index of arc right action.
  };

  Action() : AbstractAction() {}

  /**
   * Constructor for action.
   *
   *  @param[in]  name  The name for the action.
   *  @param[in]  rel   The dependency relation.
   */
  Action(int name, deprel_t rel) : AbstractAction(name, rel) {}

  //! Overload the ostream function.
  friend std::ostream& operator<<(std::ostream& os, const Action& act);

  //! For is_shift, is_left_arc, is_right_arc;
  friend class ActionUtils;
};

class ActionFactory {
public:
  /**
   * Make a shift action.
   *
   *  @return Action  A shift action.
   */
  static Action make_shift();

  /**
   * Make a reduce action.
   *
   *  @return Action  A reduce action.
   */
  static Action make_reduce();

  /**
   * Make a arc left action.
   *
   *  @param[in]  rel     The dependency relation.
   *  @return     Action  The arc left action.
   */
  static Action make_left_arc(const deprel_t& rel);

  /**
   * Make a arc right action.
   *
   *  @param[in]  rel     The dependency relation.
   *  @return     Action  The arc right action.
   */
  static Action make_right_arc(const deprel_t& rel);
};

} //  namespace hcsearchdependencyparser
} //  namespace experimental
} //  namespace zuopar

#endif  //  end for __ZUOPAR_EXPERIMENTAL_HCSEARCH_ARCEAGER_ACTION_H__