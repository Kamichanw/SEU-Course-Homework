#include<algorithm>
#include<iostream>

#include<vector>
#include<bitset>

using namespace std;
struct work{
	int day;
	long long pay;
}works[50005];

signed main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		
		
		int maxddl=0;
		for(int i=0;i<n;i++){
			cin>>works[i].day>>works[i].pay;
			maxddl=max(works[i].day,maxddl);
			
		}
		bool *isbusy=new bool[maxddl+1];
		for(int i=0;i<=maxddl;i++){
			isbusy[i]=false;
			
		}
		
		//if(n==1)cout<<work[0].pay;
		sort(works,works+n,[](const work &a,const work &b){
			if(a.pay!=b.pay)return a.pay>b.pay;
			return a.day>b.day;
		});
		long long ans=0;
		for(int i=0;i<n;i++){
			for(long long j=works[i].day;j>0;j--){
				if(isbusy[j]==false){
					isbusy[j]=true;
					ans += works[i].pay;
					break;
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0; 
	
} 