#include <cstdio>
#include <algorithm>

int ans, N, K, A[ 100100 ], dp[ 2 ][ 100100 ];

int main( void ) {
  scanf("%d%d", &N, &K );
  for( int i = 1; i <= N; i++ ) scanf("%d", &A[ i ] );
  for( int i = 1; i <= K; i++ ) {
    int maxim = -A[ 1 ];
    for( int j = 2; j <= N; j++ ) {
      dp[ i % 2 ][ j ] = std::max( dp[ i % 2 ][ j - 1 ], A[ j ] + maxim );
      maxim = std::max( maxim, -A[ j ] + dp[ ( i - 1 ) % 2 ][ j ] );
      if( j == N ) ans = std::max( ans, dp[ i % 2 ][ j ] );
    }
  }
  printf("%d\n", ans );
  return 0;
}
