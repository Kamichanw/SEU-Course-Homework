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
int f[100001];
int l1, l2;
char s[100001],p[100001];
int find(int k) {
	int i = k;
	int j = 0;
	while (i < l1 && j < l2) {
		if (j == -1 || s[i] == p[j]) {
			i++;
			j++;
		} else {
			j = f[j];
		}
	}
	if (j < l2)return -1;
	return i - l2;
}

signed main() {
	int t;
	cin >> t;
	while (t--) {
		cin >> l1 >> l2;
		for(int i=0;i<l1;i++){
			cin>>s[i];
		}
		for(int i=0;i<l2;i++){
			cin>>p[i];
		}
	
		int j = 0;
		int k = -1;
		f[0] = -1;
		while (j < l2 ) {
			if (k == -1 || p[j] == p[k]) {
				j++;
				k++;
				f[j] = k;
			} else {
				k = f[k];
			}
		}
		int index = 0, ans = 0;
		while (index <= l1 - l2) {
			int x = find(index);//就是kmp找到了一个匹配的子串，然后index+1再找下一个
			if (x == -1)break;
			else {
				index = x + 1;
				ans++;
			}
		}
		cout << ans << endl;

	}

	return 0;

}