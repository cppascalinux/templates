//2019.02.18
//luogu2742 凸包 graham扫描法
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define db double
#define eps 1e-8
using namespace std;
int sgn(db x)
{
	return x>eps?1:(x<-eps?-1:0);
}
struct pt
{
	db x,y;
	pt(){}
	pt(db a,db b){x=a,y=b;}
	bool operator <(const pt &p) const{return sgn(x-p.x)<0||(sgn(x-p.x)==0&&sgn(y-p.y)<0);}
	pt operator +(pt p){return pt(x+p.x,y+p.y);}
	pt operator -(pt p){return pt(x-p.x,y-p.y);}
	db operator *(pt p){return x*p.x+y*p.y;}
	db operator ^(pt p){return x*p.y-y*p.x;}
	int geta() {return sgn(x)==1?(sgn(y)==1?2:1):(sgn(y)==1?3:4);}
	db getl() {return sqrt(x*x+y*y);}
};
int n;
pt p[10009],td,st[10009];
bool cmp(pt a,pt b)
{
	a=a-td,b=b-td;
	// if(a.geta()!=b.geta())
	// 	return a.geta()<b.geta();
	// return sgn(a^b)>0;
	return sgn(a^b)!=0?sgn(a^b)>0:a<b;
}
db cross(pt o,pt a,pt b)
{
	return (a-o)^(b-o);
}
void solve()
{
	for(int i=2;i<=n;i++)
		if(p[i]<p[1])
			swap(p[i],p[1]);
	td=p[1];
	sort(p+2,p+n+1,cmp);
	for(int i=1;i<=n;i++)
		printf("i:%d px:%lf py:%lf\n",i,p[i].x,p[i].y);
	int top=0;
	for(int i=1;i<=n;i++)
	{
		while(top>1&&sgn(cross(st[top],st[top-1],p[i]))>=0)
			top--;
		st[++top]=p[i];
	}
	for(int i=1;i<=top;i++)
		printf("i:%d x:%lf y:%lf\n",i,st[i].x,st[i].y);
	st[top+1]=p[1];
	db ans=0;
	for(int i=1;i<=top;i++)
		ans+=(st[i+1]-st[i]).getl();
	printf("%.2lf",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("hull.in","r",stdin);
	freopen("graham.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf",&p[i].x,&p[i].y);
	solve();
	return 0;
}