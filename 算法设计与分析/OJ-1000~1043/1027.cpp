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
int dp[10010];
struct ev{
	int s;
	int e;
	int w;
	bool operator < (const ev & b)const{
		return e<b.e;
	}
};

int main(){
	int t;
	cin>>t;
	while(t--){
		vector<ev> evs;
		int n;
		cin>>n;
		for(int i=0;i<n;i++){
			ev temp;
			cin>>temp.s>>temp.e>>temp.w;
			evs.emplace_back(temp);
			
		}
		sort(evs.begin(),evs.end());
		for(int i=0;i<10010;i++){
			dp[i]=0;
		}
		int bef=0,now;
		for(ev x:evs){
			now=x.e;
			for(;bef<now;bef++)
				dp[bef+1]=dp[bef];
			dp[x.e]=max(dp[x.s]+x.w,dp[x.e]);
		}
		cout<<dp[evs[n-1].e]<<endl;
	}
	return 0; 
	
} 