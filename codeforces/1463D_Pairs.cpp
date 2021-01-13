
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
const int MAX_N = 1e3 + 7;

const bool TEST_CASES = true;

int n;
set<int> s;

inline void read()
{
	cin >> n;
	For( i, 1, n )
	{
		int a; cin >> a; s.insert( a );
	}
}

inline void solve()
{
	int start = 1;
	int cnt = 0;
	int rest = 0;
	for ( auto e : s )
	{
		rest += e - start;
		if ( rest > 0 )
		{
			cnt++;
			rest--;
		}
		start = e + 1;
	}
	int min1 = n - cnt;

	start = 2 * n;
	cnt = 0;
	rest = 0;
	for ( auto iter = s.rbegin(); iter != s.rend(); ++iter )
	{
		int e = *iter;
		rest += start - e;
		if ( rest > 0 )
		{
			cnt++;
			rest--;
		}
		start = e - 1;
	}
	int min2 = cnt;

	cout << min2 - min1 + 1 << '\n';


	s.clear();
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
