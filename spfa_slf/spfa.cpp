#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
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
	queue<int> q;
	q.push(s);
	memset(dis,0x7F,sizeof(dis));
	dis[s]=0;
	vis[s]=1;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		vis[x]=0;
		for(PII t:g[x])
			if(dis[t.FI]>dis[x]+t.SE)
			{
				dis[t.FI]=dis[x]+t.SE;
				if(!vis[t.FI])
				{
					vis[t.FI]=1;
					q.push(t.FI);
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
	freopen("spfa.out","w",stdout);
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