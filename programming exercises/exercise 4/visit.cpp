#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

#define MAXN 60100
#define INF 123456789012345LL

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair< ll, int > pii;

int N, M, A, B, T, in_path[ MAXN + 1 ], pos_path[ MAXN + 1 ];

ll dist[ MAXN + 1 ];
set< pii > S;
vector< pii > G[ MAXN + 1 ];

vector< int > path;
vector< ll > times;

void calculate_path() {
    times.pb( 0LL );
    for( int i = 1; i < ( int )path.size(); i++ ) {
        int u = path[ i - 1 ], v = path[ i ], w = 0;
        for( int j = 0; j < G[ u ].size(); j++ ) {
            if( v == G[ u ][ j ].Y ) {
                w = G[ u ][ j ].X;
                break;
            }
        }
        times.pb( ( ll )times[ i - 1 ] + ( ll )w );
    }
}

ll valid_time( int u, int v, ll d, int w ) {
    if( !in_path[ u ] || !in_path[ v ] ) return ( ll )( d + w );
    int pos1 = pos_path[ u ], pos2 = pos_path[ v ];
    if( pos1 > pos2 ) {
        swap( pos1, pos2 );
        swap( u, v );
    }
    if( pos1 != pos2 - 1 ) return ( ll )( d + w );
    int time1 = times[ pos1 ], time2 = times[ pos2 ];
    if( d + w < time1 ) return ( ll )( d + w );
    if( d >= time2 ) return ( ll )( d + w );
    return ( ll )( w + time2 );
}

void dijkstra( int s ) {
    for( int i = 0; i <= N + 5; i++ ) dist[ i ] = INF;
    dist[ s ] = T;
    S.insert( mp( T, s ) );
    while( !S.empty() ) {
        pii A = *S.begin();
        S.erase( S.begin() );
        int u = A.Y;
        ll d = A.X;
        for( int i = 0; i < G[ u ].size(); i++ ) {
            int v = G[ u ][ i ].Y, w = G[ u ][ i ].X;
            ll get_dist = valid_time( u, v, d, w );
            if( dist[ v ] > get_dist ) {
                dist[ v ] = get_dist;
                S.insert( mp( dist[ v ], v ) );
            }
        }
    }
}

int main( void ) {
    int K, u, v, w;
    scanf("%d%d%d%d%d%d", &N, &M, &A, &B, &T, &K );
    for( int i = 0; i < K; i++ ) {
        scanf("%d", &u );
        path.pb( u );
        in_path[ u ] = true;
        pos_path[ u ] = i;
    }
    for( int i = 0; i < M; i++ ) {
        scanf("%d%d%d", &u, &v, &w );
        G[ u ].pb( mp( w, v ) );
        G[ v ].pb( mp( w, u ) );
    }
    calculate_path();
    dijkstra( A );
    printf("%lld\n", dist[ B ] - T );
    return 0;
}
