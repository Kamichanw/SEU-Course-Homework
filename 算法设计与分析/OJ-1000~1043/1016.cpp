#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<string>
#include<stack>
#include<cmath>
using namespace std;


int main(){
	int t;
	cin>>t;
	while(t--){
		int n,x;
		cin>>n>>x;
		vector<int>v;
		while(n--){
			int a;
			cin>>a;
			v.push_back(a);
		}
		sort(v.begin(),v.end());
		int l=0,r=v.size()-1;
		int flag=1;
		while(l<r){
			if(v[l]+v[r]==x){
				cout<<"yes"<<endl;
				flag=0;
				break;
			}
			else if(v[l]+v[r]>x)
				r--;
			else l++;
		}
		if(flag)cout<<"no\n";
	}
	return 0; 
	
} 