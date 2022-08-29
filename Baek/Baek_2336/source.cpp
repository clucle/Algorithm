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

const bool TEST_CASES = false;

inline void presolve()
{

}

struct q
{
	int a, b, c;
};

int N;
q arr[ 500100 ];

int tree[ 2'000'010 ];

inline void read()
{
	cin >> N;
	For( i, 1, N )
	{
		int a; cin >> a;
		arr[ a ].a = i;
	}
	For( i, 1, N )
	{
		int a; cin >> a;
		arr[ a ].b = i;
	}
	For( i, 1, N )
	{
		int a; cin >> a;
		arr[ a ].c = i;
	}
}



void build()
{
	For( i, 1, 4 * N + 1 ) tree[ i ] = 500100;
}

/*
10
2 5 3 8 10 7 1 6 9 4
1 2 3 4 5 6 7 8 9 10
3 8 7 10 5 4 1 2 6 9

1 2 8
2 5 5
3 3 1
4 8 2
5 10 4
6 7 3
7 1 7
8 6 9
9 9 10
10 4 6

*/

int get( int idx, int start, int end, int l, int r )
{
	// if ( start > end ) return 500100;
	if ( r < start || l > end ) return 500100;
	if ( l <= start && end <= r ) return tree[ idx ];

	int mid = start + ( end - start ) / 2;
	return std::min(
		get( idx * 2 + 0, start, mid, l, std::min( mid, r ) ),
		get( idx * 2 + 1, mid + 1, end, std::max( mid + 1, l ), r )
	);
}

void upd( int idx, int x, int val, int start, int end )
{
	if ( tree[ idx ] > val ) tree[ idx ] = val;
	if ( start == end ) return;

	int mid = start + ( end - start ) / 2;
	if ( x <= mid ) upd( idx * 2 + 0, x, val, start, mid );
	else upd( idx * 2 + 1, x, val, mid + 1, end );
}

inline void solve()
{


	sort( arr + 1, arr + N + 1, []( const q& lhs, const q& rhs ) {
		if ( lhs.a != rhs.a ) return lhs.a < rhs.a;
		if ( lhs.b != rhs.b ) return lhs.b < rhs.b;
		return lhs.c < rhs.c;

		} );

	build();

	int ret = 0;
	For( i, 1, N )
	{
		if ( get( 1, 1, N, 1, arr[ i ].b ) > arr[ i ].c ) ret++;
		upd( 1, arr[ i ].b, arr[ i ].c, 1, N );
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
