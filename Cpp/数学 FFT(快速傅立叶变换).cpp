//多项式乘法
// http://codeforces.com/gym/100783 题C
#include <bits/stdc++.h>

using namespace std;
typedef complex<double> cd;         //复数类的定义
const int maxl = 2094153;           // nlogn的最大长度
const double PI = 3.14159265358979; //圆周率
int d, n, m;
cd b[maxl], a[maxl];
bool s[maxl] = {0};

int rev[maxl]; //用于储存二进制反转的结果
void getrev(int bit) {
  for (int i = 0; i < (1 << bit); i++) { //高位决定二进制数的大小
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
  } //能保证(x>>1)<x,满足递推性质
}

void fft(cd *a, int n, int dft) { //变换主要过程
  for (int i = 0; i < n; i++) {   //按照二进制反转
    if (i < rev[i]) //保证只把前面的数和后面的数交换,(否则数组会被翻回来)
      swap(a[i], a[rev[i]]);
  }
  for (int step = 1; step < n; step <<= 1) { //枚举步长的一半
    cd wn = exp(cd(0, dft * PI / step));     //计算单位复根
    for (int j = 0; j < n; j += step << 1) { //对于每一块
      cd wnk(1, 0); //!!每一块都是一个独立序列,都是以零次方位为起始的
      for (int k = j; k < j + step; k++) { //蝴蝶操作处理这一块
        cd x = a[k];
        cd y = wnk * a[k + step];
        a[k] = x + y;
        a[k + step] = x - y;
        wnk *= wn; //计算下一次的复根
      }
    }
  }
  if (dft == -1) { //如果是反变换,则要将序列除以n
    for (int i = 0; i < n; i++)
      a[i] /= n;
  }
}

bool ft[maxl];

int main() {
  int temp, maxq = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &temp);
    ft[temp] = 1;
    a[temp] = double(1);
    b[temp] = double(1);
    if (temp > maxq) {
      maxq = temp;
    }
  }
  int bit = 1, s = 2;
  for (bit = 1; (1 << bit) < 2 * maxq - 1; bit++) {
    s <<= 1; //找到第一个二的整数次幂使得其可以容纳这两个数的乘积
  }

  getrev(bit);
  fft(a, s, 1);
  fft(b, s, 1); // dft

  for (int i = 0; i < s; i++)
    a[i] *= b[i]; //对应相乘

  fft(a, s, -1); // idft

  for (int i = 1; i <= 2 * maxq; i++) {
    if ((int)(a[i].real() + 0.5) != 0) { //精度误差
      ft[i] = 1;
    }
  }
  long long ans = 0;
  scanf("%d", &m);
  for (int q = 1; q <= m; q++) {
    scanf("%d", &d);
    if (ft[d] == 1) {
      ans++;
    }
  }
  cout << ans << endl;
  //	system("pause");
  return 0;
}
