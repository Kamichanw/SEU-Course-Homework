#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<string>
#include<stack>
#include<cmath>// 0 0 0 0 0 1 1 1 1 1
using namespace std;
double p[505];
double q[505];
double e[505][505];
double w[505][505];

signed main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int waste;
		for(int i=0;i<n;i++){
			cin>>waste;
		}
		for(int i=1;i<=n;i++){
			cin>>p[i];
		}
		for(int i=0;i<=n;i++){
			cin>>q[i];
		}
		for(int i=0;i<=n;i++){
			e[i][i]=0;
			w[i][i]=q[i];
		}
		for(int l=1;l<=n;l++){
			for(int i=0;i<=n-l;i++){
				int j=i+l;
				e[i][j]=0x3f3f3f3f;
				w[i][j]=w[i][j-1]+p[j]+q[j];
				for(int k=i+1;k<=j;k++){
					if((e[i][k-1]+e[k][j]+w[i][j])<e[i][j])
						e[i][j]=e[i][k-1]+e[k][j]+w[i][j];
				}
			}
		}
		printf("%.6lf\n",e[0][n]);
	}
	return 0; 
	
} 
