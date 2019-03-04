#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define rg int
using namespace std;
int n,m,tot,t;
int head[100010],edge[200010],next[200010];
int dfn[100010],low[100010],ans[100010];
void add(int a,int b)
{
	edge[++tot]=b;
	next[tot]=head[a];
	head[a]=tot;
}
void dfs(int x,int fa)
{
	dfn[x]=low[x]=++t;
	int child=0;
	for(rg i=head[x];i;i=next[i])
		if(!dfn[edge[i]])
		{
			child++;
			dfs(edge[i],x);
			low[x]=min(low[x],low[edge[i]]);
			if(low[edge[i]]>=dfn[x])
				ans[x]=1;
		}
		else if(dfn[edge[i]]<dfn[x]&&edge[i]!=fa)
			low[x]=min(low[x],dfn[edge[i]]);
	if(!fa&&child==1)
		ans[x]=0;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("tarjan.in","r",stdin);
	freopen("tarjan.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	int a,b;
	for(rg i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
	}
	for(rg i=1;i<=n;i++)
		if(!dfn[i])
			dfs(i,0);
	int sum=0;
	for(rg i=1;i<=n;i++)
		if(ans[i])
			sum++;
	printf("%d\n",sum);
	for(rg i=1;i<=n;i++)
		if(ans[i])
			printf("%d ",i);
	return 0;
}