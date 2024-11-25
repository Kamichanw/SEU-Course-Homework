#include "iostream"
#include <vector>
#include <string>
#include<queue>
#include<algorithm>
using namespace  std;
int dp[10005];
int l[10005];
int value[10005];

int main(){

        int t;
        cin>>t;
        while(t--){
                for(int i=0;i<10005;i++)dp[i]=0;
                int n,k;
                cin>>n>>k;
                int minl=100000,mini;
                for(int i=0;i<k;i++){
                        cin>>l[i]>>value[i];
                        if(l[i]<minl ){
                        mini=i;
                        minl=l[i];
                }}
                dp[minl]=value[mini];
                for(int i=minl;i<=n;i++){
                        dp[i]=dp[i-1];
                        for(int j=0;j<k;j++){
                                if(i>=l[j]){

                                        dp[i]=max(dp[i],dp[i-l[j]]+value[j]);
                                }
                        }
                }
                cout<<dp[n]<<endl;
        }

        return 0;
}