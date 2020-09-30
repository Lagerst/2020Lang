#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 300;
string st;
int a[maxn] = {0};
unsigned long long h[maxn][30] = {0};
unsigned long long poww(int a, unsigned long long b) {
  unsigned long long ans = 1, base = a;
  while (b != 0) {
    if (b & 1 != 0)
      ans *= base;
    base *= base;
    b >>= 1;
  }
  return ans;
}
int main() {
  cin >> st;
  for (int i = st.length() - 1; i >= 0; i--) {
    a[i] = st[i] - 'a';
    h[i][0] = a[i];
  }
  int j = 1;
  unsigned long long temp = 163;
  while (1) {
    for (int i = 0; i < st.length(); i++) {
      if (i + (1 << (j - 1)) <= maxn)
        h[i][j] = h[i][j - 1] * temp + h[i + (1 << (j - 1))][j - 1];
    }
    temp *= temp;
    j++;
    if (1 << j >= st.length())
      break;
  }
  // for (int i=0;i<st.length();i++){
  //	for (int j=0;j<=3;j++){
  //		cout<<h[i][j]<<' ';
  //	}
  //	cout<<endl;
  //}
  int n, l, r;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &l, &r);
    l--;
    r--;
    unsigned long long temp = 0;
    while (l <= r) {
      int j = 0;
      while (l + (1 << j) <= r) {
        j++;
      }
      j--;
      if (j == -1)
        j++;
      temp = temp * (poww(163, 1 << j)) + h[l][j];
      l += 1 << j;
    }
    cout << temp << endl;
  }
  return 0;
}