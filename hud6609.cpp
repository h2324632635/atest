/*

Find the answer
Time Limit: 4000/4000 MS (Java/Others)    Memory Limit: 65536/65536 K (Java/Others)
Total Submission(s): 4780    Accepted Submission(s): 1522


Problem Description
Given a sequence of n integers called W and an integer m. For each i (1 <= i <= n), you can choose some elements Wk (1 <= k < i), and change them to zero to make ∑ij=1Wj<=m. So what's the minimum number of chosen elements to meet the requirements above?.
 

Input
The first line contains an integer Q --- the number of test cases.
For each test case:
The first line contains two integers n and m --- n represents the number of elemens in sequence W and m is as described above.
The second line contains n integers, which means the sequence W.

1 <= Q <= 15
1 <= n <= 2*105
1 <= m <= 109
For each i, 1 <= Wi <= m
 

Output
For each test case, you should output n integers in one line: i-th integer means the minimum number of chosen elements Wk (1 <= k < i), and change them to zero to make ∑ij=1Wj<=m.
 

Sample Input
2  
7 15  
1 2 3 4 5 6 7  
5 100  
80 40 40 40 60
 

Sample Output
0 0 0 0 0 2 3  
0 1 1 2 3



用权值线段树维护区间总和和总个数。

然后在权值线段树上面二分即可。因为区间比较大，所以动态开点。但是要注意到，我们二分的是严格闭区间，所以还要考虑当前点能不能继续减少。


*/



#pragma comment(linker, "/STACK:102400000,102400000")
#pragma GCC optimize("-Ofast","-funroll-all-loops")
#include<bits/stdc++.h>
//#define int long long
#define mid (l+r>>1)
using namespace std;
typedef long long LL;
const int N=2e5+10,M=N*80;
int n,m,res[N],rt,lc[M],rc[M],num[M],cnt;
LL sum[M],s;
void change(int &p,int l,int r,int x){
	if(!p)	p=++cnt,lc[p]=rc[p]=sum[p]=num[p]=0;
	if(l==r)	return sum[p]+=l,num[p]++,void();
	if(x<=mid)	change(lc[p],l,mid,x);
	else change(rc[p],mid+1,r,x);
	sum[p]=sum[lc[p]]+sum[rc[p]];
	num[p]=num[lc[p]]+num[rc[p]];
}
int ask(int p,int l,int r,LL val){
	if(l==r)	return l;
	if(sum[rc[p]]>=val)	return ask(rc[p],mid+1,r,val);
	else return ask(lc[p],l,mid,val-sum[rc[p]]);
}
LL asksum(int p,int l,int r,int ql,int qr){
	if(!p)	return 0;
	if(l==ql&&r==qr)	return sum[p];
	if(qr<=mid)	return asksum(lc[p],l,mid,ql,qr);
	else if(ql>mid)	return asksum(rc[p],mid+1,r,ql,qr);
	else return asksum(lc[p],l,mid,ql,mid)+asksum(rc[p],mid+1,r,mid+1,qr);
}
int asknum(int p,int l,int r,int ql,int qr){
	if(!p)	return 0;
	if(l==ql&&r==qr)	return num[p];
	if(qr<=mid)	return asknum(lc[p],l,mid,ql,qr);
	else if(ql>mid)	return asknum(rc[p],mid+1,r,ql,qr);
	else return asknum(lc[p],l,mid,ql,mid)+asknum(rc[p],mid+1,r,mid+1,qr);
}
void solve(){
	cin>>n>>m; s=cnt=rt=0;
	for(int i=1,x,pos,del;i<=n;i++){
		scanf("%d",&x);	 s+=x;	LL tot=0;
		if(s<=m){res[i]=0;	change(rt,1,m,x);	continue;}
		pos=ask(rt,1,m,s-m),del=asknum(rt,1,m,pos,m);
		tot=asksum(rt,1,m,pos,m);
		res[i]=del-(tot-s+m)/pos;
		change(rt,1,m,x);
	}
	for(int i=1;i<=n;i++)	printf("%d ",res[i]);puts("");
}
signed main(){
	int T;	cin>>T;
	while(T--)	solve();
	return 0;
}
