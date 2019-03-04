#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<cstdlib>
#define update(x) s[x]=s[ch[x][0]]+s[ch[x][1]]+(x>0);
#define inf 0x7FFFFFFF
#define rm 100000001
using namespace std;
int n,m,tot1=1,tot2;
int root[3000010],lp[3000010],rp[3000010];
int ch[3000010][2],s[3000010],val[3000010],rnd[3000010];
int num[50010];
void rotate(int &p,int k)
{
	int x=ch[p][k];
	ch[p][k]=ch[x][k^1];
	ch[x][k^1]=p;
	update(p);
	update(x);
	p=x;
}
void insert(int &p,int x)
{
	if(!p)
	{
		p=++tot2;
		val[p]=x;
		s[p]=1;
		rnd[p]=rand();
	}
	else
	{
		int d=x>val[p];
		insert(ch[p][d],x);
		update(p);
		if(rnd[ch[p][d]]>rnd[p])
			rotate(p,d);
	}
}
void del(int &p,int x)
{
	if(x==val[p])
	{
		if(!(ch[p][0]&&ch[p][1]))
			p=ch[p][0]|ch[p][1];
		else
		{
			int d=rnd[ch[p][1]]>rnd[ch[p][0]];
			rotate(p,d);
			del(ch[p][d^1],x);
		}
	}
	else
	{
		int d=x>val[p];
		del(ch[p][d],x);
	}
	update(p);
}
int rank(int p,int x)
{
	if(x==val[p]||!p)
		return s[ch[p][0]]+1;
	if(x<val[p])
		return rank(ch[p][0],x);
	return s[ch[p][0]]+1+rank(ch[p][1],x);
}
void add(int a,int l,int r,int pos,int x)
{
	insert(root[a],x);
	if(l^r)
	{
		int mid=(l+r)>>1;
		if(pos<=mid)
		{
			if(!lp[a])
				lp[a]=++tot1;
			add(lp[a],l,mid,pos,x);
		}
		else
		{
			if(!rp[a])
				rp[a]=++tot1;
			add(rp[a],mid+1,r,pos,x);
		}
	}
}
void erase(int a,int l,int r,int pos,int x)
{
	del(root[a],x);
	if(l^r)
	{
		int mid=(l+r)>>1;
		if(pos<=mid)
			erase(lp[a],l,mid,pos,x);
		else
			erase(rp[a],mid+1,r,pos,x);
	}
}
int getrk(int a,int l,int r,int ll,int rr,int x)
{
	if(l==r||!a)
		return 1;
	int mid=(l+r)>>1;
	if(x<=mid)
		return getrk(lp[a],l,mid,ll,rr,x);
	int sum=rank(root[lp[a]],rr+1)-rank(root[lp[a]],ll);
	return sum+getrk(rp[a],mid+1,r,ll,rr,x);
}
int kth(int a,int l,int r,int ll,int rr,int x)
{
	if(l==r)
		return l;
	int mid=(l+r)>>1;
	int sum=rank(root[lp[a]],rr+1)-rank(root[lp[a]],ll);
	if(x<=sum)
		return kth(lp[a],l,mid,ll,rr,x);
	else
		return kth(rp[a],mid+1,r,ll,rr,x-sum);
}
int main()
{
	int s=clock();
	#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("treap.out","w",stdout);
	#endif
	srand(time(0));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",num+i);
		add(1,0,rm,num[i],i);
	}
	for(int i=1;i<=m;i++)
	{
		int a,b,c,d;
		scanf("%d",&a);
		if(a==1)
		{
			scanf("%d%d%d",&b,&c,&d);
			printf("%d\n",getrk(1,0,rm,b,c,d));
		}
		else if(a==2)
		{
			scanf("%d%d%d",&b,&c,&d);
			printf("%d\n",kth(1,0,rm,b,c,d));
		}
		else if(a==3)
		{
			scanf("%d%d",&b,&c);
			erase(1,0,rm,num[b],b);
			num[b]=c;
			add(1,0,rm,c,b);
		}
		else if(a==4)
		{
			scanf("%d%d%d",&b,&c,&d);
			int t=getrk(1,0,rm,b,c,d);
			if(t<=1)
				printf("%d\n",-inf);
			else
				printf("%d\n",kth(1,0,rm,b,c,t-1));
		}
		else if(a==5)
		{
			scanf("%d%d%d",&b,&c,&d);
			int t=getrk(1,0,rm,b,c,d+1);
			if(t>=c-b+2)
				printf("%d\n",inf);
			else
				printf("%d\n",kth(1,0,rm,b,c,t));
		}
	}
	int t=clock();
	// cerr<<t-s;
	return 0;
}