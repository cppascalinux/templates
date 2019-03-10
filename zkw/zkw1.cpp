#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,bit=1;
int num[500010];
int sum[2000010];
void build()
{
	for(bit=1;bit<n;bit<<=1);
	for(int i=1;i<=n;i++)
		sum[bit+i]=num[i];
	for(int i=bit;i>=1;i--)
		sum[i]=sum[i<<1]+sum[i<<1|1];
}
void add(int x,int a)
{
	for(x+=bit;x;x>>=1)
		sum[x]+=a;
}
int ask(int ll,int rr)
{
	int ans=0;
	ll+=bit;
	rr+=bit;
	ans+=sum[ll];
	ans+=sum[rr];
	for(;ll^rr^1;ll>>=1,rr>>=1)
	{
		if(~ll&1)
			ans+=sum[ll^1];
		if(rr&1)
			ans+=sum[rr^1];
	}
	return ans;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("zkw1.in","r",stdin);
	freopen("zkw1.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",num+i);
	build();
	for(int i=1;i<=m;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		if(a==1)
			add(b,c);
		else
			printf("%d\n",ask(b,c));
	}
	return 0;
}