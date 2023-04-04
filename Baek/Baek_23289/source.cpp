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

int R, C, K;
int board[ 22 ][ 22 ];
int W;
int wall[ 22 ][ 22 ][ 2 ];

std::pair<int, int> operator +( const std::pair<int, int>& x, const std::pair<int, int>& y )
{
	return std::make_pair( x.first + y.first, x.second + y.second );
}

inline void read()
{
	cin >> R >> C >> K;
	For( r, 1, R ) For( c, 1, C ) cin >> board[ r ][ c ];
	cin >> W;
	For( w, 1, W )
	{
		int x, y, t; cin >> x >> y >> t;
		wall[ x ][ y ][ t ] = 1;
	}
}

int heat[ 22 ][ 22 ] = { 0, };
vector<pii> needCheck;

int heat_lr[ 9 ][ 5 ] = {
	{0,0,0,0,1},
	{0,0,0,2,1},
	{0,0,3,2,1},
	{0,4,3,2,1},
	{5,4,3,2,1},
	{0,4,3,2,1},
	{0,0,3,2,1},
	{0,0,0,2,1},
	{0,0,0,0,1}
};

int heat_ud[ 5 ][ 9 ] = {
	{0,0,0,0,5,0,0,0,0},
	{0,0,0,4,4,4,0,0,0},
	{0,0,3,3,3,3,3,0,0},
	{0,2,2,2,2,2,2,2,0},
	{1,1,1,1,1,1,1,1,1}
};

int dir_r[ 5 ] = { 0,0,0,-1,1 };
int dir_c[ 5 ] = { 0,1, -1, 0, 0 };

pii additional( int dir, int num )
{
	if ( dir == 1 || dir == 2 ) return{ num,0 };
	else if ( dir == 3 || dir == 4 ) return { 0,num };

	return { 0,0 };
}

bool isValid( int r, int c )
{
	if ( r < 1 || r > R || c < 1 || c > C ) return false;
	return true;
}

bool Blocked( int r, int c, pii dir, pii additional )
{
	if ( additional != pii( 0, 0 ) )
	{
		if ( additional == pii( 0, 1 ) )
		{
			if ( wall[ r ][ c ][ 1 ] ) return true;
			c++;
		}
		else if ( additional == pii( 0, -1 ) )
		{
			c--;
			if ( wall[ r ][ c ][ 1 ] ) return true;
		}
		else if ( additional == pii( 1, 0 ) )
		{
			r++;
			if ( wall[ r ][ c ][ 0 ] ) return true;
		}
		else if ( additional == pii( -1, 0 ) )
		{
			if ( wall[ r ][ c ][ 0 ] ) return true;
			r--;
		}
	}

	if ( dir == pii( 0, 1 ) )
	{
		if ( wall[ r ][ c ][ 1 ] ) return true;
		c++;
	}
	else if ( dir == pii( 0, -1 ) )
	{
		c--;
		if ( wall[ r ][ c ][ 1 ] ) return true;
	}
	else if ( dir == pii( 1, 0 ) )
	{
		r++;
		if ( wall[ r ][ c ][ 0 ] ) return true;
	}
	else if ( dir == pii( -1, 0 ) )
	{
		if ( wall[ r ][ c ][ 0 ] ) return true;
		r--;
	}

	return false;
}

inline void pre()
{
	// 5 6 0 -> 4 6 ∞˙ 5 6 ªÁ¿Ã
	// 4 4 1 -> 4 4 øÕ 5 4 ªÁ¿Ã

	For( r, 1, R ) For( c, 1, C )
	{
		if ( board[ r ][ c ] == 0 ) continue;

		if ( board[ r ][ c ] == 5 )
		{
			needCheck.push_back( { r,c } );
			continue;
		}

		int dir = board[ r ][ c ];
		int src_r = r + dir_r[ dir ];
		int src_c = c + dir_c[ dir ];

		int tmp[ 22 ][ 22 ];
		memset( tmp, 0, sizeof( tmp ) );

		queue<pair<pii, int>> q;
		q.push( { { src_r, src_c }, 5 } );

		while ( !q.empty() )
		{
			int here_r = q.front().first.first;
			int here_c = q.front().first.second;
			int here_temperature = q.front().second;
			q.pop();

			tmp[ here_r ][ here_c ] = here_temperature;
			if ( here_temperature == 1 ) continue;

			pii dirVector = { dir_r[ dir ], dir_c[ dir ] };
			pii next_tmp = pii( here_r + dir_r[ dir ], here_c + dir_c[ dir ] );
			for ( int i = -1; i <= 1; ++i )
			{
				pii next = next_tmp + additional( dir, i );
				if ( !isValid( next.first, next.second ) ) continue;
				if ( Blocked( here_r, here_c, dirVector, additional( dir, i ) ) ) continue;

				q.push( { next, here_temperature - 1 } );
			}
		}

		For( r, 1, R ) For( c, 1, C )
		{
			heat[ r ][ c ] += tmp[ r ][ c ];
		}
	}
}

inline void solve()
{
	pre();
	int ret[ 22 ][ 22 ];
	memset( ret, 0, sizeof( ret ) );

	int choco = 0;
	while ( true )
	{
		// ¡ˆ¿◊
		For( r, 1, R ) For( c, 1, C )
			ret[ r ][ c ] += heat[ r ][ c ];

		// Ω¥Ωµ
		int tmp[ 22 ][ 22 ];
		memset( tmp, 0, sizeof( tmp ) );
		For( r, 1, R ) For( c, 1, C )
		{
			if ( c + 1 <= C && wall[ r ][ c ][ 1 ] == 0 )
			{
				// ø¿∏•¬ 
				int diff1 = ( ret[ r ][ c ] - ret[ r ][ c + 1 ] ) / 4;
				tmp[ r ][ c ] -= diff1;
				tmp[ r ][ c + 1 ] += diff1;
			}


			if ( r + 1 <= R && wall[ r + 1 ][ c ][ 0 ] == 0 )
			{
				// æ∆∑°¬ 
				int diff2 = ( ret[ r ][ c ] - ret[ r + 1 ][ c ] ) / 4;
				tmp[ r ][ c ] -= diff2;
				tmp[ r + 1 ][ c ] += diff2;
			}
		}

		For( r, 1, R ) For( c, 1, C )
		{
			ret[ r ][ c ] += tmp[ r ][ c ];
		}

		For( r, 1, R )
		{
			ret[ r ][ 1 ] = max( ret[ r ][ 1 ] - 1, 0 );
			ret[ r ][ C ] = max( ret[ r ][ C ] - 1, 0 );
		}

		For( c, 2, C - 1 )
		{
			ret[ 1 ][ c ] = max( ret[ 1 ][ c ] - 1, 0 );
			ret[ R ][ c ] = max( ret[ R ][ c ] - 1, 0 );
		}

		// ≥»
		choco++;

		if ( choco > 100 ) break;

		bool ok = true;
		// √§¡°
		for ( const pii& pos : needCheck )
		{
			if ( ret[ pos.first ][ pos.second ] < K )
			{
				ok = false;
			}
		}

		if ( ok ) break;
	}

	cout << choco;
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
