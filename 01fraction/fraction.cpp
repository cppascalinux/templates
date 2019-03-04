#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
using namespace std;
int n,k;
int a[1010],b[1010];
double s[1010];
int judge(double x)
{
	double sum=0.0;
	for(rg i=1;i<=n;i++)
		s[i]=a[i]-b[i]*x;
	sort(s+1,s+n+1);
	for(rg i=n;i>=n-k+1;i--)
		sum+=s[i];
	return sum>=0.0;
}
double bin()
{
	double l=0.0,r=1e9,mid;
	while(r-l>1e-5)
	{
		mid=(l+r)/2;
		if(judge(mid))
			l=mid;
		else
			r=mid;
	}
	return mid;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("fraction.in","r",stdin);
	freopen("fraction.out","w",stdout);
	#endif
	scanf("%d%d",&n,&k);
	while(n)
	{
		k=n-k;
		for(rg i=1;i<=n;i++)
			scanf("%d",a+i);
		for(rg i=1;i<=n;i++)
			scanf("%d",b+i);
		for(rg i=1;i<=n;i++)
			s[i]=i;
		printf("%.0lf\n",bin()*100.0);
		scanf("%d%d",&n,&k);
	}
	return 0;
}