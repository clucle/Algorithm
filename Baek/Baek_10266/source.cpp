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

vector<int> getPi( const vector<int>& v )
{
	// ABCDABE 였다면 AB 가 겹침

	int sz = v.size();
	vector<int> pi;
	pi.resize( sz );

	int j = 0; // j 가 갯수
	For2( i, 1, sz )
	{
		while ( j > 0 && v[ i ] != v[ j ] ) j = pi[ j - 1 ];
		if ( v[ i ] == v[ j ] )
			pi[ i ] = ++j;
	}

	return pi;
}

bool kmp( const vector<int>& v1, const vector<int>& v2 )
{
	auto pi = getPi( v2 );
	int j = 0;
	For2( i, 1, v1.size() )
	{
		while ( j > 0 && v1[ i ] != v2[ j ] ) j = pi[ j - 1 ];

		if ( v1[ i ] == v2[ j ] )
		{
			if ( j == v2.size() - 1 ) return true;
			else j++;
		}
	}
	return false;
}

/* ------------------- Custom clucle ------------------- */
/* ----------------------------------------------------- */

const ll MYMOD = 1'000'000'007;
const int MAX_N = 100'001;

const bool TEST_CASES = false;

int N;
vector<int> v1;
vector<int> v2;

vector<int> diff1;
vector<int> diff2;

inline void presolve()
{
}

inline void read()
{
	cin >> N;
	v1.resize( N );
	v2.resize( N );
	For2( i, 0, N ) cin >> v1[ i ];
	For2( i, 0, N ) cin >> v2[ i ];
}

inline void solve()
{
	sort( v1.begin(), v1.end() );
	sort( v2.begin(), v2.end() );

	// 음..
	// 일단 N 이 20만..
	// diff 의 순서가 동일하면 돌려서 같을거 같은데..
	// 일단 n 이 2보다 크기때문에 ..
	// diff 부터 구해보면..

	diff1.resize( N );
	diff2.resize( 2 * N );
	For2( i, 0, N - 1 )
	{
		diff1[ i ] = v1[ i + 1 ] - v1[ i ];
		diff2[ i ] = v2[ i + 1 ] - v2[ i ];
	}

	diff1[ N - 1 ] = 360000 + v1[ 0 ] - v1[ N - 1 ];
	diff2[ N - 1 ] = 360000 + v2[ 0 ] - v2[ N - 1 ];

	// 그러면 diff2 를 2배로 늘리고 kmp 를 쳐야하나..?
	For2( i, N, 2 * N ) diff2[ i ] = diff2[ i - N ];

	if ( kmp( diff2, diff1 ) )
		cout << "possible";
	else
		cout << "impossible";
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
