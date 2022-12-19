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
const int MAX_N = 51;

int N;
int arr[ 100001 ];
vector<int> v[ 4 * 100001 ];

const bool TEST_CASES = false;
const bool READ_FILE = false;

inline void presolve()
{}

inline void read()
{
	cin >> N;
	For( i, 1, N ) cin >> arr[ i ];
}

const std::vector<int>& build( int node, int l, int r )
{
	if ( l == r )
	{
		v[ node ].push_back( arr[ l ] );
		return v[ node ];
	}

	int mid = l + ( r - l ) / 2;
	auto& v_l = build( node * 2, l, mid );
	auto& v_r = build( node * 2 + 1, mid + 1, r );

	int idx_l = 0;
	int idx_r = 0;
	v[ node ].reserve( v_l.size() + v_r.size() );
	while ( idx_l < v_l.size() && idx_r < v_r.size() )
	{
		if ( v_l[ idx_l ] > v_r[ idx_r ] )
			v[ node ].push_back( v_r[ idx_r++ ] );
		else
			v[ node ].push_back( v_l[ idx_l++ ] );
	}

	while ( idx_l < v_l.size() ) v[ node ].push_back( v_l[ idx_l++ ] );
	while ( idx_r < v_r.size() ) v[ node ].push_back( v_r[ idx_r++ ] );

	return v[ node ];
}

int get( int node, int l, int r, int start, int end, int val )
{
	if ( start <= l && r <= end )
	{
		auto up = std::upper_bound( v[ node ].begin(), v[ node ].end(), val );
		return v[ node ].end() - up;
	}
	if ( r < start || l > end ) return 0;

	int mid = l + ( r - l ) / 2;
	return get( node * 2, l, mid, start, end, val ) + get( node * 2 + 1, mid + 1, r, start, end, val );
}


inline void solve()
{
	build( 1, 1, N );

	int ans = 0;
	int M; cin >> M;
	int i, j, k;
	while ( M-- )
	{
		cin >> i >> j >> k;
		i ^= ans;
		j ^= ans;
		k ^= ans;
		ans = get( 1, 1, N, i, j, k );
		cout << ans << '\n';
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
