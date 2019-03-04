#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int vist[100000010],prime[10000010],tot;
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	#endif
	int n=10000000;
	vist[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!vist[i])
			prime[++tot]=i;
		for(int j=1;j<=tot&&i*prime[j]<=n;j++)
		{
			vist[i*prime[j]]=1;
			if(!i%prime[j])
				break;
		}
	}
	for(int i=1;i<=tot;i++)
		printf("%d\n",prime[i]);
	return 0;
}