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
using namespace std;

#define ft first
#define sc second
#define re return
#define pb push_back
#define For(i,j,k) for (int i=(int)(j);i<=(k);i++)
#define For2(i,j,k) for (int i=(int)(j);i<(k);i++)
#define Rep(i,j,k) for (int i=(int)(j);i>=(k);i--)

#define mp make_pair
#define sz(a) int((a).size())
#define all(c) (c).begin(),(c).end()
#define forit(it,S) for(__typeof(S.begin()) it = S.begin(); it != S.end(); ++it)

#define DEBUG true

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

template <class T>
struct BIT
{
    int n;
    vector<T> tree;
    BIT( int n ) :n( n + 1 ), tree( n + 1 ) {}
    void add( int x, T a )
    {
        for ( ; x < n; x += x & -x ) tree[ x ] += a;
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
/* ----------------------------------------------------- */

const int SIZE = 500100;
int n, k;
int arr[ SIZE ];

inline void read()
{
    cin >> n >> k;
    For( i, 1, n )
    {
        cin >> arr[ i ];
        arr[ i ]++;
    }
}

inline void solve()
{
    BIT<ll> bit( 65536 );
    ll ret = 0;

    For2( i, 1, k )
    {
        bit.add( arr[ i ], 1 );
    }

    int idx = ( k + 1 ) / 2;

    For( i, k, n )
    {
        bit.add( arr[ i ], 1 );

        int l = 0;
        int r = 65536;
        while ( l < r )
        {
            int mid = ( l + r ) / 2;
            ll sum = bit.sum( mid );
            if ( sum >= idx ) r = mid;
            else l = mid + 1;
        }

        // cout << r << '\n';

        ret += r;
        ret--;
        bit.add( arr[ i - k + 1 ], -1 );
    }

    cout << ret;
}

int main()
{
    ios::sync_with_stdio( false );
    cin.tie( 0 ); cout.tie( 0 );
    cout.precision( 10 ); cout << fixed;

    read();
    solve();

    return 0;
}