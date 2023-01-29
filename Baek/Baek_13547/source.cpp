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
int arr[ 100'001 ];
int ret[ 100'001 ] = { 0, };

inline void presolve()
{
}

struct Query
{
	int idx;
	int i, j;
};

vector<Query> querys;

inline void read()
{
	cin >> N;
	For( i, 1, N ) cin >> arr[ i ];

	int Q;
	cin >> Q;
	querys.resize( Q );
	For2( q, 0, Q )
	{
		querys[ q ].idx = q;
		cin >> querys[ q ].i >> querys[ q ].j;
	}
}

int cnt[ 1'000'001 ] = { 0, };

inline void solve()
{
	int sq = sqrt( N );
	sort( querys.begin(), querys.end(),
		[&]( const Query& lhs, const Query& rhs ) {
			if ( lhs.i / sq != rhs.i / sq ) return lhs.i / sq < rhs.i / sq;
			return lhs.j < rhs.j;
		} );

	int uniqueCount = 0;
	int s = querys[ 0 ].i;
	int e = querys[ 0 ].j;
	For( i, s, e )
	{
		if ( cnt[ arr[ i ] ]++ == 0 ) uniqueCount++;
	}
	ret[ querys[ 0 ].idx ] = uniqueCount;

	For2( q, 1, querys.size() )
	{
		while ( s < querys[ q ].i ) if ( --cnt[ arr[ s++ ] ] == 0 ) uniqueCount--;
		while ( s > querys[ q ].i ) if ( cnt[ arr[ --s ] ]++ == 0 ) uniqueCount++;
		while ( e < querys[ q ].j ) if ( cnt[ arr[ ++e ] ]++ == 0 ) uniqueCount++;
		while ( e > querys[ q ].j ) if ( --cnt[ arr[ e-- ] ] == 0 ) uniqueCount--;
		ret[ querys[ q ].idx ] = uniqueCount;
	}

	For2( i, 0, querys.size() )
	{
		cout << ret[ i ] << '\n';
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
