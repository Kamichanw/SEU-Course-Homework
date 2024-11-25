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
int edge[55][55];
int girls[55];
int match[55];

int n,m;
bool find(int x){
	for(int i=1;i<=m;i++){
		if(edge[x][i]==1&&0==match[i]){
			match[i]=1;
			if(girls[i]==0||find(girls[i])){
				girls[i]=x;
				return true;
			}
		}
	}
	
	
	
	return false;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
	for(int i=0;i<55;i++){
		for(int j=0;j<55;j++){
			edge[i][j]=0;
		}
		match[i]=0;
		girls[i]=0;
	}
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			int k;
			cin>>k;
			while(k--){
				int b;
				cin>>b;
				edge[i][b]=1;
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++){
			memset(match,0,sizeof(match));
			if(find(i))ans++;
		}
			
		cout<<ans<<endl;
	}
	return 0; 
	
} 