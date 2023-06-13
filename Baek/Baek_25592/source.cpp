

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

int N;
inline void read()
{
    cin >> N;
}

inline void solve()
{
    bool flag = true;
    int cnt = 1;
    while ( N >= 0 )
    {
        N = N - cnt;
        if ( N < 0 )
        {
            if ( flag ) cout << -N << '\n';
            else cout << 0 << '\n';

            return;
        }

        cnt++;
        flag = !flag;
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
