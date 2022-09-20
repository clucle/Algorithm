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


bool board[ 10 ][ 10 ];
bool tmp[ 10 ][ 10 ];

inline void read()
{
	For( i, 0, 9 ) For( j, 0, 9 )
	{
		char c; cin >> c;
		board[ i ][ j ] = ( c == '#' ? false : true );
	}
}

const int rDiff[ 5 ] = { 0,0,0,-1,1 };
const int cDiff[ 5 ] = { -1,1,0,0,0 };

inline bool isValid( int r, int c )
{
	if ( r < 0 || c < 0 || r > 9 || c > 9 ) return false;
	return true;
}

inline void func( int r, int c )
{
	For( i, 0, 4 )
	{
		int rr = r + rDiff[ i ];
		int cc = c + cDiff[ i ];
		if ( !isValid( rr, cc ) ) continue;

		tmp[ rr ][ cc ] = !tmp[ rr ][ cc ];
	}
}

inline void solve()
{
	int ret = 10 * 10 + 1;

	// 맨 윗행에서 누를수있는 모든 경우의수
	For2( cur, 0, ( 1 << 10 ) )
	{
		int cnt = 0;
		memcpy( tmp, board, sizeof( board ) );

		For( c, 0, 9 )
		{
			if ( cur & ( 1 << c ) )
			{
				func( 0, c );
				cnt++;
			}
		}

		For( r, 1, 9 ) For( c, 0, 9 )
		{
			if ( tmp[ r - 1 ][ c ] )
			{
				func( r, c );
				cnt++;
			}
		}

		bool good = true;
		For( c, 0, 9 )
		{
			if ( tmp[ 9 ][ c ] ) good = false;
		}

		if ( good )
		{
			ret = min( ret, cnt );
		}
	}

	if ( ret == 10 * 10 + 1 )
	{
		cout << -1;
	}
	else
	{
		cout << ret;
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
	if ( TEST_CASES )
		cin >> t;
	while ( t-- )
	{
		read();
		solve();
	}

	return 0;
}
