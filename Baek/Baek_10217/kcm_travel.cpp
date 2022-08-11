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

const bool TEST_CASES = true;

int N, M, K;

struct node
{
	node() {};
	node( int dst, int cost, int time ) : dst( dst ), cost( cost ), time( time ) {}

	int dst;
	int cost;
	int time;
};

class Compare1
{
public:
	bool operator()( node a, node b )
	{
		return a.time > b.time;
	}
};

map< int, vector< node > > G;

inline void read()
{
	cin >> N >> M >> K;
	G.clear();

	int src;
	For2( i, 0, K )
	{
		cin >> src;
		node n;
		cin >> n.dst >> n.cost >> n.time;
		G[ src ].emplace_back( n );
	}
}

int cur_time[ 101 ][ 10001 ];
std::priority_queue< node, std::vector< node >, Compare1 > pq;

inline void solve()
{
	For( i, 1, N ) For( j, 0, 10'000 ) cur_time[ i ][ j ] = 1'000'001;

	while ( !pq.empty() )
		pq.pop();
	pq.push( node( 1, 0, 0 ) );

	while ( !pq.empty() )
	{
		int here = pq.top().dst;
		int cost = pq.top().cost;
		int time = pq.top().time;
		pq.pop();

		if ( here == N )
		{
			cout << time << '\n';
			return;
		}

		if ( cur_time[ here ][ cost ] < time )
			continue;

		for ( auto& n : G[ here ] )
		{
			if ( n.cost + cost > M )
				continue;

			if ( cur_time[ n.dst ][ n.cost + cost ] <= n.time + time )
				continue;

			For( i, n.cost + cost, M )
			{
				if ( cur_time[ n.dst ][ i ] > n.time + time )
					cur_time[ n.dst ][ i ] = n.time + time;
			}

			pq.push( node( n.dst, n.cost + cost, n.time + time ) );
		}
	}

	cout << "Poor KCM\n";
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
