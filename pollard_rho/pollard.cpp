//2019.05.21
//luoguP4718 【模板】Pollard-Rho算法 玄学调参 卡时
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<cmath>
#define li long long
#define ldb long double
using namespace std;
li mx;
li qmul(li a,li b,li mod)
{
	a%=mod,b%=mod;
	return (a*b-(li)((ldb)a*b/mod)*mod+mod)%mod;
}
li qpow(li a,li b,li mod)
{
	li ans=1;
	a%=mod;
	for(;b;b>>=1,a=qmul(a,a,mod))
		if(b&1)
			ans=qmul(ans,a,mod);
	return ans;
}
int test(li x,li a)
{
	if(qpow(a,x-1,x)!=1)
		return 0;
	li t=x-1;
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
	for(int i=1;i<=20;i++)
		if(!test(x,rand()%(x-1)+1))
			return 0;
	return 1;
}
li g(li x,li b,li mod)
{
	return (qmul(x,x,mod)+b)%mod;
}
li gcd(li a,li b)
{
	return !a||!b?a+b:gcd(b,a%b);
}
void pollard(li x)
{
	if(miller(x))
	{
		mx=max(mx,x);
		return;
	}
	if(x%2==0){return mx=max(mx,2LL),pollard(x/2);}
	if(x%3==0){return mx=max(mx,3LL),pollard(x/3);}
	if(x%5==0){return mx=max(mx,5LL),pollard(x/5);}
	if(x%7==0){return mx=max(mx,7LL),pollard(x/7);}
	if(x%11==0){return mx=max(mx,11LL),pollard(x/11);}
	while(1)
	{
		li b=rand()%(x-1)+1;
		li p1=rand()%(x-1)+1,p2=p1;
		p2=g(p2,b,x);
		int tme=0;
		li sm=1;
		while(p1!=p2)
		{
			li np1=g(p1,b,x),np2=g(g(p2,b,x),b,x);
			sm=qmul(sm,abs(p1-p2),x);
			tme++;
			if(tme<=50||tme%10==0||np1==np2)
			{
				li t=gcd(sm,x);
				sm=1;
				if(t>1&&t<x)
				{
					pollard(t),pollard(x/t);
					return;
				}
			}
			p1=np1,p2=np2;
		}
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("pollard.in","r",stdin);
	freopen("pollard.out","w",stdout);
#endif
	srand(time(0)+20020618+20030619);
	int t;
	scanf("%d",&t);
	while(t--)
	{
		li x;
		scanf("%lld",&x);
		if(miller(x))
			printf("Prime\n");
		else
		{
			mx=0;
			pollard(x);
			printf("%lld\n",mx);
		}
	}
	return 0;
}