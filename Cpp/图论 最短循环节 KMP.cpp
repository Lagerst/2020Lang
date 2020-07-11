#include<iostream>
#include<cstdio>
#include<string.h>
//最短循环节,KMP,
//样例 
// 1000
// 7
// abcabca 
// Output 3 abc 

using namespace std;

#define next next2
int next[100100];
char st[100100];

void getnext(int len){      
    int i=0,j=-1;
    next[0]=-1;
    while(i<len){
        if(j==-1 || st[i]==st[j]){
            i++;j++;
            next[i]=j;
        }else
            j=next[j];
    }
}

int main(){
	int t,n;
	scanf("%d\n",&t);
	while (t--){
		scanf("%d\n",&n);
		gets(st);
		getnext(n);
		int i=n-1;
		//cout<<i<<' '<<next[i]<<endl;
		bool flag=1;
		int p=n-next[n];
		for (int i=0;i<n-p;i++){
			if (st[i]!=st[i+p]){
				flag=0;
				break;
			} 
		} 
		if (flag)
		{
			cout<<p<<endl;
			for (int j=0;j<p;j++){
				cout<<st[j]; 
			}
			cout<<endl;
		} else{
			cout<<n<<endl<<st<<endl;
		}
	} 
}
