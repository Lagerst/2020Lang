
#include<cstdio>

typedef long long LL;

LL inv(LL t, LL p) 

{//求t关于p的逆元，注意:t要小于p，最好传参前先把t%p一下 

    return t == 1 ? 1 : (p - p / t) * inv(p % t, p) % p;

}


void exgcd(int a, int b, int &x, int &y) 

{//扩展欧几里得求逆元

    if(0 == b){

        x = 1, y = 0;

        return ;

    }

    exgcd(b, a%b, x, y);

    int flag = x;

    x = y;

    y = flag - a/b * y;

}

//费马小定理
//假如p是质数，且gcd(a,p)=1，那么 a(p-1)≡1（mod p）
//则 k* b mod m = 1 且 b ^ (m-1) mod m = 1 所以 k* b = b ^ (m-1)
//可直接得出b的模m乘法逆元为 b ^ (m-2)
//在算法中常模1e9+7为质数，可用费马小定理转换。


int main()

{

    LL a, p;

    while(~scanf("%lld%lld", &a, &p))

    {

        printf("%lld\n", inv(a%p, p));

    }





}



//*扩展欧几里得

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
