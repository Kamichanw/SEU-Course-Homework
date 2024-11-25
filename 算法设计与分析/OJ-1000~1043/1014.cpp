#include "iostream"
#include <vector>
#include <string>
#include<algorithm>
using namespace  std;
int dp[50005];
int num[50005];
int main(){	
	int t;
	cin>>t;
	while (t--) {
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>num[i];
			dp[i]=num[i];
		}
		for(int i=2;i<=n;i++){
			if(dp[i-1]>0)dp[i]+=dp[i-1];
			
		}
		int ans=-0x3f3f3f3f;
		for(int i=1;i<=n;i++)
			if(ans<dp[i])ans=dp[i];
		cout<<ans<<endl;
		
	}
	return 0;
}
