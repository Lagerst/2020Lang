#include<bits/stdc++.h>
#define M 1000000007
using namespace std;

long long f[100100]={0};

long long inv(long long t,long long p)

{//��t����p����Ԫ��ע��:tҪС��p����ô���ǰ�Ȱ�t%pһ�� 

	return t == 1 ? 1 : (p - p / t) * inv(p % t,p) % p;

}

int main() {
	long long n;
	cin>>n;
	f[1]=1;
	for (long long i=2;i<=n;i++) {
		f[i]=(f[i-1]*(4*i-2)%M)*(inv(i+1,M)%M)%M;
	}
	cout<<f[n]<<endl;
	return 0;
}