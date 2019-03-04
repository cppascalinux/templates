#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 998244353
#define ll long long
using namespace std;
int n,len;
int mp[1050000],rt[2][1050000];
int g[1050000],f[1050000],tg[1050000];
int iv[1050000];
int qpow(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1)
			ans=(ll)ans*a%mod;
		b>>=1;
		a=(ll)a*a%mod;
	}
	return ans;
}
void init(int bit)
{
	len=1<<bit;
	for(int i=0;i<len;i++)
		mp[i]=(mp[i>>1]>>1)|((i&1)<<(bit-1));
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
		int inv=iv[len];
		for(int i=0;i<len;i++)
			s[i]=(ll)s[i]*inv%mod;
	}
}
void dif(int *s,int l)
{
	for(int i=0;i<l-1;i++)
		s[i]=(ll)s[i+1]*(i+1)%mod;
	s[l-1]=0;
}
void ing(int *s,int l)
{
	for(int i=l-1;i>=1;i--)
		s[i]=(ll)s[i-1]*iv[i]%mod;
	s[0]=0;
}
void getinv()
{
	f[0]=1;
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
	}
}
void getlog()
{
	getinv();
	dif(g,n);
	int bit=0;
	while(1<<bit<2*n)
		bit++;
	init(bit);
	for(int i=n;i<len;i++)
		f[i]=0;
	// for(int i=0;i<10;i++)
	// 	printf("i:%d g:%d f:%d\n",i,g[i],f[i]);
	fft(f,0);
	fft(g,0);
	for(int i=0;i<len;i++)
		f[i]=(ll)f[i]*g[i]%mod;
	fft(f,1);
	// for(int i=0;i<10;i++)
	// 	printf("i:%d f:%d\n",i,f[i]);
	ing(f,n);
	for(int i=0;i<n;i++)
		printf("%d ",f[i]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("log.in","r",stdin);
	freopen("log.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",g+i);
	iv[1]=1;
	for(int i=2;i<1050000;i++)
		iv[i]=(ll)(mod-mod/i)*iv[mod%i]%mod;
	getlog();
	return 0;
}