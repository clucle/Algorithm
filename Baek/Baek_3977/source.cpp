#include <iostream>
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
const int MAX_N = 100'001;

const bool TEST_CASES = true;

int N, M;
vector<int> v[ MAX_N ];
int arr_id[ MAX_N ];
bool finished[ MAX_N ];
int id, g_scc_id;
int scc[ MAX_N ];

inline void presolve()
{
}

inline void read()
{
	cin >> N >> M;
	For2( i, 0, N ) v[ i ].clear();
	For( i, 1, M )
	{
		int a, b; cin >> a >> b;
		v[ a ].pb( b );
	}
}

stack<int> st;
int dfs( int here )
{
	arr_id[ here ] = ++id;
	st.push( here );

	int parent = arr_id[ here ];
	for ( auto there : v[ here ] )
	{
		if ( !arr_id[ there ] ) parent = min( parent, dfs( there ) );
		else if ( !finished[ there ] ) parent = min( parent, arr_id[ there ] ); // 사이클
	}

	if ( parent == arr_id[ here ] )
	{
		g_scc_id++;
		while ( true )
		{
			int num = st.top();
			st.pop();
			scc[ num ] = g_scc_id;
			finished[ num ] = true;
			if ( num == here ) break;
		}
	}

	return parent;
}

bool visited[ MAX_N ];

inline void solve()
{
	memset( arr_id, 0, sizeof( arr_id ) );
	memset( finished, 0, sizeof( finished ) );
	id = 0;
	g_scc_id = 0;
	For2( i, 0, N )
	{
		if ( arr_id[ i ] == 0 ) dfs( i );
	}

	std::set<int> ignore;
	// g_scc_id
	For( i, 0, N )
	{
		for ( auto there : v[ i ] )
		{
			if ( scc[ i ] != scc[ there ] ) ignore.insert( scc[ there ] );
		}
	}

	int x = 0;
	For( i, 1, g_scc_id )
	{
		if ( ignore.find( i ) != ignore.end() ) continue;

		For2( j, 0, N ) if ( scc[ j ] == i )
		{
			x = j;
			i = g_scc_id;
			break;
		}
	}

	queue<int> q;
	q.push( x );
	memset( visited, 0, sizeof( visited ) );
	visited[ x ] = true;
	while ( !q.empty() )
	{
		int here = q.front();
		q.pop();

		for ( auto there : v[ here ] )
		{
			if ( !visited[ there ] )
			{
				visited[ there ] = true;
				q.push( there );
			}
		}
	}

	For2( i, 0, N ) if ( !visited[ i ] )
	{
		cout << "Confused\n\n";
		return;
	}

	For2( i, 0, N )
	{
		if ( scc[ i ] == scc[ x ] ) cout << i << '\n';
	}
	cout << '\n';
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
