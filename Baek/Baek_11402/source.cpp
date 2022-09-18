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

ll N, K, M;

ll getPow( ll x, ll cnt )
{
	if ( cnt == 0 ) return 1;


	ll tmp = getPow( x, cnt / 2 ) % M;
	ll ret = ( tmp * tmp ) % M;


	if ( cnt % 2 == 0 )
	{
		return ret;
	}

	return ( ret * x ) % M;
}



inline void read()
{
	cin >> N >> K >> M;
}

ll nCk[ 2001 ][ 2001 ];

inline void solve()
{
	// N C K 를 M 으로 나눈 나머지
	for ( int i = 0; i < M; i++ )
	{
		nCk[ i ][ 0 ] = 1;
		for ( int j = 1; j <= i; j++ )
		{
			nCk[ i ][ j ] = ( nCk[ i - 1 ][ j - 1 ] + nCk[ i - 1 ][ j ] ) % M;
		}
	}

	ll ret = 1;
	while ( N > 0 || K > 0 )
	{
		ll n_i = N % M;
		ll n_k = K % M;

		N /= M;
		K /= M;

		ret *= nCk[ n_i ][ n_k ];
		ret %= M;
	}

	cout << ret;
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
