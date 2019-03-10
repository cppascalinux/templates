//zroj614 智慧树 Bluestein任意基数NTT
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define mod 950009857
using namespace std;
int n,m,tot,len,bit;
int v[8009];
int hd[8009],eg[16009],nxt[16009];
int son[8009],sz[8009];
//bluestein
int f[21][58009];
int rt0[2][116009];
int ans[131109],tx[131109];
//fft
int rt1[2][131109],mp[131109];
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
	//bluestein
	rt0[0][0]=rt0[1][0]=1;
	rt0[0][1]=qpow(7,(mod-1)/m/2);
	for(int i=2;i<2*m;i++)
		rt0[0][i]=(ll)rt0[0][i-1]*rt0[0][1]%mod;
	for(int i=1;i<2*m;i++)
		rt0[1][i]=rt0[0][2*m-i];
	//fft
	while((1<<bit)<m*2)
		bit++;
	len=1<<bit;
	rt1[0][0]=rt1[1][0]=1;
	rt1[0][1]=qpow(7,(mod-1)/len);
	for(int i=2;i<len;i++)
		rt1[0][i]=(ll)rt1[0][i-1]*rt1[0][1]%mod;
	for(int i=1;i<len;i++)
		rt1[1][i]=rt1[0][len-i];
	for(int i=1;i<len;i++)
		mp[i]=(mp[i>>1]>>1)|((i&1)<<(bit-1));
}
void fft(int *s,int c)
{
	for(int i=0;i<len;i++)
		if(i<mp[i])
			swap(s[i],s[mp[i]]);
	for(int l=2;l<=len;l<<=1)
	{
		int d=l>>1,sp=len/l;
		for(int j=0;j<len;j+=l)
			for(int i=0;i<d;i++)
			{
				int t=(ll)rt1[c][sp*i]*s[i+j+d]%mod;
				s[i+j+d]=(s[i+j]+mod-t)%mod;
				s[i+j]=(s[i+j]+t)%mod;
			}
	}
	if(c)
	{
		int inv=qpow(len,mod-2);
		for(int i=0;i<len;i++)
			s[i]=(ll)s[i]*inv%mod;
	}
}
void dft(int *s,int *t,int c)
{
	for(int i=0;i<m;i++)
	{
		s[i]=(ll)s[i]*rt0[c][(ll)i*i%(m*2)]%mod;
		t[i]=rt0[c^1][(ll)i*i%(m*2)];
	}
	fft(s,0);
	fft(t,0);
	for(int i=0;i<len;i++)
		s[i]=(ll)s[i]*t[i]%mod;
	fft(s,1);
	for(int i=m;i<len;i++)
		s[i%m]=(s[i%m]+s[i])%mod;
	for(int i=0;i<m;i++)
		s[i]=(ll)s[i]*rt0[c][(ll)i*i%(m*2)]%mod;
	if(c)
	{
		int inv=qpow(m,mod-2);
		for(int i=0;i<m;i++)
			s[i]=(ll)s[i]*inv%mod;
	}
}
void dfs0(int x,int fa)
{
	sz[x]=1;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			dfs0(eg[i],x);
			sz[x]+=sz[eg[i]];
			if(sz[eg[i]]>sz[son[x]])
				son[x]=eg[i];
		}
}
void dfs1(int x,int fa,int d)
{
	memset(f[d],0,m<<2);
	if(!son[x])
	{
		int tmp=0;
		for(int i=0;i<m;i++)
		{
			// f[d][i]=rt0[0][(2LL*v[x]*i)%(m*2)];
			f[d][i]=rt0[0][tmp];
			tmp+=2*v[x];
			// tmp%=m*2;
			tmp-=tmp>=2*m?2*m:0;
		}
		// printf("x:%d---------------\n",x);
		// for(int i=0;i<m;i++)
		// 	printf("i:%d f:%d rt:%d\n",i,f[d][i],rt0[0][i*2]);
		for(int i=0;i<m;i++)
		{
			ans[i]+=f[d][i];
			ans[i]-=ans[i]>=mod?mod:0;
		}
		return;
	}
	else
	{
		dfs1(son[x],x,d);
		for(int i=0;i<m;i++)
		{
			f[d][i]++;
			f[d][i]-=f[d][i]>=mod?mod:0;
		}
	}
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa&&eg[i]!=son[x])
		{
			dfs1(eg[i],x,d+1);
			for(int j=0;j<m;j++)
				f[d][j]=(ll)f[d][j]*(f[d+1][j]+1)%mod;
		}
	int tmp=0;
	for(int i=0;i<m;i++)
	{
		// f[d][i]=(ll)f[d][i]*rt0[0][(2LL*v[x]*i)%(m*2)]%mod;
		f[d][i]=(ll)f[d][i]*rt0[0][tmp]%mod;
		tmp+=2*v[x];
		tmp-=tmp>=2*m?2*m:0;
	}
	// printf("x:%d---------------\n",x);
	// for(int i=0;i<m;i++)
	// 	printf("i:%d f:%d rt:%d\n",i,f[d][i],rt0[0][i*2]);
	for(int i=0;i<m;i++)
	{
		ans[i]+=f[d][i];
		ans[i]-=ans[i]>=mod?mod:0;
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a2.out","w",stdout);
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
	// printf("len:%d\n",len);
	dfs0(1,0);
	dfs1(1,0,1);
	dft(ans,tx,1);
	// for(int i=0;i<m;i++)
	// 	printf("%d ",ans[i]);
	// printf("\n");
	// fft(ans,1);
	for(int i=0;i<m;i++)
		printf("%d ",ans[i]);
	return 0;
}