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
	string a;
	getline(cin,a);
	while(t--){
		getline(cin,a);
		int ans=0;
		for(int i=0;i<a.length();i++){
			if(a[i]>='0'&&a[i]<='9')
				ans++;
		}
		cout<<ans<<endl;
	}
	return 0; 
	
} 