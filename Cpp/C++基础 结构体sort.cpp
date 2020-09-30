// ConsoleApplication4.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define scanf scanf_s

#include "bits/stdc++.h"

using namespace std;

struct node {
  int l, r, data;
};

node p[300100];

int cmp(const node &a, const node &b) { return a.l < b.l; }

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", &p[i].l, &p[i].r);
    p[i].data = i;
  }
  sort(p + 1, p + n + 1, cmp);
  int minr = p[n].r, location = p[n].data;
  for (int i = n - 1; i > 0; i--) {
    if (p[i].r < minr) {
      minr = p[i].r;
      location = p[i].data;
    } else {
      cout << location << ' ' << p[i].data << endl;
      return 0;
    }
  }
  cout << -1 << ' ' << -1 << endl;
  return 0;
}
