// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define scanf scanf_s

#include "bits/stdc++.h"
using namespace std;

const int maxn = 1e5 + 10;
const int maxm = 1e3 + 10;
int a[maxn], belong[maxn];
int atag[maxm];
int n, sz;
set<int> st[maxm];
map<int, int> cnt[maxm];

void add(int l, int r, int c) {
  for (int i = l; i <= min(belong[l] * sz, r); i++) {
    if (!--cnt[belong[l]][a[i]]) {
      st[belong[l]].erase(a[i]);
    }
    a[i] += c;
    cnt[belong[l]][a[i]]++;
    st[belong[l]].insert(a[i]);
  }
  if (belong[l] != belong[r]) {
    for (int i = (belong[r] - 1) * sz + 1; i <= r; i++) {
      if (!--cnt[belong[r]][a[i]]) {
        st[belong[r]].erase(a[i]);
      }
      a[i] += c;
      cnt[belong[r]][a[i]]++;
      st[belong[r]].insert(a[i]);
    }
  }
  for (int i = belong[l] + 1; i <= belong[r] - 1; i++)
    atag[i] += c;
}

int query(int l, int r, int c) {
  int ans = -1;
  for (int i = l; i <= min(belong[l] * sz, r); i++) {
    int val = a[i] + atag[belong[l]];
    if (val < c)
      ans = max(val, ans);
  }
  if (belong[l] != belong[r]) {
    for (int i = (belong[r] - 1) * sz + 1; i <= r; i++) {
      int val = a[i] + atag[belong[r]];
      if (val < c)
        ans = max(val, ans);
    }
  }
  for (int i = belong[l] + 1; i <= belong[r] - 1; i++) {
    int x = c - atag[i];
    set<int>::iterator it = st[i].lower_bound(x);
    if (it == st[i].begin())
      continue;
    --it;
    ans = max(ans, *it + atag[i]);
  }
  return ans;
}

int main() {
  int i, j, k, x, y, z, l, r, c, opt;
  while (scanf("%d", &n) != EOF) {
    sz = sqrt(n) * 2;
    for (i = 1; i <= n / sz + 1; i++)
      st[i].clear();
    memset(atag, 0, sizeof(atag));
    for (i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
      belong[i] = (i - 1) / sz + 1;
      st[belong[i]].insert(a[i]);
      cnt[belong[i]][a[i]]++;
    }
    for (i = 1; i <= n; i++) {
      scanf("%d%d%d%d", &opt, &l, &r, &c);
      if (opt == 0)
        add(l, r, c);
      else if (opt == 1)
        printf("%d\n", query(l, r, c));
    }
  }
  return 0;
}