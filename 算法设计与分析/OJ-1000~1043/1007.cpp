#include "iostream"
#include <vector>
#include <string>
using namespace  std;
bool isuse[45];
long long num[45];



int main(){	
	int t;
	cin>>t;
	while (t--) {
		int n,k;
		cin>>n>>k;
		for(int i=0;i<45;i++){
			isuse[i]=0;
			num[i]=0;
		}
		string s;
		cin>>s;
		for(int i=0;i<n;i++)num[i]=s[i]-'0';
		while((n-k-1)!=0){
			k++;
			double maxw=0;
			int maxi,maxj;
			
			for(int i=0;i<n-1;i++){
				if(!isuse[i]&&num[i]!=0){
					int j=i+1;
					while(isuse[j])j++;
					if(j>=n)break;
					if(num[j]==0){
						maxi=i;
						maxj=j;
						break;
					}
					int weishu=0;
					int temp2=num[j]
					;
					if(temp2==0){
						temp2=10;
					}
					else{
						while (temp2){
							weishu++;
							temp2 /= 10;
						}
						temp2=1;
						while(weishu--)temp2*=10;
					}
					double temp=(temp2*num[i]+num[j])*1.0/(num[i]*num[j])*1.0;
					if(temp>maxw){
						maxw=temp;
						maxi=i;
						maxj=j;
					}
				}
			}
			isuse[maxj]=1;
			int weishu=0;
			int temp2=num[maxj];
			if(temp2==0){
				temp2=10;
			}
			else{
				
				
				while(temp2){
					temp2/=10;
					weishu++;
				}
				temp2=1;
				while(weishu--)temp2 *=10;
			}
			
			num[maxi]=temp2*num[maxi]+num[maxj];
			
		}
		long long result=1;
		for(int i=0;i<n;i++){
			if(!isuse[i]){
				result*=num[i];
			}
		}
		cout<<result<<endl;
		
	}
	return 0;
}
