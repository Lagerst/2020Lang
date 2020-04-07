#include<bits/stdc++.h>
using namespace std;

int a[10005],b[10005],c[10005];
long long n,m,k,p,cnt=0;
char goal[10005];

int comb(int a[],int b[],int length1,int length2){
	int goal[10005]={0},sum[10005]={0},start=0;
	for (int i=0;i < length1;i++){
		start=i;
		for (int j=0;j < length2;j++){
			sum[start]+=a[i]*b[j];
			start++;
		}
	}	int i=0;
	for (i=0;i < start;i++){
		sum[i+1]+=sum[i]/10;
		sum[i]=sum[i]%10;
	}
	while (sum[i]==0){
		i--;
	}
	for (int j=i;j>=0;j--){
		a[j]=sum[j];
	}
	return i+1;
}


int main()
{
	scanf("%lld",&m);
while (m--){
	scanf("%lld",&n);
	if (n<=0){
		cout<<0<<endl;
		continue;
	}

		long long sum1,sum2,sum3;
		sum1=n;sum2=n+1;sum3=n+2;
		if (n%2==0)
			sum1=n/2;
		else{
			sum2=(n+1)/2;
		};
		if (n%3==0){
			sum1=sum1/3;
		}
		else if(sum2%3==0){
			sum2=sum2/3;
		}
		else{
			sum3=sum3/3;
		}

		int p1=0;
		while (sum1){
			a[p1++]=sum1%10;
			sum1/=10;
		}
		int p2=0;
		while (sum2){
			b[p2++]=sum2%10;
			sum2/=10;
		}
		int p3=0;
		while (sum3){
			c[p3++]=sum3%10;
			sum3/=10;
		}


		p1=comb(a,a,p1,p1);
		p2=comb(b,b,p2,p2);
		p3=comb(c,c,p3,p3);
		p2=comb(b,c,p2,p3);
		p1=comb(a,b,p1,p2);

		for (int i=p1-1;i>=0;i--){
			cout<<a[i];
		}
		cout<<endl;

	}
    return 0;
}