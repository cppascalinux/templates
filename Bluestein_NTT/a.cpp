#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 950009857
#define ll long long
using namespace std;
int n,tot,m;
int v[8009];
int f[109][209],t[209],ans[209];
int hd[8009],eg[16009],nxt[16009];
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs(int x,int fa)
{
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
			dfs(eg[i],x);
	memset(t,0,sizeof(t));
	f[x][v[x]]=1;
	t[v[x]]=1;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			for(int j=0;j<m;j++)
				for(int k=0;k<m;k++)
					t[(j+k)%m]=(t[(j+k)%m]+(ll)f[x][j]*f[eg[i]][k])%mod;
			memcpy(f[x],t,sizeof(t));
		}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",v+i);
	for(int i=1,a,b;i<=n-1;i++)
	{
		scanf("%d%d",&a,&b);
		ins(a,b);
		ins(b,a);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)
		for(int j=0;j<m;j++)
			ans[j]=(ans[j]+f[i][j])%mod;
	for(int i=0;i<m;i++)
		printf("%d ",ans[i]);
	return 0;
}