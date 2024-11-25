#include "iostream"
#include <vector>
#include <string>
#include<cstring>
#include<queue>
using namespace std;
struct node {
	int v;
	long long weight;
	node * next;
	node(int a,long long b){v=a;weight=b;next=NULL;}
};
struct bnode{
	int v;
	long long  dis;
	bool operator <(const bnode &b)const{
		return dis>b.dis;
	}
};
inline long long mymin(long long a,long long b){
	return a>b?b:a;
}
vector<node*> head(505,NULL);
int isdone[505];
int dis[505];
int main(){
	int t;
	cin>>t;
	while(t--){
	int N,M,s,end;
	cin>>N>>M>>s>>end;
	for(int i=0;i<505;i++)head[i]=NULL;
	for(int i=0;i<=504;i++){
		dis[i]=0x3f3f;
		isdone[i]=0;
	}
	while(M--){
		long long  u,v,w;
		cin>>u>>v>>w;
		node *temp=head[u];
		if(temp==NULL){
			head[u]=new node(v,w);
		}
		else{
			if(head[u]->v==v){
				head[u]->weight=min(w,head[u]->weight);
				continue;
			}
			int flag=1;
			while(temp->next!=NULL){
				temp=temp->next;
				if(temp->v==v){
					temp->weight=min(w,temp->weight);
					flag=0;
					break;
				}
			}
			if(flag)
			temp->next=new node(v,w);
		}
		temp=head[v];
		if(temp==NULL){
			head[v]=new node(u,w);
		}
		else{
			if(head[v]->v==u){
				head[v]->weight=min(w,head[v]->weight);
				continue;
			}
			int flag=1;
			while(temp->next!=NULL){
				temp=temp->next;
				if(temp->v==u){
					temp->weight=min(w,temp->weight);
					flag=0;
					break;
				}
			}
			if(flag)
				temp->next=new node(u,w);
		}
		
	}
	priority_queue<bnode> pq;
	node *first=head[s];
	dis[s]=0;
	while(first!=NULL){
		bnode temp;
		temp.v=first->v;
		temp.dis=first->weight;
		dis[temp.v]=first->weight;
		pq.push(temp);
		first=first->next;
	}
	while(!pq.empty()){
		bnode nownode=pq.top();
		pq.pop();
		if(isdone[nownode.v])continue;
		isdone[nownode.v]=1;
		node *temp=head[nownode.v];
		while(temp!=NULL){
			if(!isdone[temp->v]){
				if(dis[temp->v]>dis[nownode.v]+temp->weight){
					dis[temp->v]=dis[nownode.v]+temp->weight;
					bnode a;
					a.v=temp->v;
					a.dis=dis[temp->v];
					pq.push(a);
				}
			}
			temp=temp->next;
			
		}
		
		
	}
	cout<<(dis[end]>=1000?-1:dis[end])<<endl;
	
		
		
		
	}
	return 0;
}