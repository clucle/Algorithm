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
	if ( b == 0 )
		return { a, 1, 0 };
	gxy ret = xGcd( b, a % b );
	return { ret.g, ret.y, ret.x - ( a / b ) * ret.y };
}

/* ------------------- Custom clucle ------------------- */
/* ----------------------------------------------------- */

const ll MYMOD = (ll)1e9 + 7;
const int MAX_N = (int)2e5 + 10;

const bool TEST_CASES = true;

inline void presolve()
{}

int N, K;
int arr[ 100001 ];


inline void read()
{
	cin >> N >> K;
}

vector< int > max_tree;
vector< int > min_tree;

inline void init()
{
	int h = log2( N ) + 1;
	min_tree.resize( 1 << ( h + 1 ) );
	max_tree.resize( 1 << ( h + 1 ) );

	For( i, 1, N ) arr[ i ] = i;
}

int build_max( int idx, int l, int r )
{
	if ( l == r )
	{
		return max_tree[ idx ] = arr[ l ];
	}

	int mid = l + ( r - l ) / 2;
	return max_tree[ idx ] = max(
		build_max( idx * 2 + 0, l, mid ),
		build_max( idx * 2 + 1, mid + 1, r ) );
}

int build_min( int idx, int l, int r )
{
	if ( l == r )
	{
		return min_tree[ idx ] = arr[ l ];
	}

	int mid = l + ( r - l ) / 2;
	return min_tree[ idx ] = min(
			   build_min( idx * 2 + 0, l, mid ),
			   build_min( idx * 2 + 1, mid + 1, r ) );
}

int update_max( int idx, int l, int r, int cur )
{
	if ( cur < l || cur > r )
		return max_tree[ idx ];

	if ( l == r )
		return max_tree[ idx ] = arr[ l ];

	int mid = l + ( r - l ) / 2;
	return max_tree[ idx ] = max(
		update_max( idx * 2 + 0, l, mid, cur ),
		update_max( idx * 2 + 1, mid + 1, r, cur ) );
}

int update_min( int idx, int l, int r, int cur )
{
	if ( cur < l || cur > r )
		return min_tree[ idx ];

	if ( l == r )
		return min_tree[ idx ] = arr[ l ];

	int mid = l + ( r - l ) / 2;
	return min_tree[ idx ] = min(
		update_min( idx * 2 + 0, l, mid, cur ),
		update_min( idx * 2 + 1, mid + 1, r, cur ) );
}

int get_max( int idx, int start, int end, int l, int r )
{
	if ( l <= start && end <= r )
		return max_tree[ idx ];

	if ( l > end || r < start )
		return 0;

	int mid = start + ( end - start ) / 2;
	return max(
		get_max( idx * 2 + 0, start, mid, l, r ),
		get_max( idx * 2 + 1, mid + 1, end, l, r ) );
}

int get_min( int idx, int start, int end, int l, int r )
{
	if ( l <= start && end <= r )
		return min_tree[ idx ];

	if ( l > end || r < start )
		return N + 1;

	int mid = start + ( end - start ) / 2;
	return min(
		get_min( idx * 2 + 0, start, mid, l, r ),
		get_min( idx * 2 + 1, mid + 1, end, l, r ) );
}


inline void solve()
{
	init();

	build_max( 1, 1, N );
	build_min( 1, 1, N );

	For( i, 1, K )
	{
		int Q, A, B;
		cin >> Q >> A >> B;
		A++;
		B++;

		if ( A > B )
			swap( A, B );

		if ( Q == 0 )
		{
			swap( arr[ A ], arr[ B ] );
			// A 번이 arr[A] 로 업데이트
			// B 번이 arr[B] 로 업데이트

			update_max( 1, 1, N, A );
			update_max( 1, 1, N, B );
			update_min( 1, 1, N, A );
			update_min( 1, 1, N, B );
		}
		else
		{
			int _max = get_max( 1, 1, N, A, B );
			int _min = get_min( 1, 1, N, A, B );

			if ( _min == A && _max == B )
			{
				cout << "YES\n";
			}
			else
			{
				cout << "NO\n";
			}
			// YES OR NO
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
	if ( TEST_CASES )
		cin >> t;
	while ( t-- )
	{
		read();
		solve();
	}

	return 0;
}
