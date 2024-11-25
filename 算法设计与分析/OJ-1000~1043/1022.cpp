#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<string>
#include<stack>
#include<cmath>
using namespace std;
string a,b;
int dp[505][505];

int main(){
	int t;
	cin>>t;
	while(t--){
		for(int i=0;i<505;i++)
			for(int j=0;j<505;j++)
				dp[i][j]=0;
		cin>>a>>b;
		for(int i=1;i<=a.length();i++){
			for(int j=1;j<=b.length();j++){
				if(a[i-1]==b[j-1]){
					dp[i][j]=max(dp[i][j],dp[i-1][j-1]+1);
				}
				else{
					dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
				}
			}
		}
		cout<<dp[a.length()][b.length()]<<endl;
	}
	return 0; 
	
} 