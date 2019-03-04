//2018.12.14
//luogu3803 【模板】多项式乘法（FFT） ntt版
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define rg register int
#define mod 998244353
#define ll long long
#define rc register char
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m,l1,l2;
int inv[2100000],omg[2][2100000];
int v1[2100000],v2[2100000];
void read(int &x)
{
	rc ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
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
void init()
{
	while((1<<m)<n)
		m++;
	n=1<<m;
	omg[0][0]=1;
	omg[0][1]=qpow(3,119*(1<<(23-m)));
	for(rg i=2;i<n;i++)
		omg[0][i]=(ll)omg[0][i-1]*omg[0][1]%mod;
	omg[1][0]=1;
	omg[1][1]=qpow(omg[0][1],mod-2);
	for(rg i=2;i<n;i++)
		omg[1][i]=(ll)omg[1][i-1]*omg[1][1]%mod;
	for(rg i=0;i<n;i++)
		inv[i]=(inv[i>>1]>>1)|((i&1)<<(m-1));
}
void ntt(int c,int *s)
{
	for(rg i=0;i<n;i++)
		if(i<inv[i])
			swap(s[i],s[inv[i]]);
	for(rg l=2;l<=n;l<<=1)
	{
		int p=l>>1;
		for(rg j=0;j<n;j+=l)
			for(rg i=0;i<p;i++)
			{
				int t=(ll)omg[c][n/l*i]*s[i+j+p]%mod;
				s[i+j+p]=(s[i+j]-t+mod)%mod;
				s[i+j]=(s[i+j]+t)%mod;
			}
	}
}
void out(int x)
{
	if(!x)
		return;
	out(x/10);
	putchar(x%10+'0');
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("ntt.in","r",stdin);
	freopen("ntt.out","w",stdout);
	#endif
	read(l1),read(l2);
	l1++,l2++;
	for(rg i=0;i<l1;i++)
		read(v1[i]);
	for(rg i=0;i<l2;i++)
		read(v2[i]);
	n=l1+l2-1;
	init();
	ntt(0,v1);
	ntt(0,v2);
	for(rg i=0;i<n;i++)
		v1[i]=(ll)v1[i]*v2[i]%mod;
	ntt(1,v1);
	int ti=qpow(n,mod-2);
	for(rg i=0;i<l1+l2-1;i++)
	{
		int tmp=((ll)v1[i]*ti%mod);
		if(!tmp)
			putchar('0');
		else
			out(tmp);
		putchar(' ');
	}
	return 0;
}