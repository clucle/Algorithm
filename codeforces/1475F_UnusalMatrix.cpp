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

using namespace std;

#define ft first
#define sc second
#define re return
#define pb push_back
#define For(i,j,k) for (int i=(int)(j);i<=(k);i++)
#define Rep(i,j,k) for (int i=(int)(j);i>=(k);i--)
#define For2(i,j,k) for (int i=(int)(j);i<(k);i++)
#define Rep2(i,j,k) for (int i=(int)(j);i>(k);i--)

#define mp make_pair
#define sz(a) int((a).size())
#define all(c) (c).begin(),(c).end()
#define forit(it,S) for(__typeof(S.begin()) it = S.begin(); it != S.end(); ++it)

#define vi vector<int> 

#define DEBUG false

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const long long MOD = 1e9 + 7;

template <class T>
struct BIT
{
	int n;
	vector<T> tree;
	BIT( int n ) :n( n + 1 ), tree( n + 1 ) {}
	void add( int x, T a )
	{
		for ( ; x < n; x += x & -x ) tree[ x ] += a;
	}
	T sum( int x )
	{
		T ret = 0;
		for ( ; x; x ^= x & -x ) ret += tree[ x ];
		return ret;
	}
	T rangeSum( int l, int r )
	{
		return( sum( r ) - sum( l - 1 ) );
	}
};

#define SEGMENT_TREE false
#if (SEGMENT_TREE)

namespace segtree
{
	namespace lazy
	{
		//免贸: https://bowbowbow.tistory.com/4 [港港港]
		const int MAX_N = 1000010;
		ll arr[ MAX_N ];
		typedef struct Tree
		{
			ll value, lazy;
		} Tree;

		Tree tree[ 3 * MAX_N ];

		ll init( int node, int start, int end )
		{
			if ( start == end )
				return tree[ node ].value = arr[ start ];
			else
				return tree[ node ].value =
				init( node * 2, start, ( start + end ) / 2 ) +
				init( node * 2 + 1, ( start + end ) / 2 + 1, end );
		}

		void update( int node, int start, int end, int i, int j, ll diff )
		{
			if ( tree[ node ].lazy != 0 )
			{
				tree[ node ].value += ( (ll)(end)-(ll)(start)+1 ) * tree[ node ].lazy;
				if ( start != end )
				{
					tree[ node * 2 ].lazy += tree[ node ].lazy;
					tree[ node * 2 + 1 ].lazy += tree[ node ].lazy;
				}
				tree[ node ].lazy = 0;
			}

			if ( j < start || i > end ) return;

			if ( i <= start && end <= j )
			{
				tree[ node ].value += ( (ll)(end)-(ll)(start)+1 ) * diff;
				if ( start != end )
				{
					tree[ node * 2 ].lazy += diff;
					tree[ node * 2 + 1 ].lazy += diff;
				}
				return;
			}

			update( node * 2, start, ( start + end ) / 2, i, j, diff );
			update( node * 2 + 1, ( start + end ) / 2 + 1, end, i, j, diff );

			tree[ node ].value = tree[ node * 2 ].value + tree[ node * 2 + 1 ].value;
		}

		ll getsum( int node, int start, int end, int i, int j )
		{
			if ( tree[ node ].lazy != 0 )
			{
				tree[ node ].value += ( (ll)(end)-(ll)(start)+1 ) * tree[ node ].lazy;
				if ( start != end )
				{
					tree[ node * 2 ].lazy += tree[ node ].lazy;
					tree[ node * 2 + 1 ].lazy += tree[ node ].lazy;
				}
				tree[ node ].lazy = 0;
			}
			if ( i > end || j < start ) return 0;
			if ( i <= start && end <= j ) return tree[ node ].value;
			return tree[ node ].value =
				getsum( node * 2, start, ( start + end ) / 2, i, j ) +
				getsum( node * 2 + 1, ( start + end ) / 2 + 1, end, i, j );
		}

