#define _CRT_SECURE_NO_DEPRECATE

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

/* ------------------- Custom clucle ------------------- */
/* ----------------------------------------------------- */

const ll MYMOD = 1'000'000'007;
const int MAX_N = 100'001;

const bool TEST_CASES = false;
const bool READ_FILE = false;

inline void presolve()
{
}

int N;
vector<pll> vertex;

inline void read()
{
	cin >> N;
	vertex.resize( N );
	For2( i, 0, N ) cin >> vertex[ i ].first >> vertex[ i ].second;
}

int ccw( pll v1, pll v2 )
{
	ll ccw = v1.first * v2.second - v1.second * v2.first;
	if ( ccw > 0 ) return 1;
	else if ( ccw < 0 ) return -1;
	return 0;
}

bool chk( pll point )
{
	int cnt = 0;
	For2( i, 0, N )
	{
		int j = ( i + 1 ) % N;
		pll p1 = vertex[ i ];
		pll p2 = vertex[ j ];

		// p1 의 y 좌표가 더 작음
		if ( p1.second > p2.second ) swap( p1, p2 );

		pll vp1 = { point.first - p1.first, point.second - p1.second };
		pll vp2 = { p2.first - point.first, p2.second - point.second };

		if ( ccw( vp1, vp2 ) == 0 )
		{
			// 선분 위의 점인지 확인
			if (
				min( p1.first, p2.first ) <= point.first && point.first <= max( p1.first, p2.first ) &&
				min( p1.second, p2.second ) <= point.second && point.second <= max( p1.second, p2.second ) )
				return true;
		}

		// p2 의 y 가 p1 보다 더 크거나 같은데 벗어남
		if ( p2.second <= point.second ) continue;
		// p1 의 y 가 p2 보다 작거나 같은데 벗어남
		if ( p1.second > point.second ) continue;

		// 시계방향이면 다각형 내부
		if ( ccw( vp1, vp2 ) < 0 ) cnt++;
	}

	return cnt % 2;
}

inline void solve()
{
	For( q, 1, 3 )
	{
		pll point;
		cin >> point.first >> point.second;

		if ( chk( point ) ) cout << 1 << '\n';
		else cout << 0 << '\n';
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
