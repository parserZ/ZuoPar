#include <boost/assert.hpp>
#include "app/seqlabeler/trans/action.h"

namespace ZuoPar {
namespace SequenceLabeler {

std::ostream& operator<<(std::ostream& os, const Action& act) {
  os << "TAG~" << act.name();
  return os;
}

Action ActionFactory::make(const tag_t& tag) {
  return Action(tag);
}

} //  end for namespace sequencelabeler
} //  end for namespace zuopar
