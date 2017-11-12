#include <cstdio>
#include <algorithm>

#define MAXN 705

using namespace std;

int N, K, grid[ MAXN + 1 ][ MAXN + 1 ], S[ MAXN + 1 ][ MAXN + 1 ];

inline int sum( int x1, int y1, int x2, int y2 ) {
  return S[ x2 ][ y2 ] - S[ x2 ][ y1 - 1 ] - S[ x1 - 1 ][ y2 ] + S[ x1 - 1 ][ y1 - 1 ];
}

int solve( int y1, int y2 ) {
  if( y1 == y2 ) {
    int ans = 0;
    for( int r1 = 1, r2 = r1; r1 <= r2 && r2 <= N; ) {
      int ss = sum( r1, y1, r2, y1 );
      if( ss < K ) r2++;
      else if( ss > K ) r1++;
      else {
        int rr1 = r1, rr2 = r2;
        while( sum( rr1, y1, r2, y1 ) == K && rr1 <= r2 ) rr1++;
        while( sum( r1, y1, rr2, y1 ) == K && rr2 <= N ) rr2++;
        ans += ( rr1 - r1 ) * ( rr2 - r2 );
        r1 = rr1;
        r2 = rr2;
      }
    }
    return ans;
  }
  int mid = ( y1 + y2 ) >> 1;
  int ans = solve( y1, mid  ) + solve( mid + 1, y2 );
  for( int k1 = 0; k1 <= K; k1++ ) {
    int k2 = K - k1;
    for( int r1 = 1; r1 <= N; r1++ ) {
      for( int r2 = r1, c1 = y1, c2 = y2; r2 <= N; r2++ ) {
        int num1 = 0, num2 = 0;
        while( sum( r1, c1, r2, mid ) > k1 && c1 <= mid ) c1++;
        int cc = c1;
        while( sum( r1, cc, r2, mid ) == k1 && cc <= mid ) cc++;
        if( sum( r1, c1, r2, mid ) == k1 ) num1 = cc - c1;
        while( sum( r1, mid + 1, r2, c2 ) > k2 && c2 > mid ) c2--;
        cc = c2;
        while( sum( r1, mid + 1, r2, cc ) == k2 && cc > mid ) cc--;
        if( sum( r1, mid + 1, r2, c2 ) == k2 ) num2 = c2 - cc;
        ans += num1 * num2;
      }
    }
  }
  return ans;
}

int main( void ) {
  scanf("%d%d", &N, &K );
  for( int i = 1; i <= N; i++ ) {
    scanf("\n");
    for( int j = 1; j <= N; j++ ) {
      char c = getchar_unlocked();
      grid[ i ][ j ] = c - '0';
      S[ i ][ j ] = S[ i - 1 ][ j ] + S[ i ][ j - 1 ] - S[ i - 1 ][ j - 1 ] + grid[ i ][ j ];
    }
  }
  printf("%d\n", solve( 1, N ) );
  return 0;
}
