#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int inf=0x7FFFFFFF;
int n,m;
int minn[200010],maxx[200010],l[200010],r[200010];
int num[200010];
void build(int a,int ll,int rr)
{
	l[a]=ll;
	r[a]=rr;
	if(ll==rr)
		minn[a]=maxx[a]=num[ll];
	else
	{
		int mid=(ll+rr)>>1;
		build(a<<1,ll,mid);
		build(a<<1|1,mid+1,rr);
		minn[a]=min(minn[a<<1],minn[a<<1|1]);
		maxx[a]=max(maxx[a<<1],maxx[a<<1|1]);
	}
}
int ask1(int a,int ll,int rr)
{
	if(l[a]>rr||r[a]<ll)
		return inf;
	if(l[a]>=ll&&r[a]<=rr)
		return minn[a];
	return min(ask1(a<<1,ll,rr),ask1(a<<1|1,ll,rr));
}
int ask2(int a,int ll,int rr)
{
	if(l[a]>rr||r[a]<ll)
		return 0;
	if(l[a]>=ll&&r[a]<=rr)
		return maxx[a];
	return max(ask2(a<<1,ll,rr),ask2(a<<1|1,ll,rr));
}
int main()
{
	freopen("zkw.in","r",stdin);
	freopen("zkw.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",num+i);
	build(1,1,n);
	for(int i=1;i<=m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		printf("%d\n",ask2(1,a,b)-ask1(1,a,b));
	}
	return 0;
}