//2018.11.28
//poj1279 Art Gallery 半平面交求多边形的核
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define rg register int
#define db double
#define eps 1e-8
using namespace std;
int n,ft,bk,inv;
int sgn(db x)
{
	return x>eps?1:(x<-eps?-1:0);
}
struct point
{
	db x,y;
	point(){}
	point(db a,db b){x=a,y=b;}
	point operator +(point p){return point(x+p.x,y+p.y);}
	point operator -(point p){return point(x-p.x,y-p.y);}
	point operator *(db v){return point(x*v,y*v);}
	point operator /(db v){return point(x/v,y/v);}
	db operator *(point p){return x*p.x+y*p.y;}
	db operator ^(point p){return x*p.y-y*p.x;}
	db geta(){return atan2(y,x);}
}ans[1509];
db cross(point o,point a,point b)
{
	return (a-o)^(b-o);
}
db dot(point o,point a,point b)
{
	return (a-o)*(b-o);
}
struct line
{
	point p,q;
	point operator ^(line l)
	{
		db h1=cross(p,l.p,q),h2=-cross(p,l.q,q);
		return (l.p*h2+l.q*h1)/(h1+h2);
	}
	int inc(point v){return inv^(sgn(cross(v,p,q))>0);}
	bool operator ==(line l){return sgn((q-p)^(l.q-l.p))==0&&sgn((q-p)*(l.q-l.p))>0;}
	// bool operator <(const line &l) const
	// {
	// 	if((*this==l))
	// 		return l.inc(this->p);
	// 	return (q-p).geta()<(l.q-l.p).geta();
	// }
}l[1509],q[1509];
bool operator <(line a,line b)
{
	if(a==b)
		return b.inc(a.p);
	return (b.q-b.p).geta()>(a.q-a.p).geta();
}
int check(line a,line b,line c)
{
	return c.inc(a^b);
}
void solve()
{
	ft=1;
	bk=0;
	sort(l+1,l+n+1);
	// for(rg i=1;i<=n;i++)
	// 	printf("i:%d px:%lf py:%lf qx:%lf qy:%lf\n",i,l[i].p.x,l[i].p.y,l[i].q.x,l[i].q.y);
	for(rg i=1;i<=n;i++)
	{
		if(i>1&&l[i]==l[i-1])
			continue;
		while(bk>=ft+1&&!check(q[bk-1],q[bk],l[i]))
			bk--;
		while(bk>=ft+1&&!check(q[ft+1],q[ft],l[i]))
			ft++;
		q[++bk]=l[i];
	}
	while(bk>=ft+1&&!check(q[bk-1],q[bk],q[ft]))
		bk--;
	while(bk>=ft+1&&!check(q[ft+1],q[ft],q[bk]))
		ft++;
	for(rg i=ft;i<=bk;i++)
		printf("i:%d px:%lf py:%lf qx:%lf qy:%lf\n",i,q[i].p.x,q[i].p.y,q[i].q.x,q[i].q.y);
	// for(rg i=ft;i<=bk;i++)
	// 	printf("i:%d px:%lf py:%lf qx:%lf qy:%lf\n",i,q[i].p.x,q[i].p.y,q[i].q.x,q[i].q.y);
}
void init()
{
	db sum=0;
	for(rg i=1;i<=n;i++)
		sum+=l[i].p^l[i%n+1].p;
	if(sgn(sum)<0)
		inv=1;
	else
		inv=0;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("plain.in","r",stdin);
	freopen("plain.out","w",stdout);
	#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(rg i=1;i<=n;i++)
			scanf("%lf%lf",&l[i].p.x,&l[i].p.y);
		for(rg i=1;i<=n;i++)
			l[i].q=l[i%n+1].p;
		init();
		// printf("inv:%d\n",inv);
		// for(rg i=1;i<=n;i++)
		// 	printf("i:%d x:%lf y:%lf\n",i,(l[i]^l[i%n+1]).x,(l[i]^l[i%n+1]).y);
		solve();
		if(bk<=ft+1)
			printf("0.00\n");
		else
		{
			db sum=0;
			q[bk+1]=q[ft];
			for(rg i=ft;i<=bk;i++)
				ans[i-ft+1]=q[i]^q[i+1];
			int m=bk-ft+1;
			for(rg i=1;i<=m;i++)
				sum+=ans[i]^ans[i%m+1];
			printf("%.2f\n",fabs(sum)/2+eps);
		}
	}
	// printf("%lf",atan2(-0.5,-0.5));
	return 0;
}