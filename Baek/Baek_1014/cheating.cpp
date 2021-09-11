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

int dp[ 11 ][ 2048 ] = { 0, };
int N, M;
string board[10];

inline void read()
{
	cin >> N >> M;
	For2( i, 0, N )
		cin >> board[ i ];
}

int dfs( int row, int val )
{
	if ( row == N )
		return dp[ row ][ val ] = 0;

	if ( dp[ row ][ val ] != -1 )
		return dp[ row ][ val ];

	int invalid = 0;

	for ( int bit = 1; bit < ( 1 << 10 ); bit *= 2 )
	{
		if ( val & bit )
		{
			int l = bit >> 1;
			int r = bit << 1;

			if ( l > 0 )
				invalid |= l;

			if ( r < 2048 )
				invalid |= r;
		}
	}

	for ( int m = 0; m < M; m++ )
	{
		if ( board[ row ][ m ] == 'x' )
		{
			invalid |= ( 1 << ( m ) );
		}
	}
	
	int ret = 0;
	for ( int i = 0; i < ( 1 << M ); i++ )
	{
		if ( i & invalid )
			continue;

		// i 가 두개 붙어잇는지 확인

		int cnt = 0;
		int tmp = i;
		bool flag = true;
		while ( tmp > 0 )
		{
			if ( ( tmp & 1 ) == 1 )
				cnt++;
			
			if ( ( tmp & 3 ) == 3 )
				flag = false;

			tmp /= 2;
		}
		if ( !flag )
			continue;

		ret = max( ret, cnt + dfs( row + 1, i ) );
	}

	return dp[ row ][ val ] = ret;
}

inline void solve()
{
	For( i, 0, 10 ) For2( j, 0, 2048 )
		dp[ i ][ j ] = -1;

	cout << dfs( 0, 0 ) << '\n';
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