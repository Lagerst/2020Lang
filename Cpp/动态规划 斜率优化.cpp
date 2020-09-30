// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define scanf scanf_s
#include "bits/stdc++.h"

using namespace std;

const int maxn = 50050;
#define list llist
long long v[maxn], sum[maxn], f[maxn], list[maxn];

double Y(long long j) { return f[j] + sum[j] * sum[j]; }
double X(long long j) { return sum[j]; }

double slop(long long j, long long k) { return (Y(k) - Y(j)) / (X(k) - X(j)); }

int main() {
  long long head, tail, n, p;
  scanf("%lld%lld", &n, &p);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &v[i]);
    sum[i] = sum[i - 1] + v[i] + 1;
  }
  head = 1;
  tail = 1;
  list[1] = 0;
  for (int i = 1; i <= n; i++) {
    while (head < tail &&
           slop(list[head], list[head + 1]) <= 2 * (sum[i] - 1 - p))
      head++;
    int j = list[head];
    f[i] = f[j] + (sum[i] - sum[j] - 1 - p) * (sum[i] - sum[j] - 1 - p);
    while (head < tail &&
           slop(list[tail - 1], list[tail]) > slop(list[tail], i))
      tail--;
    list[++tail] = i;
  }
  printf("%lld\n", f[n]);
  return 0;
}
/**
状态转移方程
        dp[j]=min(dp[i] + (sum[j]-sum[i]-1-p)^2 )	(i<j)
化简得
        2*(s[i]-1-p)*s[j]+f[i]=f[j]+s[j]^2+(sum[i]-1-p)^2
作斜率优化(线性规划+优先队列)
        k=2*(s[j]-1-p)
        x=s[j]
        y=f[j]+s[j]^2
*/