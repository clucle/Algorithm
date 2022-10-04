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

const ll MYMOD = 1'000'000'007;
const int MAX_N = 30'002;

const bool TEST_CASES = false;

inline void presolve()
{

}

int N;
vector<pair<pii, pii>> lines;

inline void read()
{
	cin >> N;
	lines.resize( 2 * N );
	For( i, 1, N )
	{
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		lines[ 2 * i - 2 ] = { {a, 1}, {b + 1,d + 1} };
		lines[ 2 * i - 1 ] = { {c, -1}, {b + 1,d + 1} };
	}
}

int cnt[ 4 * MAX_N ] = { 0, };
int seg[ 4 * MAX_N ] = { 0, };

void update( int here, int l, int r, int start, int end, int val )
{
	if ( end < l || r < start )
	{
		return;
	}

	if ( start <= l && r <= end )
	{
		cnt[ here ] += val;
	}
	else
	{
		int mid = l + ( r - l ) / 2;
		update( here * 2 + 0, l, mid, start, end, val );
		update( here * 2 + 1, mid + 1, r, start, end, val );
	}

	if ( cnt[ here ] )
	{
		seg[ here ] = r - l + 1;
	}
	else
	{
		if ( l == r )
		{
			seg[ here ] = 0;
		}
		else
		{
			seg[ here ] = seg[ here * 2 ] + seg[ here * 2 + 1 ];
		}
	}

}

inline void solve()
{
	sort( lines.begin(), lines.end() );

	int prev = 0;
	int ret = 0;
	for ( auto e : lines )
	{
		ret += seg[ 1 ] * ( e.first.first - prev );
		prev = e.first.first;

		update( 1, 1, MAX_N, e.second.first, e.second.second - 1, e.first.second );
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
