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

inline void read()
{}

vector<vector<int>> Graph;
vector<int> visited;
vector<int> saved;

int n, m;

int getOpposite( int index )
{
	return ( ( index + n - 1 ) % ( 2 * n ) ) + 1;
}

bool check( int index )
{
	fill( visited.begin(), visited.end(), 0 );

	queue<int> q;
	q.push( index );
	visited[ index ] = 1;

	int opposite = getOpposite( index );

	while ( !q.empty() )
	{
		int here = q.front();
		q.pop();

		for ( auto there : Graph[ here ] )
		{
			if ( visited[ there ] ) continue;
			visited[ there ] = true;
			q.push( there );

			if ( there == opposite ) return false;
		}
	}

	return true;
}

inline void solve()
{
	while ( cin >> n )
	{
		cin >> m;

		Graph.clear();
		Graph.resize( 2 * n + 1 );
		visited.resize( 2 * n + 1 );

		int a, b;
		For( i, 1, m )
		{
			cin >> a >> b;
			int indexA = a > 0 ? a : n - a;
			int indexB = b > 0 ? b : n - b;

			// p -> q 명제를 제시
			// cout << indexA << ' ' << indexB << '\n';
			// cout << getOpposite(indexA) << ' ' << getOpposite(indexB) << '\n';
			// cout << '\n';
			Graph[ getOpposite( indexA ) ].push_back( indexB );
			Graph[ getOpposite( indexB ) ].push_back( indexA );
		}

		// a -> a 를 제시..?
		Graph[ getOpposite( 1 ) ].push_back( 1 );

		bool ok = true;
		For( i, 1, n )
		{
			// 서로 반대인걸 지나면 안됨
			if ( !check( i ) && !check( i + n ) )
			{
				ok = false;
				break;
			}
		}

		if ( ok ) cout << "yes\n";
		else cout << "no\n";
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
