#include <cstdio>
#include <algorithm>
#include <vector>

#define MAXN 50000

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair< int, int > pii;
typedef pair< int, pii > edge;

vector< edge > E;
int N, K, M, parent[ MAXN + 1 ], Rank[ MAXN + 1 ], ans, ans2;

int find( int u ) {
  if( parent[ u ] == u ) return u;
  return parent[ u ] = find( parent[ u ] );
}

void Union( int u, int v ) {
  u = find( u );
  v = find( v );
  if( Rank[ u ] > Rank[ v ] ) {
    parent[ v ] = u;
  } else {
    parent[ u ] = v;
    if( Rank[ u ] == Rank[ v ] ) Rank[ v ]++;
  }
}

int main( void ) {
  int u, v, w;
  scanf("%d%d%d", &N, &K, &M );
  for( int i = 1; i <= N; i++ ) parent[ i ] = i;

  for( int i = 1; i <= K; i++ ) {
    scanf("%d%d", &u, &w );
    E.pb( mp( w, mp( 0, u ) ) );
  }
  for( int i = 1; i <= M; i++ ) {
    scanf("%d%d%d", &u, &v, &w );
    E.pb( mp( w, mp( u, v ) ) );
  }
  sort( E.begin(), E.end() );
  for( int i = 0; i < E.size(); i++ ) {
    u = E[ i ].Y.X, v = E[ i ].Y.Y, w = E[ i ].X;
    if( find( u ) != find( v ) ) {
      Union( u, v );
      ans += w;
    }
  }

  for( int i = 1; i <= N; i++ ) {
    parent[ i ] = i;
    Rank[ i ] = 0;
  }
  for( int i = 0; i < E.size(); i++ ) {
    u = E[ i ].Y.X, v = E[ i ].Y.Y, w = E[ i ].X;
    if( u != 0 && find( u ) != find( v ) ) {
      Union( u, v );
      ans2 += w;
    }
  }

  ans = min( ans, ans2 );
  printf("%d\n", ans );
  return 0;
}
