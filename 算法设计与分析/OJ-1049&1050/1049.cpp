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
#include<set>
#include<map>
using namespace std;
struct cg{
	double l;
	double r;
	double t;
	
};

int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		vector<cg> point;
		double des;
		cin>>des;
		for(int i=0;i<n;i++){
			double a,b,c;
			cin>>a>>b>>c;
			point.push_back({a,b,c});
		}
		sort(point.begin(),point.end(),[](cg &a,cg &b){
			return a.r<b.r;
		});
		
		vector<double> ansl,ansv;
		double lastpos=0;
		for(int i=0;i<n;i++){
			if (lastpos < point[i].l) {
				ansl.push_back(point[i].l);
				ansv.push_back(14.1757); //matlab求P（v）/v的最小值，v=14.1757，即14.1757m/s的时候飞固定距离耗能最小
				lastpos = point[i].l;
			}
			
			double time = point[i].t;
			int j = i + 1;
			while (j < n && point[j].r == point[i].r) {
				time += point[j].t;
				j++;
			}
			i = j - 1; 
			
			double s = (point[i].r-lastpos) / time; 
			if(s>14.1757)s=14.1757;
			ansl.push_back(point[i].r);
			ansv.push_back(s);
			
			lastpos= point[i].r; 
		}
		if (lastpos < des) {
			ansl.push_back(des);
			ansv.push_back(14.1757); 
			
		}
		
		cout<<ansv.size()<<endl;
		for(auto x:ansl){
			cout<<x<<" ";
		}
		cout<<endl;
		for(auto x:ansv)
			cout<<x<<" ";
		cout<<endl;
		
	}
	
	return 0;
}