//luoguP3389【模板】高斯消元法
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define db double
#define eps 1e-8
using namespace std;
int n;
db f[109][109];
int sgn(db x)
{
	return x>eps?1:(x<-eps?-1:0);
}
int gauss()
{
	for(int i=1;i<=n;i++)
	{
		int t=0;
		for(int j=i;j<=n;j++)
			if(sgn(f[j][i]))
				t=j;
		if(!t)
			return 0;
		for(int j=i;j<=n+1;j++)
			swap(f[i][j],f[t][j]);
		db r=f[i][i];
		for(int j=i;j<=n+1;j++)
			f[i][j]/=r;
		for(int j=i+1;j<=n;j++)
		{
			db r=f[j][i];
			for(int k=i;k<=n+1;k++)
				f[j][k]-=r*f[i][k];
		}
		// for(int i=1;i<=n;i++)
		// {
		// 	for(int j=1;j<=n+1;j++)
		// 		printf("%.2lf ",f[i][j]);
		// 	printf("\n");
		// }
		// printf("\n");
	}
	// for(int i=1;i<=n;i++)
	// {
	// 	for(int j=1;j<=n+1;j++)
	// 		printf("%.2lf ",f[i][j]);
	// 	printf("\n");
	// }
	for(int i=n-1;i>=1;i--)
		for(int j=i+1;j<=n;j++)
			f[i][n+1]-=f[i][j]*f[j][n+1];
	return 1;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("gauss.in","r",stdin);
	freopen("gauss.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n+1;j++)
			scanf("%lf",&f[i][j]);
	if(!gauss())
		printf("No Solution");
	else
		for(int i=1;i<=n;i++)
			printf("%.2lf\n",f[i][n+1]);
	return 0;
}