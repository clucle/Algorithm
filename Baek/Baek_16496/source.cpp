#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <climits>
#include <stack>
#include <cstring>

using namespace std;

using ll = long long;

int main()
{
	ios::sync_with_stdio( false );
	cin.tie( 0 );
	cout.tie( 0 );

	int N;
	cin >> N;
	vector<string> v;
	v.resize( N );
	bool onlyZero = true;
	for ( int i = 0; i < N; i++ )
	{
		cin >> v[ i ];

		if ( onlyZero )
		{
			for ( int j = 0; j < v[ i ].size(); j++ )
			{
				if ( v[ i ][ j ] != '0' )
				{
					onlyZero = false;
					break;
				}
			}
		}
	}

	if ( onlyZero )
	{
		cout << 0;
		return 0;
	}

	sort(
		v.begin(),
		v.end(),
		[]( string const& a, string const& b ) -> bool
		{
			string xa;
			string xb;
			if ( a.size() > b.size() )
			{
				xa = a + b;
				xb = b;
			}
			else if ( a.size() < b.size() )
			{
				xa = a;
				xb = b + a;
			}
			else
			{
				xa = a;
				xb = b;
			}

			int mymax = max( xa.size(), xb.size() );
			for ( int i = 0; i < mymax; i++ )
			{
				if ( xa[ i % xa.size() ] != xb[ i % xb.size() ] )
					return xa[ i % xa.size() ] > xb[ i % xb.size() ];
			}

			return xa.size() > xb.size();
		} );

	for ( auto e : v )
	{
		cout << e;
	}

	return 0;
}