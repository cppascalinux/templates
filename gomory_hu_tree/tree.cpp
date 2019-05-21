//2019.05.21
//luoguP4897 【模板】最小割树（Gomory-Hu Tree） 按s-t割分治,s-t集间连边即可
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define inf 0x7F7F7F7F
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n,m,tot=1;
int hd[509],eg[3009],nxt[3009],cap[3009],bkcap[3009];
int cur[509],dep[509];
int dis[509][509];
vector<pii> e[509];
void ins(int a,int b,int c)
{
	eg[++tot]=b;
	cap[tot]=c;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
int bfs(int s,int t)
{
	memset(dep,0,sizeof(dep));
	dep[s]=1;
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=hd[x];i;i=nxt[i])
			if(!dep[eg[i]]&&cap[i])
			{
				dep[eg[i]]=dep[x]+1;
				q.push(eg[i]);
			}
	}
	return dep[t];
}
int dfs(int t,int x,int a)
{
	if(x==t||!a)
		return a;
	int f,totf=0;
	for(int &i=cur[x];i;i=nxt[i])
		if(cap[i]&&dep[eg[i]]==dep[x]+1&&(f=dfs(t,eg[i],min(a,cap[i]))))
		{
			cap[i]-=f;
			cap[i^1]+=f;
			a-=f;
			totf+=f;
			if(!a)
				break;
		}
	return totf;
}
int flow(int s,int t)
{
	int totf=0;
	while(bfs(s,t))
	{
		for(int i=1;i<=n;i++)
			cur[i]=hd[i];
		totf+=dfs(t,s,inf);
	}
	return totf;
}
void solve(vector<int> v)
{
	if(v.size()<=1)
		return;
	int nf=flow(v[0],v[1]);
	e[v[0]].push_back(pii(v[1],nf));
	e[v[1]].push_back(pii(v[0],nf));
	for(int i=2;i<=tot;i++)
		cap[i]=bkcap[i];
	// printf("v0:%d v1;%d nf:%d\n",v[0],v[1],nf);
	vector<int> v0,v1;
	for(int i=0;i<(int)v.size();i++)
		if(dep[v[i]])
			v0.push_back(v[i]);
		else
			v1.push_back(v[i]);
	solve(v0),solve(v1);
}
void dfs1(int st,int x,int fa,int mn)
{
	dis[st][x]=mn;
	for(int i=0;i<(int)e[x].size();i++)
		if(e[x][i].fi!=fa)
			dfs1(st,e[x][i].fi,x,min(mn,e[x][i].se));
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1,a,b,c;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		ins(a,b,c),ins(b,a,c);
	}
	for(int i=2;i<=tot;i++)
		bkcap[i]=cap[i];
	vector<int> tv;
	for(int i=1;i<=n;i++)
		tv.push_back(i);
	solve(tv);
	for(int i=1;i<=n;i++)
		dfs1(i,i,0,inf);
	int q;
	scanf("%d",&q);
	for(int i=1,a,b;i<=q;i++)
	{
		scanf("%d%d",&a,&b);
		printf("%d\n",dis[a][b]);
	}
	return 0;
}