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

const ll MYMOD = 1e9 + 7;
const int MAX_N = 2e5 + 10;

const bool TEST_CASES = false;

inline void read()
{

}

int N, M;

int arr_parent[ 100'001 ];
ll diff_parent[ 100'001 ];

int get_parent( int x, ll& diff )
{
	int px = arr_parent[ x ];
	if ( arr_parent[ x ] == x )
	{
		diff = 0;
		return x;
	}

	px = get_parent( px, diff );
	arr_parent[ x ] = px;
	diff += diff_parent[ x ];
	diff_parent[ x ] = diff;

	return px;
}

inline void solve()
{
	while ( 7 )
	{
		cin >> N >> M;
		if ( N == 0 && M == 0 ) return;

		For( i, 1, N )
		{
			arr_parent[ i ] = i;
			diff_parent[ i ] = 0;
		}

		char op;
		int a, b;
		ll w;
		For( m, 1, M )
		{
			cin >> op;
			if ( op == '!' )
			{
				cin >> a >> b >> w;
				ll diff_a = 0;
				int parent_a = get_parent( a, diff_a );
				ll diff_b = 0;
				int parent_b = get_parent( b, diff_b );

				if ( parent_a != parent_b )
				{
					arr_parent[ parent_a ] = parent_b;
					diff_parent[ parent_a ] = w - diff_a + diff_b;
				}
			}
			else if ( op == '?' )
			{
				cin >> a >> b;
				ll diff_a = 0;
				ll parent_a = get_parent( a, diff_a );
				ll diff_b = 0;
				ll parent_b = get_parent( b, diff_b );

				if ( parent_a != parent_b )
				{
					cout << "UNKNOWN\n";
				}
				else
				{
					cout << diff_a - diff_b << '\n';
				}
			}
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
