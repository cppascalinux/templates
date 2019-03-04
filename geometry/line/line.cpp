//2018.11.23
//poj1269 Intersecting Lines
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define db double
#define rg register int
#define eps 1e-8
using namespace std;
int n;
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
	point operator /(db v){return point(x/v,y/v);}
	db operator *(point p){return x*p.x+y*p.y;}
	db operator ^(point p){return x*p.y-y*p.x;}
	int operator ==(point p){return sgn(x-p.x)==0&&sgn(y-p.y)==0;}
};
db cross(point o,point a,point b)
{
	return (a-o)^(b-o);
}
point getp(point p1,point q1,point p2,point q2)
{
	db h1=cross(p2,q2,p1),h2=-cross(p2,q2,q1);
	return (p1*h2+q1*h1)/(h1+h2);
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("line.in","r",stdin);
	freopen("line.out","w",stdout);
	#endif
	printf("INTERSECTING LINES OUTPUT\n");
	scanf("%d",&n);
	point p1,q1,p2,q2;
	for(rg i=1;i<=n;i++)
	{
		scanf("%Lf%Lf%Lf%Lf%Lf%Lf%Lf%Lf",&p1.x,&p1.y,&q1.x,&q1.y,&p2.x,&p2.y,&q2.x,&q2.y);
		if(sgn((q1-p1)^(q2-p2))==0)
		{
			if(sgn(cross(p1,p2,q2))==0)
			{
				printf("LINE\n");
				continue;
			}
			printf("NONE\n");
			continue;
		}
		point p=getp(p1,q1,p2,q2);
		printf("POINT %.2f %.2f\n",p.x,p.y);
	}
	printf("END OF OUTPUT\n");
	return 0;
}