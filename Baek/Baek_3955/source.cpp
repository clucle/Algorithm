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

ll K, C;

inline void read()
{
	cin >> K >> C;
}

ll gcd( ll a, ll b )
{
	if ( b == 0 ) return a;
	return gcd( b, a % b );
}

// ax + by = g �϶� x, y ã��
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

inline void solve()
{
	// e1 = K * X + 1
	// X �δ� � �ٱ�?

	// e2 = C * Y
	// �� ����� ���?

	// e1 == e2

	if ( K == 1 )
	{
		// K �� 1�϶�
		// e1 = 1 * X + 1
		// e2 = C * Y
		// X + 1 = C * Y
		// ( X > 0 )
		// C * Y >= 2
		// Y �� 2�϶� C�� ������ ���� �� ���� 

		cout << 2 << '\n';
		return;
	}

	if ( C == 1 )
	{
		// C �� 1�϶�
		// e1 = K * X + 1
		// e2 = Y
		// K * X + 1 = Y;
		// X �� 1�̶�� �ϸ�
		// K + 1 = Y �� ������ ����
		if ( K + 1 > 1'000'000'000 )
		{
			cout << "IMPOSSIBLE\n";
			return;
		}
		cout << K + 1 << '\n';
		return;
	}

	gxy ret = xGcd( K, C );
	if ( ret.g > 1 )
	{
		cout << "IMPOSSIBLE\n";
		return;
	}

	if ( ret.y < 1 )
	{
		ll cnt = ret.y / K;
		ret.y += cnt * K;
		if ( ret.y < 1 ) ret.y += K;
	}

	if ( ret.y > 1'000'000'000 )
	{
		cout << "IMPOSSIBLE\n";
		return;
	}

	cout << ret.y << '\n';
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
