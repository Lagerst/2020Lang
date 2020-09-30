// ConsoleApplication3.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define scanf scanf_s
#pragma warning(disable : 4996)

#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 300;
int a[maxn];
int po, maxindex;
int len[maxn] = {0};

int manacher(int n) {
  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (i < maxindex) {
      len[i] = min(maxindex - i, len[2 * po - i]);
    } else {
      len[i] = 1;
    }
    while (a[i - len[i]] == a[i + len[i]])
      len[i]++;
    if (len[i] + i > maxindex) {
      maxindex = len[i] + i;
      po = i;
    }
    ans = max(ans, len[i]);
  }
  return ans;
}

int main() {
  int p;
  scanf("%d", &p);
  while (p--) {
    int n;
    scanf("%d", &n);
    memset(a, 0, sizeof(a));
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[2 * i - 1]);
      a[2 * i - 2] = -1;
    }
    n = n * 2 + 1;
    a[n - 1] = -1;
    a[n] = 1e9 + 100;
    po = 0;
    maxindex = 0;
    memset(len, 0, sizeof(len));
    printf("%d\n", manacher(n) - 1);
  }
  return 0;
}

//模板

const int maxn = 1000010;
char str[maxn];      //原字符串
char tmp[maxn << 1]; //转换后的字符串
int Len[maxn << 1];
//转换原始串
int INIT(char *st) {
  int i, len = strlen(st);
  tmp[0] = '@'; //字符串开头增加一个特殊字符，防止越界
  for (i = 1; i <= 2 * len; i += 2) {
    tmp[i] = '#';
    tmp[i + 1] = st[i / 2];
  }
  tmp[2 * len + 1] = '#';
  tmp[2 * len + 2] = '$'; //字符串结尾加一个字符，防止越界
  tmp[2 * len + 3] = 0;
  return 2 * len + 1; //返回转换字符串的长度
}
// Manacher算法计算过程
int MANACHER(char *st, int len) {
  int mx = 0, ans = 0, po = 0; // mx即为当前计算回文串最右边字符的最大值
  for (int i = 1; i <= len; i++) {
    if (mx > i)
      Len[i] = min(mx - i, Len[2 * po - i]); //在Len[j]和mx-i中取个小
    else
      Len[i] = 1; //如果i>=mx，要从头开始匹配
    while (st[i - Len[i]] == st[i + Len[i]])
      Len[i]++;
    if (Len[i] + i > mx) //若新计算的回文串右端点位置大于mx，要更新po和mx的值
    {
      mx = Len[i] + i;
      po = i;
    }
    ans = max(ans, Len[i]);
  }
  return ans - 1; //返回Len[i]中的最大值-1即为原串的最长回文子串额长度
}