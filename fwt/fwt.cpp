//2019.04.09
//luoguP4717 【模板】快速沃尔什变换
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define mod 998244353
#define inv2 499122177
using namespace std;
int n;
int p[3][140009],q[3][140009];
int ans[3][140009];
void fwtor(int *s,int c)
{
	for(int l=2;l<=n;l<<=1)
	{
		int d=l>>1;
		for(int j=0;j<n;j+=l)
			for(int i=0;i<d;i++)
				if(!c)
					s[i+j+d]=(s[i+j+d]+s[i+j])%mod;
				else
					s[i+j+d]=(s[i+j+d]-s[i+j]+mod)%mod;
	}
}
void fwtand(int *s,int c)
{
	for(int l=2;l<=n;l<<=1)
	{
		int d=l>>1;
		for(int j=0;j<n;j+=l)
			for(int i=0;i<d;i++)
				if(!c)
					s[i+j]=(s[i+j]+s[i+j+d])%mod;
				else
					s[i+j]=(s[i+j]-s[i+j+d]+mod)%mod;
	}
}
void fwtxor(int *s,int c)
{
	for(int l=2;l<=n;l<<=1)
	{
		int d=l>>1;
		for(int j=0;j<n;j+=l)
			for(int i=0;i<d;i++)
			{
				int l=s[i+j],r=s[i+j+d];
				s[i+j]=(s[i+j]+r)%mod;
				s[i+j+d]=(l-s[i+j+d]+mod)%mod;
				if(c)
				{
					s[i+j]=(ll)s[i+j]*inv2%mod;
					s[i+j+d]=(ll)s[i+j+d]*inv2%mod;
				}
			}
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("fwt.in","r",stdin);
	freopen("fwt.out","w",stdout);
#endif
	scanf("%d",&n);
	n=1<<n;
	for(int i=0;i<n;i++)
		scanf("%d",p[0]+i);
	for(int i=0;i<n;i++)
		scanf("%d",q[0]+i);
	memcpy(p[1],p[0],sizeof(p[0]));
	memcpy(p[2],p[0],sizeof(p[0]));
	memcpy(q[1],q[0],sizeof(q[0]));
	memcpy(q[2],q[0],sizeof(q[0]));
	fwtor(p[0],0);
	fwtor(q[0],0);
	for(int i=0;i<n;i++)
		ans[0][i]=(ll)p[0][i]*q[0][i]%mod;
	fwtor(ans[0],1);
	fwtand(p[1],0);
	fwtand(q[1],0);
	for(int i=0;i<n;i++)
		ans[1][i]=(ll)p[1][i]*q[1][i]%mod;
	fwtand(ans[1],1);
	fwtxor(p[2],0);
	fwtxor(q[2],0);
	for(int i=0;i<n;i++)
		ans[2][i]=(ll)p[2][i]*q[2][i]%mod;
	fwtxor(ans[2],1);
	for(int i=0;i<=2;i++)
	{
		for(int j=0;j<n;j++)
			printf("%d ",ans[i][j]);
		printf("\n");
	}
	return 0;
}