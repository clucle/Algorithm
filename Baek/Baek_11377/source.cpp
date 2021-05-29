#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <cstring>
#include <queue>
#include <stack>
#include <algorithm>
#include <sstream>
#include <numeric>
using namespace std;

#define ft first
#define sc second
#define re return
#define pb push_back
#define For(i,j,k) for (int i=(int)(j);i<=(k);i++)
#define For2(i,j,k) for (int i=(int)(j);i<(k);i++)
#define Rep(i,j,k) for (int i=(int)(j);i>=(k);i--)

#define mp make_pair
#define sz(a) int((a).size())
#define all(c) (c).begin(),(c).end()
#define forit(it,S) for(__typeof(S.begin()) it = S.begin(); it != S.end(); ++it)

#define DEBUG false

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

/* ----------------------------------------------------- */

const int MAX_N = 2010;
int N, M, K;

int c[ MAX_N ][ MAX_N ] = { 0, };
int f[ MAX_N ][ MAX_N ] = { 0, };
int ret;

const int src = 2001;
const int src_k = 2002;
const int sink = 2003;

vector<int> G[ MAX_N ];

inline void read()
{
    cin >> N >> M >> K;
    For( i, 1, N )
    {
        c[ src ][ i ] = 1;
        c[ src_k ][ i ] = 1;

        G[ src ].pb( i );
        G[ src_k ].pb( i );

        G[ i ].pb( src );
        G[ i ].pb( src_k );

        int here = i;
        int there;
        int cnt; cin >> cnt;
        For( j, 1, cnt )
        {
            cin >> there;
            there += 1000;

            c[ here ][ there ] = 1;
            c[ there ][ sink ] = 1;

            G[ here ].pb( there );
            G[ there ].pb( sink );

            G[ there ].pb( here );
            G[ sink ].pb( there );
        }
    }
}

void getMaxFlow( int start, int end, int k )
{
    int parent[ MAX_N ];
    int cur = 0;
    while ( 1 )
    {
        if ( k > 0 && cur == k )
            break;

        memset( parent, 0, sizeof( parent ) );

        queue<int> q;
        q.push( start );

        while ( !q.empty() )
        {
            int here = q.front();
            q.pop();

            for ( const auto& there : G[ here ] )
            {
                if ( c[ here ][ there ] - f[ here ][ there ] > 0 && parent[ there ] == 0 )
                {
                    q.push( there );
                    parent[ there ] = here;
                    if ( there == end )
                    {
                        while ( !q.empty() )
                        {
                            q.pop();
                        }
                        break;
                    }
                }
            }
        }

        if ( parent[ sink ] == 0 )
            break;

        if ( DEBUG ) cout << "----\n";
        for ( int i = end; i != start; i = parent[ i ] )
        {
            if ( DEBUG ) cout << i << ' ' << parent[ i ] << '\n';
            f[ parent[ i ] ][ i ]++;
            f[ i ][ parent[ i ] ]--;
        }
        ret++;
        cur++;
    }
}

inline void solve()
{
    ret = 0;
    getMaxFlow( src, sink, 0 );
    getMaxFlow( src_k, sink, K );
    cout << ret << '\n';
}

int main()
{
    ios::sync_with_stdio( false );
    cin.tie( 0 ); cout.tie( 0 );
    cout.precision( 10 ); cout << fixed;

    read();
    solve();

    return 0;
}
