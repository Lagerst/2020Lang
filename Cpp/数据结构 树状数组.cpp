#include<iostream>
#include<algorithm>
#include<cstdio>
#include<string.h>
//Ê÷×´Êý×é
int t,n,a[50050],b[50050],delta,l,j,r;
char st[10];

using namespace std;

#define lowbit(x) (x&-x)

void update(int i,int c){
	for (int k=i;k<=n;k+=lowbit(k)){
		b[k]+=c;
	}
}

int getsum(int k){
	int ans=0;
	for (int i=k;i>0;i-=lowbit(i)){
		ans+=b[i];
	}
	return ans;
}

int main(){
	cin>>t;
	int t1=t;
	for (;t>0;t--){
		cin>>n;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		for (int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			update(i,a[i]);
		}
		printf("Case %d:\n",t1-t+1);
		scanf("%s",st);
		while (st[0]!='E'){
			if (st[0]=='Q'){
				scanf("%d%d",&j,&r);
				printf("%d\n",getsum(r)-getsum(j-1));
			}
			else if (st[0]=='S'){
				scanf("%d%d",&l,&delta);
				update(l,-delta);
			}
			else if (st[0]=='A'){
				scanf("%d%d",&l,&delta);
				update(l,delta);
			}
			scanf("%s",st);
		}
	}
	return 0;
}