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
int matrix[1005][1005];
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n,m,k;
		cin>>m>>n>>k;
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				cin>>matrix[i][j];
			}
		}
		int l=0,r=n-1;
		int flag=1;
		while(l<=n-1&&r>=0){
			if(matrix[l][r]==k){
				cout<<"true\n";
				flag=0;
				break;
			}
			else if(matrix[l][r]<k)
				l++;
			else
				r--;
		}
		if(flag)cout<<"false\n";
	}
	
	return 0; 
	
} 