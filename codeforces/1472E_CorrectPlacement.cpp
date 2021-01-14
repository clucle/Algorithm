
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

int n;
vector<pair<pii, int>> v;
int ret[ MAX_N ];

inline void read()
{
	cin >> n;
	For( i, 0, n - 1 )
	{
		int w, h; cin >> h >> w;
		v.push_back( { {min( h, w ), max( h, w )}, i } );
	}
}

pii dp[ MAX_N ];
int origin[ MAX_N ];

inline void solve()
{
	sort( v.begin(), v.end(), greater<pair<pii, int>>() );

	if ( DEBUG )
	{
		cout << "-----\n";
		for ( int i = 0; i < n; i++ )
		{
			cout << v[ i ].first.first << ' ' << v[ i ].first.second << ' ' << v[ i ].second << '\n';
		}
		cout << "-----\n";
	}

	for ( int i = 0; i < n; i++ )
	{
		origin[ i ] = v[ i ].second;
	}

	v.pb( { {v[ n - 1 ].first.first, 0 }, 0 } );
	dp[ n ] = { n, 1e9 + 1 };

	for ( int i = n - 1; i >= 0; i-- )
	{
		dp[ i ] = dp[ i + 1 ];
		if ( v[ i ].first.second < dp[ i + 1 ].second )
			dp[ i ] = { i, v[ i ].first.second };
	}

	if ( DEBUG )
	{
		cout << "-----\n";
		for ( int i = 0; i <= n; i++ )
		{
			cout << dp[ i ].first << ' ' << dp[ i ].second << '\n';
		}
		cout << "-----\n";
	}

	For( i, 0, n - 1 )
	{
		int j = i + 1;
		while ( j < n )
		{
			if ( v[ i ].first.first != v[ j ].first.first ) break;
			j++;
		}

		if ( DEBUG )
		{
			cout << "-----\n";
			cout << "i : " << i << " j : " << j << '\n';
			cout << "-----\n";
		}

		for ( int a = i; a < j; a++ )
		{
			// j 가 최대 n 일 수 있음 0기 때문에
			if ( v[ a ].first.second > dp[ j ].second )
			{
				ret[ origin[ a ] ] = origin[ dp[ j ].first ] + 1;
			}
			else
			{
				ret[ origin[ a ] ] = -1;
			}
		}

		i = j - 1;
	}

	for ( int i = 0; i < n; i++ )
		cout << ret[ i ] << ' ';
	cout << '\n';
	


	v.clear();
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
