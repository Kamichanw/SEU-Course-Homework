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
int dp[505][505];
pair<int,int> matr[505];
int main(){
	int t;
	cin>>t;
	while(t--){
		for(int i=1;i<505;i++)dp[i][i]=0;
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>matr[i].first>>matr[i].second;
		}
		for(int x=1;x<n;x++){
			for(int i=1;i<=n-x;i++){
				int j=i+x;
				dp[i][j]=0x3f3f3f3f;
				for(int k=i;k<j;k++){
					int q=dp[i][k]+dp[k+1][j]+matr[i].first*matr[k].second*matr[j].second;
					if(q<dp[i][j])
						dp[i][j]=q;
				}
			}
		}
		cout<<dp[1][n]<<endl;
		
	}
	return 0; 
	
} 