#include<bits/stdc++.h>

using namespace std;

struct node {
	int l,r,index;
};

int a[200100],pos[200100];
node q[200100];
long long ans[200100]={0};
long long sum=0;

bool cmp(const node&x,const node&y) {
	if (pos[x.l]!=pos[y.l])
		return pos[x.l]<pos[y.l];
	return pos[x.r]<pos[y.r];
}

map<long long,long long>s1;
long long s[1000100];

inline void insert(int k) {
	sum+=(s[k]*2+1)*k;
	s[k]++;
}

inline void erase(int k) {
	sum+=(-s[k]*2+1)*k;
	s[k]--;
}

int main() {
	int n,t;
	scanf("%d%d",&n,&t);
	for (int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
	}
	int limit=(int)sqrt(double(n)+0.5);
	for (int i=1;i<=n;i++) {
		pos[i]=(i-1)/limit+1;
	}
	for (int i=1;i<=t;i++) {
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].index=i;
	}
	sort(q+1,q+t+1,cmp);
	for (int i=q[1].l;i<=q[1].r;i++) {
		sum-=s[a[i]]*s[a[i]]*a[i];
		s[a[i]]++;
		sum+=s[a[i]]*s[a[i]]*a[i];
	}
	int left=q[1].l,right=q[1].r;
	ans[q[1].index]=sum;
	for (int i=2;i<=t;i++) {
		while (right < q[i].r) insert(a[++right]);
		while (left > q[i].l) insert(a[--left]);
		while (right > q[i].r) erase(a[right--]);
		while (left < q[i].l) erase(a[left++]);
		ans[q[i].index]=sum;
	}
	for (int i=1;i<=t;i++) {
		printf("%I64d\n",ans[i]);
	}
//	system("pause");
	return 0;
}