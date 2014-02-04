#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;
ofstream out("game10.in");
int n,mx; 
int main(int argc, char *argv[])
{
  cin>>n;
  srand((unsigned)time(0));
  out<<n<<endl;
  for(int i=0;i<n;i++)
  {
      out<<(rand()%100000000+1)<<" ";
  }
  system("PAUSE");	
  return 0;
}
