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
int N, M, parent[ MAXN + 1 ], Rank[ MAXN + 1 ];

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


vector< pii > T[ MAXN + 1 ];

int Q, depth[ MAXN + 1 ], P[ MAXN + 1 ][ 17 ], RMQ[ MAXN + 1 ][ 17 ];

void dfs( int u, int p ) {
  P[ u ][ 0 ] = p;
  for( int i = 0; i < T[ u ].size(); i++ ) {
    int v = T[ u ][ i ].X, w = T[ u ][ i ].Y;
    if( v == p ) continue;
    depth[ v ] = depth[ u ] + 1;
    RMQ[ v ][ 0 ] = w;
    dfs( v, u );
  }
}

void compute() {
  for( int j = 1; ( 1 << j ) <= N; j++ ) {
    for( int i = 1; i <= N; i++ ) {
      P[ i ][ j ] = P[ P[ i ][ j - 1 ] ][ j - 1 ];
      RMQ[ i ][ j ] = max( RMQ[ P[ i ][ j - 1 ] ][ j - 1 ], RMQ[ i ][ j - 1 ] );
    }
  }
}

int lca( int u, int v )
{
  int lg = 0;
  if( depth[ u ] < depth[ v ] ) {
    swap( u, v );
  }
  if( !depth[ u ] ) {
    return u;
  }
  for( lg = 0; 1 << lg <= depth[ u ]; lg++ );
  lg--;
  for( int i = lg; i >= 0; i-- ) {
    if( depth[ u ] - ( 1 << i ) >= depth[ v ] ) {
      u = P[ u ][ i ];
    }
  }
  if( u == v ) {
    return u;
  }
  for( int i = lg; i >= 0; i-- ) {
    if( P[ u ][ i ] != -1 && P[ u ][ i ] != P[ v ][ i ] ) {
      u = P[ u ][ i ];
      v = P[ v ][ i ];
    }
  }
  return P[ u ][ 0 ];
}

int query( int u, int v )
{
  int LCA = lca( u, v ),uv,uu, maxi = 0;
  for( uv = 0; 1 << uv <= depth[ v ]; uv++ );
  uv--;
  for( uu = 0; 1 << uu <= depth[ u ]; uu++ );
  uu--;
  if( !depth[ u ] && !depth[ v ] ) {
    return maxi;
  }
  for( int  i = uu; i >= 0; i-- ) {
    if( depth[ u ] - (1 << i) >= depth[ LCA ] ) {
      maxi = max( maxi, RMQ[ u ][ i ] );
      u = P[ u ][ i ];
    }
  }
  for( int i = uv; i >= 0; i-- ) {
    if( depth[ v ] - (1 << i) >= depth[ LCA ] ) {
      maxi = max( maxi, RMQ[ v ][ i ] );
      v = P[ v ][ i ];
    }
  }
  return maxi;
}

int main( void ) {
  int u, v, w;
  scanf("%d%d", &N, &M );
  for( int i = 1; i <= N; i++ ) parent[ i ] = i;

  for( int i = 1; i <= M; i++ ) {
    scanf("%d%d%d", &u, &v, &w );
    E.pb( mp( w, mp( u, v ) ) );
  }
  sort( E.begin(), E.end() );
  for( int i = 0; i < E.size(); i++ ) {
    u = E[ i ].Y.X, v = E[ i ].Y.Y, w = E[ i ].X;
    if( find( u ) != find( v ) ) {
      Union( u, v );
      T[ u ].pb( mp( v, w ) );
      T[ v ].pb( mp( u, w ) );
    }
  }

  dfs( 1, -1 );
  compute();

  scanf("%d", &Q );
  while( Q-- ) {
    scanf("%d%d", &u, &v );
    printf("%d\n", query( u, v ) );
  }
  return 0;
}
