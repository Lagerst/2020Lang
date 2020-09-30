#include <algorithm>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int n, maxn = INT_MAX / 2, flag, num = 0, maxflag;
float ans = 0;
int x[50000] = {0};
int y[50000] = {0};
int valid[50000] = {0};
float p[50000] = {0};

int qsort(float a[], int l, int r) {
  int i, j;
  float temp;
  i = l;
  j = r;
  temp = a[rand() % (r - l + 1) + l];
  while (i <= j) {
    while (a[i] < temp)
      i++;
    while (a[j] > temp)
      j--;
    if (i <= j) {
      swap(a[i], a[j]);
      swap(x[i], x[j]);
      swap(y[i], y[j]);
      i++;
      j--;
    }
    if (i < r)
      qsort(a, i, r);
    if (j > l)
      qsort(a, l, j);
  }
  return 0;
}

int comp(int o, int k, int target) {
  return (x[target] - x[k]) * (y[k] - y[o]) -
         (y[target] - y[k]) * (x[k] - x[o]);
}

int length(int l, int r) {
  return (x[valid[l]] - x[valid[r]]) * (x[valid[l]] - x[valid[r]]) +
         (y[valid[l]] - y[valid[r]]) * (y[valid[l]] - y[valid[r]]);
}

int deletepoint(int k) {
  valid[k] = 0;
  flag--;
  return 0;
}

int justice(int k) {
  if (k > n)
    return 0;
  else
    return k;
}

int main() {
  cin >> n;
  srand((unsigned int)(time(NULL)));
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &x[i], &y[i]);
    if ((y[i] < maxn) || ((y[i] == maxn) && (x[i] < maxflag))) {
      flag = i;
      maxn = y[i];
      maxflag = x[i];
    }
  }

  for (int i = 1; i <= n; i++) {
    if (i != flag)
      p[i] = (float)(x[i] - x[flag]) /
             sqrt(double((y[i] - y[flag]) * (y[i] - y[flag]) +
                         (x[i] - x[flag]) * (x[i] - x[flag])));
    if (i == flag)
      p[i] = -INT_MAX / 2;
  }

  qsort(p, 1, n);

  flag = 2;
  valid[1] = 1;
  valid[2] = 2;
  int j;

  for (int i = 3; i <= n; i++) {
    j = flag;
    while ((comp(valid[j - 1], valid[j], i) < 0) && (j >= 2)) {
      deletepoint(j);
      j--;
    }
    j++;
    valid[j] = i;
    flag++;
  }

  j = 3;
  for (int i = 1; i <= flag; i++) {
    while (abs(comp(valid[justice(j + 1)], valid[i], valid[justice(j + 1)])) >
           abs(comp(valid[justice(j + 1)], valid[i], valid[j]))) {
      j++;
      if (j > flag)
        j = 1;
    }

    ans = max(ans, length(i, j));
  }
  cout << ans << endl;

  return 0;
}
