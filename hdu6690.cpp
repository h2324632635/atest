#include<bits/stdc++.h>
#define mod 998244353
#define LL long long
using namespace std;

map<LL,int>f,g,h;
int inv6 = (mod+1)/6;

int solve(LL n){
	if(f.count(n)) return g[n];
	if(n<=1) return f[n] = g[n] = h[n] = n;
	if(n&1){
		LL u = n / 2  , v = n - n / 2;
		solve(u),solve(v);
		int fu = f[u] , fv = f[v] , hu = h[u] , hv = h[v] , gu = g[u] , gv = g[v];
		f[n] = (3ll * fu + fv + 1ll * (n%mod) * (n%mod + 1) / 2 - 1) % mod;
		h[n] = (6ll * hu + 2ll * hv + fu - fv + 1ll*(n%mod)*(n%mod+1)%mod*(2ll*n%mod+1)%mod*inv6%mod-1)%mod;
		g[n] = (3ll * gu + gv + 2ll * hu + fu + 1ll*(n%mod)*(n%mod+1)%mod*(n%mod+2)%mod*inv6%mod-1)%mod;
	}
	else{
		LL u = n / 2 , v = u - 1;
		solve(u),solve(v);
		int fu = f[u] , fv = f[v] , hu = h[u] , hv = h[v] , gu = g[u] , gv = g[v];
		f[n] = (3ll * fu + fv + 1ll * (n%mod) * (n%mod+1) / 2 - 1) % mod;
		h[n] = (6ll * hu + 2ll * hv - fu + fv + 1ll*(n%mod)*(n%mod+1)%mod*(2ll*n%mod+1)%mod*inv6%mod-1)%mod;
		g[n] = (3ll * gu + gv + hu + hv + fv + 1ll*(n%mod)*(n%mod+1)%mod*(n%mod+2)%mod*inv6%mod-1)%mod;
	}
	return g[n];
}

int main(){
	int T;
	for(scanf("%d",&T);T--;){
		LL a,b;
		scanf("%lld%lld",&a,&b);
		printf("%d\n",((solve(b) - solve(a-1)) % mod + mod) % mod);
	}
}
