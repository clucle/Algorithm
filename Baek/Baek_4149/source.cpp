#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <climits>
#include <cmath>
#include <complex>
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
#define __SIZEOF_INT128__ 16

typedef long long ll;
typedef unsigned long long ull;
typedef pair< int, int > pii;
typedef pair< ll, ll > pll;

#ifdef _MSC_VER
using int128_t = long long;  // MSVC에서는 long long 사용
using uint128_t = unsigned long long;
#else
using int128_t = __int128_t; // GCC, Clang에서는 __int128_t 사용
using uint128_t = __uint128_t;
#endif

const bool TEST_CASES = false;
const bool READ_FILE = false;

ll N;
inline void read()
{
	cin >> N;
}

ll mulmod(ll a, ll b, ll mod) {
	return (ll)((int128_t)a * b % mod);
}

ll powmod(ll base, ll exp, ll mod) {
	if (mod == 1) return 0;

	ll ret = 1;
	base %= mod;
	while (exp > 0) {
		if (exp % 2 == 1) {
			ret = mulmod(ret, base, mod);
		}

		exp >>= 1;
		base = mulmod(base, base, mod);
	}

	return ret;
}

ll millerRabinPrimes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 };
bool millerRabin(ll n, ll a) {
	// n 은 홀수가 들어왔을때 확률적 소수 판단
	// 2^s * d = (n - 1)
	// 2^0 * d = n - 1
	ll d = n - 1;

	while (d % 2 == 0) {
		ll m = powmod(a, d, n);
		if (m == n - 1) return true;
		d >>= 1;
	}

	// 페르마 소정리
	// a^(p-1) = 1 (mod p)
	// p = (n - 1) = 2^s * d
	// a^(2^s * d) = 1 (mod p)
	ll m = powmod(a, d, n);
	return m == 1 || m == n - 1;
}

bool isPrime(ll n) {
	if (n == 1) {
		return false;
	}

	if (n == 2 || n == 3) {
		return true;
	}

	if (n % 2 == 0) return false;

	for (auto p : millerRabinPrimes) {
		if (n == p) return true;
		if (!millerRabin(n, p)) return false;
	}

	return true;
}

ll gcd(ll a, ll b) {
	if (a < b) return gcd(b, a);

	if (b == 0) return a;
	return gcd(b, a % b);
}

// 소인수 분해 알고리즘
// 유사난수함수를 만들면 언젠가 반복됨. ex g(x) = (x^2 + 1 mod n)
// x0 = g(0) = 1
// x1 = g(1) = 2 ...
// 생일 역설에 의해 반복되기전 나오는 서로다른 xk 는 대략 sqrt(N)
// i, j 를 정하고 i 는 1칸씩, j 는 두칸씩 이동하고 gcd(xi - xj, n) != 1 인지 검사
// 만약 1이 아니라면 xk mod p 는 반복됨
ll pollardRho(ll n) {
	if (n % 2 == 0) return 2;
	if (isPrime(n)) return n;

	while (true) {
		ll x = rand() % (n - 2) + 2;
		ll y = x;
		ll c = rand() % (n - 1) + 1;
		ll d = 1;

		auto f = [&](ll x) {
			return (mulmod(x, x, n) + c) % n;
		};

		while (d == 1) {
			x = f(x);
			y = f(f(y));
			d = gcd(abs(x - y), n);
		}

		if (d != n) return d;
	}
}

ll dfs(ll num, vector<ll>& ret) {
	ll a = pollardRho(N);
	if (isPrime(a)) {
		ret.push_back(a);
	}
	else {
		a = dfs(a, ret);
	}

	return a;
}

inline void solve()
{
	vector<ll> ret;
	ll a;
	while (N > 1) {
		a = dfs(N, ret);
		N /= a;
	}
	sort(ret.begin(), ret.end());
	for (auto e : ret) {
		cout << e << '\n';
	}
}


/*
too slow?

in1:
1000001600000557631

out1:
1000000513
1000001087
*/
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

