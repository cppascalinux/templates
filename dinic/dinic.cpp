//2019.06.11
//loj101 最大流 dinic
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define inf 0x7FFFFFFFFFFFFFFFLL
#define li long long
using namespace std;
int n,m,s,t,tot=1;
int hd[109],eg[10009],nxt[10009],cap[10009];
int cur[109],dep[109];
void ins(int a,int b,int c)
{
    eg[++tot]=b,cap[tot]=c,nxt[tot]=hd[a],hd[a]=tot;
    eg[++tot]=a,cap[tot]=0,nxt[tot]=hd[b],hd[b]=tot;
}
int bfs()
{
    queue<int> q;
    memset(dep,0,sizeof(dep));
    dep[s]=1;
    q.push(s);
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        for(int i=hd[x];i;i=nxt[i])
            if(cap[i]&&!dep[eg[i]])
            {
                dep[eg[i]]=dep[x]+1;
                q.push(eg[i]);
            }
    }
    return dep[t];
}
li dfs(int x,li a)
{
    if(x==t||!a)
        return a;
    li totf=0;
    int f;
    for(int &i=cur[x];i;i=nxt[i])
        if(cap[i]&&dep[eg[i]]==dep[x]+1&&(f=dfs(eg[i],min(a,(li)cap[i]))))
        {
            cap[i]-=f,cap[i^1]+=f;
            a-=f,totf+=f;
            if(!a)
                break;
        }
    return totf;
}
li flow()
{
    li totf=0;
    while(bfs())
    {
        for(int i=1;i<=n;i++)
            cur[i]=hd[i];
        totf+=dfs(s,inf);
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
    for(int i=1,a,b,c;i<=m;i++)
    {
        scanf("%d%d%d",&a,&b,&c);
        ins(a,b,c);
    }
    printf("%lld",flow());
    return 0;
}