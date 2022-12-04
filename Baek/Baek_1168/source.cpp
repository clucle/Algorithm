#include <iostream>
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

template <class T>
struct BIT
{
	int n;
	vector<T> tree;
	BIT( int n ) :n( n + 1 ), tree( n + 1 ) {}
	void add( int x, T a )
	{
		for ( ; x < n; x += x & -x )
		{
			tree[ x ] += a;
		}
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

/* ------------------- Custom clucle ------------------- */
/* ----------------------------------------------------- */

const ll MYMOD = 1'000'000'007;
const int MAX_N = 100'001;

const bool TEST_CASES = false;

int N, K;

inline void presolve()
{
}

inline void read()
{
	cin >> N >> K;
}

int check[ MAX_N ];

int update_cur( int cur )
{
	if ( check[ cur ] == cur ) return cur;

	return check[ cur ] = update_cur( check[ cur ] );
}

inline void solve()
{
	BIT<ll> bit( N );
	For( i, 1, N )
	{
		check[ i ] = i;
		bit.add( i, 1 );
	}

	int cur = 1;

	cout << "<";
	For2( i, 1, N )
	{
		// 일단은 남은 갯수만큼 모듈러
		int count = K % ( N - i + 1 );

		if ( count == 0 ) count = ( N - i + 1 );

		// 그리고 일단 끝까지 가봐
		// cur 에서 N 까지
		int sum1 = bit.rangeSum( cur, N );

		int l = cur;
		int r = N;
		if ( count > sum1 )
		{
			count -= sum1;
			l = 1;
			r = cur;
		}

		const int start = l;

		int ret = 0;
		while ( true )
		{
			int mid = l + ( r - l ) / 2;
			int c = bit.rangeSum( start, mid );
			if ( c < count )
			{
				l = mid + 1;
			}
			else if ( c == count )
			{
				if ( check[ mid ] == mid )
				{
					ret = mid;
					break;
				}
				else
				{
					r = mid - 1;
				}
			}
			else
			{
				r = mid - 1;
			}
		}

		check[ ret ] = ( ret % N ) + 1;
		cur = update_cur( ret );

		bit.add( ret, -1 );
		cout << ret << ", ";
	}
	cout << cur;
	cout << ">";
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
