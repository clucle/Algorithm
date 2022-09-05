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

const ll MYMOD = (ll)1e9 + 7;
const int MAX_N = (int)2e5 + 10;

const bool TEST_CASES = false;

inline void presolve()
{

}

// src = 1, src_n = 2, src_k = 3
// N ( 1001 ~ 2000 ) M ( 2001 ~ 3000 )
// dst = 3001

vector<int> Graph[ 802 ];
int f[ 802 ][ 802 ] = { 0, };
int c[ 802 ][ 802 ] = { 0, };
int visited[ 802 ];

int N, P;

int get_exit( int here )
{
	return here + 400;
}

inline void read()
{
	cin >> N >> P;
	int a, b;
	For( i, 1, P )
	{
		cin >> a >> b;
		Graph[ get_exit( a ) ].pb( b );
		Graph[ get_exit( b ) ].pb( a );

		f[ get_exit( a ) ][ b ] = 1;
		f[ get_exit( b ) ][ a ] = 1;

		Graph[ b ].pb( get_exit( a ) );
		Graph[ a ].pb( get_exit( b ) );
	}
}

inline void solve()
{
	int src = 1;
	int dst = 402;

	// 세팅
	For( i, 1, N )
	{
		Graph[ i ].pb( get_exit( i ) );

		int ff = 1;
		if ( i == 1 || i == 2 ) ff = INT_MAX;
		f[ i ][ get_exit( i ) ] = ff;
	}

	// 세팅 끝났으면
	// src-> dst 까지 플로우 맥스 찾기

	int ret = 0;
	while ( true )
	{
		memset( visited, 0, sizeof( visited ) );
		queue<int> q;
		q.push( src );

		while ( !q.empty() )
		{
			int here = q.front();
			q.pop();

			for ( auto there : Graph[ here ] )
			{
				// here 에서 there 로 갈수 있니?
				if ( visited[ there ] ) continue;
				if ( f[ here ][ there ] - c[ here ][ there ] <= 0 ) continue;

				// 부모 설정하자
				visited[ there ] = here;
				q.push( there );

				if ( there == dst )
				{
					while ( !q.empty() ) q.pop();
					break;
				}
			}
		}

		// 싹 돌았더니 dst 에 도착못하면 끝
		if ( !visited[ dst ] ) break;

		int cur = dst;
		int cost = 1;

		// 흘려주자
		cur = dst;
		for ( ; cur != src; cur = visited[ cur ] )
		{
			int prev = visited[ cur ];
			c[ prev ][ cur ] += cost;
			c[ cur ][ prev ] -= cost;
		}

		ret += cost;
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
