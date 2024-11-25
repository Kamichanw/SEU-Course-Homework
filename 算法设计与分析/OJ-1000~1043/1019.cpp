#include "iostream"
#include <vector>
#include <string>
#include<algorithm>
using namespace  std;
int dp[10000];
int w[10000];
int value[10000];
int main(){	
	int t;
	cin>>t;
	while (t--) {
		for(int i=0;i<10000;i++){
			dp[i]=0;
			w[i]=0;
			value[i]=0;
	}
			
		int n,c;
		cin>>n>>c;
		for(int i=0;i<n;i++){
			cin>>w[i];
			cin>>value[i];
		}
		for(int i=0;i<n;i++){
			for(int j=c;j>=w[i];j--)
				dp[j]=max(dp[j],dp[j-w[i]]+value[i]);
		}
		
		cout<<dp[c]<<endl;
	}
	return 0;
}
