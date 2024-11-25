#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<string>
#include<stack>
#include<cmath>
#include<set>
using namespace std;
long long dp[25][25];
int num[25];
long long sum(int i,int j){
	long long a=0;
	for(int k=i;k<=j;k++){
		a+=num[k];
	}
	return a;
	
}
int main(){
	int t;
	cin>>t;
	while(t--){
		for(int i=0;i<25;i++)
			for(int j=0;j<25;j++)
				dp[i][j]=0;
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>num[i];
		}
		dp[1][0]=num[1];
		for(int i=2;i<=n;i++)
			dp[i][0]=dp[i-1][0]+num[i];
		for(int i=2;i<=n;i++){
			for(int j=1;j<=min(i-1,k);j++){
				for(int l=2;l<=n;l++){
					dp[i][j]=max(dp[i][j],dp[l-1][j-1]*sum(l,i));
				}
				
			}
		}
		cout<<dp[n][k]<<endl;
		
		
		
	}
	return 0; 
	
} 