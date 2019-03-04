//2018.12.03
//poj2154 color polya定理+枚举置换+分解质因数+枚举约数+欧拉函数+快速幂
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
#define ll long long
using namespace std;
int n,p,m,ans;
int c[100],k[100];
int s[100];
void init()
{
	m=0;
	int x=n;
	for(rg i=2;i*i<=x;i++)
		if(x%i==0)
		{
			m++;
			c[m]=i;
			k[m]=0;
			while(x%i==0)
			{
				x/=i;
				k[m]++;
			}
		}
	if(x>1)
	{
		c[++m]=x;
		k[m]=1;
	}
	// for(rg i=1;i<=m;i++)
	// 	printf("i:%d c:%d k:%d\n",i,c[i],k[i]);
}
int qpow(int a,int b,int mod)
{
	a%=mod;
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
void solve(int nm)
{
	// printf("nm:%d\n",nm);
	// for(rg i=1;i<=m;i++)
	// 	printf("i:%d s:%d\n",i,s[i]);
	int sm=1;
	for(rg i=1;i<=m;i++)
		if(s[i])
			sm=(ll)sm*(c[i]-1)%p*qpow(c[i],s[i]-1,p)%p;
	ans=(ans+(ll)qpow(n,nm-1,p)*sm)%p;
}
void dfs(int d,int nm)
{
	if(d>m)
	{
		solve(nm);
		return;
	}
	int lst=nm;
	for(rg i=k[d];i>=0;i--)
	{
		s[d]=i;
		dfs(d+1,lst);
		lst*=c[d];
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&p);
		init();
		ans=0;
		dfs(1,1);
		printf("%d\n",ans);
	}
	return 0;
}