#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cmath>
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
#include <unordered_map>
#include <cassert>
#include <fstream>
#include <functional>

using namespace std;

#define For( i, j, k ) for ( int i = (int)( j ); i <= ( k ); i++ )

using ll = long long;
using pii = pair<int, int>;

const bool TEST_CASES = false;
const bool READ_FILE = false;

int N, M;

int c[ 820 ][ 820 ] = { 0, };
int f[ 820 ][ 820 ] = { 0, };
int d[ 820 ][ 820 ] = { 0, };

inline void read()
{
    cin >> N >> M;

    // 1~400 worker
    // 401~800 todo
    // 801 src
    // 802 dst

    For( i, 1, N )
    {
        int cnt = 0; cin >> cnt;

        int todo = 0, pay = 0;
        For( j, 1, cnt )
        {
            cin >> todo >> pay;
            c[ i ][ todo + 400 ] = 1;
            d[ i ][ todo + 400 ] = pay;
            d[ todo + 400 ][ i ] = -pay; // 비용도 반대로 처리해줘야하는구나
        }
    }
}

inline void solve()
{
    int src = 801;
    int dst = 802;
    For( i, 1, 400 )
    {
        c[ src ][ i ] = 1;
        c[ i + 400 ][ dst ] = 1;
    }

    int parent[ 820 ];
    int dist[ 820 ];
    int chk[ 820 ];

    int ret = 0;
    int cost = 0;

    while ( true )
    {
        memset( parent, 0, sizeof( parent ) );
        memset( chk, 0, sizeof( chk ) );
        fill( begin( dist ), end( dist ), 1'000'000'000 );

        queue<int> q;
        q.push( src );
        dist[ src ] = 0;
        parent[ src ] = src;

        while ( !q.empty() )
        {
            int here = q.front();
            q.pop();

            chk[ here ] = false;

            For( there, 1, 802 )
            {
                if (
                    c[ here ][ there ] - f[ here ][ there ] > 0 &&
                    dist[ there ] > dist[ here ] + d[ here ][ there ] )
                {
                    parent[ there ] = here;
                    dist[ there ] = dist[ here ] + d[ here ][ there ];

                    if ( !chk[ there ] )
                    {
                        chk[ there ] = true;
                        q.push( there );
                    }
                }
            }
        }

        if ( !parent[ dst ] ) break;

        for ( int there = dst; parent[ there ] != there; there = parent[ there ] )
        {
            int here = parent[ there ];
            f[ here ][ there ]++;
            f[ there ][ here ]--;

            cost += d[ here ][ there ];
        }

        ret++;
    }

    cout << ret << '\n';
    cout << cost << '\n';
}

int main()
{
    ios::sync_with_stdio( false );
    cin.tie( 0 );
    cout.tie( 0 );
    cout.precision( 8 );
    cout << fixed;

    int t = 1;
    if ( READ_FILE )
        freopen( "D:\\test.txt", "r", stdin );
    if ( TEST_CASES )
        cin >> t;
    while ( t-- )
    {
        read();
        solve();
    }

    return 0;
}