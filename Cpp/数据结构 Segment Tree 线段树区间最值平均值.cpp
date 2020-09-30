// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define scanf scanf_s

#include "bits/stdc++.h"
using namespace std;

const int maxn = 1000000;
struct node {
  int left, right, maxv, minv, value;
  long long total;
} segtree[maxn * 4 + 10];

void build(int num, int begin, int end) {
  segtree[num].value = 0;
  segtree[num].left = begin;
  segtree[num].right = end;
  segtree[num].maxv = 0;
  segtree[num].minv = 0;
  segtree[num].total = 0;
  if (end > begin) {
    int mid = (begin + end) / 2;
    build(num * 2, begin, mid);
    build(num * 2 + 1, mid + 1, end);
  }
}

void adjust(int x, int y, int num) {
  if (segtree[num].left < segtree[num].right) {
    int mid = (segtree[num].left + segtree[num].right) / 2;
    if (mid >= x) {
      adjust(x, y, num * 2);
    } else {
      adjust(x, y, num * 2 + 1);
    }
    segtree[num].total = segtree[num * 2].total + segtree[num * 2 + 1].total;
    segtree[num].maxv = max(segtree[num * 2].maxv, segtree[num * 2 + 1].maxv);
    segtree[num].minv = min(segtree[num * 2].minv, segtree[num * 2 + 1].minv);
  } else {
    segtree[num].value = y;
    segtree[num].total = y;
    segtree[num].maxv = y;
    segtree[num].minv = y;
  }
}
long long calculate(int x, int y, int num, int *segmax, int *segmin) {
  long long ans = 0;
  if (x <= segtree[num].left && y >= segtree[num].right) {
    *segmax = max(*segmax, segtree[num].maxv);
    *segmin = min(*segmin, segtree[num].minv);
    ans += segtree[num].total;
    return ans;
  }
  int mid = (segtree[num].left + segtree[num].right) / 2;
  if (mid < x) {
    ans += calculate(x, y, num * 2 + 1, segmax, segmin);
    return ans;
  } else if (mid >= y) {
    ans += calculate(x, y, num * 2, segmax, segmin);
    return ans;
  } else {
    ans += calculate(x, y, num * 2, segmax, segmin) +
           calculate(x, y, num * 2 + 1, segmax, segmin);
    return ans;
  }
}

int main() {
  int n, m, o, x, y, segmax, segmin;
  cin >> n >> m;
  build(1, 1, n);
  for (int i = 1; i <= m; i++) {
    scanf("%d %d %d", &o, &x, &y);
    if (o == 0) {
      adjust(x, y, 1);
    } else {
      segmax = -2147483647;
      segmin = 2147483646;
      printf("%lld\n", calculate(x, y, 1, &segmax, &segmin) - segmin - segmax);
    }
  }
  return 0;
}
