#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define rg register int
using namespace std;
ll n;
int m;
ll p[20],v[20];
void exgcd(ll a,ll b,ll &x,ll &y)
{
	if(b==0)
	{
		x=1;
		y=0;
		return;
	}
	exgcd(b,a%b,y,x);
	y-=a/b*x;
}
ll inv(ll a,ll mod)
{
	ll x,y;
	exgcd(a,mod,x,y);
	x=(x%mod+mod)%mod;
	return x;
}
ll mul(ll a,ll b,ll mod)
{
	ll ans=0;
	a%=mod;
	b%=mod;
	if(a<b)
		swap(a,b);
	while(b)
	{
		if(b&1)
			ans=(ans+a)%mod;
		b>>=1;
		a=(a<<1)%mod;
	}
	return ans;
}
ll solve()
{
	ll sum=1,t,it,ans=0;
	for(rg i=1;i<=m;i++)
		sum*=p[i];
	for(rg i=1;i<=m;i++)
	{
		t=sum/p[i];
		it=inv(t,p[i]);
//		printf("i:%d t:%lld it:%lld ",i,t,it);
		t=mul(t,it,sum);
		t=mul(t,v[i],sum);
//		printf(" t1:%lld\n",t);
		ans=(ans+t)%sum;
	}
//	printf("ans:%lld\n",ans);
	if(ans>n)
		return -1;
	return (n-ans)%sum;
}
int main()
{
	freopen("hanxin.in","r",stdin);
	freopen("hanxin.out","w",stdout);
	scanf("%lld%d",&n,&m);
	for(rg i=1;i<=m;i++)
		scanf("%lld%lld",p+i,v+i);
	printf("%lld\n",solve());
	return 0;
}