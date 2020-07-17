//2020.07.17
//luoguP3371 【模板】单源最短路径（弱化版）spfa
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define INF 0x7FFFFFFF
#define PII pair<int,int>
#define FI first
#define SE second
#define PB push_back
#define gc() (p1==p2&&(p2=(p1=buf1)+fread(buf1,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buf1[10000009];
int n,m,s;
int vis[10009],dis[10009];
vector<PII> e[10009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+ch-'0',ch=gc();
}
void spfa()
{
	queue<int> q;
	for(int i=1;i<=n;i++)
		dis[i]=INF;
	vis[s]=1;
	dis[s]=0;
	q.push(s);
	while(!q.empty())
	{
		int t=q.front();
		q.pop();
		vis[t]=0;
		for(auto i:e[t])
			if(vis[i.FI])
				dis[i.FI]=min(dis[i.FI],dis[t]+i.SE);
			else if(dis[i.FI]>dis[t]+i.SE)
				dis[i.FI]=dis[t]+i.SE,vis[i.FI]=1,q.push(i.FI);
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("spfa.in","r",stdin);
	freopen("spfa.out","w",stdout);
#endif
	rd(n),rd(m),rd(s);
	for(int i=1,a,b,c;i<=m;i++)
	{
		rd(a),rd(b),rd(c);
		e[a].PB(PII(b,c));
	}
	spfa();
	for(int i=1;i<=n;i++)
		printf("%d ",dis[i]);
	return 0;
}