//2020.07.16
//luogu P4779 【模板】单源最短路径（标准版） 堆优化dijkstra
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define INF 0x7F7F7F7F
#define PB push_back
#define PII pair<int,int>
#define FI first
#define SE second
using namespace std;
int n,m,s;
int vis[100009],dis[100009];
vector<PII> e[100009];
void dij()
{
	memset(dis,0x7F,sizeof(dis));
	priority_queue<PII,vector<PII>,greater<PII> > pq;
	dis[s]=0;
	pq.push(PII(0,s));
	while(!pq.empty())
	{
		PII p=pq.top();
		pq.pop();
		if(vis[p.SE])
			continue;
		int x=p.SE,l=p.FI;
		vis[x]=1;
		for(auto i:e[x])
			if(!vis[i.FI]&&dis[i.FI]>l+i.SE)
				dis[i.FI]=l+i.SE,pq.push(PII(dis[i.FI],i.FI));
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("heap.in","r",stdin);
	freopen("heap.out","w",stdout);
#endif
	scanf("%d%d%d",&n,&m,&s);
	for(int i=1,a,b,c;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		e[a].PB(PII(b,c));
	}
	dij();
	for(int i=1;i<=n;i++)
		printf("%d ",dis[i]);
	return 0;
}