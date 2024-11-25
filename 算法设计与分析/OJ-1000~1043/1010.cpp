#include "iostream"
#include <vector>
#include <string>
using namespace  std;
int n,target;
long long num[20005];
int main(){	
	int t;
	cin>>t;
	while (t--) {
		cin>>n>>target;
		for(int i=0;i<n;i++)cin>>num[i];
		int l=0,r=n-1;
		int flag=1;
		int mid,pre;
		while(l<=r){
			pre=mid;
			mid=l+(r-l)/2;
			if(num[mid]==target){
				cout<<"success, father is "<<num[pre]<<endl;
				flag=0;
				break;
			}
			else if(num[mid]>target){
				r=mid-1;
			}
			else{
				l=mid+1;
			}
		}
		if(flag)
			cout<<"not found, father is "<<num[mid]<<endl;
	}
	return 0;
}
