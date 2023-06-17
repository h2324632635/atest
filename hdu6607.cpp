#include <map>
#include <cmath>
#include <cstdio>

#define F(i, a, b) for (LL i = a; i <= b; i ++)
#define G(i, a, b) for (LL i = a; i >= b; i --)
#define add(a, b) ((a) = (a + b) % Mo)
#define sqr(x) ((x) * (x))

typedef long long LL;

const LL Mo = 1e9 + 7;
const LL M = 1e2 + 10;
const LL N = 4e6 + 10;
const LL Q = 3e5 + 10;
const LL Ny2 = 500000004;
const LL Ny6 = 166666668;

using namespace std;

LL T, n, m, sqr, k, Ans, jc[M], ny[M], S[M], Sm[N], Pre[M], Suf[M], y[M];
LL z[N / 10], bz[N], g[Q], id1[Q], id2[Q], w[Q], phi[N];
map <LL, LL> H;
map <LL, LL> :: iterator it;

LL gcd(LL x, LL y) { return !y ? x : gcd(y, x % y); }

LL ksm(LL x, LL y) {
	LL ans = 1;
	for (; y ; y >>= 1, x = (x * x) % Mo)
		if (y & 1)
			ans = (ans * x) % Mo;
	return ans;
}

LL FF(LL n) { n %= Mo; return n * (n + 1) % Mo * (2 * n + 1) % Mo * Ny6 % Mo; }
LL calc(LL n) {
	if (n <= N - 10) return Sm[n];
	it = H.find(n);
	LL ans = it -> second;
	if (it == H.end()) {
		ans = 0;
		for (LL i = 2, j; i <= n; i = j + 1) {
			j = (n / (n / i));
			LL Sum = (FF(j) - FF(i - 1)) * calc(n / i) % Mo;
			add(ans, Sum);
		}
		ans = (sqr(((n % Mo * ((n + 1) % Mo) % Mo * Ny2) % Mo)) % Mo - ans) % Mo;
		H[n] = ans;
	}
	return ans;
}

LL Gunc(LL n) {
	LL Sum = 0;
	Pre[0] = Suf[k + 3] = 1;
	LL mm = n % Mo;
	F(i, 1, k + 2)
		Pre[i] = Pre[i - 1] * (mm - i) % Mo;
	G(i, k + 2, 1)
		Suf[i] = Suf[i + 1] * (mm - i) % Mo;
	F(i, 1, k + 2)
		add(Sum, y[i] * Pre[i - 1] % Mo * Suf[i + 1] % Mo * ny[i - 1] % Mo * ny[k + 2 - i] % Mo * (((k + 2 - i) & 1) ? (- 1) : 1));
	return Sum;
}

void Min25() {
	F(i, 1, k + 2)
		y[i] = ksm(i, k);
	F(i, 1, k + 2)
		add(y[i], y[i - 1]);

	sqr = floor(sqrt(n)), m = 0;
	for (LL i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i), w[++ m] = n / i;
		if (w[m] <= sqr) id1[w[m]] = m; else id2[n / w[m]] = m;
		g[m] = Gunc(w[m]) - 1;
	}
	LL Sm = 0;
	F(j, 1, z[0]) {
		LL F = ksm(z[j], k);
		for (LL i = 1; i <= m && z[j] * z[j] <= w[i]; i ++) {
			LL x = w[i] / z[j];
			LL num = x <= sqr ? id1[x] : id2[n / x];
			g[i] = (g[i] - F * (g[num] - Sm)) % Mo;
		}
		add(Sm, F);
	}
}

int main() {
	phi[1] = 1;
	F(i, 2, N - 10) {
		if (!bz[i])
			z[++ z[0]] = i, phi[i] = i - 1;
		F(j, 1, z[0]) {
			LL t = z[j] * i;
			if (t > N - 10) break;
			bz[t] = 1;
			if (i % z[j] == 0) {
				phi[t] = phi[i] * z[j];
				break;
			}
			else phi[t] = phi[i] * (z[j] - 1);
		}
	}
	F(i, 1, N - 10)
		add(Sm[i], Sm[i - 1] + i * i % Mo * phi[i] % Mo);
	jc[0] = ny[0] = 1;
	F(i, 1, M - 1) {
		jc[i] = jc[i - 1] * i % Mo;
		ny[i] = ksm(jc[i], Mo - 2);
	}

	for (scanf("%lld", &T); T --; ) {
		scanf("%lld %lld", &n, &k), Ans = 0, k ++;
		Min25(), g[m + 1] = 0;
		for (LL i = 1, j, k = m; i <= n; i = j, k --) {
			j = n / (n / i) + 1;
			LL F = calc(n / i);
			LL sum = g[k] - g[k + 1];
			add(Ans, sum * F % Mo);
		}
		printf("%lld\n", (Ans + Mo) % Mo);
	}
}
