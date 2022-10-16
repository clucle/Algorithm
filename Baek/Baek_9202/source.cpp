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

struct Tree
{
	char me;
	int cnt = 0;
	bool isLeaf = false;
	int height;
	Tree* subtree[ 26 ];
};

void insert( Tree* t, string s )
{
	char cur = s[ 0 ] - 'A';
	if ( !t->subtree[ cur ] )
	{
		t->subtree[ cur ] = new Tree();
		t->subtree[ cur ]->me = s[ 0 ];
	}

	string next = s.substr( 1 );

	if ( s.size() == 1 )
	{
		t->subtree[ cur ]->isLeaf = true;
		return;
	}

	insert( t->subtree[ cur ], next );
}

int w;
Tree g_tree;

inline void read()
{
	/*
	ifstream is( "input.txt" );

	is >> w;
	For( i, 1, w )
	{
		string s; is >> s;
		insert( &g_tree, s );
	}
	*/

	cin >> w;
	For( i, 1, w )
	{
		string s; cin >> s;
		insert( &g_tree, s );
	}
}

Tree* getSubTree( Tree* tree, char c )
{
	if ( !tree ) return nullptr;
	int idx = c - 'A';
	return tree->subtree[ idx ];
}

string board[ 4 ];
bool visited[ 4 ][ 4 ];
int rDiff[ 8 ] = { -1,-1,-1,0,0,1,1,1 };
int cDiff[ 8 ] = { -1,0,1,-1,1,-1,0,1 };
int scoreMap[ 9 ] = { 0,0,0,1,1,2,3,5,11 };

set<string> ret;

void func( int r, int c, int cnt, string s, Tree* tree )
{
	cnt++;
	Tree* subTree = getSubTree( tree, board[ r ][ c ] );
	if ( !subTree )
	{
		return;
	}

	s += board[ r ][ c ];
	if ( subTree->isLeaf )
	{
		ret.insert( s );
	}

	if ( cnt == 8 )
	{
		return;
	}

	For( d, 0, 7 )
	{
		int _r = r + rDiff[ d ];
		int _c = c + cDiff[ d ];
		if ( !isValid( _r, _c ) || visited[ _r ][ _c ] ) continue;

		visited[ r ][ c ] = 1;
		func( _r, _c, cnt, s, subTree );
		visited[ r ][ c ] = 0;
	}
}

inline void solve()
{
	int b;
	cin >> b;
	while ( b-- )
	{
		cin >> board[ 0 ];
		cin >> board[ 1 ];
		cin >> board[ 2 ];
		cin >> board[ 3 ];

		ret.clear();

		For( r, 0, 3 ) For( c, 0, 3 )
		{
			func( r, c, 0, "", &g_tree );
		}

		int score = 0;
		int count = 0;
		string s = "";
		for ( auto e : ret )
		{
			count++;
			score += scoreMap[ e.size() ];
			if ( s.size() < e.size() ) s = e;
			else if ( s.size() == e.size() && s > e ) s = e;
		}

		cout << score << ' ' << s << ' ' << count << '\n';
	}
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
