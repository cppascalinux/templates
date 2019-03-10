#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long lll;
int n,m,bit;
lll sum[400010],add[400010];
lll num[100010];
void build()
{
	for(bit=1;bit<n;bit<<=1);
	bit--;
	for(int i=1;i<=n;i++)
		sum[bit+i]=add[bit+i]=num[i];
	for(int i=bit;i>=1;i--)
		sum[i]=sum[i<<1]+sum[i<<1|1];
}
void update(int ll,int rr,lll x)
{
	int len=1,lsum=1,rsum=1,tot=rr-ll+1;
	if(ll==rr)
		add[ll+bit]+=x;
	for(ll+=bit,rr+=bit;ll^rr;ll>>=1,rr>>=1,len<<=1)
	{
		sum[ll]+=lsum*x;
		sum[rr]+=rsum*x;
		if(len==1)
		{
			add[ll]+=x;
			add[rr]+=x;
		}
		if(ll^rr^1)
		{
			if(~ll&1)
			{
				sum[ll^1]+=len*x;
				add[ll^1]+=x;
				lsum+=len;
			}
			if(rr&1)
			{
				sum[rr^1]+=len*x;
				add[rr^1]+=x;
				rsum+=len;
			}
		}
	}
	for(;ll;ll>>=1)
		sum[ll]+=x*tot;
}
lll ask(int ll,int rr)
{
	int len=1,lsum=1,rsum=1,tot=rr-ll+1;
	lll ans=0;
	for(ll+=bit,rr+=bit;ll^rr;ll>>=1,rr>>=1,len<<=1)
	{
		ans+=lsum*add[ll];
		ans+=rsum*add[rr];
		if(ll^rr^1)
		{
			if(~ll&1)
			{
				ans+=sum[ll^1];
				lsum+=len;
			}
			if(rr&1)
			{
				ans+=sum[rr^1];
				rsum+=len;
			}
		}
	}
	for(;ll;ll>>=1)
		ans+=tot*add[ll];
	return ans;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("tot.in","r",stdin);
	freopen("tot.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld",num+i);
	build();
	//for(int i=1;i<=bit+n;i++)
	//	printf("%d %d\n",i,sum[i]);
	for(int i=1;i<=m;i++)
	{
		int a,b,c;
		lll d;
		scanf("%d",&a);
		if(a==1)
		{
			scanf("%d%d%lld",&b,&c,&d);
			update(b,c,d);
		}
		else
		{
			scanf("%d%d",&b,&c);
			printf("%lld\n",ask(b,c));
		}
	}
	return 0;
}