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

#define DEBUG false

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;


const ll MYMOD = 1e9 + 7;
const int MAX_N = 1e5 + 7;

const bool TEST_CASES = false;

inline void pre()
{
}

int N;
vector<pii> v[ MAX_N ];

int Q;
vector<pii> query;

inline void read()
{
	cin >> N;
	For2( i, 1, N )
	{
		int A, B, C;
		cin >> A >> B >> C;
		v[ A ].push_back( { B, C } );
		v[ B ].push_back( { A, C } );
	}

	cin >> Q;
	query.resize( Q );
	For2( i, 0, Q )
	{
		cin >> query[ i ].first >> query[ i ].second;
	}
}

int visited[ MAX_N ] = { 0, };
int parent[ MAX_N ][ 22 ] = { 0, };
int level[ MAX_N ] = { 0, };
int min_dist[ MAX_N ][ 22 ] = { 0, };
int max_dist[ MAX_N ][ 22 ] = { 0, };

inline void solve()
{
	visited[ 1 ] = 1;
	parent[ 1 ][ 0 ] = 0;

	queue<pii> q;
	q.push( { 1,1 } );
	while ( !q.empty() )
	{
		int here = q.front().first;
		int lev = q.front().second;

		level[ here ] = lev;
		q.pop();

		for ( const auto& e : v[ here ] )
		{
			int there = e.first;
			int dist = e.second;

			if ( !visited[ there ] )
			{
				visited[ there ] = 1;
				parent[ there ][ 0 ] = here;
				min_dist[ there ][ 0 ] = dist;
				max_dist[ there ][ 0 ] = dist;
				q.push( { there, lev + 1 } );
			}
		}
	}

	for ( int i = 1; i < 22; i++ )
	{
		for ( int j = 1; j <= N; j++ )
		{
			min_dist[ j ][ i ] = min( min_dist[ j ][ i - 1 ], min_dist[ parent[ j ][ i - 1 ] ][ i - 1 ] );
			max_dist[ j ][ i ] = max( max_dist[ j ][ i - 1 ], max_dist[ parent[ j ][ i - 1 ] ][ i - 1 ] );
			parent[ j ][ i ] = parent[ parent[ j ][ i - 1 ] ][ i - 1 ];
		}
	}

	for ( const auto& e : query )
	{
		int a = e.first;
		int b = e.second;

		if ( level[ a ] < level[ b ] ) swap( a, b );
		int cnt = 0;
		int diff = level[ a ] - level[ b ];

		int _min = INT_MAX;
		int _max = 0;

		if ( diff > 0 )
		{
			while ( diff > 0 )
			{
				if ( diff % 2 == 1 )
				{
					_min = min( _min, min_dist[ a ][ cnt ] );
					_max = max( _max, max_dist[ a ][ cnt ] );
					a = parent[ a ][ cnt ];
				}

				diff /= 2;
				cnt++;
			}
		}

		while ( a != b )
		{
			for ( int k = 21; k >= 0; k-- )
			{
				if ( parent[ a ][ k ] != 0
					&& parent[ b ][ k ] != 0
					&& parent[ a ][ k ] != parent[ b ][ k ] )
				{
					_min = min( _min, min_dist[ a ][ k ] );
					_min = min( _min, min_dist[ b ][ k ] );
					_max = max( _max, max_dist[ a ][ k ] );
					_max = max( _max, max_dist[ b ][ k ] );
					a = parent[ a ][ k ];
					b = parent[ b ][ k ];
					break;
				}
			}
			if ( a == b ) break;

			_min = min( _min, min_dist[ a ][ 0 ] );
			_min = min( _min, min_dist[ b ][ 0 ] );
			_max = max( _max, max_dist[ a ][ 0 ] );
			_max = max( _max, max_dist[ b ][ 0 ] );

			a = parent[ a ][ 0 ];
			b = parent[ b ][ 0 ];
		}
		cout << _min << ' ' << _max << '\n';

	}

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