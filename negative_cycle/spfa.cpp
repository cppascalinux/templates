//2020.07.17
//luoguP3385 【模板】负环 spfa判负环
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define PII pair<int,int>
#define FI first
#define SE second
#define PB push_back
using namespace std;
int n,m;
int dis[2009],vis[2009],dep[2009];
vector<PII> e[2009];
int spfa()
{
	queue<int> q;
	memset(dis,0x7F,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(dep,0,sizeof(dep));
	dis[1]=0,vis[1]=1,dep[1]=1;
	q.push(1);
	while(!q.empty())
	{
		int t=q.front();
		q.pop();
		vis[t]=0;
		for(auto i:e[t])
			if(dis[i.FI]>dis[t]+i.SE)
			{
				int x=i.FI,l=i.SE;
				if((dep[x]=dep[t]+1)>n)
					return 1;
				dis[x]=dis[t]+l;
				if(!vis[x])
					vis[x]=1,q.push(x);
			}
	}
	return 0;
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("spfa.in","r",stdin);
	freopen("spfa.out","w",stdout);
#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1,a,b,c;i<=m;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			e[a].PB(PII(b,c));
			if(c>=0)
				e[b].PB(PII(a,c));
		}
		if(spfa())
			printf("YES\n");
		else
			printf("NO\n");
		for(int i=1;i<=n;i++)
			e[i].clear();
	}
	return 0;
}