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

/* ------------------- Custom clucle ------------------- */
/* ----------------------------------------------------- */

const ll MYMOD = (ll)1e9 + 7;
const int MAX_N = (int)2e5 + 10;

const bool TEST_CASES = false;

inline void presolve()
{

}

// src = 1, src_n = 2, src_k = 3
// N ( 1001 ~ 2000 ) M ( 2001 ~ 3000 )
// dst = 3001

vector<int> Graph[ 3002 ];
int f[ 3002 ][ 3002 ] = { 0, };
int c[ 3002 ][ 3002 ] = { 0, };
int visited[ 3003 ];

int N, M, K;

inline void read()
{
	cin >> N >> M >> K;

	int cnt = 0;
	int x;
	For( i, 1, N )
	{
		cin >> cnt;
		For2( j, 0, cnt )
		{
			cin >> x;
			Graph[ i + 1000 ].push_back( x + 2000 );
			Graph[ x + 2000 ].push_back( i + 1000 );

			f[ i + 1000 ][ x + 2000 ] = K + 1;
		}
	}
}

inline void solve()
{
	// src �� �ϴ� ����
	int src = 1;
	int src_n = 2;
	int src_k = 3;
	int dst = 3001;

	// src_n �� ��� ������ 1�� ���Ҽ��ֵ��� �ϱ�
	Graph[ src ].push_back( src_n );
	Graph[ src_n ].push_back( src );
	f[ src ][ src_n ] = N;

	For( i, 1, N )
	{
		Graph[ src_n ].push_back( i + 1000 );
		Graph[ i + 1000 ].push_back( src_n );
		f[ src_n ][ i + 1000 ] = 1;
	}

	// src_k �� � �����̵� ���ļ� K ��ŭ ���Ҽ��ְ��ϱ�
	Graph[ src ].push_back( src_k );
	Graph[ src_k ].push_back( src );
	f[ src ][ src_k ] = K;

	For( i, 1, N )
	{
		Graph[ src_k ].push_back( i + 1000 );
		Graph[ i + 1000 ].push_back( src_k );
		f[ src_k ][ i + 1000 ] = K;
	}

	// dst ���� ��δ� �̾�����
	For( i, 1, M )
	{
		Graph[ i + 2000 ].push_back( dst );
		Graph[ dst ].push_back( i + 2000 );
		f[ i + 2000 ][ dst ] = 1;
	}

	// ���� ��������
	// src-> dst ���� �÷ο� �ƽ� ã��

	int ret = 0;
	while ( true )
	{
		memset( visited, 0, sizeof( visited ) );
		queue<int> q;
		q.push( src );

		while ( !q.empty() )
		{
			int here = q.front();
			q.pop();

			for ( auto there : Graph[ here ] )
			{
				// here ���� there �� ���� �ִ�?
				if ( visited[ there ] ) continue;
				if ( f[ here ][ there ] - c[ here ][ there ] <= 0 ) continue;


				// �θ� ��������
				visited[ there ] = here;
				q.push( there );

				if ( there == dst )
				{
					while ( !q.empty() ) q.pop();
					break;
				}
			}
		}

		// �� ���Ҵ��� dst �� �������ϸ� ��
		if ( !visited[ dst ] ) break;

		int cur = dst;
		int cost = N + K;
		// �ϴ� �� ���� cost ã��
		for ( ; cur != src; cur = visited[ cur ] )
		{
			int prev = visited[ cur ];
			cost = min( cost, f[ prev ][ cur ] - c[ prev ][ cur ] );
		}

		// �������
		cur = dst;
		for ( ; cur != src; cur = visited[ cur ] )
		{
			int prev = visited[ cur ];
			c[ prev ][ cur ] += cost;
			c[ cur ][ prev ] -= cost;
		}

		ret += cost;
	}

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
