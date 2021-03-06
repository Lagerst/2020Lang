// ConsoleApplication2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define scanf scanf_s

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>

using namespace std;

string t, s;
int n[10000] = {0};
int l1, l2;

void getnext() {
  int j, k;
  j = 0;
  k = -1;
  n[0] = -1;
  while (j < t.length() - 1) {
    if (k == -1 || t[j] == t[k]) {
      j++;
      k++;
      n[j] = k;
    } else {
      k = n[k];
    }
  }
} //改进前

void getnextval() {
  int j = 0, k = -1;
  n[0] = -1;
  while (j < t.length() - 1) {
    if (k == -1 || t[j] == t[k]) {
      j++;
      k++;
      if (t[j] == t[k]) {
        n[j] = n[k];
      } else {
        n[j] = k;
      }
    } else {
      k = n[k];
    }
  }
}

int KMP() {
  int i = 0, j = 0;
  while (
      i < l2 &&
      j < l1) { //有符号跟无符号数一起运算时全部当成无符号数处理,string.length()返回非标准int(无符号)
    if (j == -1 || s[i] == t[j]) {
      i++;
      j++;
    } else {
      j = n[j];
    }
  }
  if (j >= t.length())
    return (i - t.length());
  else
    return (-1);
}

void print_array(int a[]) {
  int l = t.length();
  for (int i = 0; i < l; i++) {
    printf("%4d", i);
  }
  cout << endl;
  for (int i = 0; i < l; i++) {
    printf("%4c", t[i]);
  }
  cout << endl;
  for (int i = 0; i < l; i++) {
    printf("%4d", a[i]);
  }
  cout << endl;
  cout << endl;
}

int main() {
  cin >> t;
  l1 = t.length();
  cin >> s;
  l2 = s.length();
  getnext();
  print_array(n);
  getnextval();
  print_array(n);
  cout << endl;
  cout << KMP();
  cout << endl;
  system("pause");
  return 0;
}
