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
bool isexcept[100005];
long long cost[100005];
long long needs[100005];
int main(){
	int t;
	cin>>t;
	
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>cost[i];
		}
		for(int i=1;i<=n;i++)cin>>needs[i];
		long long ans=0;
		int bf=cost[1],bfday=1;
		for(int i=1;i<=n;i++){
			
			if(i-bfday+bf<cost[i])	{
				ans += needs[i]*(i-bfday+bf);
			}
			else{
				ans += needs[i]*cost[i];
				bf=cost[i];
				bfday=i;
			}
			
		}
		cout<<ans<<endl;
	}
	return 0; 
	
} 