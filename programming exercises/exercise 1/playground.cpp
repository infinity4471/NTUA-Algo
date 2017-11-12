#include <cstdio>
#include <algorithm>

#define MAXN 800

using namespace std;

int N, K, grid[ MAXN + 1 ][ MAXN + 1 ], S[ MAXN + 1 ][ MAXN + 1 ];

int sum( int x1, int y1, int x2, int y2 ) {
  return S[ x2 ][ y2 ] - S[ x2 ][ y1 - 1 ] - S[ x1 - 1 ][ y2 ] + S[ x1 - 1 ][ y1 - 1 ];
}

int main( void ) {
  freopen("input.txt","rt",stdin);
  scanf("%d%d", &N, &K );
  for( int i = 1; i <= N; i++ ) {
    scanf("\n");
    for( int j = 1; j <= N; j++ ) {
      char c = getchar_unlocked();
      grid[ i ][ j ] = c - '0';
    }
  }
  for( int i = 1; i <= N; i++ ) {
    for( int j = 1; j <= N; j++ ) {
      S[ i ][ j ] = S[ i - 1 ][ j ] + S[ i ][ j - 1 ] - S[ i - 1 ][ j - 1 ] + grid[ i ][ j ];
    }
  }
  int ans = 0;
  for( int x1 = 1; x1 <= N; x1++ ) {
    for( int x2 = x1; x2 <= N; x2++ ) {
      for( int y1 = 1, y2 = 1; y2 <= N; ) {
        int getsum = sum( x1, y1, x2, y2 );
        if( getsum < K ) y2++;
        else if( getsum > K ) y1++;
        else {
          int cnt1 = 0, cnt2 = 0, yy = y1;
          while( sum( x1, y1, x2, y2 ) == K ) {
            y1++;
            cnt1++;
          }
          y1--;
          while( sum( x1, yy, x2, y2 ) == K ) {
            y2++;
            cnt2++;
          }
          ans += cnt1 * cnt2;
        }
      }
    }
  }
  printf("%d\n", ans );
  return 0;
}
