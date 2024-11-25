#include "iostream"
#include <vector>
#include <string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
struct edge{
	int u;
	int v;
	int w;
	edge(){}
	edge(int a,int b,double c){
		u=a;
		v=b;
		w=c;
	}
} ;
vector<edge> edgelist;
int fa[1001];
void init(){
	for(int i=0;i<1001;i++){
		fa[i]=i;
	}
}
int find(int x){
	if(fa[x]==x)return x;
	else{
		int ff=find(fa[x]);
		fa[x]=ff;
		return fa[x];
	}
}
void merge(int i,int j){
	int a=find(i);
	int b=find(j);
	if(a!=b)
		fa[a]=b;
}

int main(){
	int t;
	cin>>t;
	while(t--){
		
	
	init();
	int n,e;
	cin>>n>>e;
	edgelist.clear();
	for(int i=0;i<e;i++){
		int x,y,h;
		cin>>x>>y>>h;
		edge temp;
		temp.u=x;
		temp.v=y;
		temp.w=h;
		
		edgelist.push_back(temp);
		temp.v=x;
		temp.u=y;
		edgelist.push_back(temp);
	}
	
	sort(edgelist.begin(),edgelist.end(),[](const edge &a,const edge &b){
		return a.w<b.w;
	});
	int totalnum=0;
	long long ans=0;
	for(edge nowedge:edgelist){
		if(find(nowedge.u)!=find(nowedge.v)){
			merge(nowedge.u,nowedge.v);
			totalnum++;	
			ans += nowedge.w;
		}
		if(totalnum==n-1)break;
	}
	if(totalnum<n-1)cout<<"-1\n";
	else cout<<ans<<endl;
	
	}
	return 0;
}