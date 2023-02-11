#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cmath>
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
#include <functional>

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

inline int log2i( int x )
{
	int log2Val = 0;
	while ( x >>= 1 ) log2Val++;
	return log2Val;
}

int powi( int x, int cnt )
{
	if ( cnt == 0 ) return 1;
	if ( cnt == 1 ) return x;

	int ret = 1;
	if ( cnt % 2 == 1 ) ret *= x;
	int child = powi( x, cnt / 2 );
	ret *= child;
	ret *= child;
	return ret;
}

int ccw( pll v1, pll v2 )
{
	ll ccw = v1.first * v2.second - v1.second * v2.first;
	if ( ccw > 0 ) return 1;
	else if ( ccw < 0 ) return -1;
	return 0;
}

/* ------------------- Custom clucle ------------------- */
/* ----------------------------------------------------- */

const ll MYMOD = 1'000'000'007;
const int MAX_N = 100'001;

const bool TEST_CASES = false;
const bool READ_FILE = false;

inline void presolve()
{
}

int N, M, K;
vector<pll> polygon1;
vector<pll> polygon2;

inline void read()
{
	cin >> N >> M >> K;
	polygon1.resize( N );
	polygon2.resize( M );
	For2( i, 0, N ) cin >> polygon1[ i ].first >> polygon1[ i ].second;
	For2( i, 0, M ) cin >> polygon2[ i ].first >> polygon2[ i ].second;
}

pll GetAtoB( pll a, pll b )
{
	return { b.first - a.first, b.second - a.second };
}

bool IsInside( const vector<pll>& convex, pll point )
{
	int l = 1;
	int r = convex.size() - 1;

	pll v_l = GetAtoB( convex[ 0 ], convex[ l ] );
	pll v_r = GetAtoB( convex[ 0 ], convex[ r ] );

	pll v_point = GetAtoB( convex[ 0 ], point );
	if ( ccw( v_l, v_point ) <= 0 ) return false;
	if ( ccw( v_r, v_point ) >= 0 ) return false;

	while ( l + 1 < r )
	{
		int mid = l + ( r - l ) / 2;

		pll v_mid = GetAtoB( convex[ 0 ], convex[ mid ] );

		int _ccw = ccw( v_mid, v_point );
		if ( _ccw == 0 )
		{
			if ( abs( v_point.first ) < abs( v_mid.first ) || abs( v_point.second ) < abs( v_mid.second ) ) return true;
			return false;
		}
		else if ( _ccw > 0 ) // 반시계에 있다네
		{
			l = mid;
		}
		else // 시계에 있다네
		{
			r = mid;
		}
	}

	v_l = GetAtoB( convex[ l ], point );
	v_r = GetAtoB( point, convex[ l + 1 ] );

	return ccw( v_l, v_r ) < 0;

}

inline void solve()
{
	int ret = 0;
	while ( K-- )
	{
		ll x, y;
		cin >> x >> y;

		if ( !IsInside( polygon1, { x,y } ) || IsInside( polygon2, { x,y } ) )
			ret++;
	}
	if ( ret == 0 ) cout << "YES";
	else cout << ret;
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
	if ( READ_FILE )
		freopen( "D:\\test.txt", "r", stdin );
	if ( TEST_CASES )
		cin >> t;
	while ( t-- )
	{
		read();
		solve();
	}

	return 0;
}
