#include<stdio.h>
#include<iostream>
#include<fstream>

using namespace std;

int main(){
	int d;
	FILE *fp;
	FILE *fp2;
	fp=fopen("data.in","r");
	fp2=fopen("data.out","w");
 	fscanf(fp,"%d",&d);
 	fprintf(fp2,"%d\n",d);
	fclose(fp);
	fclose(fp2);
 
	return 0;


{
//	FILE2

//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
//	�ض������������ 

//	fclose(stdin);
//	fclose(stdin);
//	�ض�������������ر��ļ� 
}

{
//	FILE3

//	ifstream mycin("data.in");
//	mycin>>d;
//	mycin.close();

//	ofstream mycout("data.out");
//	mycout<<d<<endl;
//	mycout.close();
}

} 