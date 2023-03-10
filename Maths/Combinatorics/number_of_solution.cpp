#include <bits/stdc++.h>

/*
@uthor: Nasrum Nur
---------------------------
code n drink Pennyroyal tea
*/

#ifdef Pennyroyal
#include <debug.h>
#else
#define debug(...)
#define sdebug(...)
#endif

using namespace std;
using ll = long long;

/**
 *** From Benq's template
 * Description: Modular arithmetic. Assumes $MOD$ is prime.
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/modulararithmetic
 * Usage: mi a = MOD+5; inv(a); // 400000003
 */
template<int MOD> struct mint {
	static const int mod = MOD; int v; 
 	explicit operator int() const { return v; } 
	mint() : v(0) {}
	mint(ll _v) : v(int(_v % MOD)) { v += (v < 0) * MOD; }
	mint& operator+=(mint o) { 
		if ((v += o.v) >= MOD) v -= MOD; return *this; }
	mint& operator-=(mint o) { 
		if ((v -= o.v) < 0) v += MOD; return *this; }
	mint& operator*=(mint o) { 
		v = int((ll)v * o.v % MOD); return *this; }
	friend mint pow(mint a, ll p) {
		assert(p >= 0);
		return p == 0 ? 1 : pow(a * a, p / 2) * (p & 1 ? a : 1);
	}
	friend mint inv(mint a) { assert(a.v != 0); return pow(a, MOD - 2); }
	friend mint operator+(mint a, mint b) { return a += b; }
	friend mint operator-(mint a, mint b) { return a -= b; }
	friend mint operator*(mint a, mint b) { return a *= b; }
};

using mi = mint<(int)1e9+7>;

const int nmax = 2e5 + 1;

mi factorial[nmax + 1];
mi inverse_factorial[nmax + 1];

void preCalc(int n) {
	factorial[0] = inverse_factorial[0] = 1;
	for (int i = 1; i <= n; i++) {
		factorial[i] = mi(i) * factorial[i - 1];
	}
	inverse_factorial[n] = inv(factorial[n]);
	for (int i = n - 1; i >= 1; i--) {
		inverse_factorial[i] = mi(i + 1) * inverse_factorial[i + 1];
	}
}

inline int nCr(int n, int r) {
	if (r > n) return INT_MAX;
	mi res = factorial[n] * inverse_factorial[r] * inverse_factorial[n - r];
	return res.v;
}

/*
x1+x2+...+xr = n  where xi >= a
how many solutions?
------------------------------------------------
(x1-a)+(x2-a)+...+(xr-a) = n-ra  where xi-a >= 0
y1+y2+...+yr = n-ra  where yi >= 0
*/
void solve(void) {
	int n = 5, r = 3, a = 1;
	cout << nCr(n - r * a + r - 1, r - 1) << '\n';
}

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    preCalc(nmax);
    solve();

    return 0;
}