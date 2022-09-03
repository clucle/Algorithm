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

const ll MYMOD = (ll)1e9 + 7;
const int MAX_N = (int)2e5 + 10;

const bool TEST_CASES = false;

inline void presolve()
{

}

int ccw( const pii& x, const pii& y )
{
	// 오른손잡기 +
	// ad - bc
	return x.first * y.second - x.second * y.first;
}

int dist_square( const pii& x, const pii& y )
{
	return ( x.first - y.first ) * ( x.first - y.first ) +
		( x.second - y.second ) * ( x.second - y.second );
}

int N;
vector<pii> v;
inline void read()
{
	cin >> N;
	v.resize( N );
	For2( i, 0, N )
	{
		cin >> v[ i ].first >> v[ i ].second;
	}
}

inline void solve()
{
	sort( v.begin(), v.end() );
	// 1. y 젤 작고 그중에 x 젤 작은게 v[0];

	pii base = v[ 0 ];
	auto iter = v.begin();
	iter++;
	sort( iter, v.end(), [base]( const pii& x, const pii& y )
		{
			pii xdir = { x.first - base.first, x.second - base.second };
			pii ydir = { y.first - base.first, y.second - base.second };
			int c = ccw( xdir, ydir );
			if ( c != 0 )
				return c > 0;

			int dx = dist_square( x, base );
			int dy = dist_square( y, base );

			return dx < dy;
		} );

	vector<pii> convex;
	convex.push_back( v[ 0 ] );
	convex.push_back( v[ 1 ] );

	// 맨첨에 점 두개를 넣고
	// 다음 점을 전전점, 전점, 점 이거 ccw 돌렸는데 오목하다?
	// 그럼 전점 빼고 다시 돌려
	For2( i, 2, N )
	{
		while ( convex.size() >= 2 )
		{
			int pprev = convex.size() - 2;
			int prev = convex.size() - 1;

			pii prevDir = {
				convex[ prev ].first - convex[ pprev ].first,
				convex[ prev ].second - convex[ pprev ].second
			};

			pii curDir = {
				v[ i ].first - convex[ pprev ].first,
				v[ i ].second - convex[ pprev ].second,
			};

			if ( ccw( prevDir, curDir ) <= 0 )
			{
				convex.pop_back();
			}
			else
			{
				break;
			}
		}
		convex.push_back( v[ i ] );
	}

	// 회전하는 캘리퍼스를 적용한다면??
	int sz = convex.size();
	int idx_l = 0;
	int idx_r = 0;
	For2( i, 0, sz )
	{
		if ( convex[ i ].second < convex[ idx_l ].second ) idx_l = i;
		if ( convex[ i ].second > convex[ idx_r ].second ) idx_r = i;
	}

	double ret = 0;
	int d = dist_square( convex[ idx_l ], convex[ idx_r ] );
	double tmp = sqrt( double( d ) );
	ret = max( ret, tmp );

	For( i, 0, sz )
	{
		pii ldir = {
			convex[ ( idx_l + 1 ) % sz ].first - convex[ idx_l ].first,
			convex[ ( idx_l + 1 ) % sz ].second - convex[ idx_l ].second
		};

		pii minus_rdir = {
			convex[ idx_r ].first - convex[ ( idx_r + 1 ) % sz ].first,
			convex[ idx_r ].second - convex[ ( idx_r + 1 ) % sz ].second
		};

		int c = ccw( ldir, minus_rdir );
		if ( c > 0 )
		{
			// r 이 더 많이 꺽이는 상태
			idx_l = ( idx_l + 1 ) % sz;
		}
		else
		{
			idx_r = ( idx_r + 1 ) % sz;
		}

		int d = dist_square( convex[ idx_l ], convex[ idx_r ] );
		double tmp = sqrt( double( d ) );
		ret = max( ret, tmp );
	}
	/*
	double ret = 0;
	int sz = convex.size();
	For2( i, 0, sz )
	{
		For2( j, i + 1, sz )
		{
			int d = dist_square( convex[ i ], convex[ j ] );
			double tmp = sqrt( double( d ) );
			ret = max( ret, tmp );
		}
	}
	*/
	cout.precision( 9 );
	cout << ret;
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
