#include <boost/assert.hpp>
#include "experimental/acl2015/mono_predicate_srl/action.h"

namespace ZuoPar {
namespace Experimental {
namespace ACL2015 {
namespace MonoPredicateSRL {

Action ActionFactory::make_O() {
  return Action(Action::kO, 0);
}

Action ActionFactory::make_B(const tag_t& tag) {
  return Action(Action::kB, tag);
}

Action ActionFactory::make_I(const tag_t& tag) {
  return Action(Action::kI, tag);
}

} //  namespace monopredicatesrl
} //  namespace acl2015
} //  namespace experimental
} //  namespace zuopar