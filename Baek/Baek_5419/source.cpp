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

const ll MYMOD = 1e9 + 7;
const int MAX_N = 2e5 + 10;

const bool TEST_CASES = true;

int arr[ 75001 ];
int N;
vector<pii> v;

struct Segtree
{
	vector<ll> tree; int N;

	Segtree( int N ) : tree( 2 * N ), N( N ) {}

	void clear()
	{
		fill( tree.begin(), tree.end(), 0 );
	}

	void upd( int i )
	{
		i += N;
		while ( i > 0 )
		{
			tree[ i ]++;
			i /= 2;
		}
	}

	ll get( int l, int r )
	{
		ll ret = 0;
		l += N; r += N;
		while ( l <= r )
		{
			if ( l & 1 ) ret += tree[ l ];
			if ( !( r & 1 ) ) ret += tree[ r ];

			l = ( l + 1 ) / 2;
			r = ( r - 1 ) / 2;
		}
		return ret;
	}
};

Segtree g_seg = Segtree( 75000 );

inline void presolve()
{

}

inline void read()
{
	cin >> N;
	v.resize( N );
	For2( i, 0, N )
	{
		cin >> v[ i ].first >> v[ i ].second;
	}
}


inline void solve()
{
	g_seg.clear();

	sort(
		v.begin(), v.end(),
		[]( const pii& a, const pii& b ) {
			if ( a.first == b.first ) return a.second > b.second;
			return a.first < b.first;
		} );

	vector<pii> tmp;
	tmp.resize( N );
	For2( i, 0, N )
	{
		tmp[ i ] = { v[ i ].second, i };
	}
	sort( tmp.begin(), tmp.end() );

	int start = 0;
	v[ tmp[ 0 ].second ].second = start;
	For2( i, 1, N )
	{
		if ( tmp[ i ].first != tmp[ i - 1 ].first ) ++start;
		v[ tmp[ i ].second ].second = start;
	}

	ll ret = 0;
	For2( i, 0, N )
	{
		ret += g_seg.get( v[ i ].second, N );
		g_seg.upd( v[ i ].second );
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
