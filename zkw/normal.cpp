#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
int n,m;
int num[500010];
int sum[2000010],l[2000010],r[2000010];
void build(int a,int ll,int rr)
{
	l[a]=ll;
	r[a]=rr;
	if(ll==rr)
		sum[a]=num[ll];
	else
	{
		int mid=(ll+rr)>>1;
		build(a<<1,ll,mid);
		build(a<<1|1,mid+1,rr);
		sum[a]=sum[a<<1]+sum[a<<1|1];
	}
}
void add(int a,int p,int x)
{
	if(p<l[a]||p>r[a])
		return;
	sum[a]+=x;
	if(l[a]^r[a])
	{
		add(a<<1,p,x);
		add(a<<1|1,p,x);
	}
}
int ask(int a,int ll,int rr)
{
	if(l[a]>rr||r[a]<ll)
		return 0;
	if(l[a]>=ll&&r[a]<=rr)
		return sum[a];
	return ask(a<<1,ll,rr)+ask(a<<1|1,ll,rr);
}
#undef int
int main()
#define int long long
{
#ifndef ONLINE_JUDGE
	freopen("zkw1.in","r",stdin);
	freopen("zkw1.out","w",stdout);
#endif
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld",num+i);
	build(1,1,n);
	for(int i=1;i<=m;i++)
	{
		int a,b,c;
		scanf("%lld%lld%lld",&a,&b,&c);
		if(a==1)
			add(1,b,c);
		else
			printf("%lld\n",ask(1,b,c));
	}
	return 0;
}