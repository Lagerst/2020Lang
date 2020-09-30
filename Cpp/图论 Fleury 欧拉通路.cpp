//�ڽӾ���+Fleury
#include <iostream>
#include <stack>
const int MAXN = 111;
using namespace std;

stack<int> S;
int edge[MAXN][MAXN];
int n, m;

void dfs(int x) {
  S.push(x);
  for (int i = 1; i <= n; i++) {
    if (edge[x][i] > 0) {
      edge[i][x] = edge[x][i] = 0; //ɾ���˱�
      dfs(i);
      break;
    }
  }
}

// Fleury�㷨��ʵ��
void Fleury(int x) {
  S.push(x);
  while (!S.empty()) {
    int b = 0;
    for (int i = 1; i <= n; i++) {
      if (edge[S.top()][i] > 0) {
        b = 1;
        break;
      }
    }
    if (b == 0) {
      printf("%d", S.top());
      S.pop();
    } else {
      int y = S.top();
      S.pop();
      dfs(y); //����У���dfs
    }
  }
  printf("\n");
}

int main() {
  scanf("%d%d", &n, &m); //���붥�����Լ�����
  memset(edge, 0, sizeof(edge));
  int x, y;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &x, &y);
    edge[x][y] = edge[y][x] = 1;
  }
  //��������������㣬��������������������Ӷ���0����
  int num = 0, start = 1;
  for (int i = 1; i <= n; i++) { //�ж��Ƿ����ŷ����·
    int degree = 0;
    for (int j = 1; j <= n; j++) {
      degree += edge[i][j];
    }
    if (degree & 1) {
      start = i, num++;
    }
  }
  if (num == 0 || num == 2) {
    Fleury(start);
  } else
    printf("No Euler Path\n");
  return 0;
}

// Set�ڽӱ�+Fleury
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 20;
int n, m, u, v, cnt[maxn] = {0}, oddcnt = 0;
int record[6] = {0};
set<int> matrix[maxn];
stack<int> s;

void dfs(int x) {
  s.push(x);
  int temp = x, pre;
  while (!matrix[temp].empty()) {
    pre = temp;
    temp = *(matrix[temp].begin());
    matrix[pre].erase(temp);
    matrix[temp].erase(pre);
    s.push(temp);
  }
}

void Fleury(int x) {
  s.push(x);
  while (!s.empty()) {
    int b = 0, temp = s.top();
    if (!matrix[temp].empty()) {
      b = 1;
    }
    if (!b) {
      printf("%d ", temp);
      s.pop();
    } else {
      s.pop();
      dfs(temp);
    }
  }
  printf("\n");
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &u, &v);
    cnt[u]++;
    cnt[v]++;
    matrix[u].insert(v);
    matrix[v].insert(u);
  }
  for (int i = 0; i < n; i++) {
    if (cnt[i] & 1) {
      record[++oddcnt] = i;
      if (oddcnt == 3)
        break;
    }
  }
  if (!(oddcnt == 0 || oddcnt == 2)) {
    cout << "No" << endl;
    return 0;
  }

  cout << "Yes" << endl;
  Fleury(record[1]);
  return 0;
}

// Vector�ڽӱ�+Fleury
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 20;
int n, m, u, v, cnt[maxn] = {0}, oddcnt = 0;
int record[6] = {0};
vector<int> matrix[maxn];
stack<int> s;

void erase_(int x, int y) {
  for (vector<int>::iterator it = matrix[x].begin(); it != matrix[x].end();
       it++) {
    if (*it == y) {
      matrix[x].erase(it);
      break;
    }
  }
}

void dfs(int x) {
  s.push(x);
  int temp = x, pre;
  while (!matrix[temp].empty()) {
    pre = temp;
    temp = *(matrix[temp].begin());

    erase_(pre, temp);
    erase_(temp, pre);

    s.push(temp);
  }
}

void Fleury(int x) {
  s.push(x);
  while (!s.empty()) {
    int b = 0, temp = s.top();
    if (!matrix[temp].empty()) {
      b = 1;
    }
    if (!b) {
      printf("%d ", temp);
      s.pop();
    } else {
      s.pop();
      dfs(temp);
    }
  }
  printf("\n");
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &u, &v);
    cnt[u]++;
    cnt[v]++;
    matrix[u].push_back(v);
    matrix[v].push_back(u);
  }
  for (int i = 0; i < n; i++) {
    if (cnt[i] & 1) {
      record[++oddcnt] = i;
      if (oddcnt == 3)
        break;
    }
  }
  if (!(oddcnt == 0 || oddcnt == 2)) {
    cout << "No" << endl;
    return 0;
  }

  cout << "Yes" << endl;
  Fleury(record[1]);
  return 0;
}