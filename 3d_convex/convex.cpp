//2019.04.13
//luoguP4724 【模板】三维凸包
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
	return x<-eps?-1:(x>eps?1:0);
}
struct pt
{
	db x,y,z;
	pt(){}
	pt(db a,db b,db c){x=a,y=b,z=c;}
	pt operator +(pt p){return pt(x+p.x,y+p.y,z+p.z);}
	pt operator -(pt p){return pt(x-p.x,y-p.y,z-p.z);}
	pt operator *(db v){return pt(x*v,y*v,z*v);}
	pt operator /(db v){return pt(x/v,y/v,z/v);}
	db operator *(pt p){return x*p.x+y*p.y+z*p.z;}
	pt operator ^(pt p){return pt(y*p.z-p.y*z,z*p.x-p.z*x,x*p.y-p.x*y);}
	db getl(){return sqrt(x*x+y*y+z*z);}
};
struct fc
{
	int v[3];
	fc(){}
	fc(int a,int b,int c){v[0]=a,v[1]=b,v[2]=c;}
};
int n,tot;
int e[2009][2009];
pt p[2009];
fc f[4009],tmp[4009];
pt cross(pt o,pt a,pt b)
{
	return (a-o)^(b-o);
}
db crossl(pt o,pt a,pt b)
{
	return ((a-o)^(b-o)).getl();
}
db dot(pt o,pt a,pt b)
{
	return (a-o)*(b-o);
}
int in(fc f,pt q)
{
	pt t=cross(p[f.v[0]],p[f.v[1]],p[f.v[2]]);
	return sgn(t*(q-p[f.v[0]]))<0;
}
void solve()
{
	f[++tot]=fc(1,2,3);
	f[++tot]=fc(1,3,2);
	for(int i=4;i<=n;i++)
	{
		int ntot=0;
		for(int j=1;j<=tot;j++)
		{
			int t=in(f[j],p[i]);
			if(t)
				tmp[++ntot]=f[j];
			for(int k=0;k<=2;k++)
			{
				int a=f[j].v[k],b=f[j].v[(k+1)%3];
				e[a][b]=t;
			}
		}
		for(int j=1;j<=tot;j++)
			for(int k=0;k<=2;k++)
			{
				int a=f[j].v[k],b=f[j].v[(k+1)%3];
				if(e[a][b]&&!e[b][a])
					tmp[++ntot]=fc(i,b,a);
			}
		for(int j=1;j<=ntot;j++)
			f[j]=tmp[j];
		tot=ntot;
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("convex.in","r",stdin);
	freopen("convex.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf%lf",&p[i].x,&p[i].y,&p[i].z);
	solve();
	db ans=0;
	// printf("tot:%d\n",tot);
	for(int i=1;i<=tot;i++)
		ans+=crossl(p[f[i].v[0]],p[f[i].v[1]],p[f[i].v[2]])/2;
	printf("%.3lf",ans);
	return 0;
}