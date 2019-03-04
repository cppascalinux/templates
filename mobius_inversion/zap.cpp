//2019.02.14
//luogu3455 [POI2007]ZAP-Queries 莫比乌斯反演
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
int n,m,k,tot;
int pm[50009],vis[50009],mu[50009];
ll sm[50009];
void init()
{
	vis[1]=mu[1]=1;
	for(int i=2;i<=50000;i++)
	{
		if(!vis[i])
		{
			pm[++tot]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=tot&&i*pm[j]<=50000;j++)
		{
			vis[i*pm[j]]=1;
			if(i%pm[j]==0)
			{
				mu[i*pm[j]]=0;
				break;
			}
			mu[i*pm[j]]=-mu[i];
		}
	}
	for(int i=1;i<=50000;i++)
		sm[i]=sm[i-1]+mu[i];
	// for(int i=1;i<=10;i++)
	// 	printf("mu:%d sm:%d\n",mu[i],sm[i]);
}
void solve(int a,int b)
{
	ll ans=0;
	int l=1,ra,rb;
	while(l<=min(a,b))
	{
		ra=a/(a/l);
		rb=b/(b/l);
		if(ra>rb)
			swap(ra,rb),swap(a,b);
		ans+=(ll)(a/l)*(b/l)*(sm[ra]-sm[l-1]);
		l=ra+1;
	}
	printf("%lld\n",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("zap.in","r",stdin);
	freopen("zap.out","w",stdout);
#endif
	init();
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d",&n,&m,&k);
		n/=k;
		m/=k;
		solve(n,m);
	}
	return 0;
}