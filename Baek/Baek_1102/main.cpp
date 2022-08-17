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
#include <unordered_map>
#include <cassert>
#include <fstream>

using namespace std;

#define ft first
#define sc second
#define re return
#define pb push_back
#define For( i, j, k ) for ( int i = (int)( j ); i <= ( k ); i++ )
#define Rep( i, j, k ) for ( int i = (int)( j ); i >= ( k ); i-- )
#define For2( i, j, k ) for ( int i = (int)( j ); i < ( k ); i++ )
#define Rep2( i, j, k ) for ( int i = (int)( j ); i > ( k ); i-- )

#define mp make_pair
#define sz( a ) int( ( a ).size() )
#define all( c ) ( c ).begin(), ( c ).end()
#define forit( it, S ) for ( __typeof( S.begin() ) it = S.begin(); it != S.end(); ++it )

#define vi vector< int >

#define DEBUG true

typedef long long ll;
typedef unsigned long long ull;
typedef pair< int, int > pii;
typedef pair< ll, ll > pll;

/* ------------------- Custom clucle ------------------- */
/* ----------------------------------------------------- */

const ll MYMOD = 1e9 + 7;
const int MAX_N = 2e5 + 10;
const int INF = 800;

const bool TEST_CASES = false;

int N;
int cost[ 17 ][ 17 ] = {
	0,
};
string s;
int P;

inline void read()
{
	cin >> N;
	For( i, 1, N ) For( j, 1, N ) cin >> cost[ i ][ j ];
	cin >> s;
	cin >> P;
}

int dp[ ( 1 << 16 ) + 1 ]; // 도착시
int dp2[ ( 1 << 16 ) + 1 ]; // 끝가지 갈때
int g_min = INF;

/*
16
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
YNNNNNNNNNNNNNNN
16
*/

// (16 ^ 16 dp 로 처리) * ( 16 * 16 ) = 2^24
int dfs( int bit, int cnt, int curcost )
{
	if ( dp[ bit ] <= curcost )
		return dp2[ bit ];
	dp[ bit ] = curcost;

	if ( curcost > g_min )
		return INF;

	if ( cnt >= P )
	{
		dp[ bit ] = min( dp[ bit ], curcost );
		dp2[ bit ] = min( dp2[ bit ], curcost );
		g_min = min( g_min, dp2[ bit ] );
		return dp2[ bit ];
	}

	std::set< int > visited;
	int chk = 1;
	For( i, 1, N )
	{
		if ( bit & chk )
		{
			visited.insert( i );
		}
		chk = chk << 1;
	}

	int ret = INF;
	For( i, 1, N )
	{
		if ( visited.find( i ) != visited.end() )
			continue;

		int mymin = INF;
		for ( auto here : visited )
		{
			mymin = min( mymin, cost[ here ][ i ] );
		}

		int nxt = ( bit | ( 1 << ( i - 1 ) ) );
		ret = min( ret, dfs( nxt, cnt + 1, curcost + mymin ) );
	}
	dp2[ bit ] = ret;

	return dp2[ bit ];
}

inline void solve()
{
	int bit = 0;
	int cnt = 0;

	For( i, 0, 1 << 16 )
	{
		dp[ i ] = INF;
		dp2[ i ] = INF;
	}

	reverse( s.begin(), s.end() );
	For2( i, 0, N )
	{
		bit = bit << 1;
		if ( s[ i ] == 'Y' )
		{
			bit |= 1;
			cnt++;
		}
	}

	if ( cnt == 0 )
	{
		if ( P == 0 )
			cout << 0 << '\n';
		else
			cout << -1 << '\n';
		return;
	}

	cout << dfs( bit, cnt, 0 ) << '\n';
}

int main()
{
	ios::sync_with_stdio( false );
	cin.tie( 0 );
	cout.tie( 0 );
	cout.precision( 2 );
	cout << fixed;

	int t = 1;
	if ( TEST_CASES )
		cin >> t;
	while ( t-- )
	{
		read();
		solve();
	}

	return 0;
}