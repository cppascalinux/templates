#include<iostream>
#include<cstdio>
#include<random>
#include<algorithm>
using namespace std;
random_device rnd;
int n=100000,m;
int r=20,c=5000;
int nm[29][5009];
struct edge
{
	int u,v,l;
}e[400009];
void adde(int a,int b,int c)
{
	e[++m]=edge{a,b,c};
}
void shuf()
{
	static int p[100009];
	for(int i=1;i<=n;i++)
		p[i]=i;
	shuffle(p+1,p+n+1,rnd);
	for(int i=1;i<=m;i++)
		e[i].u=p[e[i].u],e[i].v=p[e[i].v];
	shuffle(e+1,e+m+1,rnd);
	printf("%d %d\n",n,m);
	for(int i=1;i<=m;i++)
		printf("%d %d 1 %d\n",e[i].u,e[i].v,e[i].l);
	printf("0");
}
int main()
{
	freopen("slf.in","w",stdout);
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
			nm[i][j]=(i-1)*c+j;
	for(int i=1;i<=r;i++)
		for(int j=2;j<=c;j++)
			adde(nm[i][j-1],nm[i][j],rnd()%10000000+1);
	for(int i=2;i<=r;i++)
		for(int j=1;j<=c;j++)
			adde(nm[i-1][j],nm[i][j],1);
	shuf();
	return 0;
}