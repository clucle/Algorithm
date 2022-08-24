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

const ll MYMOD = 1e9 + 7;
const int MAX_N = 2e5 + 10;

const bool TEST_CASES = false;

inline void presolve()
{

}

int N, M;
vector<int> graph[ 20'010 ];

int get_opposite( int x )
{
	if ( x < 0 ) return -x;
	return N + x;
}

int get_cur( int x )
{
	if ( x < 0 ) return N - x;
	return x;
}

inline void read()
{
	cin >> N >> M;

	int xi, xj;
	For( i, 1, M )
	{
		cin >> xi >> xj;
		graph[ get_opposite( xi ) ].push_back( get_cur( xj ) );
		graph[ get_opposite( xj ) ].push_back( get_cur( xi ) );
	}
}

int visited[ 20'010 ];
int finished[ 20'010 ];
int id;
stack<int>s;
vector<vector<int>> g_scc;

int dfs( int here )
{
	visited[ here ] = ++id;
	s.push( here );

	int parent = visited[ here ];
	for ( auto there : graph[ here ] )
	{
		if ( !visited[ there ] ) parent = min( parent, dfs( there ) );
		else if ( !finished[ there ] ) parent = min( parent, visited[ there ] );
	}

	if ( parent == visited[ here ] )
	{
		vector<int> scc;
		while ( 7 )
		{
			int top = s.top();
			s.pop();
			scc.push_back( top );
			finished[ top ] = 1;
			if ( top == here ) break;
		}
		g_scc.emplace_back( scc );
	}

	return parent;
}

inline void solve()
{
	id = 0;
	memset( visited, 0, sizeof( visited ) );
	memset( finished, 0, sizeof( finished ) );
	For( i, 1, 2 * N )
	{
		if ( !visited[ i ] ) dfs( i );
	}

	bool ok = true;
	vector<pii> tmp( 2 * N );
	int cnt = 0;
	int group = 0;
	for ( auto& v : g_scc )
	{
		set<int> s;
		for ( auto e : v )
		{
			tmp[ cnt++ ] = { group, e };
			if ( e > N ) e -= N;
			if ( !s.insert( e ).second ) ok = false;
		}
		++group;
	}

	cout << ( ok ? 1 : 0 );
	if ( !ok ) return;
	cout << '\n';

	vector<int> ret( N + 1 );
	fill( ret.begin(), ret.end(), -1 );
	for ( auto iter = tmp.rbegin(); iter != tmp.rend(); ++iter )
	{
		int origin = iter->second;
		if ( origin > N ) origin -= N;

		if ( ret[ origin ] == -1 )
		{
			ret[ origin ] = ( origin == iter->second ? 0 : 1 );
		}
	}

	For( i, 1, N ) cout << ret[ i ] << ' ';
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
