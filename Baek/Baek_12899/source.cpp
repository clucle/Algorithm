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
#include <functional>

using namespace std;

#define For( i, j, k ) for ( int i = (int)( j ); i <= ( k ); i++ )

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const bool TEST_CASES = false;
const bool READ_FILE = false;

std::pair<int, int> operator +( const std::pair<int, int>& x, const std::pair<int, int>& y )
{
	return std::make_pair( x.first + y.first, x.second + y.second );
}

int N;
vector<pii> query;

inline void read()
{
	cin >> N;
	query.resize( N );
	For( i, 0, N - 1 ) cin >> query[ i ].first >> query[ i ].second;
}

int arr[ 2'000'001 ];
vector<int> tree;

void add( int node, int start, int end, int num, int val )
{
	if ( num < start || end < num ) return;
	tree[ node ] += val;

	if ( start == end ) return;

	int mid = start + ( end - start ) / 2;
	add( node * 2, start, mid, num, val );
	add( node * 2 + 1, mid + 1, end, num, val );
}

int get( int node, int start, int end, int left, int right )
{
	if ( right < start || end < left ) return 0;
	if ( left <= start && end <= right ) return tree[ node ];

	int mid = start + ( end - start ) / 2;
	return
		get( node * 2, start, mid, left, right ) +
		get( node * 2 + 1, mid + 1, end, left, right );
}

int process( int node, int start, int end, int count )
{
	if ( start == end )
	{
		return start;
	}

	int mid = start + ( end - start ) / 2;
	if ( tree[ node * 2 ] >= count )
		return process( node * 2, start, mid, count );

	return process( node * 2 + 1, mid + 1, end, count - tree[ node * 2 ] );
}

const int MAX_N = 2'000'000;

int count[ MAX_N + 1 ] = { 0, };

inline void solve()
{
	int h = log2( MAX_N ) + 1;
	int size = 1 << ( h + 1 );
	tree.resize( size );

	for ( const auto& x : query )
	{
		int op = x.first;
		int num = x.second;

		if ( op == 1 )
		{
			add( 1, 1, MAX_N, num, 1 );
			// m[ num ]++;
		}
		else
		{
			/*
			int l = 0;
			int r = MAX_N;

			int count = 0;

			// 2'000'000 * 21 * 21 = 882'000'000 ( 8¾ï ..? )
			// N lgN lgN ...?

			while ( l + 1 < r )
			{
				int mid = l + ( r - l + 1 ) / 2;

				int n = get( 1, 1, MAX_N, 1, mid );
				if ( n >= num )
					r = mid;
				else
					l = mid;
			}

			add( 1, 1, MAX_N, r, -1 );

			cout << r << '\n';
			*/

			int ret = process( 1, 1, MAX_N, num );
			add( 1, 1, MAX_N, ret, -1 );
			cout << ret << '\n';
		}
	}
}

int main()
{
	ios::sync_with_stdio( false );
	cin.tie( 0 );
	cout.tie( 0 );
	cout.precision( 8 );
	cout << fixed;

	int t = 1;
	if ( READ_FILE )
		freopen( "D:\\test.txt", "r", stdin );
	if ( TEST_CASES )
		cin >> t;
	while ( t-- )
	{
		read();
		solve();
	}

	return 0;
}
