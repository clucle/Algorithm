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

int r, c;

inline void read()
{
    cin >> r >> c;
}

string str = "abbab";
vector<pair<pii, pii>> dp[ 6 ][ 6 ];
char board[ 15 ][ 20 ];
int visited[ 15 ][ 15 ] = { 0, };

int rDiff[ 4 ] = { -1,1,0,0 };
int cDiff[ 4 ] = { 0,0,-1,1 };

void dfs( pii base, pii pos, pii mymin, pii mymax, int cnt )
{


    if ( cnt == 5 )
    {
        int _r = ( base.first - 1 ) % 5 + 1;
        int _c = ( base.second - 1 ) % 5 + 1;

        int _pr = pos.first + 5;
        int _pc = pos.second + 5;

        dp[ _r ][ _c ].push_back( { mymin, mymax } );

        return;
    }

    int _r = base.first + pos.first;
    int _c = base.second + pos.second;

    int nxtCnt = cnt + 1;

    For( d, 0, 3 )
    {
        int nxtR = pos.first + rDiff[ d ];
        int nxtC = pos.second + cDiff[ d ];

        if ( visited[ base.first + nxtR ][ base.second + nxtC ] ) continue;
        if ( board[ base.first + nxtR ][ base.second + nxtC ] != str[ nxtCnt - 1 ] ) continue;

        pii nxtMin = { min( mymin.first, nxtR ), min( mymin.second, nxtC ) };
        pii nxtMax = { max( mymax.first, nxtR ), max( mymax.second, nxtC ) };

        visited[ base.first + nxtR ][ base.second + nxtC ] = 1;

        dfs( base, { nxtR, nxtC }, nxtMin, nxtMax, nxtCnt );

        visited[ base.first + nxtR ][ base.second + nxtC ] = 0;
    }
}

inline void pre()
{
    int chk = c % 5;
    int cnt = 0;

    For( r, 1, 15 ) For( c, 1, 15 + chk )
    {
        board[ r ][ c ] = str[ cnt ];

        cnt++;
        cnt %= 5;
    }

    For( r, 6, 10 )
    {
        For( c, 6, 10 )
        {
            if ( board[ r ][ c ] == 'b' ) continue;
            // b ´Â ½ºÅµ
            visited[ r ][ c ] = 1;
            dfs( { r,c }, { 0,0 }, { 0,0 }, { 0,0 }, 1 );
            visited[ r ][ c ] = 0;
        }
    }
}

ll sum[ 500000 ];

ll ok( int idx )
{
    if ( sum[ idx ] != -1 ) return sum[ idx ];

    int saved = idx;

    ll ret = 0;

    int rightLimit = idx % 10; idx /= 10;
    int leftLimit = idx % 10; idx /= 10;
    int cDiff = idx % 10; idx /= 10;
    int bottomLimit = idx % 10; idx /= 10;
    int topLimit = idx % 10; idx /= 10;
    int rDiff = idx % 10; idx /= 10;

    int a = 1 + rDiff;
    for ( int i = 1; i <= a; i++ )
    {
        // 1) topLimit = topLimit
        // 2) topLimit = topLimit + 1

        // i = i + rDiff) bottomLimit = botomLimit;
        // i = i + rDiff - 1) bottomLimit = bottomLimit + 1;

        int tmpTopLimit = topLimit + ( i - 1 );
        int tmpBottomLimit = bottomLimit + ( rDiff - i + 1 );

        int b = 1 + cDiff;
        for ( int j = 1; j <= b; j++ )
        {
            int tmpLeftLimit = leftLimit + ( j - 1 );
            int tmpRightLimit = rightLimit + ( cDiff - j + 1 );

            int py = ( i - 1 ) % 5 + 1;
            int px = ( j - 1 ) % 5 + 1;

            for ( auto& e : dp[ py ][ px ] )
            {
                auto& mymin = e.first;
                auto& mymax = e.second;

                int rMin = mymin.first;
                int cMin = mymin.second;
                int rMax = mymax.first;
                int cMax = mymax.second;

                if ( tmpTopLimit < -rMin || tmpLeftLimit < -cMin || tmpBottomLimit < rMax || tmpRightLimit < cMax ) continue;

                ret += 1;
            }
        }
    }

    sum[ saved ] = ret;

    return ret;
}


inline void solve()
{
    pre();

    for ( int i = 0; i < 500000; ++i ) sum[ i ] = -1;

    ll ret = 0;
    for ( int i = 1; i <= r; i += 5 )
    {
        int top = i;
        int bottom = min( i + 4, r );

        int rDiff = bottom - top;
        int topLimit = min( 4, top - 1 );
        int bottomLimit = min( 4, r - bottom );

        for ( int j = 1; j <= c; j += 5 )
        {
            int left = j;
            int right = min( j + 4, c );

            int cDiff = right - left;
            int leftLimit = min( 4, left - 1 );
            int rightLimit = min( 4, c - right );

            int idx =
                rDiff * 100000 +
                topLimit * 10000 +
                bottomLimit * 1000 +
                cDiff * 100 +
                leftLimit * 10 +
                rightLimit * 1;

            ret += ok( idx );
        }
    }
    cout << ret;
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