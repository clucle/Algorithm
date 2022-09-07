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
const int MAX_N = 200'001;

const bool TEST_CASES = false;

inline void presolve()
{

}

int N;
ll arr[ 200000 ];
vector<ll> sum_tree;
vector<ll> cnt_tree;

inline void read()
{
	cin >> N;
}

ll get_sum( int idx, int start, int end, int l, int r )
{
	if ( l <= start && end <= r ) return sum_tree[ idx ];
	if ( l > end || r < start ) return 0;

	int mid = start + ( end - start ) / 2;
	return
		get_sum( idx * 2 + 0, start, mid, l, r ) +
		get_sum( idx * 2 + 1, mid + 1, end, l, r );
}

void update_sum( int idx, int start, int end, int pos )
{
	if ( pos < start || end < start ) return;
	if ( start == end )
	{
		sum_tree[ idx ] += pos;
		return;
	}

	sum_tree[ idx ] += pos;
	int mid = start + ( end - start ) / 2;
	if ( pos <= mid )
	{
		update_sum( idx * 2 + 0, start, mid, pos );
	}
	else
	{
		update_sum( idx * 2 + 1, mid + 1, end, pos );
	}
}


ll get_cnt( int idx, int start, int end, int l, int r )
{
	if ( l <= start && end <= r ) return cnt_tree[ idx ];
	if ( l > end || r < start ) return 0;

	int mid = start + ( end - start ) / 2;
	return
		get_cnt( idx * 2 + 0, start, mid, l, r ) +
		get_cnt( idx * 2 + 1, mid + 1, end, l, r );
}

void update_cnt( int idx, int start, int end, int pos )
{
	if ( pos < start || end < start ) return;
	if ( start == end )
	{
		cnt_tree[ idx ]++;
		return;
	}

	cnt_tree[ idx ]++;
	int mid = start + ( end - start ) / 2;
	if ( pos <= mid )
	{
		update_cnt( idx * 2 + 0, start, mid, pos );
	}
	else
	{
		update_cnt( idx * 2 + 1, mid + 1, end, pos );
	}
}

inline void solve()
{
	ll h = log2( MAX_N + 1 ) + 1;
	sum_tree.resize( 1 << ( h + 1 ) );
	cnt_tree.resize( 1 << ( h + 1 ) );

	ll ret = 1;

	ll a;
	cin >> a;
	a++;
	update_sum( 1, 1, MAX_N, a );
	update_cnt( 1, 1, MAX_N, a );

	For( i, 2, N )
	{
		cin >> a;
		a++;
		// 1 ~ a
		ll s_left = get_sum( 1, 1, MAX_N, 1, a );
		ll cnt_left = get_cnt( 1, 1, MAX_N, 1, a );
		ll lsum = cnt_left * a - s_left;

		// a ~ N
		ll s_right = get_sum( 1, 1, MAX_N, a, MAX_N );
		ll cnt_right = get_cnt( 1, 1, MAX_N, a, MAX_N );
		ll rsum = s_right - cnt_right * a;

		ll tmp = lsum + rsum;
		tmp %= MYMOD;

		ret *= tmp;
		ret %= MYMOD;

		update_sum( 1, 1, MAX_N, a );
		update_cnt( 1, 1, MAX_N, a );
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
