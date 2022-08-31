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

// ax + by = g 일때 x, y 찾기
struct gxy
{
	ll g, x, y;
};

gxy xGcd( ll a, ll b )
{
	if ( b == 0 ) return { a,1,0 };
	gxy ret = xGcd( b, a % b );
	return { ret.g, ret.y, ret.x - ( a / b ) * ret.y };
}

/* ------------------- Custom clucle ------------------- */
/* ----------------------------------------------------- */

const ll MYMOD = (ll)1e9 + 7;
const int MAX_N = (int)2e5 + 10;

const bool TEST_CASES = false;

inline void presolve()
{

}

int n, k;
int Graph[ 501 ][ 501 ] = { 0, };

inline void read()
{
	cin >> n >> k;
	For2( i, 0, k )
	{
		int y, x; cin >> y >> x;
		Graph[ y ][ x ] = 1;
	}
}

int visited[ 501 ] = { 0, };
int selected[ 501 ] = { 0, };
int cnt = 1;

int dfs( int here )
{
	if ( visited[ here ] == cnt ) return 0;
	visited[ here ] = cnt;

	for ( int x = 1; x <= n; x++ )
	{
		if ( Graph[ here ][ x ] )
		{
			int there = x;
			if ( selected[ there ] == 0 || dfs( selected[ there ] ) )
			{
				selected[ there ] = here;
				return 1;
			}
		}
	}
	return 0;
}

inline void solve()
{
	int ret = 0;
	For( i, 1, n )
	{
		cnt++;
		if ( dfs( i ) ) ret++;
	}
	cout << ret << '\n';
}
int main()
{
	ios::sync_with_stdio( false );
	cin.tie( 0 );
	cout.tie( 0 );
	cout.precision( 2 );
	cout << fixed;

	presolve();

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
