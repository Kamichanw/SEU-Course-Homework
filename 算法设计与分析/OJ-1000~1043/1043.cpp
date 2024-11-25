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
int dp[105][10005];

int dfs(int k,int n){
	if(k==1)return n;
	if(n==0)return 0;
	if(dp[k][n]>0)return dp[k][n];
	int minans=10010;
	int l=1,r=n;
	while(l<=r){
		int mid=l+(r-l)/2;
		int t1=dfs(k-1,mid-1);
		int t2=dfs(k,n-mid);
		if(t1>t2){
			minans=min(minans,t1+1);
			r=mid-1;
		}
		else{
			minans=min(minans,t2+1);
			l=mid+1;
		}
	}
	dp[k][n]=minans;
	return minans;
	
}

int main(){
	int t;
	cin>>t;
	vector<pair<int,int>> da;
	int maxegg=0,maxfloor=0;
	while(t--){
		int a,b;
		cin>>a>>b;
		cout<<dfs(a,b)<<endl;
	}
	return 0; 
	
} 