		ll getmax( int node, int start, int end, int i, int j )
		{
			if ( tree[ node ].lazy != 0 )
			{
				tree[ node ].value += ( (ll)(end)-(ll)(start)+1 ) * tree[ node ].lazy;
				if ( start != end )
				{
					tree[ node * 2 ].lazy += tree[ node ].lazy;
					tree[ node * 2 + 1 ].lazy += tree[ node ].lazy;
				}
				tree[ node ].lazy = 0;
			}
			if ( i > end || j < start ) return 0;
			if ( i <= start && end <= j ) return tree[ node ].value;
			return tree[ node ].value = max(
				getmax( node * 2, start, ( start + end ) / 2, i, j ),
				getmax( node * 2 + 1, ( start + end ) / 2 + 1, end, i, j ) );
		}
	}
	namespace standard
	{
		// https://stonejjun.tistory.com/66

		const int MAX_N = 1000010;
		ll arr[ MAX_N ];
		ll tree[ 3 * MAX_N ];

		void update( int node, int start, int en, int index, long long int diff )
		{
			if ( index<start || index>en ) return;
			tree[ node ] = tree[ node ] + diff;
			if ( start != en )
			{
				update( node * 2, start, ( start + en ) / 2, index, diff );
				update( node * 2 + 1, ( start + en ) / 2 + 1, en, index, diff );
			}
		}

		long long getsum( int node, int start, int en, int left, int right )
		{
			if ( left > en || right < start ) return 0;
			if ( left <= start && en <= right ) return tree[ node ];
			return getsum( node * 2, start, ( start + en ) / 2, left, right ) +
				getsum( node * 2 + 1, ( start + en ) / 2 + 1, en, left, right );
		}
	}

}

#endif

/* ----------------------------------------------------- */

long long fact[ 4000000 ] = { 0, };
long long getPow( long long base, int exponent )
{
	if ( exponent == 0 ) return 1;
	if ( exponent == 1 ) return base;
	long long pow = getPow( base, exponent / 2 );
	if ( exponent % 2 == 1 )
	{
		return ( ( ( base * pow ) % MOD ) * pow ) % MOD;
	}
	return ( pow * pow ) % MOD;
}

inline void pre()
{
	/*
	fact[ 0 ] = 1;
	fact[ 1 ] = 1;
	for ( int i = 2; i <= 1020; i++ )
	{
		fact[ i ] = ( fact[ i - 1 ] * i ) % MOD;
	}
	*/
}

const ll MYMOD = 1e9 + 7;
const int MAX_N = 1e3 + 7;

const bool TEST_CASES = true;

int n;
int a[ MAX_N ][ MAX_N ];
int b[ MAX_N ][ MAX_N ];


inline void read()
{
	cin >> n;
	For( i, 1, n ) For( j, 1, n )
	{
		char c; cin >> c;
		a[ i ][ j ] = c - '0';
	}

	For( i, 1, n ) For( j, 1, n )
	{
		char c; cin >> c;
		b[ i ][ j ] = c - '0';
	}
}

inline void solve()
{
	For( i, 1, n )
		if ( a[ i ][ 1 ] != b[ i ][ 1 ] )
			For( j, 1, n ) a[ i ][ j ] = 1 - a[ i ][ j ];

	For( j, 1, n )
		if ( a[ 1 ][ j ] != b[ 1 ][ j ] )
			For( i, 1, n ) a[ i ][ j ] = 1 - a[ i ][ j ];

	For( i, 1, n ) For( j, 1, n )
		if ( a[ i ][ j ] != b[ i ][ j ] )
		{
			cout << "NO\n";
			return;
		}

	cout << "YES\n";
}

int main()
{
	ios::sync_with_stdio( false );
	cin.tie( 0 ); cout.tie( 0 );
	cout.precision( 2 ); cout << fixed;

	pre();

	int t = 1;
	if ( TEST_CASES ) cin >> t;
	while ( t-- )
	{
		read();
		solve();
	}

	return 0;
}