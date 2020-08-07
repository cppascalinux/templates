//2020.08.07
//luoguP4779 spfa+slf优化..然而并不能通过只是用来套数据..
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<deque>
#include<vector>
#include<random>
#define LL long long
#define PII pair<int,int>
#define FI first
#define SE second
using namespace std;
int n,m,s;
LL dis[100009];
int vis[100009];
vector<PII> g[100009];
void spfa(int s)
{
	deque<int> q;
	q.push_back(s);
	memset(dis,0x7F,sizeof(dis));
	dis[s]=0;
	vis[s]=1;
	while(!q.empty())
	{
		int x=q.front();
		q.pop_front();
		vis[x]=0;
		for(PII t:g[x])
			if(dis[t.FI]>dis[x]+t.SE)
			{
				dis[t.FI]=dis[x]+t.SE;
				if(!vis[t.FI])
				{
					vis[t.FI]=1;
					if(dis[t.FI]<dis[q.front()])
						q.push_front(t.FI);
					else
						q.push_back(t.FI);
				}
			}
	}
	for(int i=1;i<=n;i++)
		printf("%lld ",dis[i]);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("slf.in","r",stdin);
	freopen("slf.out","w",stdout);
#endif
	scanf("%d%d%d",&n,&m,&s);
	for(int i=1,a,b,c;i<=m;i++)
		scanf("%d%d%d",&a,&b,&c),g[a].push_back(PII(b,c)),g[b].push_back(PII(a,c));
	mt19937 rnd;
	for(int i=1;i<=n;i++)
		shuffle(g[i].begin(),g[i].end(),rnd);
	spfa(s);
	return 0;
}