#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;
int main()
{
  freopen("coingame.in","r",stdin);
  freopen("coingame.out","w",stdout);
  int T=0,Cas=0;
  T=1;
  while(T--)
  {
    long long N,C,K;
    cin>>N>>K>>C;
    long long ans=1000000000000000000ll;
    for(long long i=0;i<N;i++)
    {
        long long temp=N-i,less=0;
        if(K%temp!=0)
          less=temp-K%temp;
        if(temp*(K/temp)>=C)
            less=0;
       // if(Cas==1 && i<=2)
       // cout<<less<<" "<<K/temp<<" "<<C<<endl;
        ans=min(ans,i+C+less);
    }
    cout<<ans<<endl;
  }
  return 0;
}