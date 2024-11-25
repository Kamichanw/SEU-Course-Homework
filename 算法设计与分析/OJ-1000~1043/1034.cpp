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
int dp[50005][2];//dp[i][0]表示i结点染白的最大数量，dp[i][1]表示i结点染黑的最大数量
void dfs(int parent, vector<int> tree[50005]) {
	dp[parent][0] = 0;
	dp[parent][1] = 1;
	for (size_t i = 0; i < tree[parent].size(); i++) {
		int temp=tree[parent][i];
		dfs(temp, tree);
		dp[parent][0] += max(dp[temp][1], dp[temp][0]);
		dp[parent][1] += dp[temp][0];
	}
}

signed main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<int> tree[50005];
		vector<int> isroot(n);
		for (int i = 0; i < n - 1; i++) {
			int a, b;
			cin >> a >> b;
			tree[a].push_back(b);
			isroot[b] = 1;
		}
		for (int i = 0; i < 50005; i++) {
			dp[i][0] = 0;
			dp[i][1] = 0;
		}
		int root;
		for(int i=0;i<n;i++){
		if(isroot[i]==0)root=i;
		}

		dfs(root, tree);
	
		cout<<max(dp[root][0],dp[root][1])<<endl;
	}

	return 0;

}