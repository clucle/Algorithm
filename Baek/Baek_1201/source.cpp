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

struct q
{
	int a, b, c;
};

int N, M, K;

inline void read()
{
	cin >> N >> M >> K;
}

int arr[ 501 ];

inline void solve()
{
	int cur = 0;

	if ( N < M + K - 1 || N > M * K )
	{
		cout << -1;
		return;
	}

	For( i, 1, N ) arr[ i ] = i;

	int prev = 0;
	For( i, 1, M )
	{
		// 10 3 8
		// 이라고 하면
		// 8 7 6 5 4 3 2 1 , 9, 10

		// 맨처음에 prev 가 0 이었기때문에
		// prev + 1 ~ prev + K 가 최상인 상태
		// i 가 M 인 경우 적어도 1개 남아있어야함이 보장 
		// i 가 M - 1 인경우 적어도 2개 남아있어야함이 보장
		// (N - end + 1) >= ( M - i + 1)
		// end <= N - M + i - 1
		int start = prev + 1;
		int end = min( prev + K, N - M + i );
		reverse( arr + start, arr + end + 1 );
		prev = end;
	}

	For( i, 1, N ) cout << arr[ i ] << ' ';
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
