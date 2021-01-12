
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

#define DEBUG true

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const long long MOD = 1e9 + 7;

template <class T>
struct BIT {
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

/* ----------------------------------------------------- */

const ll MYMOD = 1e9 + 7;
const int MAX_N = 3e5 + 7;

const bool TEST_CASES = false;

int n[ 4 ];
int a[ 4 ][ MAX_N ];


inline void read()
{
	cin >> n[ 1 ] >> n[ 2 ] >> n[ 3 ];
	For( i, 1, 3 )
	{
		For( j, 1, n[ i ] )
		{
			cin >> a[ i ][ j ];
		}
	}
}



inline void solve()
{
	ll sum[ 4 ] = { 0, };
	ll mn[ 4 ] = { 0, };

	mn[ 1 ] = LLONG_MAX;
	mn[ 2 ] = LLONG_MAX;
	mn[ 3 ] = LLONG_MAX;

	For( i, 1, 3 )
	{
		For( j, 1, n[ i ] )
		{
			sum[ i ] += (ll)( a[ i ][ j ] );
			mn[ i ] = min( mn[ i ], (ll)( a[ i ][ j ] ) );
		}
	}
	ll tot = sum[ 1 ] + sum[ 2 ] + sum[ 3 ];

	ll ret = 0;

	For( i, 1, 3 )
	{
		ret = max( ret, abs( tot - 2 * sum[ i ] ) );
	}

	ret = max( ret, abs( tot - 2 * mn[ 1 ] - 2 * mn[ 2 ] ) );
	ret = max( ret, abs( tot - 2 * mn[ 1 ] - 2 * mn[ 3 ] ) );
	ret = max( ret, abs( tot - 2 * mn[ 2 ] - 2 * mn[ 3 ] ) );

	cout << ret;
}

int main()
{
	ios::sync_with_stdio( false );
	cin.tie( 0 ); cout.tie( 0 );
	cout.precision( 10 ); cout << fixed;

	int t = 1;
	if ( TEST_CASES ) cin >> t;
	while ( t-- )
	{
		read();
		solve();
	}

	return 0;
}
