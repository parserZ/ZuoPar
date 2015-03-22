#include "app/depparser/choi2013/weight.h"

namespace ZuoPar {
namespace DependencyParser {
namespace Choi2013 {

Weight::Weight() {
  // Unigram
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S0w, S0p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0L2p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0L1w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0L1p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0R1w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0R1p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0R2p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0w, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0L2w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0L1w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0L1p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0R1w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0R1p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0R2w );
  // Bigram
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0R1p, S0p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S1p, S0p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S1p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0L1p, S0w );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0R1p, S0w );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0R1p, N0w );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0R1w, S0p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0R1w, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0R1w, S0p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0R1w, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0R1w, S0w );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S1w, S0w );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S1w, N0w );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S0R1w, S0w );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S0R1w, N0w );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0L1w, S0w );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0R1w, S0w );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0R1w, N0w );
  // Trigram
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0L2p, S0L1p, S0p);
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0L1p, S0p, S0R1p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0p, S0R1p, S0R2p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( N0L1p, N0p, N0R1p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( N0p, N0R1p, N0R2p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0L2p, S0p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0L1p, S0p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0R1p, S0p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0R2p, S0p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( N0L2p, S0p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( N0L1p, S0p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( N0R2p, S0p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( N0R1p, S0p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S1p, S0p, N0p );
  // Word pair
  ZUOPAR_FEATURE_MAP_REGIST_Q1111(S0w, S0p, N0w, N0p);
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0w, S0p, N0w );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0w, N0w, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0w, S0p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0p, N0w, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S0w, N0w );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S0p, N0p );
  // Distance feature
  ZUOPAR_FEATURE_MAP_REGIST_B11( S0w, DistS0N0 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S0p, DistS0N0 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0w, DistS0N0 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0p, DistS0N0 );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0w, N0w, DistS0N0 );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0p, N0p, DistS0N0 );
  // Valancy
  ZUOPAR_FEATURE_MAP_REGIST_B10( S0w, S0ra );
  ZUOPAR_FEATURE_MAP_REGIST_B10( S0p, S0ra );
  ZUOPAR_FEATURE_MAP_REGIST_B10( S0w, S0la );
  ZUOPAR_FEATURE_MAP_REGIST_B10( S0p, S0la );
  ZUOPAR_FEATURE_MAP_REGIST_B10( N0w, N0la );
  ZUOPAR_FEATURE_MAP_REGIST_B10( N0p, N0la );
  // label set 
  ZUOPAR_FEATURE_MAP_REGIST_T100( S0w, S0lsetl, S0lseth );
  ZUOPAR_FEATURE_MAP_REGIST_T100( S0p, S0lsetl, S0lseth );
  ZUOPAR_FEATURE_MAP_REGIST_T100( S0w, S0rsetl, S0rsetl );
  ZUOPAR_FEATURE_MAP_REGIST_T100( S0p, S0rsetl, S0rseth );
  ZUOPAR_FEATURE_MAP_REGIST_T100( N0w, N0lsetl, N0lseth );
  ZUOPAR_FEATURE_MAP_REGIST_T100( N0p, N0lsetl, N0lseth );
  // 2nd-order
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0hw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0hp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0hl );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0hw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0hp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0hl );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0ldw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0ldp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0ldl );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0rdw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0rdp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0rdl );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0ldw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0ldp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0ldl );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S0ldl, S0hl );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S0rdl, S0hl );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S0h2l, S0hl );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0ldl, N0hl );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0h2l, N0hl );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0hp, S0p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( N0hp, S0p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0ldp, S0p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0rdp, S0p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( N0ldp, S0p, N0p );
  // 3rd-order
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0h2w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0h2p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0h2l );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0h2w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0h2p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0h2l );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0l2dw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0l2dp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0l2dl );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0r2dw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0r2dp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0r2dl );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0l2dw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0l2dp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0l2dl );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S0l2dl, S0hl );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S0r2dl, S0hl );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0l2dl, N0hl );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0p, S0ldp, S0l2dp );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0p, S0rdp, S0r2dp );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0p, S0hp, S0h2p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( N0p, N0ldp, N0l2dp );
  ZUOPAR_FEATURE_MAP_REGIST_T111( N0p, N0hp, N0h2p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0l2dp, S0p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0r2dp, S0p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( N0l2dp, S0p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0h2p, S0p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( N0h2p, S0p, N0p );
  // CoNLL feats: so mophological category
  ufeat_map_repo.push_back( uf_map_t([](const ScoreContext& ctx,
          std::vector<ufp_t>& cache) -> void {
        if (ctx.S0Feat) {
          for (int _: (*ctx.S0Feat)) { cache.push_back( ufp_t(_) ); }
        }
      }) );
  ufeat_map_repo.push_back( uf_map_t([](const ScoreContext& ctx,
          std::vector<ufp_t>& cache) -> void {
        if (ctx.N0Feat) {
          for (int _: (*ctx.N0Feat)) { cache.push_back( ufp_t(_) ); }
        }
      }) );
  bfeat_map_repo.push_back( bf_map_t([](const ScoreContext& ctx,
          std::vector<bfp_t>& cache) -> void {
        if (ctx.S0Feat && ctx.N0Feat) {
          for (int _1: (*ctx.S0Feat)) {
            for (int _2: (*ctx.N0Feat)) { cache.push_back( bfp_t(_1, _2) ); }
          }
        }
      }) );
  // Binary
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0IsBegin );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0IsEnd );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0N0Adjacent );
}

} //  end for namespace choi2013
} //  end for namespace dependencyparser
} //  end for namespace zuopar
