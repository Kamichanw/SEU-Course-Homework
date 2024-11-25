#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <cstring>
#include <cmath>
#include <set>
#include <math.h>
using namespace std;
int dp[400];
int isvisit[400];
int cost[2];

signed main() {
	int t;
	cin >> t;
	while (t--) {
		for (int i = 0; i < 400; i++) {
			dp[i] = 0;
			isvisit[i] = 0;
		}
		int n;
		set<int> day;
		cin >> n;
		int maxday = 0;
		for (int i = 0; i < n; i++) {
			int t;

			cin >> t;
			isvisit[t] = 1;
			maxday = t > maxday ? t : maxday;
		}
		for (int i = 0; i < 3; i++) {
			cin >> cost[i];
		}
		for (int i = 1; i <= maxday; i++) {
			if (!isvisit[i]) {
				dp[i+30] = dp[i + 30 - 1];
			} else {

				dp[i+30]=min(dp[i+29]+cost[0],min(dp[i+23]+cost[1],dp[i]+cost[2]));
				
			}

		}
		cout << dp[maxday + 30] << endl;



	}

	return 0;

}