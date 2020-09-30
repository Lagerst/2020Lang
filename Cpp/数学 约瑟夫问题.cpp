// ConsoleApplication5.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define scanf scanf_s

#include "bits/stdc++.h"
using namespace std;

int ysf(int n, int m) {
  if (n == 1) {
    return 0;
  } else {
    return (ysf(n - 1, m) + m) % n;
  }
}

int main() {
  int n, m;
  while (1) {
    cin >> n >> m;
    if (n == 0 && m == 0)
      break;
    printf("%d\n", ysf(n, m) + 1);
  }
  return 0;
}
