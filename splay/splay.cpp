#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define inf 0x7FFFFFFF
#define ninf 0x80000000
using namespace std;
int ch[100010][2],val[100010],s[100010],cnt[100010],f[100010];
int n,tot,root;/*
void update(int p)
{
	s[p]=s[ch[p][0]]+s[ch[p][1]]+cnt[p];
}*/
#define update(p) s[p]=s[ch[p][0]]+s[ch[p][1]]+cnt[p]
void rotate(int x)
{
	int y=f[x];
	int z=f[y];
	int kx=x==ch[y][1],ky=y==ch[z][1];
	f[x]=z;
	f[y]=x;
	f[ch[x][kx^1]]=y;
	ch[z][ky]=x;
	ch[y][kx]=ch[x][kx^1];
	ch[x][kx^1]=y;
	update(y);
	update(x);
}
void splay(int x,int fa)
{
	while(f[x]^fa)
	{
		int y=f[x];
		int z=f[y];
		if(z^fa)
			(x==ch[y][1])^(y==ch[z][1])?rotate(x):rotate(y);
		rotate(x);
	}
	if(fa==0)
		root=x;
}
void find(int x)
{
	int p=root;
	if(!p)
		return;
	while(ch[p][x>val[p]]&&val[p]^x)
		p=ch[p][x>val[p]];
	splay(p,0);
}
int next(int x,int c)
{
	find(x);
	int p=root;
	if(val[p]<x&&!c)
		return p;
	if(val[p]>x&&c)
		return p;
	p=ch[p][c];
	while(ch[p][c^1])
		p=ch[p][c^1];
	return p;
}
void insert(int x)
{
	int p=root,fa=0;
	while(p&&val[p]^x)
	{
		fa=p;
		p=ch[p][x>val[p]];
	}
	if(p)
		cnt[p]++;
	else
	{
		p=++tot;
		if(fa)
			ch[fa][x>val[fa]]=p;
		ch[p][0]=ch[p][1]=0;
		f[p]=fa;
		val[p]=x;
		cnt[p]=s[p]=1;
	}
	splay(p,0);
}
void del(int x)
{
	int l=next(x,0);
	int r=next(x,1);
	splay(l,0);
	splay(r,l);
	int mid=ch[r][0];
	if(cnt[mid]>1)
	{
		cnt[mid]--;
		splay(mid,0);
	}
	else
		ch[r][0]=0;
}
int rank(int x)
{
	find(x);
	return s[ch[root][0]]+1;
}
int kth(int x)
{
	int p=root,now=s[ch[root][0]]+1;
	while(p&&x<now||x>now+cnt[p]-1)
	{
		if(now>x)
		{
			p=ch[p][0];
			now-=s[ch[p][1]];
			now-=cnt[p];
		}
		else
		{
			now+=cnt[p];
			p=ch[p][1];
			now+=s[ch[p][0]];
		}
	}
	splay(p,0);
	return val[p];
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("splay.in","r",stdin);
	freopen("splay.out","w",stdout);
	#endif
	int a,b;
	scanf("%d",&n);
	insert(ninf);
	insert(inf);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a,&b);
		//printf("i:%d\n",i);
	//	fflush(stdout);
		if(a==1)
			insert(b);
		if(a==2)
			del(b);
		if(a==3)
			printf("%d\n",rank(b)-1);
		if(a==4)
			printf("%d\n",kth(b+1));
		if(a==5)
			printf("%d\n",val[next(b,0)]);
		if(a==6)
			printf("%d\n",val[next(b,1)]);
	}
	return 0;
}