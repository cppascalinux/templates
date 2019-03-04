#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define rg register int
#define rc register char
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000010];
int n,m,s,tot;
int f[500010];
int head[500010],edge[1000010],nxt[1000010];
int hq[500010],v[1000010],id[1000010],nq[1000010];
int vist[500010];
int ans[500010];
void read(int &x)
{
    rc ch=0;
    x=0;
    while(ch<'0'||ch>'9')
        ch=gc();
    while(ch>='0'&&ch<='9')
        x=(x<<1)+(x<<3)+(ch&15),ch=gc();
}
void ins(int a,int b)
{
    edge[++tot]=b;
    nxt[tot]=head[a];
    head[a]=tot;
}
void insq(int a,int b,int c)
{
    v[++tot]=b;
    id[tot]=c;
    nq[tot]=hq[a];
    hq[a]=tot;
}
int find(int x)
{
    if(x==f[x])
        return x;
    return f[x]=find(f[x]);
}
void dfs(int x,int fa)
{
    vist[x]=1;
    for(int i=head[x];i;i=nxt[i])
        if(edge[i]^fa)
            dfs(edge[i],x);
    for(rg i=hq[x];i;i=nq[i])
	{
        if(vist[id[i]])
            ans[id[i]]=find(v[i]);
		vist[id[i]]=1;
	}
    f[find(x)]=find(fa);
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("lca.in","r",stdin);
    freopen("lca.out","w",stdout);
    #endif
    read(n);
    read(m);
    read(s);
    int a,b;
    for(rg i=1;i<=n;i++)
        f[i]=i;
    for(rg i=1;i<=n-1;i++)
    {
        read(a);
        read(b);
        ins(a,b);
        ins(b,a);
    }
    tot=1;
    for(rg i=1;i<=m;i++)
    {
        read(a);
        read(b);
        insq(a,b,i);
        insq(b,a,i);
    }
    dfs(s,0);
    for(rg i=1;i<=m;i++)
        printf("%d\n",ans[i]);
    return 0;
}