#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<string>
#include<stack>
#include<cstring>
#include<cmath>
using namespace std;
int dui[1005];
void adjust(int len,int index){
	int l=index*2+1;
	int r=l+1;
	int smallest=index;
	if(l<=len&&dui[l]<dui[smallest])smallest=l;
	if(r<=len&&dui[r]<dui[smallest])smallest=r;
	if(smallest!=index){
		swap(dui[index],dui[smallest]);
		adjust(len,smallest);
	}
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=0;i<n;i++){
			cin>>dui[i];
		}
		for(int i=(n-2)/2;i>=0;i--){
			adjust(n-1,i);
		}
		
		for(int i=0;i<n;i++){
			cout<<dui[i]<<" ";
		}
		cout<<endl;
	}
	
	return 0; 
	
} 