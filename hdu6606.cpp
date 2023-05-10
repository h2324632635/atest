/*

Distribution of books
Time Limit: 8000/8000 MS (Java/Others)    Memory Limit: 65536/65536 K (Java/Others)
Total Submission(s): 1404    Accepted Submission(s): 547

 
Problem Description

zz6d likes reading very much, so he bought a lot of books. One day, zz6d brought n books to a classroom in school. The books of zz6d is so popular that K students in the classroom want to borrow his books to read. Every book of zz6d has a number i (1<=i<=n). Every student in the classroom wants to get a continuous number books. Every book has a pleasure value, which can be 0 or even negative (causing discomfort). Now zz6d needs to distribute these books to K students. The pleasure value of each student is defined as the sum of the pleasure values of all the books he obtains.Zz6d didn't want his classmates to be too happy, so he wanted to minimize the maximum pleasure of the K classmates. zz6d can hide some last numbered books and not distribute them,which means he can just split the first x books into k parts and ignore the rest books, every part is consecutive and no two parts intersect with each other.However,every classmate must get at least one book.Now he wonders how small can the maximum pleasure of the K classmates be.

1<=T<=10
1<=n<=2*105
1<=k<=n
-109 <=ai <=109

 

 
Input

Input contains multiple test cases.
The first line of the input is a single integer T which is the number of test cases. T test cases follow.
For each test case, the first line contains two integer n,k: the number of books and the number of his classmates. The second line contains n integers a1 ,a2 ,…, an−1 ,an . (ai means the pleasure value of book i.)∑ n<=2*105 .

 

 
Output

For each case, print the smallest maximum pleasure of the K classmates, and one line one case.

 

 
Sample Input

 
2 4 2 3 -2 4 -2 5 4 -1 -1 -1 -1 6

 

 
Sample Output

 
2 -1
Hint

In the first example,classmate 1 get book 1,2, classmate 2 get book 3,4.the maximum pleasure is max((3-2),(4-2))=2; In the second example,he can ignore book 5 and spilt the first 4 books into 4 parts,give them to his classmates.
 

 
Source

2019 Multi-University Training Contest 3

 

 
Recommend

chendu   |   We have carefully selected several similar problems for you:  6742 6741 6740 6739 6738 



OJ题号
HDU - 6606

简单题意
将一个长度为n的数组a[1]、a[2]、… 、a[n]， 要求取前k段（要求各段连续，但不可交叉，每段元素个数≥1），使得最大的那段和最小，并输出该和。

1 <= n <= 2*105
1 <= k <= n
-109 <= ai <= 109

正解思路
最大值最小，所以这题的思路肯定为二分，但这题的a[i]有负数，所以贪心的判断函数肯定是不行的了。这题考虑DP

我们设dp[i]为前i个数可以得到最多满足条件的段数。

则dp[i]=max(dp[j])+1,  sum[i]-sum[j]<=x&&0<=j<i

但这样找是o(n^2)的，所以我们需要对其优化，因为要找前面的最大值所以线段树优化DP即可。

我们对于sum[i]离散化后建立权值线段树，维护最大权值dp[i]，对于当前的sum[i],需要找到sum[j]>=sum[i]-x,所以直接查找即可(sum[i]-x,sum[i]）的最大值即可。

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
 
LL ans_sum,ans_maxx,ans_minn;
struct node
{
    int l,r;
    LL maxx;
    int add;
} tree[N<<2];
 
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
void add_data(int pos,int i,LL val)
{
    if(tree[i].l==tree[i].r)
    {
        tree[i].maxx = max(val,tree[i].maxx);
        return;
    }
    int mid = (tree[i].l+tree[i].r)>>1;
    if(pos<=mid)
        add_data(pos,lson,val);
    else
        add_data(pos,rson,val);
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
    int mid = (tree[i].l+tree[i].r)>>1;
    if(l<=mid)
        query(l,r,lson);
    if(r>mid)
        query(l,r,rson);
    pushup(i);
}
int n,m,b_n;
LL sum[N],b[N];
LL dp[N];
int check(LL mid)
{
 
    for(int i=1; i<=n; i++)
        dp[i]=0;
 
    build(1,b_n,1);
    for(int i=1; i<=n; i++)
    {
        if(b[sum[i]]<=mid)
            dp[i]=1;
        LL l=lower_bound(b+1,b+b_n+1,b[sum[i]]-mid)-b;
        ans_maxx=0;
        query(l,b_n,1);
        if(ans_maxx!=0)
            dp[i]=max(dp[i],ans_maxx+1);
        add_data(sum[i],1,dp[i]);
        if(dp[i]>=m)
            return 1;
    }
 
    return 0;
 
}
 
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        LL x;
        sum[0]=0;
        for(int i=1; i<=n; i++)
        {
            scanf("%lld",&x);
            sum[i]=sum[i-1]+x;
            b[i]=sum[i];
        }
        sort(b+1,b+n+1);
        b_n=unique(b+1,b+n+1)-(b+1);
 
        for(int i=1; i<=n; i++)
        {
            sum[i]=lower_bound(b+1,b+b_n+1,sum[i])-b;
        }
 
        LL l=-1e15,r=1e15+1;
        while(l<r)
        {
            //cout<<"l r:"<<l<<" "<<r<<endl;
            LL mid=(l+r)>>1;
            if(check(mid))
                r=mid;
            else
                l=mid+1;
        }
 
        if(l==1e15+1)
            l=-1;
        printf("%lld\n",l);
    }
}
 
