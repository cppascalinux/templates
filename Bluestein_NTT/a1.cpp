#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#define ll long long
#define mod 950009857
using namespace std;
int n,m,tot;
int v[8009];
int hd[8009],eg[16009],nxt[16009];
int sz[8009],son[8009];
int rt[2][32809],mp[32809];
int g[19][32809],tg[32809];
int ans[32809];
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(ll)a*a%mod)
		if(b&1)
			ans=(ll)ans*a%mod;
	return ans;
}
void init()
{
	int bit=0;
	while((1<<bit)<m)
		bit++;
	rt[0][0]=rt[1][0]=1;
	rt[0][1]=qpow(7,(mod-1)/m);
	for(int i=2;i<m;i++)
		rt[0][i]=(ll)rt[0][i-1]*rt[0][1]%mod;
	for(int i=1;i<m;i++)
		rt[1][i]=rt[0][m-i];
	for(int i=0;i<m;i++)
		mp[i]=(mp[i>>1]>>1)|((i&1)<<(bit-1));
}
void fft(int *s,int c)
{
	for(int i=0;i<m;i++)
		if(i<mp[i])
			swap(s[i],s[mp[i]]);
	for(int l=2;l<=m;l<<=1)
	{
		int d=l>>1,sp=m/l;
		for(int j=0;j<m;j+=l)
			for(int i=0;i<d;i++)
			{
				int t=(ll)s[i+j+d]*rt[c][sp*i]%mod;
				s[i+j+d]=(s[i+j]-t+mod)%mod;
				s[i+j]=(s[i+j]+t)%mod;
			}
	}
	if(c)
	{
		int inv=qpow(m,mod-2);
		for(int i=0;i<m;i++)
			s[i]=(ll)s[i]*inv%mod;
	}
}
void dfs1(int x,int fa)
{
	sz[x]=1;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			dfs1(eg[i],x);
			sz[x]+=sz[eg[i]];
			if(sz[eg[i]]>sz[son[x]])
				son[x]=eg[i];
		}
}
void dfs2(int x,int fa,int tag)
{
	memset(g[tag],0,m<<2);
	if(son[x])
	{
		dfs2(son[x],x,tag);
		for(int i=0;i<m;i++)
		{
			g[tag][i]++;
			g[tag][i]-=g[tag][i]>=mod?mod:0;
		}
	}
	else
	{
		for(int i=0;i<m;i++)
			g[tag][i]=rt[0][(ll)i*v[x]%m];
		for(int i=0;i<m;i++)
		{
			ans[i]+=g[tag][i];
			ans[i]-=ans[i]>=mod?mod:0;
		}
		memcpy(tg,g[tag],m<<2);
		// fft(tg,1);
		printf("x:%d ----------\n",x);
		for(int i=0;i<m;i++)
			printf("i:%d g:%d\n",i,tg[i]);
		return;
	}
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa&&eg[i]!=son[x])
		{
			dfs2(eg[i],x,tag+1);
			for(int j=0;j<m;j++)
				g[tag][j]=(ll)g[tag][j]*(g[tag+1][j]+1)%mod;
		}
	for(int i=0;i<m;i++)
		g[tag][i]=(ll)g[tag][i]*rt[0][(ll)i*v[x]%m]%mod;
	memcpy(tg,g[tag],m<<2);
	// fft(tg,1);
	printf("x:%d ----------\n",x);
	for(int i=0;i<m;i++)
		printf("i:%d g:%d\n",i,tg[i]);
	for(int i=0;i<m;i++)
	{
		ans[i]+=g[tag][i];
		ans[i]-=ans[i]>=mod?mod:0;
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a1.out","w",stdout);
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
	init();
	dfs1(1,0);
	dfs2(1,0,1);
	for(int i=0;i<m;i++)
		printf("%d ",ans[i]);
	printf("\n");
	fft(ans,1);
	for(int i=0;i<m;i++)
		printf("%d ",ans[i]);
	cerr<<clock();
	return 0;
}