#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mo(x) while(x>=mod) x-=mod
#define long long long
#define rg register int
using namespace std;
int n,m,root,mod,tot,tote;
int val[100010];
int head[100010],next[200010],edge[200010];
int s[100010],top[100010],son[100010],dep[100010],f[100010],id[100010],pos[100010],last[100010];
int sum[400010],l[400010],r[400010],lazy[400010];
void ins(int a,int b)
{
	edge[++tot]=b;
	next[tot]=head[a];
	head[a]=tot;
}
void dfs1(int x,int fa)
{
	f[x]=fa;
	s[x]=1;
	dep[x]=dep[fa]+1;
	for(int i=head[x];i;i=next[i])
		if(edge[i]^fa)
		{
			dfs1(edge[i],x);
			s[x]+=s[edge[i]];
			if(s[edge[i]]>s[son[x]])
				son[x]=edge[i];
		}
}
void dfs2(int x,int t)
{
	if(!x)
		return;
	last[x]=id[x]=++tote;
	pos[tote]=x;
	top[x]=t;
	dfs2(son[x],t);
	last[x]=max(last[x],last[son[x]]);
	for(int i=head[x];i;i=next[i])
		if(edge[i]^f[x]&&edge[i]^son[x])
		{
			dfs2(edge[i],edge[i]);
			last[x]=max(last[x],last[edge[i]]);
		}
}
void build(int a,int ll,int rr)
{
	l[a]=ll;
	r[a]=rr;
	if(ll==rr)
		sum[a]=val[pos[ll]];
	else
	{
		int mid=(ll+rr)>>1;
		build(a<<1,ll,mid);
		build(a<<1|1,mid+1,rr);
		sum[a]=sum[a<<1]+sum[a<<1|1];
		mo(sum[a]);
	}
}
void down(int a)
{
	int la=a<<1,ra=a<<1|1;
	sum[la]=(sum[la]+(long)lazy[a]*(r[la]-l[la]+1))%mod;
	sum[ra]=(sum[ra]+(long)lazy[a]*(r[ra]-l[ra]+1))%mod;
	lazy[la]+=lazy[a];
	lazy[ra]+=lazy[a];
	lazy[a]=0;
	mo(lazy[la]);
	mo(lazy[ra]);
}
void add(int a,int ll,int rr,int val)
{
	if(l[a]>rr||r[a]<ll)
		return;
	if(l[a]>=ll&&r[a]<=rr)
	{
		sum[a]=(sum[a]+(long)val*(r[a]-l[a]+1))%mod;
		lazy[a]+=val;
		mo(lazy[a]);
		return;
	}
	down(a);
	add(a<<1,ll,rr,val);
	add(a<<1|1,ll,rr,val);
	sum[a]=sum[a<<1]+sum[a<<1|1];
	mo(sum[a]);
}
int ask(int a,int ll,int rr)
{
	if(l[a]>rr||r[a]<ll)
		return 0;
	if(l[a]>=ll&&r[a]<=rr)
		return sum[a];
	down(a);
	int tmp=ask(a<<1,ll,rr)+ask(a<<1|1,ll,rr);
	mo(tmp);
	return tmp;
}
void upd1(int x,int y,int val)
{
	int fx=top[x],fy=top[y];
	val%=mod;
	while(fx^fy)
	{
		if(dep[fx]>=dep[fy])
		{
			add(1,id[fx],id[x],val);
			x=f[fx];
		}
		else
		{
			add(1,id[fy],id[y],val);
			y=f[fy];
		}
		fx=top[x];
		fy=top[y];
	}
	if(id[x]<=id[y])
		add(1,id[x],id[y],val);
	else
		add(1,id[y],id[x],val);
}
int query1(int x,int y)
{
	int ans=0,fx=top[x],fy=top[y];
	while(fx^fy)
	{
		if(dep[fx]>=dep[fy])
		{
			ans+=ask(1,id[fx],id[x]);
			x=f[fx];
		}
		else
		{
			ans+=ask(1,id[fy],id[y]);
			y=f[fy];
		}
		mo(ans);
		fx=top[x];
		fy=top[y];
	}
	if(id[x]<=id[y])
		ans+=ask(1,id[x],id[y]);
	else
		ans+=ask(1,id[y],id[x]);
	mo(ans);
	return ans;
}
void upd2(int x,int val)
{
	int a=id[x],b=last[x];
	val%=mod;
	add(1,a,b,val);
}
int query2(int x)
{
	int a=id[x],b=last[x];
	return ask(1,a,b);
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("chain.in","r",stdin);
	freopen("chain.out","w",stdout);
	#endif
	scanf("%d%d%d%d",&n,&m,&root,&mod);
	for(rg i=1;i<=n;i++)
	{
		scanf("%d",val+i);
		val[i]%=mod;
	}
	for(rg i=1;i<=n-1;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		ins(a,b);
		ins(b,a);
	}
	dfs1(root,0);
	dfs2(root,root);
	build(1,1,n);
//	for(int i=1;i<=n;i++)
//		printf("i:%d si:%d depi:%d soni:%d idi:%d last:%d\n",i,s[i],dep[i],son[i],id[i],last[i]);
	for(rg i=1;i<=m;i++)
	{
		int a,b,c,d;
		scanf("%d",&a);
		if(a==1)
		{
			scanf("%d%d%d",&b,&c,&d);
			upd1(b,c,d);
		}
		else if(a==2)
		{
			scanf("%d%d",&b,&c);
			printf("%d\n",query1(b,c));
		}
		else if(a==3)
		{
			scanf("%d%d",&b,&c);
			upd2(b,c);
		}
		else
		{
			scanf("%d",&b);
			printf("%d\n",query2(b));
		}
//		for(int i=1;i<=n;i++)
//			printf("%d ",ask(1,id[i],id[i]));
//		printf("\n");
	}
	return 0;
}