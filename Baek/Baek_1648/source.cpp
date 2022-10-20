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

int N, M;

inline void read()
{
	cin >> N >> M;
}

std::vector<int> dp_vec[ ( 1 << 14 ) ];
int dp_cnt[ ( 1 << 14 ) ];
int dp[ 14 ][ ( 1 << 14 ) ];

int dfs( int h, int arr )
{
	if ( dp[ h ][ arr ] != -1 )
		return dp[ h ][ arr ];

	if ( h == N - 1 )
	{
		return dp[ h ][ arr ] = dp_cnt[ arr ];
	}

	int ret = 0;
	for ( auto nxt : dp_vec[ arr ] )
	{
		ret += dfs( h + 1, nxt );
		ret %= 9901;
	}

	return dp[ h ][ arr ] = ret;
}

void generate( int here, int idx, int arr, int nxt )
{
	if ( idx == M )
	{
		dp_vec[ here ].push_back( nxt );
		return;
	}

	if ( arr & ( 1 << idx ) )
	{
		return generate( here, idx + 1, arr, nxt );
	}
	else
	{
		int tmp_arr = arr;
		tmp_arr |= ( 1 << idx );
		{
			int tmp_nxt = nxt;
			tmp_nxt |= ( 1 << idx );
			generate( here, idx + 1, tmp_arr, tmp_nxt );
		}

		if ( idx + 1 < M && !( arr & ( 1 << ( idx + 1 ) ) ) )
		{
			tmp_arr |= ( 1 << ( idx + 1 ) );
			generate( here, idx + 2, tmp_arr, nxt );
		}
	}
}

void generate_ret( int arr )
{
	int idx = 0;
	int tmp = arr;
	while ( idx < M )
	{
		if ( tmp & ( 1 << idx ) )
		{
			idx++;
		}
		else
		{
			if ( idx + 1 < M && !( arr & ( 1 << ( idx + 1 ) ) ) )
			{
				tmp |= ( 1 << idx );
				tmp |= ( 1 << ( idx + 1 ) );
			}
			idx += 2;
		}
	}

	if ( tmp + 1 == ( 1 << M ) )
	{
		dp_cnt[ arr ] = 1;
	}
	else
	{
		dp_cnt[ arr ] = 0;
	}
}

inline void solve()
{
	if ( M % 2 == 1 ) swap( N, M );
	if ( M % 2 == 1 )
	{
		cout << 0 << '\n';
		return;
	}

	// M 칸에 대해 만들수 있는거 싹 만들기
	For2( i, 0, ( 1 << M ) )
	{
		For2( j, 0, 14 ) dp[ j ][ i ] = -1;
		generate( i, 0, i, 0 );
		generate_ret( i );
	}

	int ret = dfs( 0, 0 );
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
