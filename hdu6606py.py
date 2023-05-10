import math

N = 1000005
MOD = 1000000007
INF = 0x3f3f3f3f

ans_sum, ans_maxx, ans_minn = 0, 0, INF

class node:
    def __init__(self, l, r):
        self.l = l
        self.r = r
        self.maxx = 0
        self.add = 0

def pushup(i):
    global ans_maxx
    tree[i].maxx = max(tree[lson].maxx, tree[rson].maxx)

def build(l, r, i):
    tree[i].l = l
    tree[i].r = r
    tree[i].add = 0
    if l == r:
        tree[i].maxx = 0
        return
    mid = (l + r) >> 1
    build(LS)
    build(RS)
    pushup(i)

def add_data(pos, i, val):
    if tree[i].l == tree[i].r:
        tree[i].maxx = max(val, tree[i].maxx)
        return
    mid = (tree[i].l + tree[i].r) >> 1
    if pos <= mid:
        add_data(pos, lson, val)
    else:
        add_data(pos, rson, val)
    pushup(i)

def query(l, r, i):
    global ans_maxx
    if l <= tree[i].l and tree[i].r <= r:
        ans_maxx = max(ans_maxx, tree[i].maxx)
        return
    mid = (tree[i].l + tree[i].r) >> 1
    if l <= mid:
        query(l, r, lson)
    if r > mid:
        query(l, r, rson)
    pushup(i)

def check(mid):
    dp = [0] * (n + 1)
    build(1, b_n, 1)
    for i in range(1, n + 1):
        if b[sum[i]] <= mid:
            dp[i] = 1
        l = math.ceil(b[sum[i]] - mid)
        ans_maxx = 0
        query(l, b_n, 1)
        if ans_maxx != 0:
            dp[i] = max(dp[i], ans_maxx + 1)
        add_data(sum[i], 1, dp[i])
        if dp[i] >= m:
            return 1
    return 0

T = int(input())
while T > 0:
    n, m = map(int, input().split())
    x = list(map(int, input().split()))
    sum = [0] * (n + 1)
    b = [0] * (n + 1)
    sum[0] = 0
    for i in range(1, n + 1):
        sum[i] = sum[i - 1] + x[i - 1]
        b[i] = sum[i]
    b = sorted(b[1:n + 1])
    b_n = len(set(b))
    for i in range(1, n + 1):
        sum[i] = b.index(sum[i]) + 1
    l = -1e15
    r = 1e15 + 1
    while l < r:
        mid = (l + r) >> 1
        if check(mid):
            r = mid
        else:
            l = mid + 1

    if l == 1e15 + 1:
        l = -1
    print(l)

    T -= 1
