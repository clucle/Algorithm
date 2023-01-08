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
const int MAX_N = 100'001;

const bool TEST_CASES = false;
const bool READ_FILE = false;

int K, N;

vector<string> v[ 11 ];

inline void presolve()
{
}

inline void read()
{
	// K 개중 N 개
	cin >> K >> N;

	string s;
	For( i, 1, K )
	{
		cin >> s;
		v[ s.size() ].pb( s );
	}
}

int gcd( int a, int b )
{
	if ( b == 0 ) return a;
	return gcd( b, a % b );
}

vector<string> candidate;
inline void solve()
{
	auto comparator = []( const string& lhs, const string& rhs )
	{
		if ( lhs == rhs ) return lhs < rhs;

		int l = 0;
		int r = 0;

		int lcm = lhs.size() * rhs.size() / gcd( lhs.size(), rhs.size() );

		For( i, 1, lcm )
		{
			if ( lhs[ l ] != rhs[ r ] ) return lhs[ l ] > rhs[ r ];
			l++;
			r++;
			if ( l == lhs.size() ) l = 0;
			if ( r == rhs.size() ) r = 0;
		}

		return lhs < rhs;
	};

	int diff = max( N - K, 0 );
	if ( N > K )
	{
		N = K;
	}

	bool getBig = false;
	string big;

	Rep( i, 10, 1 )
	{
		if ( !v[ i ].size() ) continue;

		if ( !getBig )
		{
			getBig = true;
			sort( v[ i ].begin(), v[ i ].end(), comparator );
			big = v[ i ][ 0 ];
		}

		if ( v[ i ].size() > N )
		{
			sort( v[ i ].begin(), v[ i ].end(), comparator );

			auto it = std::next( v[ i ].begin(), N );
			std::move( v[ i ].begin(), it, std::back_inserter( candidate ) );
			break;
		}
		else
		{
			std::move( v[ i ].begin(), v[ i ].end(), std::back_inserter( candidate ) );
			N -= v[ i ].size();
		}
	}

	sort( candidate.begin(), candidate.end(), comparator );
	string ret;
	bool chk = false;
	for ( auto e : candidate )
	{
		cout << e;
		if ( !chk && e == big )
		{
			chk = true;
			For( i, 1, diff ) cout << big;
		}
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
