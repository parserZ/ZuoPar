#include "app/depparser/arceager/weight.h"
#include "app/depparser/arceager/action.h"
#include "app/depparser/arceager/score_context.h"

namespace ZuoPar {
namespace DependencyParser {
namespace ArcEager {

Weight::Weight() {
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S0w, S0p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0w, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N1w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N1p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N1w, N1p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N2w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N2p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N2w, N2p );
  // There should be a quadgram feature in Zhang and Nirve (2011)
  // regist_quadgram_feature( S0w, S0p, N0w, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_Q1100(S0w, S0p, N0w, N0p);
  ZUOPAR_FEATURE_MAP_REGIST_T110( S0w, S0p, N0w );
  ZUOPAR_FEATURE_MAP_REGIST_T100( S0w, N0w, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T110( S0w, S0p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T100( S0p, N0w, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_B10( S0w, N0w );
  ZUOPAR_FEATURE_MAP_REGIST_B10( S0p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_B10( N0p, N1p );
  ZUOPAR_FEATURE_MAP_REGIST_T100( N0p, N1p, N2p );
  ZUOPAR_FEATURE_MAP_REGIST_T110( S0p, N0p, N1p );
  ZUOPAR_FEATURE_MAP_REGIST_T110( S0hp, S0p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T110( S0p, S0ldp, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T110( S0p, S0rdp, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0p, N0p, N0ldp );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S0w, DistS0N0 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S0p, DistS0N0 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0w, DistS0N0 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0p, DistS0N0 );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0w, N0w, DistS0N0 );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0p, N0p, DistS0N0 );
  ZUOPAR_FEATURE_MAP_REGIST_B10( S0w, S0ra );
  ZUOPAR_FEATURE_MAP_REGIST_B10( S0p, S0ra );
  ZUOPAR_FEATURE_MAP_REGIST_B10( S0w, S0la );
  ZUOPAR_FEATURE_MAP_REGIST_B10( S0p, S0la );
  ZUOPAR_FEATURE_MAP_REGIST_B10( N0w, N0la );
  ZUOPAR_FEATURE_MAP_REGIST_B10( N0p, N0la );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0hw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0hp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0hl );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0ldw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0ldp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0ldl );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0rdw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0rdp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0rdl );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0ldw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0ldp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0ldl );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0h2w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0h2p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0h2l );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0l2dw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0l2dp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0l2dl );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0r2dw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0r2dp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0r2dl );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0l2dw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0l2dp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0l2dl );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0p, S0ldp, S0l2dp );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0p, S0rdp, S0r2dp );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0p, S0hp, S0h2p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( N0p, N0ldp, N0l2dp );
  ZUOPAR_FEATURE_MAP_REGIST_B10( S0w, S0lset );
  ZUOPAR_FEATURE_MAP_REGIST_B10( S0p, S0lset );
  ZUOPAR_FEATURE_MAP_REGIST_B10( S0w, S0rset );
  ZUOPAR_FEATURE_MAP_REGIST_B10( S0p, S0rset );
  ZUOPAR_FEATURE_MAP_REGIST_B10( N0w, N0lset );
  ZUOPAR_FEATURE_MAP_REGIST_B10( N0p, N0lset );
  // There should also be the label set feature.
}

#undef _u
#undef _b
#undef _t

#undef ZUOPAR_FEATURE_MAP_REGIST_U1
#undef ZUOPAR_FEATURE_MAP_REGIST_B11
#undef ZUOPAR_FEATURE_MAP_REGIST_T111

} //  end for namespace arceager
} //  end for namespace dependencyparser
} //  end for namespace zuopar
