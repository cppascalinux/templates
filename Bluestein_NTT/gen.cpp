#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<random>
#include<ctime>
#define ll long long
#define mod 950009857
using namespace std;
mt19937 rnd(time(0));
int n,m;
int main()
{
	freopen("a.in","w",stdout);
	n=8000,m=57984;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)
		printf("%d ",rnd()%m);
	printf("\n");
	for(int i=2;i<=n;i++)
		printf("%d %d\n",i,rnd()%(i-1)+1);
	return 0;
}