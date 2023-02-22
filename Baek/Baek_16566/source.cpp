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

const bool TEST_CASES = false;
const bool READ_FILE = false;

int N, M, K;

vector<int> hand;
vector<int> field;

inline void read()
{
	cin >> N >> M >> K;
	hand.resize( M + 1 );
	field.resize( K + 1 );
	For( i, 1, M ) cin >> hand[ i ];
	hand[ 0 ] = N + 1;
	For( i, 1, K ) cin >> field[ i ];
}

vector<int> parent;
int getParent( int here )
{
	if ( parent[ here ] == here ) return here;
	return parent[ here ] = getParent( parent[ here ] );
}

inline void solve()
{
	sort( hand.begin(), hand.end() );

	parent.resize( M + 1 );
	For( i, 0, M ) parent[ i ] = i;

	int curMinIdx = 0;

	For( i, 1, K )
	{
		auto iter = std::upper_bound( hand.begin(), hand.end(), field[ i ] );
		int index = iter - hand.begin();
		int p = getParent( index );

		if ( p == M )
		{
			while ( true )
			{
				int tmp = getParent( curMinIdx );
				if ( curMinIdx == tmp ) break;
				curMinIdx = tmp;
			}

			cout << hand[ curMinIdx ] << '\n';
			parent[ curMinIdx ] = getParent( curMinIdx + 1 );
		}
		else
		{
			cout << hand[ p ] << '\n';
			parent[ p ] = getParent( p + 1 );
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
