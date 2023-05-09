/*
Problem Description

You are given two integers C,K and an array of N integers a1,a2,...,aN . It is guaranteed that the value of ai is between 1 to C .

We define that a continuous subsequence al,al+1,...,ar(l≤r) of array a is a good subarray if and only if the following condition is met:
 
∀x∈[1,C],∑i=lr[ai=x]=0or∑i=lr[ai=x]≥K



It implies that if a number appears in the subarray, it will appear no less than K times.

You should find the longest good subarray and output its length. Or you should print 0 if you cannot find any.
 

 
Input

There are multiple test cases.

Each case starts with a line containing three positive integers N,C,K(N,C,K≤105) .

The second line contains N integer a1,a2,...,aN(1≤ai≤C) .

We guarantee that the sum of N s, the sum of C s and the sum of K s in all test cases are all no larger than 5×105 .

 

 
Output

For each test case, output one line containing an integer denoting the length of the longest good subarray.

 

 
Sample Input

 
7 4 2 2 1 4 1 4 3 2

 

 
Sample Output

 
4

简单题意
题意：求最长的连续子序列，满足序列中每个数至少出现 k 次或不出现。
*/

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <vector>
#include <math.h>
#include <bitset>
#include <algorithm>
#include <climits>
using namespace std;
 
#define lson i<<1
#define rson i<<1|1
#define LS l,mid,lson
#define RS mid+1,r,rson
#define LL long long
#define N 1000005
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EXP 1e-8
#define lowbit(x) (x&-x)
 
int ans_sum,ans_maxx,ans_minn;
struct node
{
    int l,r;
    int maxx;
    int add;
} tree[N<<2];
 
void pushdown(int i)//标记下传
{
    tree[lson].add+=tree[i].add;///给左子节点打上延迟标记
    tree[rson].add+=tree[i].add;///给右子节点打上延迟标记
    //tree[lson].minn+=tree[i].add;
    //tree[rson].minn+=tree[i].add;
    tree[lson].maxx+=tree[i].add;
    tree[rson].maxx+=tree[i].add;
    //tree[lson].sum+=tree[i].add*(tree[lson].r-tree[lson].l+1); ///更新左子节点消息
    //tree[rson].sum+=tree[i].add*(tree[rson].r-tree[rson].l+1); ///更新右子节点消息
    tree[i].add = 0;  ///清除标记
 
}
 
void pushup(int i)
{
    // tree[i].sum=tree[lson].sum+tree[rson].sum;
    tree[i].maxx=max(tree[lson].maxx,tree[rson].maxx);
    //tree[i].minn=min(tree[lson].minn,tree[rson].minn);
}
//建立线段树
void build(int l,int r,int i)
{
    tree[i].l = l;
    tree[i].r = r;
    tree[i].add = 0;
    //tree[i].sett = -1;
    if(l == r)
    {
        //tree[i].sum = 0;
        tree[i].maxx = 0;
        //tree[i].minn = 0;
        return;
    }
    int mid = (l+r)>>1;
    build(LS);
    build(RS);
    pushup(i);
}
//tree[l,r]+=val
void add_data(int l,int r,int i,int val)
{
    if(tree[i].l>=l&&tree[i].r<=r)
    {
        tree[i].maxx += val;
        tree[i].add += val;
        return;
    }
    pushdown(i);//标记下传
    int mid = (tree[i].l+tree[i].r)>>1;
    if(l<=mid)
        add_data(l,r,lson,val);
    if(r>mid)
        add_data(l,r,rson,val);
    pushup(i);
}
 
void query(int l,int r,int i)
{
    if(l <= tree[i].l && tree[i].r <= r)
    {
        //ans_sum += tree[i].sum;
        ans_maxx = max(ans_maxx,tree[i].maxx);
        //ans_minn = min(ans_minn,tree[i].minn);
        return ;
    }
    pushdown(i);
    int mid = (tree[i].l+tree[i].r)>>1;
    if(l<=mid)
        query(l,r,lson);
    if(r>mid)
        query(l,r,rson);
    pushup(i);
}
int query_pos(int rt,int val)
{
    int l=tree[rt].l;
    int r=tree[rt].r;
    if(l==r)
    {
        return l;
    }
    pushdown(rt);
    if(tree[rt<<1].maxx==val)
        return query_pos(rt<<1,val);
    else if(tree[rt<<1|1].maxx==val)
        return query_pos(rt<<1|1,val);
    else
        return -1;
    pushup(rt);
}
int n,c,k;
vector<int>pos[N];
int a[N],num[N];
int main()
{
    while(~scanf("%d%d%d",&n,&c,&k))
    {
        for(int i=0; i<=c; i++)
        {
            num[i]=0;
            pos[i].clear();
            pos[i].push_back(0);
        }
        for(int i=1; i<=n; i++)
        {
            scanf("%d",&a[i]);
            pos[a[i]].push_back(i);
        }
        if(k==1)
        {
            printf("%d\n",n);
            continue;
        }
 
        build(1,n,1);
 
        LL ans=0;
        for(int i=1; i<=n; i++)
        {
 
            add_data(i,i,1,c-1);
 
            num[a[i]]++;
 
             if(pos[a[i]][num[a[i]]]-1>=pos[a[i]][num[a[i]]-1]+1)
            {
                add_data(pos[a[i]][num[a[i]]-1]+1,pos[a[i]][num[a[i]]]-1,1,-1);
            }
 
            if(num[a[i]]>=k)
            {
                add_data(pos[a[i]][num[a[i]]-k]+1,pos[a[i]][num[a[i]]-k+1],1,1);
            }
 
            int templ=query_pos(1,c);
            if(templ!=-1)
                ans=max(ans,(LL)i-templ+1);
        }
        printf("%lld\n",ans);
 
 
    }
}
 
