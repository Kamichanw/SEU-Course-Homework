#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<string>
#include<stack>
#include<cmath>
using namespace std;
int num[1005];
int res[1005];
int n;
void quicks(int left,int right,int times){
	if(left>=right)return;
	if(left+1==right){
		if(num[left]>num[right])swap(num[left],num[right]);
		return;
	}
	int base=num[left];
	int l=left;
	for(int i=left+1;i<=right;i++){
		if(num[i]<base){
			l++;
			swap(num[l],num[i]);
		}
	}
	swap(num[left],num[l]);
	if(times==0){
		res[l]=num[l];
	}
	if(times==1){
		for(int i=left;i<=right;i++)
			res[i]=num[i];
	}
	quicks(left,l-1,times+1);
	quicks(l+1,right,times+1);
	
}

int main(){
	int t;
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=0;i<n;i++)cin>>num[i];
		quicks(0,n-1,0);
		for(int i=0;i<n;i++)cout<<res[i]<<" ";
		cout<<endl;
	}
	return 0; 
	
} 