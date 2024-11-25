#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<string>
#include<stack>
#include<cstring>
#include<cmath>
#include<math.h>
using namespace std;
struct point{
	double x;
	double y;
	double rsect;
	
	
}pos[10010];
const double minINF = 0.00000000001;
int iscover[10010];
int n;
double d;
int cmp(const void *a, const void *b) {
	point *ta, *tb;
	ta = (point *)a;
	tb = (point *)b;
	double temp = ta->rsect-tb->rsect;
	if(-minINF<=temp && temp<=minINF) {
		//if(temp == 0) {
		return 0;
	}
	else if (temp < 0) {
		return -1;
	}
	else {
		return 1;
	}
}

signed main(){
	int t;
	cin>>t;
	while(t--){
		scanf("%d%lf", &n, &d);
		for(int i=0; i<n; i++) {
			scanf("%lf%lf", &pos[i].x, &pos[i].y);
			pos[i].rsect = pos[i].x + sqrt(d*d-pos[i].y*pos[i].y);
			
		}
		memset(iscover,0,sizeof(iscover));
		qsort(pos, n, sizeof(point), cmp);//这边本来是手写了个sort的比较函数的，但是由于sort要求的是bool类型，怎么改都不行，所以就用了样例的比较函数
		int ans=0;
		for(int i=0;i<n;i++){
			if(iscover[i]==1)continue;
			ans++;
			for(int j=i;j<n;j++){
				if(pos[j].rsect-pos[i].rsect>2*d)break;
				if(iscover[j]==1)continue;
				double temp = (pos[j].x-pos[i].rsect)*(pos[j].x-pos[i].rsect) + pos[j].y*pos[j].y - d*d;
				if(temp<=0.00000000001) {
					iscover[j] = 1;
				}
			}
		}
		cout<<ans<<endl;
	}
	
	return 0; 
	
} 