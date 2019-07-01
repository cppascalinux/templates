//2019.07.01
//luoguP4781 【模板】拉格朗日插值 直接套公式即可(其实和crt很像本质上就是一个构造)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
#define mod 998244353
using namespace std;
int n,k;
int vx[2009],vy[2009];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(li)a*a%mod)
		if(b&1)
			ans=(li)ans*a%mod;
	return ans;
}
void solve()
{
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int sm1=vy[i],sm2=1;
		for(int j=1;j<=n;j++)
			if(i!=j)
			{
				sm1=(li)sm1*(k+mod-vx[j])%mod;
				sm2=(li)sm2*(vx[i]+mod-vx[j])%mod;
			}
		ans=(ans+(li)sm1*qpow(sm2,mod-2))%mod;
	}
	printf("%d",ans);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("lag.in","r",stdin);
	freopen("lag.out","w",stdout);
#endif
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d%d",vx+i,vy+i);
	solve();
	return 0;
}