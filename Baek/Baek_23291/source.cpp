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
const int MAX_N = 30'002;

const bool TEST_CASES = false;

bool isValid( int r, int c )
{
	if ( r < 0 || r > 3 || c < 0 || c > 3 ) return false;
	return true;
}

inline void presolve()
{
}

int N, K;
int arr[ 101 ][ 101 ];
int temp[ 101 ][ 101 ];

inline void read()
{
	cin >> N >> K;
	For( i, 1, N ) cin >> arr[ 1 ][ i ];
}

void _debug_print()
{
	return;
	For( i, 1, N )
	{
		For( j, 1, N )
		{
			cout << arr[ i ][ j ] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}

inline void solve()
{

	int ret = 0;

	while ( true )
	{
		int l = N;

		// step 0
		int cur_max = -1;
		int cur_min = INT_MAX;
		For( i, 1, N )
		{
			cur_max = max( cur_max, arr[ 1 ][ i ] );
			cur_min = min( cur_min, arr[ 1 ][ i ] );
		}

		if ( cur_max - cur_min <= K ) break;
		ret++;

		// step 1
		For( i, 1, N )
		{
			if ( arr[ 1 ][ i ] == cur_min ) arr[ 1 ][ i ]++;
		}

		_debug_print();

		// step 2
		int next_r = 1;
		int next_c = 1;

		while ( l - next_r - next_c >= 0 )
		{
			// r, c -> c, r 로 변경
			For( i, 1, next_r ) For( j, 1, next_c ) temp[ next_c - j + 1 ][ i ] = arr[ i ][ j ];
			// 2, 1 에서부터 쌓음
			For( i, 1, next_c ) For( j, 1, next_r )
				arr[ i + 1 ][ j ] = temp[ i ][ j ];

			memcpy( &arr[ 1 ][ 1 ], &arr[ 1 ][ 1 + next_c ], sizeof( int ) * l );
			l -= next_c;

			if ( next_r == next_c ) next_r++;
			else next_c++;
		}

		_debug_print();

		memset( temp, 0, sizeof( temp ) );
		// step 3
		For( i, 1, next_r ) For( j, 1, next_c )
		{
			if ( i + 1 <= next_r )
			{
				if ( int diff = ( arr[ i ][ j ] - arr[ i + 1 ][ j ] ) / 5; diff > 0 )
				{
					temp[ i + 0 ][ j ] -= diff;
					temp[ i + 1 ][ j ] += diff;
				}
				if ( int diff = ( arr[ i + 1 ][ j ] - arr[ i ][ j ] ) / 5; diff > 0 )
				{
					temp[ i + 0 ][ j ] += diff;
					temp[ i + 1 ][ j ] -= diff;
				}
			}

			if ( j + 1 <= next_c )
			{
				if ( int diff = ( arr[ i ][ j ] - arr[ i ][ j + 1 ] ) / 5; diff > 0 )
				{
					temp[ i ][ j + 0 ] -= diff;
					temp[ i ][ j + 1 ] += diff;
				}
				if ( int diff = ( arr[ i ][ j + 1 ] - arr[ i ][ j ] ) / 5; diff > 0 )
				{
					temp[ i ][ j + 0 ] += diff;
					temp[ i ][ j + 1 ] -= diff;
				}
			}
		}

		For2( i, next_c, l )
		{
			if ( int diff = ( arr[ 1 ][ i ] - arr[ 1 ][ i + 1 ] ) / 5; diff > 0 )
			{
				temp[ 1 ][ i + 0 ] -= diff;
				temp[ 1 ][ i + 1 ] += diff;
			}
			if ( int diff = ( arr[ 1 ][ i + 1 ] - arr[ 1 ][ i ] ) / 5; diff > 0 )
			{
				temp[ 1 ][ i + 0 ] += diff;
				temp[ 1 ][ i + 1 ] -= diff;
			}
		}


		For( i, 1, 100 ) For( j, 1, 100 ) arr[ i ][ j ] += temp[ i ][ j ];
		// _debug_print();

		_debug_print();

		// step 4
		memcpy( &arr[ 1 ][ 1 + (next_r)*next_c ], &arr[ 1 ][ 1 + next_c ], sizeof( int ) * ( l - next_c + 1 ) );

		int cnt = 1 + next_r * next_c;
		Rep( i, next_c, 1 ) Rep( j, next_r, 1 )
		{
			cnt--;
			arr[ 1 ][ cnt ] = arr[ j ][ i ];
		}

		_debug_print();

		// step 5
		For( i, 1, N / 2 )
		{
			arr[ 2 ][ i ] = arr[ 1 ][ ( N / 2 ) - i + 1 ];
		}
		For( i, 1, N / 2 )
		{
			arr[ 1 ][ i ] = arr[ 1 ][ ( N / 2 ) + i ];
		}
		For( i, 1, N / 4 )
		{
			arr[ 3 ][ i ] = arr[ 2 ][ ( N / 4 ) - i + 1 ];
			arr[ 4 ][ i ] = arr[ 1 ][ ( N / 4 ) - i + 1 ];
		}
		For( i, 1, N / 4 )
		{
			arr[ 1 ][ i ] = arr[ 1 ][ ( N / 4 ) + i ];
			arr[ 2 ][ i ] = arr[ 2 ][ ( N / 4 ) + i ];
		}

		_debug_print();

		// step 6
		next_r = 4;
		next_c = N / 4;
		memset( temp, 0, sizeof( temp ) );
		For( i, 1, next_r ) For( j, 1, next_c )
		{
			if ( i + 1 <= next_r )
			{
				if ( int diff = ( arr[ i ][ j ] - arr[ i + 1 ][ j ] ) / 5; diff > 0 )
				{
					temp[ i + 0 ][ j ] -= diff;
					temp[ i + 1 ][ j ] += diff;
				}
				if ( int diff = ( arr[ i + 1 ][ j ] - arr[ i ][ j ] ) / 5; diff > 0 )
				{
					temp[ i + 0 ][ j ] += diff;
					temp[ i + 1 ][ j ] -= diff;
				}
			}

			if ( j + 1 <= next_c )
			{
				if ( int diff = ( arr[ i ][ j ] - arr[ i ][ j + 1 ] ) / 5; diff > 0 )
				{
					temp[ i ][ j + 0 ] -= diff;
					temp[ i ][ j + 1 ] += diff;
				}
				if ( int diff = ( arr[ i ][ j + 1 ] - arr[ i ][ j ] ) / 5; diff > 0 )
				{
					temp[ i ][ j + 0 ] += diff;
					temp[ i ][ j + 1 ] -= diff;
				}
			}
		}

		For( i, 1, 100 ) For( j, 1, 100 ) arr[ i ][ j ] += temp[ i ][ j ];
		_debug_print();

		// step 7
		cnt = N + 1;

		Rep( i, ( N / 4 ), 1 ) Rep( j, 4, 1 )
		{
			cnt--;
			arr[ 1 ][ cnt ] = arr[ j ][ i ];
		}

		_debug_print();
	}

	cout << ret << '\n';
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
