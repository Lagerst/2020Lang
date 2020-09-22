#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e8 + 10;
char str[N];
int nex[N];
void getNex(char *str) {
  memset(nex, 0, sizeof nex);
  for (int i = 2, j = 0; str[i]; i++) {
    while (j > 0 && str[i] != str[j + 1])
      j = nex[j];
    if (str[i] == str[j + 1])
      j++;
    nex[i] = j;
  }
}
void solve() {
  /*计算答案并输出*/
  getNex(str);
  int n = strlen(str) - 1;
  if (n % (n - nex[n]))
    puts("1");
  else
    printf("%d\n", n / (n - nex[n]));
}
int main() {
  for (int i = 0; i < 1e8; i++) {
    str[i + 1] = '1';
  }
  str[int(1e8) + 2] = '\0';
  str[0] = '*';
  solve();
  while (scanf("%s", str + 1) && str[1] != '.') {
    str[0] = '*';
    solve();
  }
  return 0;
}