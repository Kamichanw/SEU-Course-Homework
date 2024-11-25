#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<string>
#include<stack>
#include<cmath>// 0 0 0 0 0 1 1 1 1 1
using namespace std;

int main(){
	int t;
	cin>>t;
	while(t--){
		stack<int> white,black;
		int n;
		int ans=0;
		cin>>n;
		for(int i=1;i<=2*n;i++){
			int a;
			cin>>a;
			if(a==1){
				if(white.empty()){
					black.push(i);
				}
					
				else{
					ans += i-white.top();
					white.pop();
					
				}
			}
			if(a==0){
				if(black.empty()){
					white.push(i);
				}
				
				else{
					ans += i-black.top();
					black.pop();;
				}
			}
			
			
		}
		cout<<ans<<endl;
	}
	return 0; 
	
} 