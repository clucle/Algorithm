#include <iostream>
#include <cstdio>
#include <cstdlib>
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

#define f first
#define s second
#define mp make_pair
#define sz(a) int((a).size())
#define re return
#define pb push_back
#define all(c) (c).begin(),(c).end()
#define forit(it,S) for(__typeof(S.begin()) it = S.begin(); it != S.end(); ++it)
#ifdef WIN32
#define I64d "%I64d"
#else
#define I64d "%lld"
#endif

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

typedef struct Node
{
	ll value, lazy;
} Node;

vector<Node> tree;
vector<ll> arr;

ll build( int node, int start, int end )
{
	if ( start == end )
	{
		re tree[ node ].value = arr[ start ];
	}
	else
	{
		re tree[ node ].value =
			build( node * 2, start, ( start + end ) / 2 ) +
			build( node * 2 + 1, ( start + end ) / 2 + 1, end );
	}
}

/*
void upd(int idx, int node, int start, int end, ll diff) {
	if (idx < start || idx > end) return;
	tree[node] += diff;
	if (start != end) {
		upd(idx, node * 2, start, (start + end) / 2, diff);
		upd(idx, node * 2 + 1, (start + end) / 2 + 1, end, diff);
	}
}
*/

void upd_range( int l, int r, int node, int start, int end, ll diff )
{
	if ( tree[ node ].lazy != 0 )
	{
		tree[ node ].value += ( end - start + 1 ) * tree[ node ].lazy;
		if ( start != end )
		{
			tree[ node * 2 ].lazy += tree[ node ].lazy;
			tree[ node * 2 + 1 ].lazy += tree[ node ].lazy;
		}
		tree[ node ].lazy = 0;
	}

	if ( r < start || l > end ) re;

	if ( l <= start && end <= r )
	{
		tree[ node ].value += ( end - start + 1 ) * diff;
		if ( start != end )
		{
			tree[ node * 2 ].lazy += diff;
			tree[ node * 2 + 1 ].lazy += diff;
		}
		re;
	}

	upd_range( l, r, node * 2, start, ( start + end ) / 2, diff );
	upd_range( l, r, node * 2 + 1, ( start + end ) / 2 + 1, end, diff );

	tree[ node ].value = tree[ node * 2 ].value + tree[ node * 2 + 1 ].value;
}

/*
ll sum(int node, int start, int end, int left, int right) {
	if (left > end || right < start) re 0;
	if (left <= start && end <= right) re tree[node];
	re
		sum(node * 2, start, (start + end) / 2, left, right) +
		sum(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
}
*/

ll sum( int node, int start, int end, int l, int r )
{
	if ( tree[ node ].lazy != 0 )
	{
		tree[ node ].value += ( end - start + 1 ) * tree[ node ].lazy;
		if ( start != end )
		{
			tree[ node * 2 ].lazy += tree[ node ].lazy;
			tree[ node * 2 + 1 ].lazy += tree[ node ].lazy;
		}
		tree[ node ].lazy = 0;
	}

	if ( l > end || r < start ) re 0;
	if ( l <= start && end <= r ) re tree[ node ].value;
	re
		sum( node * 2, start, ( start + end ) / 2, l, r ) +
		sum( node * 2 + 1, ( start + end ) / 2 + 1, end, l, r );
}

int main()
{
	// boj 10999

	ios::sync_with_stdio( false );
	cin.tie( 0 ); cout.tie( 0 );

	int N, M, K;
	cin >> N >> M >> K;

	arr.resize( N );
	for ( int i = 0; i < N; i++ )
	{
		cin >> arr[ i ];
	}

	int h = (int)ceil( log2( N ) );
	int sz = ( 1 << ( h + 1 ) );
	tree.resize( sz );

	build( 1, 0, N - 1 );

	int q = M + K;
	while ( q-- )
	{
		ll a, b, c, d; cin >> a >> b >> c;
		if ( a == 1 )
		{
			cin >> d;
			upd_range( b - 1, c - 1, 1, 0, N - 1, d );
		}
		else
		{
			cout << sum( 1, 0, N - 1, b - 1, c - 1 ) << '\n';
		}
	}

	return 0;
}