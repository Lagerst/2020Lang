//����ʽ�˷�
// http://codeforces.com/gym/100783 ��C
#include <bits/stdc++.h>

using namespace std;
typedef complex<double> cd;         //������Ķ���
const int maxl = 2094153;           // nlogn����󳤶�
const double PI = 3.14159265358979; //Բ����
int d, n, m;
cd b[maxl], a[maxl];
bool s[maxl] = {0};

int rev[maxl]; //���ڴ�������Ʒ�ת�Ľ��
void getrev(int bit) {
  for (int i = 0; i < (1 << bit); i++) { //��λ�������������Ĵ�С
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
  } //�ܱ�֤(x>>1)<x,�����������
}

void fft(cd *a, int n, int dft) { //�任��Ҫ����
  for (int i = 0; i < n; i++) {   //���ն����Ʒ�ת
    if (i < rev[i]) //��ֻ֤��ǰ������ͺ����������,(��������ᱻ������)
      swap(a[i], a[rev[i]]);
  }
  for (int step = 1; step < n; step <<= 1) { //ö�ٲ�����һ��
    cd wn = exp(cd(0, dft * PI / step));     //���㵥λ����
    for (int j = 0; j < n; j += step << 1) { //����ÿһ��
      cd wnk(1, 0); //!!ÿһ�鶼��һ����������,��������η�λΪ��ʼ��
      for (int k = j; k < j + step; k++) { //��������������һ��
        cd x = a[k];
        cd y = wnk * a[k + step];
        a[k] = x + y;
        a[k + step] = x - y;
        wnk *= wn; //������һ�εĸ���
      }
    }
  }
  if (dft == -1) { //����Ƿ��任,��Ҫ�����г���n
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
    s <<= 1; //�ҵ���һ��������������ʹ��������������������ĳ˻�
  }

  getrev(bit);
  fft(a, s, 1);
  fft(b, s, 1); // dft

  for (int i = 0; i < s; i++)
    a[i] *= b[i]; //��Ӧ���

  fft(a, s, -1); // idft

  for (int i = 1; i <= 2 * maxq; i++) {
    if ((int)(a[i].real() + 0.5) != 0) { //�������
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
