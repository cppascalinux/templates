//2020.07.17
//luoguP5905 【模板】Johnson 全源最短路 大概就是先用spfa跑一遍最短路..然后一定有dis[v]<=dis[u]+l(u,v)
//所以把新的边权设为dis[u]-dis[v]+l(u,v)>=0,就可以跑n次dijkstra了..最后dis项全消掉了只剩s和t..再处理一下就行
//注意整个有向图不一定是强连通的..所以直接建一个超级源点,向每个点连一条权值为0的边..(其实就是spfa一开始全入队)
//总时间复杂度O(nmlogm)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cassert>
#define LL long long
#define INF 1000000000
#define PII pair<int,int>
#define FI first
#define SE second
#define PB push_back
using namespace std;
int n,m;
int dis0[3009],vis[3009],dep[3009];
int ans[3009][3009];
vector<PII> e[3009];
int spfa()
{
	queue<int> q;
	for(int i=1;i<=n;i++)
		vis[i]=dep[i]=1,q.push(i);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		vis[x]=0;
		for(auto i:e[x])
			if(dis0[i.FI]>dis0[x]+i.SE)
			{
				dis0[i.FI]=dis0[x]+i.SE;
				if((dep[i.FI]=dep[x]+1)>n)
					return 0;
				if(!vis[i.FI])
					vis[i.FI]=1,q.push(i.FI);
			}
	}
	return 1;
}
void rebuild()
{
	for(int i=1;i<=n;i++)
		for(auto &j:e[i])
			j.SE+=dis0[i]-dis0[j.FI];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			ans[i][j]=INF;
}
void dij(int s)
{
	int *dis=ans[s];
	memset(vis,0,sizeof(vis));
	dis[s]=0;
	priority_queue<PII,vector<PII>,greater<PII> > pq;
	pq.push(PII(0,s));
	while(!pq.empty())
	{
		PII x=pq.top();
		pq.pop();
		if(vis[x.SE])
			continue;
		vis[x.SE]=1;
		for(auto t:e[x.SE])
			if(!vis[t.FI]&&dis[t.FI]>x.FI+t.SE)
				dis[t.FI]=x.FI+t.SE,pq.push(PII(dis[t.FI],t.FI));
	}
	for(int i=1;i<=n;i++)
		if(dis[i]<INF)
			dis[i]+=dis0[i]-dis0[s];
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("johnson.in","r",stdin);
	freopen("johnson.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1,a,b,c;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		e[a].PB(PII(b,c));
	}
	if(!spfa())
		return printf("-1"),0;
	rebuild();
	for(int i=1;i<=n;i++)
		dij(i);
	for(int i=1;i<=n;i++)
	{
		LL out=0;
		for(int j=1;j<=n;j++)
			out+=(LL)j*ans[i][j];
		printf("%lld\n",out);
	}
	return 0;
}