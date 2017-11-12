#include <cstdio>
#include <algorithm>

#define MAXN 2510
#define INF 123456789

using namespace std;

int N, K, A[ MAXN + 1 ][ MAXN + 1 ], S[ MAXN + 1 ][ MAXN + 1 ], pos[ MAXN + 1 ][ MAXN + 1 ], dp[ MAXN + 1][ MAXN + 1 ];

int readint() {
    int n = 0;
    char c = getchar_unlocked();
    while ( !( '0' <= c && c <= '9' ) ) {
        c = getchar_unlocked();
    }
    while ( '0' <= c && c <= '9' ) {
        n = n * 10 + c - '0';
        c = getchar_unlocked();
    }
    return n;
}

int sum( int x1, int y1, int x2, int y2 ) {
  return S[ x2 ][ y2 ] - S[ x1 - 1 ][ y2 ] - S[ x2 ][ y1 - 1 ] + S[ x1 - 1 ][ y1 - 1 ];
}

void calculate( int k, int x1, int x2, int p1, int p2 ) {
  if( x1 > x2 ) return;
  int mid = ( x1 + x2 ) >> 1;
  pos[ mid ][ k ] = -1;
  dp[ mid ][ k ] = INF;
  for( int i = p1; i <= p2; i++ ) {
    int val = dp[ i ][ k - 1 ] + sum( i + 1, i + 1, mid, mid );
    if( val < dp[ mid ][ k ] ) {
      dp[ mid ][ k ] = val;
      pos[ mid ][ k ] = i;
    }
  }
  calculate( k, x1, mid - 1, p1, pos[ mid ][ k ] );
  calculate( k, mid + 1, x2, pos[ mid ][ k ], p2 );
}

int main( void ) {
  N = readint();
  K = readint();
  for( int i = 1; i <= N; i++ ) {
    for( int j = i + 1; j <= N; j++ ) {
      A[ i ][ j ] = readint();
    }
  }

  for( int i = 1; i <= N; i++ ) {
    for( int j = 1; j <= N; j++ ) {
      S[ i ][ j ] = S[ i - 1 ][ j ] + S[ i ][ j - 1 ] - S[ i - 1 ][ j - 1 ] + A[ i ][ j ];
    }
  }

  for( int i = 1; i <= N; i++ ) {
    dp[ i ][ 1 ] = sum( 1, 1, i, i );
    pos[ i ][ 1 ] = 0;
  }

  for( int k = 2; k <= K; k++ ) calculate( k, 0, N, 0, N );
  printf("%d\n", dp[ N ][ K ] );
  return 0;
}
