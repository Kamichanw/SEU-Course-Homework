#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <cstring>
#include <cmath>
#include <math.h>
using namespace std;
int graph[305][305];
int indegree[305];
signed main() {
	int t;
	cin >> t;
	while (t--) {
		int n,m;
		cin>>n>>m;
		for(int i=0;i<=n;i++){
			for(int j=0;j<=n;j++){
				graph[i][j]=0;
				
			}
			indegree[i]=0;
		}
		for(int i=0;i<m;i++){
			int u,v;
			cin>>u>>v;
			if(graph[u][v]==0)indegree[v]++;
			graph[u][v]=1;
			
			
		}
		queue<int> q;
		for(int i=1;i<=n;i++){
			if(indegree[i]==0)
				q.push(i);
		}
		vector<int> result;
		int num=0;
		while(!q.empty()){
			int cur=q.front();
			result.push_back(cur);
			num++;
			q.pop();
			for(int i=1;i<=n;i++){
				if(graph[cur][i]>0){
					graph[cur][i]=0;
					indegree[i]--;
					if(indegree[i]==0){
							q.push(i);
					}
					
				}
			}
		}
		if(num==n){
			for(auto x:result){
				cout<<x<<" ";
				
			}
			cout<<endl;
		}
		else{
			cout<<"0"<<endl;
		}
		
	}

	return 0;

}