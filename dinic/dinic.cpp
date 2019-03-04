#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int inf=0x7FFFFFFF;
int n,m,s,t,tot=1;
int head[10010],cur[10010],d[10010];
int edge[1000010],next[1000010],cap[1000010];
queue<int> q;
void ins(int a,int b,int c)
{
    edge[++tot]=b;
    cap[tot]=c;
    next[tot]=head[a];
    head[a]=tot;
    edge[++tot]=a;
    cap[tot]=0;
    next[tot]=head[b];
    head[b]=tot;
}
int bfs()
{
    int x;
    memset(d,0,sizeof(d));
    d[s]=1;
    q.push(s);
    while(!q.empty())
    {
        x=q.front();
        q.pop();
        for(int i=head[x];i;i=next[i])
            if(!d[edge[i]]&&cap[i])
            {
                d[edge[i]]=d[x]+1;
                q.push(edge[i]);
            }
    }
    return d[t];
}
int dfs(int x,int a)
{
    if(x==t||a==0)
        return a;
    int f,totf=0;
    for(int &i=cur[x];i;i=next[i])
        if(d[edge[i]]==d[x]+1&&(f=dfs(edge[i],min(a,cap[i]))))
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
int flow()
{
    int totf=0;
    while(bfs())
    {
        for(int i=1;i<=n;i++)
            cur[i]=head[i];
        totf+=dfs(s,inf);
    }
    return totf;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("dinic.in","r",stdin);
	freopen("dinic.out","w",stdout);
	#endif
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1;i<=m;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        ins(a,b,c);
    }
    printf("%d\n",flow());
    return 0;
}