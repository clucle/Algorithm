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
const int INF = 800;

const bool TEST_CASES = false;

int N, M;
int arr[ 100'010 ];
struct query
{
	int i, j, k;
};
vector< query > q;

inline void read()
{
	cin >> N;
	For( i, 1, N ) cin >> arr[ i ];
	cin >> M;
	q.resize( M );
	For2( i, 0, M )
	{
		cin >> q[ i ].i;
		cin >> q[ i ].j;
		cin >> q[ i ].k;
	}
}

vector< vector<int> > v;

vector< int >& build( int idx, int l, int r )
{
	if ( l == r )
	{
		v[ idx ] = { arr[ l ] };
		return v[ idx ];
	}

	int mid = l + ( r - l ) / 2;

	vector< int >& vl = build( idx * 2 + 0, l, mid );
	vector< int >& vr = build( idx * 2 + 1, mid + 1, r );

	int il = 0;
	int ir = 0;

	vector< int >& x = v[ idx ];
	x.resize( vl.size() + vr.size() );

	while ( true )
	{
		if ( il < vl.size() && ir < vr.size() )
		{
			if ( vl[ il ] < vr[ ir ] )
			{
				x[ il + ir ] = vl[ il ];
				il++;
			}
			else
			{
				x[ il + ir ] = vr[ ir ];
				ir++;
			}
		}
		else
		{
			break;
		}
	}

	while ( il < vl.size() )
	{
		x[ il + ir ] = vl[ il ];
		il++;
	}

	while ( ir < vr.size() )
	{
		x[ il + ir ] = vr[ ir ];
		ir++;
	}

	return x;
}

int ok( int idx, int start, int end, int l, int r, int k )
{
	// l r 안에 start end 가 포함되면
	if ( r < start || end < l ) return 0;

	if ( l <= start && end <= r )
	{
		vector< int >& tmp = v[ idx ];
		int cnt = tmp.size() - ( upper_bound( tmp.begin(), tmp.end(), k ) - tmp.begin() );
		return cnt;
	}

	int mid = start + ( end - start ) / 2;
	int ret =
		ok( idx * 2 + 0, start, mid, l, r, k ) +
		ok( idx * 2 + 1, mid + 1, end, l, r, k );
	return ret;
}

inline void solve()
{
	int h = log2( N );
	v.resize( h * N );
	build( 1, 1, N );

	for ( query& x : q )
	{
		int i = x.i;
		int j = x.j;
		int k = x.k;

		cout << ok( 1, 1, N, i, j, k ) << '\n';
	}
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