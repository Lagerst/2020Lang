#include <iostream>

using namespace std;

int main(void) {
  int i = 0, j = 0, a[100];
  char c;
  while ((c = getchar()) != '\n') {
    if (c != ' ') {
      ungetc(c, stdin);
      cin >> a[i++];
    }
  }
  for (j = 0; j <= i - 1; j++) {
    cout << a[j];
  }
  cout << endl;
  return 0;
}