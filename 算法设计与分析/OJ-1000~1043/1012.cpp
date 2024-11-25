#include "iostream"
#include <vector>
#include <string>
#include<stack>
#include<cmath>
#include<algorithm>
using namespace std;
struct point{
	int x;
	int y;
	double angle;
	double len;
	point(int a,int b){
		x=a;
		y=b;
	}
	point(){}
}allpos[2001], s[2001];
int cmp_angle (const void * a, const void * b) {
	point *p1 = (point *)a;
	point *p2 = (point *)b;
	if(p1->angle - p2->angle > 0) {
		return 1;
	}
	else if(p1->angle - p2->angle < 0) {
		return -1;
	}
	else {
		if(p1->len - p2->len > 0) {
			return 1;
		}
		else if(p1->len - p2->len < 0) {
			return -1;
		}
		else {
			return 0;
		}
	}
}
int main(){	
	int t;
	cin>>t;
	int cc=t;
	while(t--){
		int n;
		cin>>n;
		int minx = 2147483647;
		int miny = 2147483647;
		int idx = 0;
		for(int i=0;i<n;i++){
			int a,b;
			cin>>a>>b;
			
			allpos[i]=point(a,b);
		}
		for(int i=0; i<n; i++) {
			if(allpos[i].y < miny) {
				miny = allpos[i].y;
				idx = i;
			}
		}
		for(int i=0; i<n; i++) {
			if(allpos[i].y==miny && allpos[i].x<minx) {
				minx = allpos[i].x;
				idx = i;
			}
		}
		point temppos=allpos[idx];
		for(int i=idx; i>0; i--) {
			allpos[i] = allpos[i-1];
		}
		allpos[0] = temppos;
		
		int len=0;
		for(int i=1; i<n; i++) {
			if(allpos[i].x==allpos[len].x && allpos[i].y==allpos[len].y) {
			}
			else {
				len++;
				allpos[len]=allpos[i];
			}
		}
		n = len+1;
		
		for(int i=1;i<n;i++){
			allpos[i].len = sqrt((allpos[i].y-allpos[0].y)*(allpos[i].y-allpos[0].y)+(allpos[i].x-allpos[0].x)*(allpos[i].x-allpos[0].x));
			allpos[i].angle = acos((allpos[i].x-allpos[0].x)/allpos[i].len);
		}
		qsort(&allpos[1], n-1, sizeof(point), cmp_angle);
		
		s[0]=allpos[0];
		int top=1;
		int k;
		for(k=2;k<n;k++){
			if(!(((allpos[k].x-allpos[0].x)*(allpos[1].y-allpos[0].y))==((allpos[k].y-allpos[0].y)*(allpos[1].x-allpos[0].x))))
				break;
		}
		s[1]=allpos[k-1];
		s[2]=allpos[k];
		top=3;
		for(int i=k+1;i<n;i++){//这边是用数组维护的栈，但改成stack没法操作（只能栈顶
				while(top>=3&&(((s[top-1].x-s[top-2].x)*(allpos[i].y-s[top-2].y))<=( (s[top-1].y-s[top-2].y)* (allpos[i].x-s[top-2].x)))){
					top--;
				}
			s[top++]=allpos[i];
		}
		printf("case %d:\n", cc-t);
		for(int i=0;i<top;i++){
			cout<<s[i].x<<" "<<s[i].y<<endl;
		}
	}
		
	
	return 0;
}
