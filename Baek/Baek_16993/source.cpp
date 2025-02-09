#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cmath>
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
#include <iomanip>
#include <functional>

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

const bool TEST_CASES = false;
const bool READ_FILE = false;


struct Point {
	int x;
	int y;
	ll weight;
};

struct SegItem {
	ll all = 0;
	ll left = 0;
	ll right = 0;
	ll mid = 0;


	const SegItem operator+(const SegItem& si) const {
		SegItem ret;
		ret.all = all + si.all;
		ret.left = max(all + si.left, left);
		ret.right = max(right + si.all, si.right);
		ret.mid = max(max(mid, si.mid), right + si.left);
		return ret;
	}

	static const SegItem Base;
};

const SegItem SegItem::Base = {
	-1000000000,
	-1000000000,
	-1000000000,
	-1000000000,
};

template<typename T>
struct SegTree {

	vector<T> tree;
	vector<T> arr;

	int N;

private:
	const T& build(int n, int l, int r) {
		if (l == r) {
			tree[n] = arr[l];
			return tree[n];
		}

		int mid = l + (r - l) / 2;
		const T& lnode = build(2 * n + 1, l, mid);
		const T& rnode = build(2 * n + 2, mid + 1, r);
		tree[n] = lnode + rnode;
		return tree[n];
	}

	T _query(int n, int start, int end, int l, int r) {
		if (r < start || end < l) {
			return T::Base;
		}

		if (l <= start && end <= r) {
			return tree[n];
		}

		int mid = start + (end - start) / 2;
		const T& lnode = _query(2 * n + 1, start, mid, l, r);
		const T& rnode = _query(2 * n + 2, mid + 1, end, l, r);
		return lnode + rnode;
	}

public:

	SegTree(const vector<T> a): arr(a) {
		N = a.size();
		tree.resize(4 * N);
		build(0, 0, N - 1);
	}

	T query(int l, int r) {
		return _query(0, 0, N - 1, l, r);
	}
};

int N;
ll arr[100001];
inline void read()
{
	cin >> N;
	For2(i, 0, N) cin >> arr[i];
}

inline void solve()
{
	vector<SegItem> v;
	v.resize(N);
	For2(i, 0, N) {
		v[i] = {
			arr[i], arr[i], arr[i], arr[i]
		};
	}
	SegTree<SegItem> t(v);

	int M;
	cin >> M;
	int l, r;
	while (M--) {
		cin >> l >> r;
		const SegItem node = t.query(l - 1, r - 1);

		cout << max(max(node.left, node.right), node.mid) << '\n';
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cout.precision(8);
	cout << fixed;

	int t = 1;
	if (READ_FILE)
		freopen("D:\\test.txt", "r", stdin);
	if (TEST_CASES)
		cin >> t;
	while (t--)
	{
		read();
		solve();
	}

	return 0;
}

