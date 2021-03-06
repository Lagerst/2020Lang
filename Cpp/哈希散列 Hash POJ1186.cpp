// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
// Hash

#include "stdafx.h"
#include <iostream>

using namespace std;

const int maxn = 4000037;
int n, m, ans = 0;
int n1;
int k[10], p[10];
int h[maxn] = {0}, l[maxn] = {0};
bool use[maxn] = {0};

int locate(int s) {
  int temp = s;
  while (temp < 0)
    temp += maxn;
  while (temp >= maxn)
    temp -= maxn;
  while (use[temp] && h[temp] != s) {
    temp++;
    if (temp >= maxn) {
      temp -= maxn;
    }
  }
  return temp;
}

void insert(int s) {
  int pos = locate(s);
  h[pos] = s;
  use[pos] = 1;
  l[pos]++;
}

void lefthalf(int num, int s) {
  int i, j, temp;
  if (num == n1) {
    insert(s);
    return;
  }
  for (int i = 1; i <= m; i++) {
    temp = k[num + 1];
    if (temp != 0 && i != 1)
      for (int j = 1; j <= p[num + 1]; j++) {
        temp *= i;
      }
    lefthalf(num + 1, s + temp);
  }
}

void righthalf(int num, int s) {
  int i, j, temp, pos;
  if (num == n) {
    s = -s;
    pos = locate(s);
    if (h[pos] == s) {
      ans += l[pos];
    }
    return;
  }
  for (int i = 1; i <= m; i++) {
    temp = k[num + 1];
    if (temp != 0 && i != 1)
      for (int j = 1; j <= p[num + 1]; j++) {
        temp *= i;
      }
    righthalf(num + 1, s + temp);
  }
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> k[i] >> p[i];
  }
  n1 = n / 2;
  lefthalf(0, 0);
  righthalf(n1, 0);
  cout << ans << endl;
  system("pause");
  return 0;
}