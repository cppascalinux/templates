//luogu P4721 【模板】分治 FFT
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define mod 998244353
using namespace std;
int n,len;
int mp[270009];
int rt[2][270009];
int f[270009],g[270009];
int tf[270009],tg[270009];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(ll)a*a%mod)
		if(b&1)
			ans=(ll)ans*a%mod;
	return ans;
}
void init(int l)
{
	int bit=0;
	while((1<<bit)<l)
		bit++;
	len=1<<bit;
	rt[0][0]=rt[1][0]=1;
	rt[0][1]=qpow(3,(mod-1)/len);
	// printf("rt:%d\n",rt[0][1]);
	for(int i=2;i<len;i++)
		rt[0][i]=(ll)rt[0][i-1]*rt[0][1]%mod;
	for(int i=1;i<len;i++)
		rt[1][i]=rt[0][len-i];
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
		int sp=len/l,d=l>>1;
		for(int j=0;j<len;j+=l)
			for(int i=0;i<d;i++)
			{
				int t=(ll)s[i+j+d]*rt[c][sp*i]%mod;
				s[i+j+d]=(s[i+j]-t+mod)%mod;
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
void cdq(int l,int r)
{
	if(l==r)
		return;
	// printf("l:%d r:%d\n",l,r);
	int mid=(l+r)>>1;
	cdq(l,mid);
	init(r+mid-2*l+1);
	memset(tf,0,len<<2);
	memset(tg,0,len<<2);
	for(int i=0;i<=r-l;i++)
		tg[i]=g[i];
	for(int i=0;i<=mid-l;i++)
		tf[i]=f[i+l];
	fft(tf,0);
	fft(tg,0);
	// fft(tf,1);
	// printf("tf: ");
	// for(int i=0;i<len;i++)
	// 	printf("%d ",tf[i]);
	// printf("\ntg: ");
	// for(int i=0;i<len;i++)
	// 	printf("%d ",tg[i]);
	// printf("\n");
	for(int i=0;i<len;i++)
		tf[i]=(ll)tf[i]*tg[i]%mod;
	fft(tf,1);
	// for(int i=0;i<len;i++)
	// 	printf("%d ",tf[i]);
	// printf("\n");
	for(int i=mid+1;i<=r;i++)
		f[i]=(f[i]+tf[i-l])%mod;
	cdq(mid+1,r);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("fft.in","r",stdin);
	freopen("fft.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++)
		scanf("%d",g+i);
	// g[0]=1;
	f[0]=1;
	cdq(0,n-1);
	for(int i=0;i<=n-1;i++)
		printf("%d ",f[i]);
	return 0;
}