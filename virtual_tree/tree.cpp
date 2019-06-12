//2019.06.11
//luoguP2495 [SDOI2011]消耗战 虚树
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define pii pair<int,int>
#define fi first
#define se second
#define li long long
#define inf 0x7F7F7F7F7F7F7F7FLL
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m,tot,tme,cntp;
int hd[250009],eg[500009],nxt[500009],len[500009];
int dfn[250009],mn[250009];
int f[250009][19],dep[250009];
int st[250009],vis[250009];
li h[250009];
int pe[1000009];
vector<int> g[250009];
vector<pii> ask;
void clr()
{
	// for(int i=1;i<=cntp;i++)
	// {
	// 	h[pe[i]]=inf;
	// 	g[pe[i]].clear();
	// 	vis[pe[i]]=0;
	// }
	// for(int i=0;i<(int)ask.size();i++)
	// 	vis[ask[i].se]=0,g[ask[i].se].clear();
	cntp=0;
	ask.clear();
}
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void ins(int a,int b,int c)
{
	eg[++tot]=b;
	len[tot]=c;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs1(int x,int fa)
{
	dfn[x]=++tme;
	dep[x]=dep[fa]+1;
	f[x][0]=fa;
	for(int i=1;i<=18;i++)
		f[x][i]=f[f[x][i-1]][i-1];
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			mn[eg[i]]=min(mn[x],len[i]);
			dfs1(eg[i],x);
		}
}
int getlca(int a,int b)
{
	if(dep[a]<dep[b])
		swap(a,b);
	int l=dep[a]-dep[b];
	for(int i=0;i<=18;i++)
		if(l>>i&1)
			a=f[a][i];
	if(a==b)
		return a;
	for(int i=18;i>=0;i--)
		if(f[a][i]!=f[b][i])
			a=f[a][i],b=f[b][i];
	return f[a][0];
}
void build()
{
	int tp=0;
	ask.push_back(pii(1,1));
	sort(ask.begin(),ask.end());
	for(int i=0;i<(int)ask.size();i++)
	{
		int p=ask[i].se,lca=getlca(p,st[tp]);
		// printf("i:%d p:%d\n",i,p);
		while(tp>1&&dfn[lca]<=dfn[st[tp-1]])
		{
			g[st[tp-1]].push_back(st[tp]);
			pe[++cntp]=st[tp-1],pe[++cntp]=st[tp--];
		}
		if(lca!=st[tp])
		{
			g[lca].push_back(st[tp]);
			pe[++cntp]=st[tp],pe[++cntp]=st[tp]=lca;
		}
		st[++tp]=p;
	}
	while(tp>1)
	{
		g[st[tp-1]].push_back(st[tp]);
		pe[++cntp]=st[tp-1],pe[++cntp]=st[tp--];
	}
}
void dfs2(int x,int fa)
{
	if(fa)
		h[x]=mn[x];
	else
		h[x]=inf;
	li sm=0;
	// printf("x:%d fa:%d\n",x,fa);
	for(int i=0;i<(int)g[x].size();i++)
		if(g[x][i]!=fa)
		{
			dfs2(g[x][i],x);
			sm+=h[g[x][i]];
		}
	if(!vis[x])
		h[x]=min((li)h[x],sm);
	vis[x]=0,g[x].clear();
}
void solve()
{
	dfs2(1,0);
	printf("%lld\n",h[1]);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	rd(n);
	for(int i=1,a,b,c;i<=n-1;i++)
	{
		rd(a),rd(b),rd(c);
		ins(a,b,c),ins(b,a,c);
	}
	memset(mn,0x7F,sizeof(mn));
	memset(h,0x7F,sizeof(h));
	dfs1(1,0);
	rd(m);
	for(int i=1,a,b;i<=m;i++)
	{
		rd(a);
		for(int j=1;j<=a;j++)
			rd(b),vis[b]=1,ask.push_back(pii(dfn[b],b));
		build();
		solve();
		clr();
	}
	return 0;
}