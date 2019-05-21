#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
#define ldb long double
using namespace std;
li qmul(li a,li b,li mod)
{
	a%=mod,b%=mod;
	return (a*b-(li)((ldb)a*b/mod)*mod+mod)%mod;
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("qmul.in","r",stdin);
	freopen("qmul.out","w",stdout);
#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		li a,b,c;
		scanf("%lld%lld%lld",&a,&b,&c);
		printf("%lld\n",qmul(a,b,c));
	}
	return 0;
}