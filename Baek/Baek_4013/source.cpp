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
const int MAX_N = 500'001;

const bool TEST_CASES = false;

inline void presolve()
{}

int N, M, src, P;
vector<int> G[ MAX_N ];
vector<int> G_rev[ MAX_N ];
int score[ MAX_N ];
bool visited[ MAX_N ];
std::stack<int> st;
vector<int> scc[ MAX_N ];
int scc_mapping[ MAX_N ];
bool restaurant[ MAX_N ] = { 0, };

set<int> scc_G[ MAX_N ];
set<int> scc_G_rev[ MAX_N ];
int scc_sum[ MAX_N ];
bool scc_restaurant[ MAX_N ];
int scc_accum[ MAX_N ] = { 0, };

inline void read()
{
	cin >> N >> M;
	For( i, 1, M )
	{
		int a, b;
		cin >> a >> b;
		G[ a ].push_back( b );
		G_rev[ b ].push_back( a );
	}

	For( i, 1, N )
	{
		cin >> score[ i ];
	}

	cin >> src >> P;
	For( i, 1, P )
	{
		int a; cin >> a;
		restaurant[ a ] = 1;
	}

	// M 개 줄에 src -> dst
	// N 개 현금의 액수
	// src 시작점
	// P 레스토랑 갯수
	// P 개 레스토랑
}

void dfs( int here )
{
	visited[ here ] = 1;
	for ( auto there : G[ here ] )
	{
		if ( !visited[ there ] ) dfs( there );
	}

	st.push( here );
}

int g_start_scc;
int dfs_scc( int here )
{
	if ( here == g_start_scc )
	{
		return scc_accum[ here ] = scc_sum[ here ];
	}
	else if ( scc_accum[ here ] >= 0 )
	{
		return scc_accum[ here ];
	}

	int tmp = 0;
	for ( auto there : scc_G_rev[ here ] )
	{
		tmp = max( tmp, dfs_scc( there ) );
	}

	if ( tmp > 0 ) scc_accum[ here ] = scc_sum[ here ] + tmp;
	else scc_accum[ here ] = 0;

	return scc_accum[ here ];
}

void generate( int here, int cnt )
{
	visited[ here ] = 1;
	scc_mapping[ here ] = cnt;
	scc[ cnt ].push_back( here );
	for ( auto there : G_rev[ here ] )
	{
		if ( !visited[ there ] ) generate( there, cnt );
	}
}

inline void solve()
{
	memset( visited, 0, sizeof( visited ) );
	For( i, 1, N )
	{
		if ( !visited[ i ] ) dfs( i );
	}

	int cnt = 0;
	memset( visited, 0, sizeof( visited ) );
	while ( !st.empty() )
	{
		if ( !visited[ st.top() ] )
		{
			generate( st.top(), cnt++ );
		}
		st.pop();
	}

	// scc 간 그래프
	For( here, 1, N )
	{
		scc_sum[ scc_mapping[ here ] ] += score[ here ];
		if ( restaurant[ here ] ) scc_restaurant[ scc_mapping[ here ] ] = 1;

		for ( auto there : G[ here ] )
		{
			if ( scc_mapping[ here ] != scc_mapping[ there ] )
			{
				scc_G[ scc_mapping[ here ] ].insert( scc_mapping[ there ] );
				scc_G_rev[ scc_mapping[ there ] ].insert( scc_mapping[ here ] );
			}
		}
	}

	g_start_scc = scc_mapping[ src ];
	For2( i, 0, cnt ) scc_accum[ i ] = -1;
	For2( i, 0, cnt )
	{
		dfs_scc( i );
	}

	int ret = 0;
	For2( i, 0, cnt )
	{
		if ( scc_restaurant[ i ] )
			ret = max( ret, scc_accum[ i ] );
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

/*
6 7
1 2
2 3
3 5
2 4
4 1
2 6
6 5
10
12
8
16
1
5
1 4
4 3 5 6
*/