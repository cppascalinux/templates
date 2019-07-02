//2019.07.02
//bzoj2654 luoguP2619 tree 设fx为选x条白边时的最小总权值,不难发现fx是一个下凸函数(一开始全选黑边,然后每次选白边,减少的权值1是递减的),然后直接套用wqs二分即可
//注意有可能存在斜率相等的情况,那么就每次都选尽量多的白边,然后二分的时候要找到"最小的选的白边条数>=need的斜率",然后直接减去斜率*need即可
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct edge
{
	int u,v,w,cl;
	edge(){}
	edge(int a,int b,int c,int d){u=a,v=b,w=c,cl=d;}
	bool operator <(const edge &p) const{return w<p.w||(w==p.w&&cl<p.cl);}
};
int n,m,tgt,sm;
int fn[50009];
edge e[100009];
int fnd(int x)
{
	return x==fn[x]?x:fn[x]=fnd(fn[x]);
}
int check(int x)
{
	for(int i=1;i<=m;i++)
		if(e[i].cl==0)
			e[i].w-=x;
	sort(e+1,e+m+1);
	for(int i=1;i<=n;i++)
		fn[i]=i;
	sm=0;
	int wt=0;
	for(int i=1;i<=m;i++)
	{
		int fu=fnd(e[i].u),fv=fnd(e[i].v);
		if(fu==fv)
			continue;
		fn[fu]=fv;
		sm+=e[i].w;
		wt+=(e[i].cl==0);
	}
	for(int i=1;i<=m;i++)
		if(e[i].cl==0)
			e[i].w+=x;
	// printf("x:%d wt:%d\n",x,wt);
	return wt>=tgt;
}
void solve()
{
	int l=-100,r=100;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(check(mid))
			r=mid;
		else
			l=mid+1;
	}
	check(l);
	printf("%d",sm+l*tgt);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("wqs.in","r",stdin);
	freopen("wqs.out","w",stdout);
#endif	
	scanf("%d%d%d",&n,&m,&tgt);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",&e[i].u,&e[i].v,&e[i].w,&e[i].cl);
		e[i].u++,e[i].v++;
	}
	solve();
	return 0;
}