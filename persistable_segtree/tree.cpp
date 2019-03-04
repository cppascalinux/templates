#pragma gcc optimize(3)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,1000000,stdin),p1==p2)?EOF:*p1++)
#define rg register int
#define cp(a,b) (lp[a]=lp[b],rp[a]=rp[b],cnt[a]=cnt[b])
#define inf 0x7FFFFFFF
using namespace std;
char *p1,*p2,buffer[1000000];
int n,m,d,tot,maxx=-inf,minn=inf;
int w[100010];
int root[100010],lp[5000010],rp[5000010],cnt[5000010];
void read(int &x)
{
	char ch=0,inv=0;
	x=0;
	while(ch<'0'||ch>'9')
	{
		ch=gc();
		if(ch=='-')
			inv=1;
	}
	while(ch>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+ch-'0',ch=gc();
	if(inv)
		x=~(x-1);
}
void insert(int &a,int x,int l,int r)
{
	int p=++tot;
	cp(p,a);
	a=p;
	cnt[a]++;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(x<=mid)
		insert(lp[a],x,l,mid);
	else
		insert(rp[a],x,mid+1,r);
}
int get(int a,int b,int l,int r,int x)
{
	if(l==r)
		return l;
	int suml=cnt[lp[b]]-cnt[lp[a]];
	int mid=(l+r)>>1;
	if(x<=suml)
		return get(lp[a],lp[b],l,mid,x);
	else
		return get(rp[a],rp[b],mid+1,r,x-suml);
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	#endif
	read(n);read(m);
	for(rg i=1;i<=n;i++)
	{
		read(w[i]);
		minn=min(minn,w[i]);
		maxx=max(maxx,w[i]);
	}
	for(rg i=1;i<=n;i++)
	{
		root[i]=root[i-1];
		insert(root[i],w[i],minn,maxx);
	}
	int a,b,c;
	for(rg i=1;i<=m;i++)
	{
		read(a);read(b);read(c);
		printf("%d\n",get(root[a-1],root[b],minn,maxx,c));
	}
	return 0;
}