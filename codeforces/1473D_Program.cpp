
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

#define DEBUG false

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
const int MAX_N = 2e5 + 7;

const bool TEST_CASES = true;


int n, m;
string s;
vector<pii> q;

int dp[ MAX_N ];
int _max[ MAX_N ];
int _min[ MAX_N ];

int _max2[ MAX_N ];
int _min2[ MAX_N ];


inline void read()
{
	cin >> n >> m >> s;
	int l, r;
	while ( m-- )
	{
		cin >> l >> r;
		q.emplace_back( l, r );
	}
}

inline void solve()
{
	dp[0] = 0;
	_max[ 0 ] = 0;
	_min[ 0 ] = 0;

	For( i, 1, n )
	{
		if ( s[ i - 1 ] == '-' ) dp[ i ] = dp[ i - 1 ] - 1;
		else dp[ i ] = dp[ i - 1 ] + 1;
		_max[ i ] = max( _max[ i - 1 ], dp[ i ] );
		_min[ i ] = min( _min[ i - 1 ], dp[ i ] );
	}

	_max2[ n + 1 ] = dp[ n ];
	_min2[ n + 1 ] = dp[ n ];

	Rep( i, n, 1 )
	{
		_max2[ i ] = max( _max2[ i + 1 ], dp[ i ] );
		_min2[ i ] = min( _min2[ i + 1 ], dp[ i ] );
	}

	for ( auto e : q )
	{
		int l = e.first;
		int r = e.second;

		int l_max = _max[ l - 1 ];
		int l_min = _min[ l - 1 ];

		int lr_max = dp[l - 1] + _max2[ r + 1 ] - dp[ r ];
		int lr_min = dp[l - 1] + _min2[ r + 1 ] - dp[ r ];

		cout << max( lr_max, l_max ) - min( lr_min, l_min ) + 1 << '\n';
	}


	q.clear();
}

int main()
{
	ios::sync_with_stdio( false );
	cin.tie( 0 ); cout.tie( 0 );
	cout.precision( 2 ); cout << fixed;

	int t = 1;
	if ( TEST_CASES ) cin >> t;
	while ( t-- )
	{
		read();
		solve();
	}

	return 0;
}
