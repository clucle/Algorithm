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
struct BIT {
    int n;
    vector<T> tree;
    BIT(int n):n(n + 1),tree(n + 1){}
    void add(int x, T a) {
        for (; x <= n; x += x&-x) tree[x] += a;
    }
    T sum(int x) {
        T ret = 0;
        for (;x;x^=x&-x) ret += tree[x];
        return ret;
    }
    T rangeSum(int l, int r) {
        return(sum(r) - sum(l - 1));
    }
};
/* ----------------------------------------------------- */

const int SIZE = 1000100;
int n, m, k;
ll arr[SIZE];
vector<tuple<int,int,int>> query;

inline void read() {
    cin >> n >> m >> k;
    For(i, 1, n) cin >> arr[i];
    For(i, 1, m + k) {
        int a,b,c; cin >> a >> b >> c;
        query.pb({a,b,c}); 
    }
}

inline void solve() {
    BIT<ll> bit(n);
    For(i,1,n) bit.add(i, arr[i]);
    For(i, 0, m + k - 1) {
        int a = get<0>(query[i]);
        int b = get<1>(query[i]);
        int c = get<2>(query[i]);
        if (a==1) {
            ll diff = c - arr[b];
            arr[b] = c;
            bit.add(b,diff);
        } else {
            cout << bit.rangeSum(b,c) << '\n';
        }
    }
}

int main() {
	ios::sync_with_stdio( false );
	cin.tie( 0 ); cout.tie( 0 );
    cout.precision(10); cout << fixed;
    
    read();
    solve();

	return 0;
}