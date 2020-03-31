#include<iostream>
#include<vector>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
	std::cin.tie(0);
    int n,t,l=0,r=0;
    vector<int> v;
    cin>>n;
    for (int i=0; i<n; i++) {
        cin>>t;
        v.push_back(t);
    }
    for (int i=0; i<n; i++) {
        cin>>t;
        if (t<v[i]) {
            l++;
        } else if (t>v[i]){
            r++;
        }
    }
    if (l==0) {
        printf("-1");
    } else {
        printf("%d", r / l + 1);
    }
}