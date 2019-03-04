#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
#define rg register int
using namespace std;
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	rg b=1;
	for(rg i=1;i<=1000000000;i++)
		b*=i;
	printf("%d\n",b);
	return 0;
}