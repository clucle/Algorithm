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

using namespace std;

#define ft first
#define sc second
#define re return
#define pb push_back
#define For(i,j,k) for (int i=(int)(j);i<=(k);i++)
#define Rep(i,j,k) for (int i=(int)(j);i>=(k);i--)
#define For2(i,j,k) for (int i=(int)(j);i<(k);i++)
#define Rep2(i,j,k) for (int i=(int)(j);i>(k);i--)

#define mp make_pair
#define sz(a) int((a).size())
#define all(c) (c).begin(),(c).end()
#define forit(it,S) for(__typeof(S.begin()) it = S.begin(); it != S.end(); ++it)

#define vi vector<int> 

#define DEBUG true

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

/* ------------------- Custom clucle ------------------- */
/* ----------------------------------------------------- */

const ll MYMOD = 1e9 + 7;
const int MAX_N = 1e5 + 10;

const bool TEST_CASES = true;

inline void pre()
{
}

int N, M;
vector<int> v[ MAX_N ];
vector<int> rv[ MAX_N ];

inline void read()
{
	For( i, 0, N )
	{
		v[ i ].clear();
		rv[ i ].clear();
	}

	cin >> N >> M;
	For( i, 1, M )
	{
		int x, y; cin >> x >> y;
		v[ x ].pb( y );
		rv[ y ].pb( x );
	}
}

int visited[ MAX_N ];
stack<int> s;
vector<int> scc[ MAX_N ];
int rscc[ MAX_N ];
int in[ MAX_N ];

void dfs( int here )
{
	visited[ here ] = 1;
	for ( auto there : v[ here ] )
	{
		if ( visited[ there ] )
			continue;
		dfs( there );
	}
	s.push( here );
}

void generate( int here, int cnt )
{
	visited[ here ] = 1;
	scc[ cnt ].pb( here );
	for ( auto there : rv[ here ] )
	{
		if ( visited[ there ] )
			continue;
		generate( there, cnt );
	}
}

inline void solve()
{
	memset( visited, 0, sizeof( int ) * ( N + 1 ) );

	For( i, 1, N )
		if ( !visited[ i ] ) dfs( i );

	memset( visited, 0, sizeof( int ) * ( N + 1 ) );

	int cnt = 0;
	while ( !s.empty() )
	{
		int here = s.top();
		s.pop();

		if ( !visited[ here ] )
		{
			generate( here, cnt++ );
		}
	}

	for ( int i = 0; i < cnt; i++ )
	{
		for ( auto e : scc[ i ] )
		{
			rscc[ e ] = i;
		}
	}

	memset( in, 0, sizeof( in ) );
	For( here, 1, N )
	{
		for ( auto there : v[ here ] )
		{
			if ( rscc[ here ] != rscc[ there ] )
			{
				in[ rscc[ there ] ]++;
			}
		}
	}

	int ret = 0;
	for ( int i = 0; i < cnt; i++ )
	{
		if ( !in[ i ] )
			ret++;

		scc[ i ].clear();
	}

	cout << max( ret, 1 ) << '\n';

}

int main()
{
	ios::sync_with_stdio( false );
	cin.tie( 0 ); cout.tie( 0 );
	cout.precision( 2 ); cout << fixed;

	pre();

	int t = 1;
	if ( TEST_CASES ) cin >> t;
	while ( t-- )
	{
		read();
		solve();
	}

	return 0;
}