#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
int N,C,K;
string str;
int check(int p)
{
  int a,n,k,c;
  n=N,k=K,c=C,a=c/n;
  if(c%n!=0) 
    a++;
  if((long long)a*(n-p)>k) return 0;
  return 1;
}
int sol1()
{
  int a,n,k,c;
  n=N,k=K,c=C;
 //   scanf("%d %d %d",&n,&k,&c);
  a=c/n;
  if(c%n!=0) a++;
  int l=0,r=n;
  while(l<=r)
  {
    //printf("%d %d\n",l,r);
    int mid=(l+r)/2;
    if(check(mid)==1) r=mid-1;
    else l=mid+1;
  }
  //cout<<n<<" "<<k<<" "<<c<<endl;
  //cout<<l+c<<endl;
  return l+c;
}

int sol2()
{
  int T=1;
  while(T--)
  {
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
    return ans;
  }
}
int main()
{
  //freopen("C:/Users/Administrator/Nutstore/Work/Workspace/in/input.txt","w",stdout);
  int T=3,cas=4;
  while(T--)
  {
    cas++;
    str="C:/Users/Administrator/Nutstore/Work/Workspace/in/";
    str+="coingame";
    if(cas==10)
      str+="10";
    else
      str+=char(cas+'0');
    str+=".in";
   // cout<<str.c_str()<<endl;
    //freopen(str.c_str(),"w",stdout);
    long long ans1,ans2;
    do
    {
      do
      {
        N=rand()*rand();
      }while(N>1000000 || N<1);
      do
      {
        C=rand()*rand();
        K=rand()*rand();
        K=C;
      }while(C>1000000 || C<1 || K<1 || K>1000000 || K<C);
     // N=497, K=999999,C=999999;
      ans1=sol1();
      ans2=sol2();
    }while(ans1==ans2);
   // cout<<ans1<<" "<<ans2<<endl;
    cout<<N<<" "<<K<<" "<<C<<endl; 

    
  }
}