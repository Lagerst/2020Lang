// ConsoleApplication3.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define scanf scanf_s
#pragma warning(disable:4996)

#include<bits/stdc++.h>
using namespace std;

int head=0,tail=1,cnt=0,int o;
node *q[1000000];
char st[1000200],temp[60];

struct node{
	node *next[26];
	node *fail;
	int sum;
}*root;

void init(node *p){
	for (int i=0;i<26;i++){
		p->next[i]=NULL;
	}
	p->fail=NULL;
	p->sum=0;
}

void Insert(char *s)
{
	node *p=root;
	for (int i=0; s[i]; i++)
	{
		int x=s[i]-'a';
		if (p->next[x]==NULL)
		{
			node *newnode=(struct node *)malloc(sizeof(struct node));
			init(newnode);
			p->next[x]=newnode;
		}
		p=p->next[x];
	}
	p->sum++;
}

void build_fail_pointer()
{
	node *p;
	node *temp;
	head=0;
	tail=1;
	q[head]=root;
	while (head < tail)
	{
		temp=q[head++];
		for (int i=0; i<=25; i++)
		{
			if (temp->next[i])
			{
				if (temp==root)
					temp->next[i]->fail=root;
				else
				{
					p=temp->fail;
					while (p)
					{
						if (p->next[i])
						{
							temp->next[i]->fail=p->next[i];
							break;
						}
						p=p->fail;
					}
					if (p==NULL) temp->next[i]->fail=root;
				}
				q[tail++]=temp->next[i];
			}
		}
	}
}

void ac_automation(char *ch)
{
	node *p=root;
	int len=strlen(ch);
	for (int i=0; i < len; i++)
	{
		int x=ch[i]-'a';
		if (p==NULL)
			p=root;
		while (!p->next[x]&&p!=root&&p->fail!=NULL)
			p=p->fail;
		p=p->next[x];
		node *temp=p;
		while (temp!=root&&temp!=NULL){
			if (temp->sum>=0){
				cnt+=temp->sum;
				//temp->sum=0;
			}
			else
				break;
			temp=temp->fail;
		}
	}
}

void destroy(node *p){
	for (int i=0;i<26;i++){
		if (p->next[i]!=NULL){
			destroy(p->next[i]);
		}
	};
	free(p);
}

int main()
{
	scanf("%d\n",&o);
	while (o--){
		scanf("%s",st);
		int n;
		cnt=0;
		root=(struct node *)malloc(sizeof(struct node));
		init(root);
		scanf("%d\n",&n);
		for (int i=1;i<=n;i++){
			scanf("%s",temp);
			Insert(temp);
		}
		build_fail_pointer();
		ac_automation(st);
		cout<<cnt<<endl;
		destroy(root);
	}

	return 0;
}