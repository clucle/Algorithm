
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

const bool TEST_CASES = true;

int n;
int a[ MAX_N ];
int q;
ll w;

inline void read()
{
	cin >> n;
	For( i, 1, n ) cin >> a[ i ];
	cin >> q;
}

inline void solve()
{
	vi v;

	For( i, 1, n )
	{
		for ( int j = 2; j * j <= a[i]; j++ )
		{
			if ( a[ i ] % j == 0 )
			{
				while ( a[ i ] % ( j * j ) == 0 )
				{
					a[ i ] /= ( j * j );
				}
			}
		}
		v.push_back( a[ i ] );
	}

	sort( v.begin(), v.end() );

	int mx[ 2 ] = { 0, 0 };
	int sum = 0;

	for ( int i = 0; i < v.size(); i++ )
	{
		int j = i;
		while ( j < v.size() && v[ i ] == v[ j ] ) j++;

		int cnt = j - i;
		mx[ cnt & 1 ] = max( mx[ cnt & 1 ], cnt );

		if ( !( cnt & 1 ) || v[i] == 1 ) sum += cnt;

		i = j - 1;
	}
	
	while ( q-- )
	{
		cin >> w;
		if ( w )
			cout << max( mx[ 1 ], sum ) << '\n';
		else
			cout << max( mx[ 0 ], mx[ 1 ] ) << '\n';
	}
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
