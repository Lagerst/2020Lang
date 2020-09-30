// http://acm.hdu.edu.cn/showproblem.php?pid=5649

#include <bits/stdc++.h>

using namespace std;

int a[100100], opt[100100], ql[100100], qr[100100];
int t, n, m, k1, l, r;
struct node {
  int left, right, value, delta;

  void update(int v) {
    value = (right - left + 1) * v;
    delta = v;
  }

} segtree[400400 * 4 + 10];

void build(int num, int begin, int end) {
  segtree[num].value = 0;
  segtree[num].delta = -1;
  segtree[num].left = begin;
  segtree[num].right = end;
  if (end > begin) {
    int mid = (begin + end) / 2;
    build(num * 2, begin, mid);
    build(num * 2 + 1, mid + 1, end);
  }
}

void update(int l, int r, int p, int o) {
  if (l <= r) {
    int x = segtree[o].left, y = segtree[o].right;
    if (x >= l && y <= r)
      segtree[o].update(p);
    else {
      if (segtree[o].delta != -1) {
        segtree[2 * o].update(segtree[o].delta);
        segtree[2 * o + 1].update(segtree[o].delta);
        segtree[o].delta = -1;
      }
      int mid = (x + y) / 2;
      if (l <= mid)
        update(l, r, p, o * 2);
      if (r > mid)
        update(l, r, p, o * 2 + 1);
      if (x != y)
        segtree[o].value = segtree[o * 2].value + segtree[o * 2 + 1].value;
    }
  }
}

int query(int l, int r, int o) {
  int x = segtree[o].left, y = segtree[o].right;
  if (x >= l && y <= r)
    return segtree[o].value;
  else {
    if (segtree[o].delta != -1) {
      segtree[2 * o].update(segtree[o].delta);
      segtree[2 * o + 1].update(segtree[o].delta);
      segtree[o].delta = -1;
    }

    int mid = (x + y) / 2, res = 0;
    if (l <= mid)
      res += query(l, r, o * 2);
    if (r > mid)
      res += query(l, r, o * 2 + 1);

    if (x != y)
      segtree[o].value = segtree[o * 2].value + segtree[o * 2 + 1].value;
    return res;
  }
}

bool check(int k) {
  build(1, 1, n);
  for (int i = 1; i <= n; i++)
    if (a[i] >= k)
      update(i, i, 1, 1);
    else
      update(i, i, 0, 1);
  for (int i = 1; i <= m; i++) {
    int x = query(ql[i], qr[i], 1);
    if (!opt[i]) {
      x = qr[i] - ql[i] + 1 - x;
      update(ql[i], ql[i] + x - 1, 0, 1);
      update(ql[i] + x, qr[i], 1, 1);
    } else {
      update(ql[i], ql[i] + x - 1, 1, 1);
      update(ql[i] + x, qr[i], 0, 1);
    }
  }
  if (query(k1, k1, 1) == 1)
    return true;
  return false;
}

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
    }
    for (int i = 1; i <= m; i++) {
      scanf("%d%d%d", &opt[i], &ql[i], &qr[i]);
    }
    scanf("%d", &k1);
    int l = 1, r = n, ans = 0;
    while (l <= r) {
      int mid = (l + r) / 2;
      if (check(mid)) {
        l = mid + 1;
        ans = mid;
      } else {
        r = mid - 1;
      }
    }
    cout << ans << endl;
  }
  //	system("pause");
  return 0;
}