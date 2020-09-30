// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define scanf scanf_s

#include "bits/stdc++.h"
using namespace std;

const int maxn = 1000000;
struct node {
  int left, right, value, delta;
  long long total;
} segtree[maxn * 4 + 10];

void build(int num, int begin, int end) {
  segtree[num].value = 0;
  segtree[num].left = begin;
  segtree[num].right = end;
  segtree[num].total = 0;
  if (end > begin) {
    int mid = (begin + end) / 2;
    build(num * 2, begin, mid);
    build(num * 2 + 1, mid + 1, end);
  }
}

void adjust(int l, int r, int y, int num) {
  if (!(segtree[num].left >= l && segtree[num].right <= r)) {
    int mid = (segtree[num].left + segtree[num].right) / 2;
    if (mid >= r) {
      adjust(l, r, y, num * 2);
    } else if (mid < l) {
      adjust(l, r, y, num * 2 + 1);
    } else {
      adjust(l, r, y, num * 2 + 1);
      adjust(l, r, y, num * 2);
    }
    segtree[num].total =
        segtree[num * 2].total + segtree[num * 2 + 1].total +
        segtree[num * 2].delta *
            (segtree[num * 2].right - segtree[num * 2].left + 1) +
        segtree[num * 2 + 1].delta *
            (segtree[num * 2 + 1].right - segtree[num * 2 + 1].left + 1);
  } else {
    segtree[num].delta += y;
  }
}

void update(int num) {
  segtree[num].total +=
      segtree[num].delta * (segtree[num].right - segtree[num].left + 1);
  segtree[num * 2].delta += segtree[num].delta;
  segtree[num * 2 + 1].delta += segtree[num].delta;
  segtree[num].delta = 0;
}

long long calculate(int x, int y, int num) {
  long long ans = 0;
  if (x <= segtree[num].left && y >= segtree[num].right) {
    ans += segtree[num].total +
           segtree[num].delta * (segtree[num].right - segtree[num].left + 1);
    return ans;
  }
  int mid = (segtree[num].left + segtree[num].right) / 2;
  if (segtree[num].delta) {
    update(num);
  }
  if (mid < x) {
    ans += calculate(x, y, num * 2 + 1);
    return ans;
  } else if (mid >= y) {
    ans += calculate(x, y, num * 2);
    return ans;
  } else {
    ans += calculate(x, y, num * 2) + calculate(x, y, num * 2 + 1);
    return ans;
  }
}

int main() {
  int n, m, o, x, y, segmax, segmin, l, r, v;
  cin >> n >> m;
  build(1, 1, n);
  for (int i = 1; i <= m; i++) {
    scanf("%d %d %d %d", &o, &l, &r, &v);
    if (o == 0) {
      adjust(l, r, v, 1);
    } else {
      printf("%lld\n", calculate(l, r, 1));
    }
  }
  return 0;
}
