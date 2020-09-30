#include "bits/stdc++.h"

using namespace std;

const int maxn = 2e5 + 10;
int a[maxn] = {0};
vector<int> b;

int main() {
  int n, len = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= n; i++) {
    vector<int>::iterator it = upper_bound(b.begin(), b.end(), a[i] - 1);
    if (it == b.end()) {
      b.push_back(a[i]);
    } else // if (*(it)!=a[i])
      *(it) = a[i];
  }
  cout << b.size() << endl;
  return 0;
}