// ConsoleApplication5.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define scanf scanf_s

#include "bits/stdc++.h"
using namespace std;
const int maxn = 2e5 + 500;

long long sum = 0;
int visited[maxn] = {0}, f[maxn] = {0}, cnt = 0;
int n, m, q;

struct node {
  int a, b, v;
} p[maxn];

bool cmp(const node &x, const node &y) { return x.v < y.v; }

int father(int k) {
  if (f[k] == k)
    return k;
  else
    f[k] = father(f[k]);
  return f[k];
}

int main() {
  cin >> n >> m;
  // init(n);
  for (int i = 1; i <= n; i++) {
    f[i] = i;
  }
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%d%d", &p[i].a, &p[i].b, &p[i].v, &q);
    if (!q) {
      i--;
      m--;
    }
  }
  sort(p + 1, p + m + 1, cmp);
  for (int i = 1; i <= m; i++) {
    int f1 = father(p[i].a), f2 = father(p[i].b);
    if (f1 != f2) {
      sum += p[i].v;
      f[f1] = f[f2];
      cnt++;
      if (cnt == n - 1)
        break;
    }
  }
  if (cnt != n - 1)
    cout << "no" << endl;
  else {
    cout << "yes" << endl;
    cout << sum << endl;
  }
  return 0;
}
