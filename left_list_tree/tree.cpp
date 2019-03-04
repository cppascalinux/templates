#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
#define rc register char
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,1000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[1000009];
int n,m;
int del[1000009];
int f[1000009];
int rt[1000009];
int mn[1000009],dist[1000009];
int lp[1000009],rp[1000009];
void read(int &x)
{
	rc ch=0,inv=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc(),ch=='-'&&(inv=1);
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
	inv&&(x=-x);
}
void readc(char &ch)
{
	ch=0;
	while(ch<'A'||ch>'Z')
		ch=gc();
}
int find(int x)
{
	return x==f[x]?x:f[x]=find(f[x]);
}
int merge(int x,int y)
{
	if(!x||!y)
		return x|y;
	if(mn[x]>=mn[y])
		swap(x,y);
	rp[x]=merge(rp[x],y);
	if(dist[lp[x]]<dist[rp[x]])
		swap(lp[x],rp[x]);
	dist[x]=dist[rp[x]]+1;
	return x;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	#endif
	read(n);
	dist[0]=-1;
	for(rg i=1;i<=n;i++)
	{
		read(mn[i]);
		f[i]=i;
		rt[i]=i;
	}
	read(m);
	int a,b,fa,fb;
	char c;
	for(rg i=1;i<=m;i++)
	{
		readc(c);
		if(c=='M')
		{
			read(a);
			read(b);
			if(del[a]||del[b])
				continue;
			fa=find(a);
			fb=find(b);
			if(fa==fb)
				continue;
			f[fa]=fb;
			int ra=rt[fa],rb=rt[fb];
			rt[fb]=merge(ra,rb);
		}
		else
		{
			read(a);
			if(del[a])
			{
				printf("0\n");
				continue;
			}
			fa=find(a);
			int ra=rt[fa];
			printf("%d\n",mn[ra]);
			del[ra]=1;
			rt[fa]=merge(lp[ra],rp[ra]);
		}
	}
	return 0;
}