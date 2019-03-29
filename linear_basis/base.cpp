//luogu3812 【模板】线性基
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
int n;
ll bs[59];
void ins(ll x)
{
	for(int i=50;i>=0;i--)
		if(x&(1LL<<i))
		{
			if(bs[i])
				x^=bs[i];
			else
			{
				for(int j=0;j<i;j++)
					if(x&(1LL<<j))
						x^=bs[j];
				for(int j=i+1;j<=50;j++)
					if(bs[j]&(1LL<<i))
						bs[j]^=x;
				bs[i]=x;
				break;
			}
		}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("base.in","r",stdin);
	freopen("base.out","w",stdout);
#endif
	scanf("%d",&n);
	ll a;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a);
		ins(a);
	}
	ll ans=0;
	for(int i=0;i<=50;i++)
		ans^=bs[i];
	printf("%lld",ans);
	return 0;
}