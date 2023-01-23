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

int N;
int arr[ 100'001 ];
int ret[ 100'001 ] = { 0, };

inline void presolve()
{
}

inline void read()
{
	cin >> N;
	For( i, 1, N ) cin >> arr[ i ];
	For( i, 1, N ) arr[ i ]++;
}

int tree[ 400'004 ];

int get( int node, int l, int r, int start, int end )
{
	if ( start <= l && r <= end ) return tree[ node ];
	if ( end < l || r < start ) return 0;

	int mid = l + ( r - l ) / 2;
	return
		get( node * 2, l, mid, start, end ) +
		get( node * 2 + 1, mid + 1, r, start, end );
}

void add( int node, int l, int r, int pos )
{
	if ( pos < l || r < pos ) return;

	tree[ node ] += 1;

	if ( l == r ) return;
	int mid = l + ( r - l ) / 2;
	add( node * 2, l, mid, pos );
	add( node * 2 + 1, mid + 1, r, pos );
}

inline void solve()
{
	For( i, 1, N )
	{
		int l = 1;
		int r = N;

		// arr[i] 로 내자리까지 1이 있어야 된다고 생각해보자

		while ( true )
		{
			int mid = l + ( r - l ) / 2;

			// 남은자리
			int cnt = mid - 1 - get( 1, 1, N, 1, mid - 1 );

			if ( ret[ mid ] > 0 )
			{
				if ( arr[ i ] > cnt )
				{
					l = mid + 1;
				}
				else
				{
					r = mid - 1;
				}
			}
			else
			{
				cnt++;
				if ( arr[ i ] > cnt )
				{
					l = mid + 1;
				}
				else if ( arr[ i ] == cnt )
				{
					ret[ mid ] = i;
					add( 1, 1, N, mid );
					break;
				}
				else
				{
					r = mid;
				}
			}
		}
	}

	For( i, 1, N ) cout << ret[ i ] << '\n';
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
