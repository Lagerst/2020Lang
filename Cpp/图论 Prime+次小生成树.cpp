// ConsoleApplication5.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define scanf scanf_s

#include "bits/stdc++.h"
using namespace std;

const int maxn = 2020;

typedef struct {
  int head;
  long long dis;
  int index;
} node;

vector<node> matrix[maxn];
long long low_dis[maxn];
bool uni[maxn] = {false};
long long max_dis[maxn][maxn] = {0};
bool used[200200] = {0};
int n, m, a[200200], b[200200], flag, low_dis_record[maxn], record,
    low_dis_index[maxn], record_index;
long long c[200200], sum = 0;

int main() {
  long long INT_MAX1 = 1e18 + 1000;
  scanf("%d%d", &n, &m);
  for (int i = 2; i <= n; i++) {
    low_dis[i] = INT_MAX1;
  }
  uni[1] = 1;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%lld", &a[i], &b[i], &c[i]);
    node temp;
    temp.dis = c[i];
    temp.head = b[i];
    temp.index = i;
    matrix[a[i]].push_back(temp);
    temp.head = a[i];
    matrix[b[i]].push_back(temp);
  }
  flag = 1;
  for (int i = 1; i < n; i++) {
    for (vector<node>::iterator iter = matrix[flag].begin();
         iter != matrix[flag].end(); iter++) {
      int temp = (*iter).head;
      if (!uni[temp] && low_dis[temp] > (*iter).dis) {
        low_dis[temp] = (*iter).dis;
        low_dis_record[temp] = flag;
        low_dis_index[temp] = (*iter).index;
      }
    }

    long long min_w = INT_MAX1;
    for (int j = 1; j <= n; j++) {
      if (!uni[j] && low_dis[j] < min_w) {
        min_w = low_dis[j];
        flag = j;
        record = low_dis_record[j];
        record_index = low_dis_index[j];
      }
    }
    uni[flag] = 1;
    sum += min_w;
    used[record_index] = 1;
    for (int i = 1; i <= n; i++) {
      if (uni[i] && i != flag) {
        max_dis[i][flag] = max(max_dis[i][record], min_w);
        max_dis[flag][i] = max_dis[i][flag];
      }
    }
  }
  flag = 0;
  for (int i = 1; i <= m; i++) {
    if (!used[i]) {
      if (c[i] <= max_dis[a[i]][b[i]]) {
        flag = 1;
        break;
      }
    }
  }
  if (flag == 1) {
    cout << "zin" << endl;
  } else {
    cout << "ogisosetsuna" << endl;
  }
  return 0;
}
