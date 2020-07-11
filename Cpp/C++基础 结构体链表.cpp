#include<iostream>
#include<stdlib.h>
#include<malloc.h>

using namespace std;

struct node{
	int data;
	node *left,*next;
};

void output(int x,int y){
	if (x>y) cout<<y<<' '<<x<<endl;
	else  cout<<x<<' '<<y<<endl;
}

int main(void){
	int n,m,k;
	node *p,*q,*w;
	cin>>m;
	free(&m);
	for (;m>0;m--){
		cin>>n>>k;
		n+=2;
		p=(node*)malloc(sizeof(node));
		(*p).data=1;
		w=p;
		for (int i=1;i<=n-1;i++){
			(*p).data=i;
			q=(node*)malloc(sizeof(node));
			(*q).left=p;
			(*p).next=q;
			p=q;
		}	
		(*p).data=n;
		(*p).next=w;
		(*w).left=p;
		p=(*w).left;
		for (int i=1;i<=n-2;i++){
			for (int j=1;j<=k;j++){
				p=(*p).next;
			}
			(*(*p).left).next=(*p).next;
			(*(*p).next).left=(*p).left;
			w=(*p).left;
			free(p);
			cout<<(*p).data<<endl;
			p=w;
		}
		output((*p).data,(*((*p).next)).data);
	}
}
