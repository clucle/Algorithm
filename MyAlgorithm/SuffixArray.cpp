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

#define DEBUG false

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;


const ll MYMOD = 1e9 + 7;
const int MAX_N = 5e5 + 7;

const bool TEST_CASES = false;

string s;

inline void pre()
{

}

inline void read()
{
	cin >> s;
}

int group[ MAX_N ];
int sa[ MAX_N ];
int tmp[ MAX_N ];
int lcp[ MAX_N ];
int d;

bool cmp( int l, int r )
{
	if ( group[ l ] == group[ r ] )
	{
		l += d;
		r += d;

		if ( l < s.size() && r < s.size() ) return group[ l ] < group[ r ];
		return l > r;
	}

	return group[ l ] < group[ r ];
}

void construct_sa()
{
	For2( i, 0, s.size() )
	{
		group[ i ] = s[ i ];
		sa[ i ] = i;
	}

	for ( d = 1; ; d *= 2 )
	{
		sort( sa, sa + s.size(), cmp );

		tmp[ 0 ] = 0;
		for ( int i = 0; i < s.size() - 1; i++ )
			tmp[ i + 1 ] = tmp[ i ] + cmp( sa[ i ], sa[ i + 1 ] );

		for ( int i = 0; i < s.size(); i++ )
			group[ sa[ i ] ] = tmp[ i ];

		if ( tmp[ s.size() - 1 ] == s.size() - 1 ) break;
	}
}

void construct_lcp()
{
	int N = s.size();
	int j, k = 0;
	for ( int i = 0; i < N; lcp[ group[ i++ ] ] = k )
	{
		k = max( k - 1, 0 );
		if ( group[ i ] < 1 )
			continue;

		for ( j = sa[ group[ i ] - 1 ]; s[ i + k ] == s[ j + k ]; k++ );
	}
}

inline void solve()
{
	construct_sa();
	construct_lcp();

	// 내가 이해 편하도록 메모
	// group -> key : idx,  value : rank
	// sa    -> key : 등수, value : idx

	For2( i, 0, s.size() )
		cout << sa[ i ] + 1 << ' ';
	cout << '\n';

	cout << 'x' << ' ';
	For2( i, 1, s.size() )
		cout << lcp[ i ] << ' ';
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