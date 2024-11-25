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
int n;
void merge(int left,int mid,int right){
	int *temp=new int[right-left+1];
	int l=left,r=mid+1;
	int i=0;
	while(l<=mid&&r<=right){
		if(num[l]<num[r])
		temp[i++]=num[l++];
		else
			temp[i++]=num[r++];
	}
	while(l<=mid)temp[i++]=num[l++];
	while(r<=right)	temp[i++]=num[r++];
	int k=0;
	for(i=left;i<=right;i++)
		num[i]=temp[k++];
	delete []temp;
}
void parti(int l,int r,int times){
	if(l<r){
		int mid=(l+r)/2;
		parti(l,mid,times+1);
		parti(mid+1,r,times+1);
		if(times>=2)
		merge(l,mid,r);
	}
}
int main(){
	int t;
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=0;i<n;i++)cin>>num[i];
		parti(0,n-1,0);
		for(int i=0;i<n;i++)cout<<num[i]<<" ";
		cout<<endl;
	}
	return 0; 
	
} 