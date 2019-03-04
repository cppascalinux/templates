//2018.11.23
//poj2318 toy 向量叉积+二分
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define db double
#define rg register int
#define eps 1e-8
using namespace std;
int n,m;
db x1,y1,x2,y2;
int sgn(db x)
{
	return x<-eps?-1:(x>eps?1:0);
}
struct point
{
	db x,y;
	point(){}
	point(db a,db b){x=a,y=b;}
	point operator +(point p){return point(x+p.x,y+p.y);}
	point operator -(point p){return point(x-p.x,y-p.y);}
	point operator *(db v){return point(x*v,y*v);}
	db operator *(point p){return x*p.x+y*p.y;}
	db operator ^(point p){return x*p.y-y*p.x;}
	int operator ==(point p){return sgn(x-p.x)==0&&sgn(y-p.y)==0;}
};
point l1[5009],l2[5009];
int ans[5009];
int cross(point o,point a,point b)
{
	return sgn((a-o)^point(b-o));
}
void solve(point p)
{
	int l=0,r=n,mid;
	while(l<r)
	{
		mid=(l+r+1)>>1;
		if(cross(p,l1[mid],l2[mid])>=0)
			l=mid;
		else
			r=mid-1;
	}
	ans[l]++;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("toy.in","r",stdin);
	freopen("toy.out","w",stdout);
	#endif
	scanf("%d%d%lf%lf%lf%lf",&n,&m,&x1,&y1,&x2,&y2);
	while(n)
	{
		l1[0]=point(x1,y1);
		l2[0]=point(x1,y2);
		for(rg i=1;i<=n;i++)
		{
			scanf("%lf%lf",&l1[i].x,&l2[i].x);
			l1[i].y=y1;
			l2[i].y=y2;
		}
		for(rg i=1;i<=m;i++)
		{
			point p;
			scanf("%lf%lf",&p.x,&p.y);
			solve(p);
		}
		for(rg i=0;i<=n;i++)
			printf("%d: %d\n",i,ans[i]);
		printf("\n");
		memset(ans,0,sizeof(ans));
		scanf("%d%d%lf%lf%lf%lf",&n,&m,&x1,&y1,&x2,&y2);
	}
	return 0;
}