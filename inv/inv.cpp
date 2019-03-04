#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
#define ll long long
using namespace std;
int inv[3000010];
int n,p;
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("inv.in","r",stdin);
	freopen("inv.out","w",stdout);
	#endif
	scanf("%d%d",&n,&p);
	inv[1]=1;
	for(rg i=2;i<=n;i++)
		inv[i]=(ll)(p-p/i)*inv[p%i]%p;
	for(rg i=1;i<=n;i++)
		printf("%d\n",inv[i]);
	return 0;
}