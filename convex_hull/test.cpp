//2018.11.26
//luogu2742 模板 二维凸包
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define rg register int
#define db double
#define eps 1e-6
using namespace std;
int n,top;
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
	db operator ^(point p){return x*p.y-y*p.x;}
	db operator ~(){return sqrt(x*x+y*y);}
	bool operator <(const point &p) const
	{
		return x<p.x||(x==p.x&&y<p.y);
	}
}p[10009],st[10009];
db cross(point o,point a,point b)
{
	return (a-o)^(b-o);
}
db solve()
{
	db ans=0;
	sort(p+1,p+n+1);
	for(rg i=1;i<=n;i++)
	{
		while(top>1&&sgn(cross(p[i],st[top],st[top-1]))>=0)
			top--;
		st[++top]=p[i];
	}
	// for(rg i=1;i<=top-1;i++)	
	// 	ans+=~(st[i+1]-st[i]);
	// printf("top:%d\n",top);
	// top=0;
	int tmp=top;
	// top--;
	for(rg i=n-1;i>=1;i--)
	{
		while(top>tmp&&sgn(cross(p[i],st[top],st[top-1]))>=0)
			top--;
		st[++top]=p[i];
	}
	// top--;
	// for(rg i=1;i<=top-1;i++)	
	// 	ans+=~(st[i+1]-st[i]);
	top--;
	return ans;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("hull.in","r",stdin);
	freopen("hull.out","w",stdout);
	#endif
	scanf("%d",&n);
	for(rg i=1;i<=n;i++)
		scanf("%lf%lf",&p[i].x,&p[i].y);
	solve();
	// for(rg i=1;i<=top;i++)
	// 	printf("i:%d x:%lf y:%lf\n",i,st[i].x,st[i].y);
	db ans=0;
	for(rg i=1;i<=top;i++)
		ans+=~(st[i%top+1]-st[i]);
	printf("%.2lf",ans);
	return 0;
}