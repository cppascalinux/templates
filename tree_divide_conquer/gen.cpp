#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#define rg register int
using namespace std;
int main()
{
	srand(time(0));
	rand();
	freopen("tree.in","w",stdout);
	int n=10000,m=10000000;
	printf("%d %d\n",n,m);
	for(rg i=1;i<=n-1;i++)
		printf("%d %d %d\n",i,i+1,100);
	return 0;
}