
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
const int MAX_N = 200100;

const bool TEST_CASES = true;

int n, m, k;

vector<pair<int, pii>> v;
int parent[ MAX_N ];

inline void read()
{
	cin >> n >> m >> k;
	For( i, 1, m )
	{
		int a, b, s;
		cin >> a >> b >> s;
		v.push_back( { s, {a,b} } );
	}
}

int getParent( int x )
{
	int p = parent[ x ];
	if ( parent[ x ] != x )
	{
		p = getParent( parent[ x ] );
	}
	parent[ x ] = p;
	return parent[ x ];
}

inline void solve()
{
	priority_queue< pair<int, pii> > pq;

	pair<int, pii> candidate = { INT_MAX, {0,0} };
	pair<int, pii> candidate2 = { INT_MAX, {0,0} };

	int saved = 0;
	int saved2 = 0;

	for ( auto e : v )
	{
		if ( e.first <= k )
		{
			int _diff = k - e.first;
			if ( _diff < candidate.first )
			{
				candidate = { _diff, {e.second.first, e.second.second} };
				saved = e.first;
			}
		}
		else
		{
			int _diff = e.first - k;
			if ( _diff < candidate2.first )
			{
				candidate2 = { _diff, {e.second.first, e.second.second} };
				saved2 = e.first;
			}
		}
	}

	ll ret1 = LLONG_MAX;

	if ( candidate.second.first != candidate.second.second )
	{
		ret1 = 0;
		for ( auto e : v )
		{
			pq.push( { -e.first, { e.second.first, e.second.second } } );
		}
		parent[ 0 ] = 0;
		For( i, 1, n ) parent[ i ] = i;
		parent[ candidate.second.second ] = candidate.second.first;


		int last_speed = 0;
		while ( !pq.empty() )
		{
			int speed = -pq.top().first;
			int a = pq.top().second.first;
			int b = pq.top().second.second;
			pq.pop();

			int _pa = getParent( a );
			int _pb = getParent( b );
			if ( _pa == _pb )
				continue;

			parent[ _pb ] = _pa;
			ret1 += (ll)( max( speed - k, 0 ) );
			last_speed = speed;
		}
		if ( last_speed <= saved )
			ret1 += candidate.first;
	}
	
	ll ret2 = LLONG_MAX;
	if ( candidate2.second.first != candidate2.second.second )
	{
		ret2 = 0;
		for ( auto e : v )
		{
			pq.push( { -e.first, { e.second.first, e.second.second } } );
		}
		parent[ 0 ] = 0;
		For( i, 1, n ) parent[ i ] = i;
		parent[ candidate2.second.second ] = candidate2.second.first;

		int last_speed = 0;
		while ( !pq.empty() )
		{
			int speed = -pq.top().first;
			int a = pq.top().second.first;
			int b = pq.top().second.second;
			pq.pop();

			int _pa = getParent( a );
			int _pb = getParent( b );
			if ( _pa == _pb )
				continue;

			parent[ _pb ] = _pa;
			ret2 += (ll)( max( speed - k, 0 ) );
			last_speed = speed;
		}

		ret2 += candidate2.first;
	}


	v.clear();
	cout << min(ret1, ret2) << '\n';
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
