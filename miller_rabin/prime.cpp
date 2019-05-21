//2019.05.21
//luoguP4718 【模板】Pollard-Rho算法
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#define li long long
#define ldb long double
using namespace std;
li qmul(li a,li b,li mod)
{
	a%=mod,b%=mod;
	return (a*b-(li)((ldb)a*b/mod)*mod+mod)%mod;
}
li qpow(li a,li b,li mod)
{
	li ans=1;
	for(;b;b>>=1,a=qmul(a,a,mod))
		if(b&1)
			ans=qmul(ans,a,mod);
	return ans;
}
int test(li x,li a)
{
	if(qpow(a,x-1,x)!=1)
		return 0;
	int t=x-1;
	while(t%2==0)
	{
		t/=2;
		li v=qpow(a,t,x);
		if(v==x-1)
			return 1;
		else if(v!=1)
			return 0;
	}
	return 1;
}
int miller(li x)
{
	if(x==2)
		return 1;
	if(x%2==0)
		return 0;
	for(int i=1;i<=10;i++)
	{
		int v=rand()%(x-1)+1;
		if(!test(x,v))
			return 0;
	}
	return 1;
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
#endif
	srand(time(0)+2002+6+18);
	int t;
	scanf("%d",&t);
	while(t--)
	{
		li x;
		scanf("%lld",&x);
		printf("%d\n",miller(x));
	}
	return 0;
}