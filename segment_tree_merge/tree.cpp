#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define inf 0x7F7F7F7F
#define rg register int
using namespace std;
int n,m,tot;
int root[100009];
int mn[1800009],mv[1800009],lp[1800009],rp[1800009];
int del[100009],f[100009];
void mt(int x)
{
	int lx=lp[x],rx=rp[x];
	if(mn[lx]>mn[rx]||(mn[lx]==mn[rx]&&mv[lx]>mv[rx]))
		swap(lx,rx);
	mn[x]=mn[lx];
	mv[x]=mv[lx];
}
int merge(int a,int b)
{
	if(!a||!b)
		return a|b;
	lp[a]=merge(lp[a],lp[b]);
	rp[a]=merge(rp[a],rp[b]);
	mt(a);
	return a;
}
void set(int &a,int l,int r,int x,int val)
{
	if(!a)
		a=++tot;
	if(l==r)
	{
		mn[a]=val;
		mv[a]=l;
	}
	else
	{
		int mid=(l+r)>>1;
		if(x<=mid)
			set(lp[a],l,mid,x,val);
		else
			set(rp[a],mid+1,r,x,val);
		mt(a);
	}
}
int find(int x)
{
	return x==f[x]?x:f[x]=find(f[x]);
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	memset(mn,inf,sizeof(mn));
	int a,b,c,fa,fb;
	for(rg i=1;i<=n;i++)
	{
		scanf("%d",&a);
		set(root[i],1,n,i,a);
		f[i]=i;
	}
	for(rg i=1;i<=m;i++)
	{
		scanf("%d",&c);
		if(c==1)
		{
			scanf("%d%d",&a,&b);
			if(del[a]||del[b])
				continue;
			fa=find(a);
			fb=find(b);
			f[fb]=fa;
			root[fa]=merge(root[fa],root[fb]);
		}
		else
		{
			scanf("%d",&a);
			if(del[a])
			{
				printf("-1\n");
				continue;
			}
			fa=find(a);
			printf("%d\n",mn[root[fa]]);
			del[mv[root[fa]]]=1;
			set(root[fa],1,n,mv[root[fa]],inf);
		}
	}
	return 0;
}