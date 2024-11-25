
#include <iostream>
#include <algorithm>
#include <queue>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <functional>
double dp[1005];
int odds[1000];
using namespace std;
int main()
{
	int x;
	cin>>x;
	while(x--){
		int n;
		cin>>n;
		for(int i=1;i<n;i++){
			cin>>odds[i];
		}
		dp[0]=1.0;
		for(int i=1;i<n;i++){
			dp[i]=0;
		}
		for(int i=1;i<n;i++){
			for(int j=i;j>=1;j--){
				dp[j]=dp[j]*(100-odds[i])*1.0/100.0+dp[j-1]*odds[i]*1.0/100.0;
			}
			dp[0]=dp[0]*(100-odds[i])*1.0/100.0;
		}
		double ans=0;
		for(int i=0;i<n;i++){
			ans += (i+1) * dp[i];
		}
		printf("%.6lf\n",ans);
	}
	
	return 0;
}
