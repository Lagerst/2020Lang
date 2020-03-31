
#include<cstdio>

typedef long long LL;

LL inv(LL t, LL p) 

{//��t����p����Ԫ��ע��:tҪС��p����ô���ǰ�Ȱ�t%pһ�� 

    return t == 1 ? 1 : (p - p / t) * inv(p % t, p) % p;

}


void exgcd(int a, int b, int &x, int &y) 

{//��չŷ���������Ԫ

    if(0 == b){

        x = 1, y = 0;

        return ;

    }

    exgcd(b, a%b, x, y);

    int flag = x;

    x = y;

    y = flag - a/b * y;

}

//����С����
//����p����������gcd(a,p)=1����ô a(p-1)��1��mod p��
//�� k* b mod m = 1 �� b ^ (m-1) mod m = 1 ���� k* b = b ^ (m-1)
//��ֱ�ӵó�b��ģm�˷���ԪΪ b ^ (m-2)
//���㷨�г�ģ1e9+7Ϊ���������÷���С����ת����


int main()

{

    LL a, p;

    while(~scanf("%lld%lld", &a, &p))

    {

        printf("%lld\n", inv(a%p, p));

    }





}



//*��չŷ�����

ll extend_gcd(ll a, ll b, ll &x, ll &y) {

    if (b == 0) {

        x = 1, y = 0;

        return a;

    }

    else {

        ll r = extend_gcd(b, a % b, y, x);

        y -= x * (a / b);

        return r;

    }

}

ll inv(ll a, ll n) {

    ll x, y;

    extend_gcd(a, n, x, y);

    x = (x % n + n) % n;

    return x;

}
*/
