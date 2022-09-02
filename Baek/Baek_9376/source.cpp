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

const bool TEST_CASES = true;

inline void presolve()
{

}


int h, w;
char arr[ 102 ][ 102 ];
int visited1[ 102 ][ 102 ];
int visited2[ 102 ][ 102 ];
int visited3[ 102 ][ 102 ];

inline void read()
{
	cin >> h >> w;
	For( i, 1, h )For( j, 1, w ) cin >> arr[ i ][ j ];
}

inline bool isValid( int y, int x )
{
	if ( y < 0 || y > h + 1 || x < 0 || x > w + 1 ) return false;
	return true;
}

int rDiff[ 4 ] = { 0,0,1,-1 };
int cDiff[ 4 ] = { 1,-1,0,0 };

inline void solve()
{
	int cnt = 0;
	pii xy[ 2 ];
	For( i, 0, h + 1 ) For( j, 0, w + 1 )
	{
		visited1[ i ][ j ] = -1;
		visited2[ i ][ j ] = -1;
		visited3[ i ][ j ] = -1;

		if ( arr[ i ][ j ] == '$' )
		{
			xy[ cnt++ ] = { i,j };
		}
	}

	For( j, 0, w + 1 )
	{
		arr[ 0 ][ j ] = '.';
		arr[ h + 1 ][ j ] = '.';
	}

	For( i, 1, h )
	{
		arr[ i ][ 0 ] = '.';
		arr[ i ][ w + 1 ] = '.';
	}

	priority_queue<pair<int, pii>> pq;
	pq.push( { 0,{0,0} } );
	visited1[ 0 ][ 0 ] = 0;
	while ( !pq.empty() )
	{
		int cost = -pq.top().first;

		int r = pq.top().second.first;
		int c = pq.top().second.second;

		pq.pop();

		For( d, 0, 3 )
		{
			int rr = r + rDiff[ d ];
			int cc = c + cDiff[ d ];
			if ( !isValid( rr, cc ) ) continue;
			if ( visited1[ rr ][ cc ] != -1 ) continue;
			if ( arr[ rr ][ cc ] == '*' ) continue;

			int nextcost = cost + ( arr[ rr ][ cc ] == '#' ? 1 : 0 );
			pq.push( { -nextcost, {rr,cc} } );
			visited1[ rr ][ cc ] = nextcost;
		}
	}

	pq.push( { 0,{xy[ 0 ].first, xy[ 0 ].second} } );
	visited2[ xy[ 0 ].first ][ xy[ 0 ].second ] = 0;
	while ( !pq.empty() )
	{
		int cost = -pq.top().first;

		int r = pq.top().second.first;
		int c = pq.top().second.second;

		pq.pop();

		For( d, 0, 3 )
		{
			int rr = r + rDiff[ d ];
			int cc = c + cDiff[ d ];
			if ( !isValid( rr, cc ) ) continue;
			if ( visited2[ rr ][ cc ] != -1 ) continue;
			if ( arr[ rr ][ cc ] == '*' ) continue;

			int nextcost = cost + ( arr[ rr ][ cc ] == '#' ? 1 : 0 );
			pq.push( { -nextcost, {rr,cc} } );
			visited2[ rr ][ cc ] = nextcost;
		}
	}

	pq.push( { 0,{xy[ 1 ].first, xy[ 1 ].second} } );
	visited3[ xy[ 1 ].first ][ xy[ 1 ].second ] = 0;
	while ( !pq.empty() )
	{
		int cost = -pq.top().first;

		int r = pq.top().second.first;
		int c = pq.top().second.second;

		pq.pop();

		For( d, 0, 3 )
		{
			int rr = r + rDiff[ d ];
			int cc = c + cDiff[ d ];
			if ( !isValid( rr, cc ) ) continue;
			if ( visited3[ rr ][ cc ] != -1 ) continue;
			if ( arr[ rr ][ cc ] == '*' ) continue;

			int nextcost = cost + ( arr[ rr ][ cc ] == '#' ? 1 : 0 );
			pq.push( { -nextcost, {rr,cc} } );
			visited3[ rr ][ cc ] = nextcost;
		}
	}

	int ret = 100000;
	For( r, 0, h + 1 ) For( c, 0, w + 1 )
	{
		if ( arr[ r ][ c ] == '*' )
			continue;

		if ( visited1[ r ][ c ] == -1 || visited2[ r ][ c ] == -1 || visited3[ r ][ c ] == -1 )
			continue;

		int cost = visited1[ r ][ c ] + visited2[ r ][ c ] + visited3[ r ][ c ];
		if ( arr[ r ][ c ] == '#' ) cost -= 2;
		ret = min( cost, ret );
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
