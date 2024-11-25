#include "iostream"
#include <vector>
#include <string>
using namespace  std;
int dp[1005];
int n;

int find1(vector<int>num){
	for(int i=0;i<=num.size();i++)dp[i]=0;
	int ans1=0;
	dp[0]=1;
	for(int i=1;i<num.size();i++){
		int temp=0;
		for(int j=0;j<i;j++){
			if(num[i]<=num[j])
				if(dp[j]>temp)temp=dp[j];
			
		}
		dp[i]=temp+1;
		if(dp[i]>ans1)ans1=dp[i];
	}
	return ans1;
	
}
int find2(vector<int>num){
	for(int i=0;i<=num.size();i++)dp[i]=0;
	int ans1=0;
	dp[0]=1;
	for(int i=1;i<num.size();i++){
		int temp=0;
		for(int j=0;j<i;j++){
			if(num[i]>=num[j])
				if(dp[j]>temp)temp=dp[j];
			
		}
		dp[i]=temp+1;
		if(dp[i]>ans1)ans1=dp[i];
	}
	return ans1;
	
}
int main(){	
	int t;
	cin>>t;
	while (t--) {
		cin>>n;
		vector<int> num;
		for(int i=1;i<=n;i++){
			int tt;
			cin>>tt;
			num.push_back(tt);
		}
		int ans1=find1(num);
		int ans2=find2(num);
		cout<<ans1<<" "<<ans2<<endl;
	}
	return 0;
}
