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
#define For(i, j, k) for (int i = (int)(j); i <= (k); i++)
#define Rep(i, j, k) for (int i = (int)(j); i >= (k); i--)
#define For2(i, j, k) for (int i = (int)(j); i < (k); i++)
#define Rep2(i, j, k) for (int i = (int)(j); i > (k); i--)

#define mp make_pair
#define sz(a) int((a).size())
#define all(c) (c).begin(), (c).end()
#define forit(it, S) for (__typeof(S.begin()) it = S.begin(); it != S.end(); ++it)

#define vi vector<int>

#define DEBUG true

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

/* ------------------- Custom clucle ------------------- */
/* ----------------------------------------------------- */

const ll MYMOD = 1e9 + 7;
const int MAX_N = 5e5 + 10;

const bool TEST_CASES = false;

int N;
int arr[ MAX_N ];

struct node
{
    node() {};
    node( int value ) : value( value ), lazy( 0 ), flag( false ) {};
    int value;
    int lazy;
    bool flag;
};

vector<node> tree;

node build( int cur, int start, int end )
{
    if ( start == end )
    {
        tree[ cur ] = node( arr[ start ] );
        return tree[ cur ];
    }

    int mid = start + ( end - start ) / 2;
    node l = build( cur * 2, start, mid );
    node r = build( cur * 2 + 1, mid + 1, end );
    return tree[ cur ] = node( l.value ^ r.value );
}

int get( int cur, int start, int end, int l, int r )
{
    if ( tree[ cur ].flag )
    {
        if ( start != end )
        {
            tree[ cur * 2 ].flag = true;
            tree[ cur * 2 ].lazy ^= tree[ cur ].lazy;

            tree[ cur * 2 + 1 ].flag = true;
            tree[ cur * 2 + 1 ].lazy ^= tree[ cur ].lazy;
        }

        if ( ( end - start + 1 ) % 2 )
            tree[ cur ].value ^= tree[cur].lazy;

        tree[ cur ].flag = false;
        tree[ cur ].lazy = 0;
    }

    if ( l <= start && end <= r )
    {
        return tree[ cur ].value;
    }

    int mid = start + ( end - start ) / 2;
    int ret = 0;
    if ( l <= mid )
        ret ^= get( cur * 2, start, mid, l, min( mid, r ) );
    if ( mid + 1 <= r )
        ret ^= get( cur * 2 + 1, mid + 1, end, max( l, mid + 1 ), r );
    return ret;
}

void update( int cur, int start, int end, int l, int r, int val )
{
    if ( l <= start && end <= r )
    {
        tree[ cur ].flag = true;
        tree[ cur ].lazy ^= val;
        return;
    }

    int mid = start + ( end - start ) / 2;
    if ( l <= mid )
        update( cur * 2, start, mid, l, min( mid, r ), val );
    if ( mid + 1 <= r )
        update( cur * 2 + 1, mid + 1, end, max( l, mid + 1 ), r, val );

    int cnt = ( r - l + 1 ) % 2;
    if ( cnt )
    {
        tree[ cur ].value ^= val;
    }
}

inline void read()
{
    cin >> N;
    arr[ 0 ] = 0;
    For( i, 1, N ) cin >> arr[ i ];
}

void print()
{
    for ( int i = 1; i <= 15; i++ ) cout << tree[ i ].value <<' ';
}

inline void solve()
{
    int h = log2( N ) + 1;
    int sz = ( 1 << ( h + 1 ) );

    tree.resize( sz );
    build( 1, 1, N );

    int M; cin >> M;
    while ( M-- )
    {
        int op; cin >> op;
        int i, j, k; cin >> i >> j;
        if ( op == 1 )
        {
            cin >> k;
            update( 1, 1, N, i + 1, j + 1, k );
            // print();
        }
        else if ( op == 2 )
        {
            cout << get( 1, 1, N, i + 1, j + 1 ) <<'\n';
        }
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