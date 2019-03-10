#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,bit;
int h[500010];
int sum[2000010];
void build()
{
	for(bit=1;bit<n;bit<<=1);
	bit--;
	for(int i=1;i<=n;i++)
		sum[i+bit]=h[i];
}
void add(int ll,int rr,int a)
{
	ll+=bit;
	rr+=bit;
	sum[ll]+=a;
	sum[rr]+=a;
	for(;ll^rr^1;ll>>=1,rr>>=1)
	{
		if(~ll&1)
			sum[ll^1]+=a;
		if(rr&1)
			sum[rr^1]+=a;
	}
}
int ask(int x)
{
	int ans=0;
	for(x+=bit;x;x>>=1)
		ans+=sum[x];
	return ans;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("zkw2.in","r",stdin);
	freopen("zkw2.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",h+i);
	build();
	for(int i=1;i<=m;i++)
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
			scanf("%d",&b);
			printf("%d\n",ask(b));
		}
	}
	return 0;
}