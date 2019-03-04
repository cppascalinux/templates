#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define rg register int
using namespace std;
int n,m,tot,t,sum;
int head[100010],edge[200010],next[200010];
int dfn[100010],low[100010];
int st[100010],top;
vector<int> ans[100010];
void add(int a,int b)
{
	edge[++tot]=b;
	next[tot]=head[a];
	head[a]=tot;
}
void dfs(int x,int fa)
{
	int child=0;
	dfn[x]=low[x]=++t;
	st[++top]=x;
	for(rg i=head[x];i;i=next[i])
		if(!dfn[edge[i]])
		{
			dfs(edge[i],x);
			low[x]=min(low[x],low[edge[i]]);
			if(low[edge[i]]>=dfn[x])
			{
				sum++;
				for(;st[top+1]^edge[i];top--)
					ans[sum].push_back(st[top]);
				ans[sum].push_back(x);
			}
		}
		else if(dfn[edge[i]]<dfn[x]&&edge[i]^fa)
			low[x]=min(low[x],dfn[edge[i]]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("bcc.in","r",stdin);
	freopen("bcc.out","w",stdout);
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
		{
			top=0;
			dfs(i,0);
		}
	printf("%d\n",sum);
	for(rg i=1;i<=sum;i++)
	{
		for(rg j=0;j<ans[i].size();j++)
			printf("%d ",ans[i][j]);
		printf("\n");
	}
	return 0;
}