#include <cstdio>
#include <algorithm>

#define MAXN 2510
#define INF 123456789

using namespace std;

int N, K, A[ MAXN + 1 ][ MAXN + 1 ], S[ MAXN + 1 ][ MAXN + 1 ], dp[ MAXN + 1][ MAXN + 1 ];

int sum( int x1, int y1, int x2, int y2 ) {
  return S[ x2 ][ y2 ] - S[ x1 - 1 ][ y2 ] - S[ x2 ][ y1 - 1 ] + S[ x1 - 1 ][ y1 - 1 ];
}

int main( void ) {
  scanf("%d%d", &N, &K );
  for( int i = 1; i <= N; i++ ) {
    for( int j = i + 1; j <= N; j++ ) {
      scanf("%d", &A[ i ][ j ] );
    }
  }

  for( int i = 1; i <= N; i++ ) {
    for( int j = 1; j <= N; j++ ) {
      S[ i ][ j ] = S[ i - 1 ][ j ] + S[ i ][ j - 1 ] - S[ i - 1 ][ j - 1 ] + A[ i ][ j ];
    }
  }
  for( int i = 1; i <= N; i++ ) dp[ i ][ 0 ] = INF;
  for( int i = 1; i <= N; i++ ) {
    for( int k = 1; k <= K; k++ ) {
      dp[ i ][ k ] = INF;
      for( int j = i; j > 0; j-- ) {
        dp[ i ][ k ] = min( dp[ i ][ k ], dp[ j - 1 ][ k - 1 ] + sum( j, j, i, i ) );
      }
    }
  }
  printf("%d\n", dp[ N ][ K ] );
  return 0;
}
