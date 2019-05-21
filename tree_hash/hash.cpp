//2019.05.21
//luoguP5043 【模板】树同构（[BJOI2015]树的同构） 找重心+哈希括号序列+map
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#define mod 1000000009
#define bse 3
#define li long long
#define inf 0x7F7F7F7F
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n,m,mn,rt1,rt2;
vector<int> e[59];
int sz[59],hs[59];
int mul[109];
pii val[59];
void clr()
{
	for(int i=1;i<=n;i++)
		e[i].clear();
}
void dfs1(int x,int fa)
{
	int mx=0;
	sz[x]=1;
	for(int i=0;i<(int)e[x].size();i++)
		if(e[x][i]!=fa)
		{
			dfs1(e[x][i],x);
			sz[x]+=sz[e[x][i]];
			mx=max(mx,sz[e[x][i]]);
		}
	mx=max(mx,n-sz[x]);
	if(mx==mn)
		rt2=x;
	else if(mx<mn)
		mn=mx,rt1=x,rt2=0;
}
void init()
{
	mul[0]=1;
	for(int i=1;i<=105;i++)
		mul[i]=(li)mul[i-1]*bse%mod;
}
bool cmp(int a,int b)
{
	return hs[a]<hs[b];
}
int dfs2(int x,int fa)
{
	sz[x]=hs[x]=1;
	for(int i=0;i<(int)e[x].size();i++)
		if(e[x][i]!=fa)
		{
			dfs2(e[x][i],x);
			sz[x]+=sz[e[x][i]];
		}
	sort(e[x].begin(),e[x].end(),cmp);
	for(int i=0;i<(int)e[x].size();i++)
		if(e[x][i]!=fa)
			hs[x]=((li)hs[x]*mul[sz[e[x][i]]*2]+hs[e[x][i]])%mod;
	return hs[x]=((li)hs[x]*bse+2)%mod;
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("hash.in","r",stdin);
	freopen("hash.out","w",stdout);
#endif
	scanf("%d",&m);
	init();
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&n);
		for(int j=1,a;j<=n;j++)
		{
			scanf("%d",&a);
			if(a)
			{
				e[a].push_back(j);
				e[j].push_back(a);
			}
		}
		mn=inf;
		dfs1(1,0);
		// printf("i:%d rt1:%d rt2:%d\n",i,rt1,rt2);
		if(rt2)
		{
			int hs1=dfs2(rt1,rt2),hs2=dfs2(rt2,rt1);
			if(hs1>hs2)
				swap(hs1,hs2);
			val[i]=pii(hs1,hs2);
		}
		else
			val[i]=pii(dfs2(rt1,0),0);
		clr();
	}
	// for(int i=1;i<=m;i++)
	// 	printf("i:%d fi:%d se:%d\n",i,val[i].fi,val[i].se);
	map<pii,int> p;
	for(int i=1;i<=m;i++)
		printf("%d\n",p[val[i]]?p[val[i]]:p[val[i]]=i);
	return 0;
}