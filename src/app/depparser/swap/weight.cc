#include "app/depparser/swap/weight.h"
#include "app/depparser/swap/action.h"
#include "app/depparser/swap/score_context.h"

namespace ZuoPar {
namespace DependencyParser {
namespace Swap {

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
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0R2w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S1w, S1p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1L2p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1L1w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1L1p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1R1w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1R1p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1R2w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0w, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0L2p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0L1w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0L1p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0R1w );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0R1p );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0R2w );
  // Bigram
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0R1p, S0p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0L1p, S0w );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0R1p, S0w );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0R1p, S1w );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0R1w, S0p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0R1w, S1p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0R1w, S0p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0R1w, S1p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0R1w, S0w );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S0R1w, S0w );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S0R1w, S1w );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0L1w, S0w );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0R1w, S0w );
  ZUOPAR_FEATURE_MAP_REGIST_B11( N0R1w, S1w );
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
  // Word Pair
  ZUOPAR_FEATURE_MAP_REGIST_T111( S1w, S1p, S0w );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S1w, S0w, S0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S1w, S1p, S0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S1p, S0w, S0p );
  ZUOPAR_FEATURE_MAP_REGIST_Q1111( S0w, S0p, S1w, S1p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S1w, S0w );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S1p, S0p );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S0p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S1p, S0p, N0p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0p, S0ldp, S1p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0p, S0rdp, S1p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0p, S1ldp, S1p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0p, S1rdp, S1p );
  // Distance feature
  ZUOPAR_FEATURE_MAP_REGIST_B11( S0w, DistS0S1 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S0p, DistS0S1 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S1w, DistS0S1 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( S1p, DistS0S1 );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0w, S1w, DistS0S1 );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0p, S1p, DistS0S1 );
  // Valancy
  ZUOPAR_FEATURE_MAP_REGIST_B10( S0w, S0la );
  ZUOPAR_FEATURE_MAP_REGIST_B10( S0w, S0ra );
  ZUOPAR_FEATURE_MAP_REGIST_B10( S0p, S0la );
  ZUOPAR_FEATURE_MAP_REGIST_B10( S0p, S0ra );
  ZUOPAR_FEATURE_MAP_REGIST_B10( S1w, S1la );
  ZUOPAR_FEATURE_MAP_REGIST_B10( S1w, S1ra );
  ZUOPAR_FEATURE_MAP_REGIST_B10( S1p, S1la );
  ZUOPAR_FEATURE_MAP_REGIST_B10( S1p, S1ra );
  // Label set
  ZUOPAR_FEATURE_MAP_REGIST_T100( S0w, S0lsetl, S0lseth );
  ZUOPAR_FEATURE_MAP_REGIST_T100( S0p, S0lsetl, S0lseth );
  ZUOPAR_FEATURE_MAP_REGIST_T100( S0w, S0rsetl, S0rseth );
  ZUOPAR_FEATURE_MAP_REGIST_T100( S0p, S0rsetl, S0rseth );
  ZUOPAR_FEATURE_MAP_REGIST_T100( S1w, S1lsetl, S1lseth );
  ZUOPAR_FEATURE_MAP_REGIST_T100( S1p, S1lsetl, S1lseth );
  ZUOPAR_FEATURE_MAP_REGIST_T100( S1w, S1rsetl, S1rseth );
  ZUOPAR_FEATURE_MAP_REGIST_T100( S1p, S1rsetl, S1rseth );
  // 2nd-order
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0ldw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0ldp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0ldl );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0rdw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0rdp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0rdl );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1ldw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1ldp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1ldl );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1rdw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1rdp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1rdl );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0ldp, S0p, S1p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0rdp, S0p, S1p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S1ldp, S0p, S1p );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S1rdp, S0p, S1p );
  // 3rd-order
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0l2dw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0l2dp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0l2dl );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0r2dw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0r2dp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0r2dl );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1l2dw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1l2dp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1l2dl );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1r2dw );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1r2dp );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1r2dl );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0p, S0ldp, S0l2dp );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S0p, S0rdp, S0r2dp );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S1p, S1ldp, S1l2dp );
  ZUOPAR_FEATURE_MAP_REGIST_T111( S1p, S1rdp, S1r2dp );
  // CoNLL feats: so mophological category
  ufeat_map_repo.push_back( uf_map_t([](const ScoreContext& ctx,
          std::vector<ufp_t>& cache) -> void {
        if (ctx.S0Feat) {
          for (int _: (*ctx.S0Feat)) { cache.push_back( ufp_t(_) ); }
        }
      }) );
  ufeat_map_repo.push_back( uf_map_t([](const ScoreContext& ctx,
          std::vector<ufp_t>& cache) -> void {
        if (ctx.S1Feat) {
          for (int _: (*ctx.S1Feat)) { cache.push_back( ufp_t(_) ); }
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
        if (ctx.S0Feat && ctx.S1Feat) {
          for (int _1: (*ctx.S0Feat)) {
            for (int _2: (*ctx.S1Feat)) { cache.push_back( bfp_t(_1, _2) ); }
          }
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
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1IsBegin );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S0IsEnd );
  ZUOPAR_FEATURE_MAP_REGIST_U1( N0IsEnd );
  ZUOPAR_FEATURE_MAP_REGIST_U1( S1S0Adjacent );

}

} //  end for namespace swap
} //  end for namespace dependencyparser
} //  end for namespace zuopar
