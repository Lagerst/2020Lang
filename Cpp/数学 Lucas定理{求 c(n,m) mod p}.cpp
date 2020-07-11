
//Lucas定理实现C(n,m)%p的代码：
//Lucas定理最大的数据处理能力是p在10^5左右，用来解决大组合数求模，p为素数


#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N =1e5;

ll n, m, p, fac[N];

void init()

{

    int i;

    fac[0] =1;

    for(i =1; i <= p; i++)

        fac[i] = fac[i-1]*i % p;

}

ll q_pow(ll a, ll b)

{

    ll  ans =1;

    while(b)

    {

        if(b &1)  ans = ans * a % p;

        b>>=1;

        a = a*a % p;   

    }

    return  ans;

}

 

ll C(ll n, ll m)

{

    if(m > n)  return 0;

    return  fac[n]*q_pow(fac[m]*fac[n-m], p-2) % p;

}

 

ll Lucas(ll n, ll m )

{

    if(m ==0)  return 1;

    else return  (C(n%p, m%p)*Lucas(n/p, m/p))%p;

}

 

int main()

{

    int t;

    scanf("%d", &t);

    while(t--)

    {

        scanf("%I64d%I64d%I64d", &n, &m, &p);

        init();

        printf("%I64d\n", Lucas(n, m));

    }

    return 0;

}

