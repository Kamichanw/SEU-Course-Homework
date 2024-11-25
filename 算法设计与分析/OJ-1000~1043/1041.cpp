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
int n,m;

signed main() {
	int t;
	cin >> t;
	while (t--) {
		
		cin>>n>>m;
		vector<int> ans;
		for(int i=0;i<n+m;i++){
			int a;
			cin>>a;
			ans.push_back(a);
		}
		
		sort(ans.begin(),ans.end());
		
		if((m+n)%2==1){
			
			cout<<ans[(m + n) / 2]<<endl;
		}
		else{
			double kk=(ans[(m + n) / 2 - 1] + ans[(m + n) / 2]) / 2.0;
			cout<<kk<<endl;
		}
		
		
	}
	
	return 0;
	
}