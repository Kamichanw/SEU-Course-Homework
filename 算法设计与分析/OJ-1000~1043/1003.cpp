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
		int n;
		cin>>n;
		vector<int> num;
		while(n--){
			int temp;
			cin>>temp;
			num.push_back(temp);
		}
		for(int i=1;i<num.size();i++){
			if(num[i-1]>num[i])swap(num[i-1],num[i]);
		}
		for(auto x:num)cout<<x<<" ";
		cout<<endl;
	}
	return 0; 
	
} 