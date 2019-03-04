#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define inf 0x7F7F7F7F
#define rg register int
using namespace std;
int n,m,tot,ans,rt,mn;
int hd[10009],eg[20009],nxt[20009],len[20009];
int sz[10009],vis[10009];
int st[10009],top;
void clr()
{
	memset(vis,0,sizeof(vis));
	memset(hd,0,sizeof(hd));
	tot=ans=0;
}
void ins(int a,int b,int c)
{
	eg[++tot]=b;
	len[tot]=c;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void getrt(int x,int fa,int siz)
{
	sz[x]=1;
	int mx=0;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]^fa&&!vis[eg[i]])
		{
			getrt(eg[i],x,siz);
			sz[x]+=sz[eg[i]];
			mx=max(mx,sz[eg[i]]);
		}
	// printf("mx0:%d\n",mx);
	mx=max(mx,siz-sz[x]);
	// printf("x:%d siz:%d mx:%d\n",x,siz,mx);
	// fflush(stdout);
	if(mx<mn)
	{
		mn=mx;
		rt=x;
	}
}
void dfs(int x,int fa,int suml)
{
	st[++top]=suml;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]^fa&&!vis[eg[i]])
			dfs(eg[i],x,suml+len[i]);
}
int cal(int x,int dis)
{
	int cnt=0;
	top=0;
	dfs(x,0,dis);
	sort(st+1,st+top+1);
	int j=top;
	for(rg i=1;i<j;i++)
	{
		while(st[i]+st[j]>m&&j>i)
			j--;
		cnt+=j-i;
	}
	return cnt;
}
void solve(int x,int sumsz)
{
	printf("x:%d\n",x);
	// for(rg i=1;i<=n;i++)
	// 	printf("i:%d sz:%d\n",i,sz[i]);
	ans+=cal(x,0);
	vis[x]=1;
	for(int i=hd[x];i;i=nxt[i])
		if(!vis[eg[i]])
		{
			ans-=cal(eg[i],len[i]);
			mn=inf;
			int tsz=sz[eg[i]]>sz[x]?sumsz-sz[x]:sz[eg[i]];
			getrt(eg[i],0,tsz);
			// mn=0;
			// getrt(rt,0,sz[eg[i]]);
			solve(rt,tsz);
		}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	while(n)
	{
		int a,b,c;
		for(rg i=1;i<=n-1;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			ins(a,b,c);
			ins(b,a,c);
		}
		mn=inf;
		getrt(1,0,n);
		// mn=0;
		// getrt(rt,0,n);
		// for(rg i=1;i<=n;i++)
		// 	printf("i:%d sz:%d\n",i,sz[i]);
		solve(rt,n);
		printf("%d\n",ans);
		clr();
		scanf("%d%d",&n,&m);
	}
	return 0;
}