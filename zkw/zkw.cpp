#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define int long long
using namespace std;
int n,m,bit=1;
int num[200010],minn[800010],maxx[800010];
void build()
{
	while(bit<n)
		bit<<=1;
	bit--;
	for(int i=1;i<=n;i++)
		minn[bit+i]=maxx[bit+i]=num[i];
	for(int i=bit;i;i--)
	{
		minn[i]=min(minn[i<<1],minn[i<<1|1]);
		maxx[i]=max(maxx[i<<1],maxx[i<<1|1]);
		minn[i<<1]-=minn[i];
		minn[i<<1|1]-=minn[i];
		maxx[i<<1]-=maxx[i];
		maxx[i<<1|1]-=maxx[i];
	}
}
int ask1(int ll,int rr)
{
	int la=0,ra=0,ans=0;
	ll+=bit;
	rr+=bit;
	while(ll^rr)
	{
		la+=minn[ll];
		ra+=minn[rr];
		if(ll^rr^1)
		{
			if(~ll&1)
				la=min(la,minn[ll^1]);
			if(rr&1)
				ra=min(ra,minn[rr^1]);
		}
		ll>>=1;
		rr>>=1;
	}
	ans=min(la,ra);
	while(ll)
	{
		ans+=minn[ll];
		ll>>=1;
	}
	return ans;
}
int ask2(int ll,int rr)
{
	int la=0,ra=0,ans=0;
	ll+=bit;
	rr+=bit;
	while(ll^rr)
	{
		la+=maxx[ll];
		ra+=maxx[rr];
		if(ll^rr^1)
		{
			if(~ll&1)
				la=max(la,maxx[ll^1]);
			if(rr&1)
				ra=max(ra,maxx[rr^1]);
		}
		ll>>=1;
		rr>>=1;
	}
	ans=max(la,ra);
	while(ll)
	{
		ans+=maxx[ll];
		ll>>=1;
	}
	return ans;
}
void mt(int x)
{
	int mi=min(minn[x],minn[x^1]);
	minn[x]-=mi;
	minn[x^1]-=mi;
	minn[x>>1]+=mi;
	int ma=max(maxx[x],maxx[x^1]);
	maxx[x]-=ma;
	maxx[x^1]-=ma;
	maxx[x>>1]+=ma;
}
void add(int ll,int rr,int a)
{
	ll+=bit;
	rr+=bit;
	minn[ll]+=a;
	maxx[ll]+=a;
	minn[rr]+=a;
	maxx[rr]+=a;
	if(~(ll^rr))
	{
		minn[ll]-=a;
		maxx[ll]-=a;
	}
	while(ll^rr)
	{
		if(ll^rr^1)
		{
			if(~ll&1)
			{
				minn[ll^1]+=a;
				maxx[ll^1]+=a;
			}
			if(rr&1)
			{
				minn[rr^1]+=a;
				maxx[rr^1]+=a;
			}
		}
		mt(ll);
		mt(rr);
		ll>>=1;
		rr>>=1;
	}
	while(ll>1)
	{
		mt(ll);
		ll>>=1;
	}
}
#undef int
int main()
#define int long long
{
#ifndef ONLINE_JUDGE
	freopen("zkw.in","r",stdin);
	freopen("zkw.out","w",stdout);
#endif
	while(~scanf("%lld%lld",&n,&m))
	{
		for(int i=1;i<=n;i++)
			scanf("%lld",num+i);
		build();
		/*for(int i=1;i<=m;i++)
		{
			int a,b,c,d;
			scanf("%d",&a);
			if(a==1)
			{
				scanf("%d%d%d",&b,&c,&d);
				add(b,c,d);
			}
			else
			{
				scanf("%d%d",&b,&c);
				printf("%d %d\n",ask1(b,c),ask2(b,c));
			}
		}*/
		for(int i=1;i<=m;i++)
		{
			char s[2];
			int a,b;
			scanf("%s%lld%lld",s,&a,&b);
			if(s[0]=='Q')
				printf("%lld\n",ask2(a,b));
			else
			{
				int t=b-num[a];
				add(a,a,t);
				num[a]=b;
			}
		}
		bit=1;
		memset(maxx,0,sizeof(maxx));
		memset(minn,0,sizeof(minn));
		memset(num,0,sizeof(num));
	}
	return 0;
}