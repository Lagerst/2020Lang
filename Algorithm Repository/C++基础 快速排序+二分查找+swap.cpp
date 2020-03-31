#include<iostream>
#include<fstream>

using namespace std;

ifstream filecin("filein.txt");
ofstream filecout("fileout.txt");

int swap_s(int *a;int *b) {
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
	return 0;
}

void quick_sort(int a[],int l,int r){
	int i=l,j=r;
	int temp=a[(l+r)/2];
	while (i<=j){
		while (a[j]>temp)
			j--;
		while (a[i]<temp)
			i++;
			if (i<=j){
				swap(a[i++],a[j--]);
			}
	}
	if (l<j)
		quick_sort(a,l,j);
	if (r>i)
		quick_sort(a,i,r);
}

int binary_search(int a[],int l,int r,int k){
	int mid=(l+r)/2;
	if (l==r&&k!=a[mid])
		return 0;
	if (a[mid]>k)
		return binary_search(a,l,mid-1,k);
	else if (a[mid]<k)
		return binary_search(a,mid+1,r,k);
	else 
		return mid;
}

int count(int a[],int pos,int k,int n){
	if (pos==0)
	 	return 0;
	int cnt=0,r=a[pos],j=pos;
	while (j>0&&a[j]==a[pos]){
		cnt++;
		j--;
	}
	j=pos+1;
	while (j<=n&&a[j]==a[pos]){
		cnt++;
		j++;
	}
	return cnt;
}

int main(){
	int n,a[5000]={0};
	filecin>>n;
	for (int i=1;i<=n;i++){
		filecin>>a[i];
	}
	quick_sort(a,1,n);
	for (int i=1;i<=n;i++){
		filecout<<a[i]<<' ';
	}
	filecout<<endl;
	
	int k;
	filecin>>k;
	filecout<<count(a,binary_search(a,1,n,k),k,n)<<endl;
	
	filecin.close();
	filecout.close();
	return 0;
}