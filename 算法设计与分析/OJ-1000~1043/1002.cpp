#include <iostream>
#include<iomanip>
using namespace std;
int numlist[100];
int part(int left,int right){
	int temp=numlist[left];
	while(left<right){
		while(numlist[right]>= temp &&left<right)
			right--;
		numlist[left]=numlist[right];
		while(numlist[left]<= temp &&left<right)
			left++;
		numlist[right]=numlist[left];
		
	}
	numlist[left]=temp;
	return left;
	
}
int find2(int left,int right){
	int position=part(left,right);
	while(position!=1){
		if(position>1){
			right=position-1;
			position=part(left,right);
		}
		else{
			left=position+1;
			position=part(left,right);
		}
	
	}
	return numlist[position];
}
int main()
{
	int m,n;
	cin>>m;
	for(int i=0;i<m;i++){
		cin>>n;
		int t=0;
		while(t++<100)
			numlist[t]=0;
		for(int j=0;j<n;j++){
			cin>>numlist[j];
		}
		int ans=find2(0,n-1);
		cout<<ans<<endl;
	}
}