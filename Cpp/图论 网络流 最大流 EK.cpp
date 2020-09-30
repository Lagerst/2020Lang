#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3000;
#define inf 2147483640

int flow[MAXN][MAXN];
int a[MAXN], b[MAXN];
int sum = 0;
int n, m;

int EK(int s, int t) {
  queue<int> q;
  int p[MAXN * 2], a[MAXN * 2];
  int f = 0;
  while (1) {
    memset(a, 0, sizeof(a));
    a[s] = 19;
    q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int v = 0; v <= t; ++v)
        if (!a[v] && flow[u][v]) {
          p[v] = u, q.push(v);
          a[v] = min(a[u], flow[u][v]);
          if (v == t)
            break;
        }
    }
    if (a[t] == 0)
      break;
    for (int u = t; u != s; u = p[u]) {
      flow[p[u]][u] -= a[t];
      flow[u][p[u]] += a[t];
    }
    f += a[t];
  }
  if (sum == f) {
    cout << "Yes" << endl;
    for (int i = 1; i <= n; i++) {
      for (int j = n + 1; j <= m + n; j++) {
        cout << 20 - flow[i][j] << ' ';
      }
      cout << endl;
    }
  } else {
    cout << "No" << endl;
  }
  return f;
}

int main() {
  cin >> n >> m;
  int sum1 = 0;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    flow[0][i] = a[i] - m;
    sum1 += a[i] - m;
  }
  for (int i = 1; i <= m; i++) {
    cin >> b[i];
    flow[n + i][n + m + 1] = b[i] - n;
    sum += b[i] - n;
  }
  if (sum1 != sum) {
    cout << "No" << endl;
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = n + 1; j <= n + m; j++) {
      flow[i][j] = 19;
    }
  }
  EK(0, n + m + 1);
  return 0;
}