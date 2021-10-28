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
struct Trie
{
	char c;
	static inline char const base = 'a';
	static inline int const sz = 26;
	bool end;
	Trie* next[ sz ];

	Trie()
	{
		end = false;
		memset( next, 0, sizeof( next ) );
	}

	~Trie()
	{
		For2( i, 0, sz )
			if ( next[ i ] != NULL ) delete next[ i ];
	}

	void insert( string s )
	{
		if ( s.size() == 0 )
		{
			end = true;
			return;
		}

		if ( next[ s[ 0 ] - base ] == NULL )
		{
			next[ s[ 0 ] - base ] = new Trie();
		}
		next[ s[ 0 ] - base ]->insert( s.substr( 1 ) );
	}

	int get( string s, bool first )
	{
		if ( s.size() == 0 )
			return 0;

		bool pass = true;
		For2( i, 0, sz )
		{
			if ( i == s[ 0 ] - base )
				continue;

			if ( next[ i ] != NULL )
				pass = false;
		}

		if ( end )
			pass = false;

		if ( first )
			pass = false;

		return next[ s[ 0 ] - base ]->get( s.substr( 1 ), false ) + ( pass ? 0 : 1 );
	}
};
/* ----------------------------------------------------- */

const ll MYMOD = 1e9 + 7;
const int MAX_N = 1e5 + 10;

const bool CIN_UNTIL_EOF = true;
const bool TEST_CASES = false;

inline void pre()
{
}

int N;
vector<string> v;

inline void read()
{
	cin >> N;
	v.resize( N );
	For2( i, 0, N )
		cin >> v[ i ];
}

inline void solve()
{
	Trie* trie = new Trie();

	For2( i, 0, N )
		trie->insert( v[ i ] );

	ll ret = 0;
	For2( i, 0, N )
	{
		ll a = trie->get( v[ i ], true );
		ret += a;
	}

	delete trie;

	cout << (double)( ret ) / (double)( N ) << '\n';
}

int main()
{
	ios::sync_with_stdio( false );
	cin.tie( 0 ); cout.tie( 0 );
	cout.precision( 2 ); cout << fixed;

	pre();

	int t = 1;
	if ( CIN_UNTIL_EOF )
	{
		while ( true )
		{
			read();
			solve();

			if ( cin.eof() )
				break;
		}
	}
	else
	{
		if ( TEST_CASES ) cin >> t;
		while ( t-- )
		{
			read();
			solve();
		}
	}

	return 0;
}