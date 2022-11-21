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

template <class T>
struct BIT
{
	int n;
	vector<T> tree;
	BIT( int n ) :n( n + 1 ), tree( n + 1 ) {}
	void add( int x, T a )
	{
		for ( ; x < n; x += x & -x )
		{
			tree[ x ] += a;
		}
	}
	T sum( int x )
	{
		T ret = 0;
		for ( ; x; x ^= x & -x ) ret += tree[ x ];
		return ret;
	}
	T rangeSum( int l, int r )
	{
		return( sum( r ) - sum( l - 1 ) );
	}
};

/* ------------------- Custom clucle ------------------- */
/* ----------------------------------------------------- */

const ll MYMOD = 1'000'000'007;
const int MAX_N = 30'002;

const bool TEST_CASES = false;

bool isValid( int r, int c )
{
	if ( r < 0 || r > 3 || c < 0 || c > 3 ) return false;
	return true;
}

inline void presolve()
{
}

int N;
int arr[ 500001 ];
inline void read()
{
	cin >> N;
	For( i, 1, N ) cin >> arr[ i ];
}

//////////////////////////
//                      //
// 2 4 1 2 2 5 1        //
// 0 1 1 2 2 3 1        //
//                      //
// 2 4 2 2 1 2 2 5 1    //
// 0 1 1 2 1 4 4 5 1    //
//                      //
// 3 3 3 2 1 1 1 1 1 4  //
//                      //
//                      //
// 1 1 1 2 3 3 3 3 3    //
//                      //
//                      //
//////////////////////////
/// 
/// 오름 차순 으로 냅두다가
/// 큰게 나오면??
/// 예를 들면  3 ... 2 ... 여기서 1이 나왔을때
/// 예를 들면  4 ... 3 ... 2... 여기서 3이 나왔을 때 

int tmp[ 500001 ];
std::map<int, int> m;
inline void solve()
{
	For( i, 1, N ) tmp[ i ] = arr[ i ];
	sort( tmp + 1, tmp + N + 1 );

	int cur = tmp[ 1 ];
	int idx = 1;
	m[ cur ] = 1;
	For( i, 2, N )
	{
		if ( tmp[ i ] == cur ) continue;
		idx++;
		cur = tmp[ i ];
		m[ cur ] = idx;
	}

	For( i, 1, N ) arr[ i ] = m[ arr[ i ] ];

	////////////////////
	BIT<int> bit( N );

	ll cnt = 0;
	priority_queue<int> pq;
	pq.push( -arr[ 1 ] );
	bit.add( arr[ 1 ], 1 );
	int curMax = arr[ 1 ];
	For( i, 2, N )
	{
		// 이 사이즈를
		// 세그트리로 바꿔야할덧?
		ll ok = 0;
		ok = bit.sum( arr[ i ] );

		while ( !pq.empty() && -pq.top() < arr[ i ] )
		{
			bit.add( -pq.top(), -1 );
			pq.pop();
		}

		if ( curMax > arr[ i ] )
		{
			ok++;
		}
		else
		{
			curMax = arr[ i ];
		}

		cnt += ok;

		pq.push( -arr[ i ] );
		bit.add( arr[ i ], 1 );

	}
	cout << cnt;
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
