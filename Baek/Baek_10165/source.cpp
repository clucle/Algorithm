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

bool isValid( int r, int c )
{
	if ( r < 0 || r > 3 || c < 0 || c > 3 ) return false;
	return true;
}

inline void presolve()
{
}

int N, M;

struct node
{
	int start, end, idx;
};

std::vector<node> v;
std::vector<node> rv;

bool live[ 500'001 ];
int g_end = 0;
int g_end_r = 0;

inline void read()
{
	cin >> N >> M;
	v.resize( M );
	rv.resize( M );
	For2( i, 0, M )
	{
		cin >> v[ i ].start >> v[ i ].end;

		rv[ i ].start = ( N - v[ i ].end ) % N;
		rv[ i ].end = ( N - v[ i ].start ) % N;

		if ( v[ i ].end < v[ i ].start )
		{
			g_end = v[ i ].end;
			v[ i ].end += N;
		}
		v[ i ].idx = i + 1;

		if ( rv[ i ].end < rv[ i ].start )
		{
			g_end_r = rv[ i ].end;
			rv[ i ].end += N;
		}
		rv[ i ].idx = i + 1;
	}
}

void func( vector<node>& v, const int g_end )
{
	sort( v.begin(), v.end(),
		[]( const node& lhs, const node& rhs ) {
			if ( lhs.start == rhs.start ) return lhs.end > rhs.end;
			return lhs.start < rhs.start;
		} );

	int start = -1;
	int end = g_end;

	For2( i, 0, M )
	{
		if ( v[ i ].start == start )
		{
			live[ v[ i ].idx ] = false;
			continue;
		}

		start = v[ i ].start;

		if ( v[ i ].end <= end )
		{
			live[ v[ i ].idx ] = false;
			continue;
		}

		end = v[ i ].end;
	}
}

inline void solve()
{
	For( i, 1, M ) live[ i ] = true;

	func( v, g_end );
	func( rv, g_end_r );

	For( i, 1, M )
	{
		if ( live[ i ] ) cout << i << ' ';
	}
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
