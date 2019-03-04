//2019.01.26
//luogu1337 吊打xxx 模拟退火/二分
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>
#define eps 1e-16
#define ll long long
#define db long double
#define rddb(t) t*(2*rand()-RAND_MAX)
using namespace std;
int n;
int x[1009],y[1009],w[1009];
db getf(db tx,db ty)
{
	db ans=0;
	for(int i=1;i<=n;i++)
		ans+=sqrtl((tx-x[i])*(tx-x[i])+(ty-y[i])*(ty-y[i]))*w[i];
	return ans;
}
void sa()
{
	srand(time(0));
	db tx,ty;
	int sw=0;
	ll sx=0,sy=0;
	for(int i=1;i<=n;i++)
	{
		sw+=w[i];
		sx+=w[i]*x[i];
		sy+=w[i]*y[i];
	}
	tx=(db)sx/sw;
	ty=(db)sy/sw;
	// printf("tx:%lf ty:%lf\n",tx,ty);
	db dx,dy,x1,y1,ans=getf(tx,ty);
	db ansx=tx,ansy=ty,mn=ans;
	for(db t0=1;t0>eps;t0*=0.99)
	{
		x1=tx+rddb(t0);
		y1=ty+rddb(t0);
		// printf("t0:%Lf rd:%Lf\n",t0,rddb(t0));
		db res=getf(x1,y1);
		if(res<mn)
		{
			mn=res;
			ansx=x1;
			ansy=y1;
		}
		if(res<ans||exp((ans-res)/t0)>(db)rand()/RAND_MAX)
		{
			ans=res;
			tx=x1;
			ty=y1;
		}
	}
	printf("%.3Lf %.3Lf",ansx,ansy);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sa.in","r",stdin);
	freopen("sa.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",x+i,y+i,w+i);
	sa();
	return 0;
}