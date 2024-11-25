#include "iostream"
#include <vector>
#include <string>
#include<algorithm>
using namespace std;
int dp[10005];
long long num[10005];
int main(){	
	int t;
	std::cin>>t;
	while (t--) {
		int n;
		std::cin>>n;
		for(int i=1;i<=n;i++){
			std::cin>>num[i];
			
		}
		dp[1]=num[1];
		int ans=1;
		for(int i=2;i<=n;i++){
			if(num[i]>=dp[ans])dp[++ans]=num[i];
			else{
				int j=upper_bound(dp+1,dp+ans+1,num[i])-dp;
				dp[j]=num[i];//由于是求最长上升子序列，答案数组是递增的，所以可以用二分查找，然后将大于num i中最小的那个数替换掉，可以增大解空间
			}
			
		}
		std::cout<<ans<<std::endl;
		
	}
	return 0;
}
