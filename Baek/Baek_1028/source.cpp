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

/* ------------------- Custom clucle ------------------- */
/* ----------------------------------------------------- */

const ll MYMOD = (ll)1e9 + 7;
const int MAX_N = (int)2e5 + 10;
const int INF = 800;

const bool TEST_CASES = false;

int R, C;
char arr[ 752 ][ 752 ] = {
	0,
};

int dp[ 752 ][ 752 ][ 4 ] = { 0, };


inline void read()
{
	For( r, 0, R + 1 ) For( c, 0, C + 1 )
		arr[ r ][ c ] = '0';
	cin >> R >> C;
	For( r, 1, R ) For( c, 1, C ) cin >> arr[ r ][ c ];
}


inline void solve()
{
	For( r, 1, R ) For( c, 1, C )
	{
		if ( arr[ r ][ c ] == '0' )
		{
			dp[ r ][ c ][ 0 ] = 0;
			dp[ r ][ c ][ 1 ] = 0;
		}
		else
		{
			dp[ r ][ c ][ 0 ] = dp[ r - 1 ][ c - 1 ][ 0 ] + 1;
			dp[ r ][ c ][ 1 ] = dp[ r - 1 ][ c + 1 ][ 1 ] + 1;
		}
	}

	Rep( r, R, 1 ) Rep( c, C, 1 )
	{
		if ( arr[ r ][ c ] == '0' )
		{
			dp[ r ][ c ][ 2 ] = 0;
			dp[ r ][ c ][ 3 ] = 0;
		}
		else
		{
			dp[ r ][ c ][ 2 ] = dp[ r + 1 ][ c - 1 ][ 2 ] + 1;
			dp[ r ][ c ][ 3 ] = dp[ r + 1 ][ c + 1 ][ 3 ] + 1;
		}
	}

	int ret = 0;
	For( r, 1, R ) For( c, 1, C )
	{
		int here_min = min( dp[ r ][ c ][ 1 ], dp[ r ][ c ][ 3 ] );

		Rep( ok, here_min, ret )
		{
			// ok = 1 자기자신
			// ok = 2 내낵스트
			int there = 2 * ( ok - 1 );
			if ( c + there > C ) continue;
			int there_min = min( dp[ r ][ c + there ][ 0 ], dp[ r ][ c + there ][ 2 ] );
			if ( there_min >= ok )
			{
				ret = ok;
				break;
			}
		}
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