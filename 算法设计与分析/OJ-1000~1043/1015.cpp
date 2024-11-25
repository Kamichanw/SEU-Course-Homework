#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<string>
#include<stack>
#include<cmath>
#include<set>
using namespace std;
int main(){//很巧妙的做法，虽然不是分治
	int t;
	cin>>t;
	vector<pair<int,int>>building;
	while(t--){
		int a,b,h;
		cin>>a>>b>>h;
		building.push_back(make_pair(a,-h));//通过正负判断是左边还是右边
		building.push_back(make_pair(b,h));
	}
	sort(building.begin(),building.end());
	multiset<int> ms;
	ms.insert(0);
	int pre=0,cur=0;
	for(auto a:building){
		if(a.second<0){
			ms.insert(-a.second);//是左边的话就把高度加入
		}
		else
			ms.erase(ms.find(a.second));//到右边了就删除这个建筑的高度
		cur=*ms.rbegin();
		if(cur!=pre){
			cout<<a.first<<" "<<cur<<endl;
			pre=cur;
		}
	}
	return 0; 
	
} 