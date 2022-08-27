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

int N, Q;
int parent[ 200'010 ];
int cur[ 200'010 ];

struct q
{
	int a, b, c;
};
vector<q> querys;

inline void read()
{
	cin >> N >> Q;
	For( i, 2, N ) cin >> parent[ i ];
	querys.resize( N + Q );
	For2( i, 0, N + Q - 1 )
	{
		cin >> querys[ i ].a >> querys[ i ].b;
		if ( querys[ i ].a == 1 ) cin >> querys[ i ].c;
	}
}

int get_parent( int here )
{
	if ( cur[ here ] == here ) return here;
	return cur[ here ] = get_parent( cur[ here ] );
}

inline void solve()
{
	parent[ 1 ] = 1;
	For( i, 1, N ) cur[ i ] = parent[ i ];

	For2( i, 0, N + Q - 1 )
	{
		if ( querys[ i ].a == 0 )
		{
			// 부모 삭제
			cur[ querys[ i ].b ] = querys[ i ].b;
		}
	}

	stack<bool> ret;
	Rep( i, N + Q - 2, 0 )
	{
		if ( querys[ i ].a == 0 )
		{
			cur[ querys[ i ].b ] = parent[ querys[ i ].b ];
		}
		else
		{
			int pb = get_parent( querys[ i ].b );
			int pc = get_parent( querys[ i ].c );

			if ( pb == pc ) ret.push( 1 );
			else ret.push( 0 );
		}
	}

	while ( !ret.empty() )
	{
		cout << ( ret.top() ? "YES\n" : "NO\n" );
		ret.pop();
	}
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
