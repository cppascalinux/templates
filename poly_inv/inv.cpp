#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 998244353
#define ll long long
using namespace std;
int len;
int rt[2][1050000];
int f[1050000],mp[1050000];
int g[1050000],tg[1050000];
int qpow(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1)
			ans=(ll)ans*a%mod;
		a=(ll)a*a%mod;
		b>>=1;
	}
	return ans;
}
void init(int bit)
{
	len=1<<bit;
	for(int i=0;i<len;i++)
		mp[i]=(mp[i>>1]>>1)|((i&1)<<(bit-1));
	// for(int i=0;i<len;i++)
	// 	printf("i:%d mp:%d\n",i,mp[i]);
	rt[0][0]=rt[1][0]=1;
	rt[0][1]=qpow(3,119*(1<<(23-bit)));
	for(int i=2;i<len;i++)
		rt[0][i]=(ll)rt[0][i-1]*rt[0][1]%mod;
	for(int i=1;i<len;i++)
		rt[1][i]=rt[0][len-i];
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
				int t=(ll)rt[c][sp*i]*s[i+j+d]%mod;
				s[i+j+d]=(s[i+j]-t+mod)%mod;
				s[i+j]=(s[i+j]+t)%mod;
			}
	}
	if(c)
	{
		int inv=qpow(len,mod-2);
		// printf("inv:%d\n",inv);
		for(int i=0;i<len;i++)
			s[i]=(ll)s[i]*inv%mod;
	}
}
void getinv(int *f,int *g,int n)
{
	f[0]=qpow(g[0],mod-2);
	for(int i=1;(1<<i)<2*n;i++)
	{
		init(i+1);
		memcpy(tg,g,len<<1);
		fft(f,0);
		fft(tg,0);
		for(int j=0;j<len;j++)
			f[j]=f[j]*(2-(ll)f[j]*tg[j]%mod+mod)%mod;
		fft(f,1);
		for(int j=len>>1;j<len;j++)
			f[j]=0;
		// printf("\ni:%d\n",i);
		// for(int j=0;j<len;j++)
		// 	printf("j:%d f:%d\n",j,f[j]);
	}
	for(int i=0;i<n;i++)
		printf("%d ",f[i]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("inv.in","r",stdin);
	freopen("inv.out","w",stdout);
#endif
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",g+i);
		g[i]%=mod;
	}
	getinv(f,g,n);
	return 0;
}