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

// ax + by = g ÀÏ¶§ x, y Ã£±â
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

const ll MYMOD = (ll)1e9 + 7;
const int MAX_N = (int)2e5 + 10;

const bool TEST_CASES = false;

inline void presolve()
{

}

int arr[ 2002 ][ 2002 ] = { 0, };
int N, K;

inline void read()
{
	cin >> N >> K;
}

bool isValid( int x, int y )
{
	if ( x < 1 || x > N || y <1 || y > N ) return false;
	return true;
}

int x_dif[ 4 ] = { 0,0,1,-1 };
int y_dif[ 4 ] = { 1,-1,0,0 };

int parent[ 100'000 ];
int get_parent( int here )
{
	if ( parent[ here ] == here ) return here;
	return get_parent( parent[ here ] );
}


inline void solve()
{
	For( i, 1, K ) parent[ i ] = i;

	queue< pair<int, pii >> q;
	queue< pair<int, pii >> q2;

	int k = 1;
	For( i, 1, K )
	{
		int x, y;
		cin >> x >> y;

		if ( arr[ x ][ y ] )
			continue;
		arr[ x ][ y ] = k;
		q.push( { k++, {x, y} } );
	}

	k--;
	// 1 ~ k ±×·ìÀÌÀÕ°ÙÁö?

	int ret = 0;

	int cnt = 0;
	while ( !q.empty() )
	{
		int group = q.front().first;
		int x = q.front().second.first;
		int y = q.front().second.second;

		q2.push( { group, {x, y} } );
		q.pop();

		For( d, 0, 3 )
		{
			int xx = x + x_dif[ d ];
			int yy = y + y_dif[ d ];

			if ( !isValid( xx, yy ) ) continue;
			if ( !arr[ xx ][ yy ] ) continue;

			int g1 = get_parent( group );
			int g2 = get_parent( arr[ xx ][ yy ] );
			if ( g1 != g2 )
			{
				if ( g1 > g2 ) swap( g1, g2 );
				parent[ g2 ] = g1;
				cnt++;
			}
		}
	}

	while ( !q2.empty() )
	{
		/*
		cout << cnt << '\n';
		For( x, 1, 5 )
		{
			For( y, 1, 5 )
			{
				cout << get_parent( arr[ x ][ y ] ) << ' ';
			}
			cout << '\n';
		}
		cout << '\n';
		*/
		if ( cnt == k - 1 ) break;

		ret++; // ÇÑÄ­¾¿ ÆÛ¶ß¸²

		swap( q2, q );
		while ( !q.empty() )
		{
			int group = q.front().first;
			int x = q.front().second.first;
			int y = q.front().second.second;

			q.pop();

			For( d, 0, 3 )
			{
				int xx = x + x_dif[ d ];
				int yy = y + y_dif[ d ];

				if ( !isValid( xx, yy ) ) continue;
				if ( arr[ xx ][ yy ] ) continue;
				arr[ xx ][ yy ] = get_parent( group );
				q2.push( { arr[ xx ][ yy ], {xx,yy} } );

				For( f, 0, 3 )
				{
					int xxx = xx + x_dif[ f ];
					int yyy = yy + y_dif[ f ];

					if ( !isValid( xxx, yyy ) ) continue;
					if ( !arr[ xxx ][ yyy ] ) continue;

					int g1 = get_parent( group );
					int g2 = get_parent( arr[ xxx ][ yyy ] );
					if ( g1 != g2 )
					{
						if ( g1 > g2 ) swap( g1, g2 );
						parent[ g2 ] = g1;
						cnt++;
					}
				}
			}
		}
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
