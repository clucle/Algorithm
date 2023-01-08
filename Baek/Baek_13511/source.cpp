#define _CRT_SECURE_NO_DEPRECATE

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
#include <functional>

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

inline int log2i( int x )
{
	int log2Val = 0;
	while ( x >>= 1 ) log2Val++;
	return log2Val;
}

int powi( int x, int cnt )
{
	if ( cnt == 0 ) return 1;
	if ( cnt == 1 ) return x;

	int ret = 1;
	if ( cnt % 2 == 1 ) ret *= x;
	int child = powi( x, cnt / 2 );
	ret *= child;
	ret *= child;
	return ret;
}

/* ------------------- Custom clucle ------------------- */
/* ----------------------------------------------------- */

const ll MYMOD = 1'000'000'007;
const int MAX_N = 100'001;

const bool TEST_CASES = false;
const bool READ_FILE = false;

int N;
vector<pll> Graph[ MAX_N ];

inline void presolve()
{
}

inline void read()
{
	cin >> N;
	ll u, v, w;
	For2( i, 1, N )
	{
		cin >> u >> v >> w;
		Graph[ u ].push_back( { v,w } );
		Graph[ v ].push_back( { u,w } );
	}
}

ll dist[ MAX_N ];
int depth[ MAX_N ];
int parent[ MAX_N ][ 21 ];
int visited[ MAX_N ] = { 0, };

void build( int here, ll w, int d )
{
	dist[ here ] = w;
	depth[ here ] = d;
	for ( auto& [there, weight] : Graph[ here ] )
	{
		if ( visited[ there ] ) continue;
		visited[ there ] = 1;

		parent[ there ][ 0 ] = here;

		build( there, w + weight, d + 1 );
	}
}

void build2()
{
	For( i, 1, 20 )
		For( j, 1, N )
	{
		parent[ j ][ i ] = parent[ parent[ j ][ i - 1 ] ][ i - 1 ];
	}
}

int lca( int a, int b )
{
	if ( depth[ a ] < depth[ b ] ) swap( a, b );
	// a 가 더 깊음
	int diff = depth[ a ] - depth[ b ];

	for ( int i = 0; diff; i++ )
	{
		if ( diff & ( 1 << i ) )
		{
			diff -= ( 1 << i );
			a = parent[ a ][ i ];
		}
	}

	if ( a == b ) return a;

	for ( int i = 20; i >= 0; i-- )
	{
		if ( parent[ a ][ i ] != parent[ b ][ i ] )
		{
			a = parent[ a ][ i ];
			b = parent[ b ][ i ];
		}
	}

	return parent[ a ][ 0 ];
}

inline void solve()
{
	parent[ 1 ][ 0 ] = 1;
	dist[ 1 ] = 0;
	visited[ 1 ] = 1;
	build( 1, 0, 1 );
	build2();

	int t; cin >> t;
	while ( t-- )
	{
		int op = 0;
		int u, v, k;
		cin >> op;
		if ( op == 1 )
		{
			cin >> u >> v;
			int p = lca( u, v );
			cout << dist[ u ] + dist[ v ] - dist[ p ] * 2 << '\n';
		}
		else
		{
			cin >> u >> v >> k;
			k--;
			int p = lca( u, v );
			int udiff = depth[ u ] - depth[ p ];
			int l = 0;
			int start = 0;
			if ( udiff > k )
			{
				l = k;
				start = u;
			}
			else if ( udiff == k )
			{
				cout << p << '\n';
				continue;
			}
			else
			{
				int vdiff = depth[ v ] - depth[ p ];
				l = udiff + vdiff - k;
				start = v;
			}

			// start 에서 l 만큼 올라가자
			for ( int i = 0; l; i++ )
			{
				if ( l & ( 1 << i ) )
				{
					l -= ( 1 << i );
					start = parent[ start ][ i ];
				}
			}
			cout << start << '\n';
		}
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
