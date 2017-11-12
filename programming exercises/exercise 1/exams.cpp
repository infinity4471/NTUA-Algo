#include <cstdio>
#include <algorithm>

#define MAXN 100100
#define INF 12345678901234567LL

using namespace std;

typedef long long ll;

int N;
ll K, A[ MAXN + 1 ];

ll check( ll time ) {
  ll total = 0LL;
  for( int i = 1; i <= N; i++ ) {
    total += time / A[ i ];
    if( time % A[ i ] ) total++;
  }
  return total;
}

int main( void ) {
  scanf("%d%lld", &N, &K );
  for( int i = 1; i <= N; i++ ) {
    scanf("%lld", &A[ i ] );
  }
  ll lo = 0, hi = INF, ans = 0;
  while( lo <= hi ) {
    ll mid = ( lo + hi ) >> 1;
    if( check( mid ) < K ) {
      lo = mid + 1;
      ans = mid;
    } else {
      hi = mid - 1;
    }
  }
  int idx = 0;
  ll total = K  - check( ans );
  for( int i = 1; i <= N; i++ ) {
    if( ans % A[ i ] == 0 ) {
      total--;
      if( !total ) {
        idx = i;
        break;
      }
    }
  }
  printf("%d %lld\n", idx, A[ idx ] + ans );
  return 0;
}
