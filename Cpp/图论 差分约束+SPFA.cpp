// ConsoleApplication5.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define scanf scanf_s

#include "bits/stdc++.h"
#define INT_MAX 2147483647
using namespace std;

const int maxn = 50500;
bool visited[maxn] = {0};
int x, y, c;
int dis[maxn] = {0};

struct node {
  int next, data;
} temp;

vector<node> matrix[maxn];
queue<int> slack;

void init(int n) {
  for (int i = 1; i <= n; i++) {
    node temp;
    temp.data = 0;
    temp.next = i;
    matrix[i - 1].push_back(temp);
    temp.data = -1;
    temp.next = i - 1;
    matrix[i].push_back(temp);
    dis[i] = -INT_MAX;
  }
  dis[0] = 0;
  slack.push(0);
  visited[0] = 1;
}

int main() {
  int k, n, x, y, c;
  scanf("%d%d", &k, &n);
  init(k);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d%d", &x, &y, &c);
    temp.next = y;
    temp.data = c;
    matrix[x - 1].push_back(temp);
  }
  while (1) {
    int j = slack.front();
    for (vector<node>::iterator iter = matrix[j].begin();
         iter != matrix[j].end(); iter++) {
      if (dis[(*iter).next] < dis[j] + (*iter).data) {
        dis[(*iter).next] = dis[j] + (*iter).data;
        if (!visited[(*iter).next]) {
          slack.push((*iter).next);
          visited[(*iter).next] = 1;
        }
      }
    }
    visited[j] = 0;
    slack.pop();
    if (slack.empty())
      break;
  }
  printf("%d\n", dis[k]);
  return 0;
}
