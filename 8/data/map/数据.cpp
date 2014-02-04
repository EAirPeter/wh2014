#include <iostream>
#include <stdlib.h>
#include <map>
#include <fstream>
using namespace std;
int n,m,k;
ofstream out("map8.in"); 
map<int,bool> bian[30000];
int main(int argc, char *argv[])
{ srand((unsigned)time(0));
  cin>>n>>m>>k;
  out<<n<<" "<<m<<endl;
  for(int i=1;i<=m;i++)
  {
    int a(rand()%n+1),b=(rand()%n+1);
    if(a!=b && bian[a][b]==0 && bian[b][a]==0)
    {
       out<<a<<" "<<b<<endl;
       bian[a][b]=1;
       bian[a][b]=1;    
    }
    else
    i--;    
  }
  out<<k<<endl;
  for(int i=0;i<k;i++)
  {
    int a=rand()%min(n,1000)+1;
    int b=max(n-rand()%1000,a);
    out<<a<<" "<<b<<endl; 
  }
  system("PAUSE");	
  return 0;
}
