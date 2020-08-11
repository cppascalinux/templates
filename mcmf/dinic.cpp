//2020.08.11
//luoguP3381 【模板】最小费用最大流 最小费用路算法..魔改dinic..注意dfs时每个点只能走一次,否则可能陷入零环,死循环..
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define INF 0x7F7F7F7F
using namespace std;
int n,m,s,t,tot=1,cnt;
int hd[5009],eg[100009],nxt[100009],cap[100009],cst[100009];
int vis[5009],dis[5009],cur[5009];
void adde(int a,int b,int c,int d)
{
	eg[++tot]=b;
	cap[tot]=c;
	cst[tot]=d;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
int spfa()
{
	queue<int> q;
	memset(vis,0,(n+1)<<2);
	memset(dis,0x7F,(n+1)<<2);
	vis[s]=1,dis[s]=0,q.push(s);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		vis[x]=0;
		for(int i=hd[x],p=eg[i];i;i=nxt[i],p=eg[i])
			if(cap[i]&&dis[p]>dis[x]+cst[i])
			{
				dis[p]=dis[x]+cst[i];
				if(!vis[p])
					vis[p]=1,q.push(p);
			}
	}
	return dis[t]<INF;
}
int dfs(int x,int a,int d)
{
	// printf("x:%d de:%d\n",x,d),fflush(stdout);
	if(x==t||a==0)
		return a;
	int f,totf=0;
	vis[x]=1;
	for(int &i=cur[x],p=eg[i];i;i=nxt[i],p=eg[i])
		if(!vis[p]&&cap[i]&&dis[p]==dis[x]+cst[i]&&(f=dfs(p,min(a,cap[i]),d+1)))
		{
			cap[i]-=f,cap[i^1]+=f;
			a-=f,totf+=f,cnt+=f*cst[i];
			if(!a)
				break;
		}
	return totf;
}
int flow()
{
	int totf=0;
	while(spfa())
	{
		// printf("qwq\n"),fflush(stdout);
		memcpy(cur,hd,(n+1)<<2);
		memset(vis,0,(n+1)<<2);
		totf+=dfs(s,INF,1);
	}
	return totf;
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("dinic.in","r",stdin);
	freopen("dinic.out","w",stdout);
#endif
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=1,a,b,c,d;i<=m;i++)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		adde(a,b,c,d);
		adde(b,a,0,-d);
	}
	int f=flow();
	printf("%d %d\n",f,cnt);
	return 0;
}