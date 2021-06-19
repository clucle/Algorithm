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

/* ----------------------------------------------------- */

/* ----------------------------------------------------- */

const ll MYMOD = 1e9 + 7;
const int MAX_N = 5e5 + 7;

const bool TEST_CASES = false;

inline void pre()
{
	return;
}

using LineSegment = pair< pll, pll >;

int ccw( ll x1, ll y1, ll x2, ll y2, ll x3, ll y3 )
{
	/*
	| x1 y1 1 |
	| x2 y2 1 |
	| x3 y3 1 |
	 = ( x1 * y2 ) + ( x2 * y3 ) + ( x3 * y1 ) -
	   ( x2 * y1 ) - ( x3 * y2 ) - ( x1 * y3 )
	*/

	ll tmp =
		( x1 * y2 ) + ( x2 * y3 ) + ( x3 * y1 ) -
		( x2 * y1 ) - ( x3 * y2 ) - ( x1 * y3 );

	if ( tmp > 0 )
		return 1;
	else if ( tmp < 0 )
		return -1;

	return 0;
}

bool isInterSect( const LineSegment& ls1, const LineSegment& ls2 )
{
	int ccw1 =
		ccw( ls1.first.first, ls1.first.second, ls1.second.first, ls1.second.second, ls2.first.first, ls2.first.second ) *
		ccw( ls1.first.first, ls1.first.second, ls1.second.first, ls1.second.second, ls2.second.first, ls2.second.second );

	int ccw2 =
		ccw( ls2.first.first, ls2.first.second, ls2.second.first, ls2.second.second, ls1.first.first, ls1.first.second ) *
		ccw( ls2.first.first, ls2.first.second, ls2.second.first, ls2.second.second, ls1.second.first, ls1.second.second );

	if ( ccw1 == 0 && ccw2 == 0 )
	{
		return ls1.first <= ls2.second && ls2.first <= ls1.second;
	}

	return ccw1 <= 0 && ccw2 <= 0;
}



inline void read()
{

}

inline void solve()
{
	int x1, y1, x2, y2, x3, y3, x4, y4;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

	LineSegment ls1 = { {x1, y1}, {x2, y2} };
	LineSegment ls2 = { {x3, y3}, {x4, y4} };

	if ( ls1.first > ls1.second )
		swap( ls1.first, ls1.second );

	if ( ls2.first > ls2.second )
		swap( ls2.first, ls2.second );

	if ( ls1 > ls2 )
		swap( ls1, ls2 );

	if ( isInterSect( ls1, ls2 ) )
		cout << 1 << '\n';
	else
		cout << 0 << '\n';
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
