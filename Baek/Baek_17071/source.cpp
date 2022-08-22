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
const int INF = 800;

const bool TEST_CASES = false;

int N, K;

int visited[ 500'001 ][ 2 ];
int check[ 500'001 ][ 2 ];

inline void read()
{
	cin >> N >> K;
}

inline void solve()
{
	For( i, 0, 500'000 )
	{
		check[ i ][ 0 ] = -1;
		check[ i ][ 1 ] = -1;

		visited[ i ][ 0 ] = 1'000'000;
		visited[ i ][ 1 ] = 1'000'000;
	}

	int acc = 0;
	For( i, 0, 500'000 )
	{
		acc += i;
		if ( K + acc > 500'000 )
			break;
		check[ K + acc ][ i % 2 ] = i;
	}

	// 큰게 먼저나오니까 - 붙임
	priority_queue< pii > pq;
	pq.push( { 0, N } );
	visited[ N ][ 0 ] = 0;
	while ( !pq.empty() )
	{
		int turn = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		if ( turn > visited[ here ][ turn % 2 ] )
			continue;

		int next = turn + 1;

		int left = here - 1;
		if ( left >= 0 && visited[ left ][ next % 2 ] > next )
		{
			visited[ left ][ next % 2 ] = next;
			pq.push( { -next, left } );
		}

		int right = here + 1;
		if ( right <= 500'000 && visited[ right ][ next % 2 ] > next )
		{
			visited[ right ][ next % 2 ] = next;
			pq.push( { -next, right } );
		}

		int there = here * 2;
		if ( there <= 500'000 && visited[ there ][ next % 2 ] > next )
		{
			visited[ there ][ next % 2 ] = next;
			pq.push( { -next, there } );
		}
	}

	int ret = 1'000'000;
	For( i, 0, 500'000 )
	{
		For( j, 0, 1 )
		{
			if ( check[ i ][ j ] > -1 && visited[ i ][ j ] <= check[ i ][ j ] )
			{
				ret = min( ret, check[ i ][ j ] );
			}
		}
	}

	if ( ret == 1'000'000 )
	{
		cout << -1 << '\n';
	}
	else
	{
		cout << ret << '\n';
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