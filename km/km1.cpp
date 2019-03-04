//2018.01.19
//二分图最大权匹配 km算法 o(n^3)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define chk(a,b) (a>b?a=b,1:0)
#define inf 0x7F7F7F7F
#define ll long long
using namespace std;
char *p1,*p2,buffer[10000009];
int n;
int w[409][409];
int lx[409],ly[409],vy[409],pre[409],mat[409],slk[409];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void km()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			lx[i]=max(lx[i],w[i][j]);
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d slk:%d\n",i,lx[i]);
	for(int i=1;i<=n;i++)
	{
		memset(vy,0,(n+1)<<2);
		memset(slk,0x7F,(n+1)<<2);
		int p=0,np;
		for(mat[p]=i;mat[p];p=np)
		{
			// printf("p:%d\n",p);
			// fflush(stdout);
			vy[p]=1;
			int d=inf,x=mat[p];
			for(int j=1;j<=n;j++)
				if(!vy[j])
				{
					if(chk(slk[j],lx[x]+ly[j]-w[x][j]))
						pre[j]=p;
					if(chk(d,slk[j]))
						np=j;
				}
			for(int j=0;j<=n;j++)
				if(vy[j])
				{
					ly[j]+=d;
					lx[mat[j]]-=d;
				}
				else
					slk[j]-=d;
		}
		for(int j=p;j;j=pre[j])
			mat[j]=mat[pre[j]];
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("km.in","r",stdin);
	freopen("km1.out","w",stdout);
#endif
	int n1,n2,m;
	rd(n1),rd(n2),rd(m);
	n=max(n1,n2);
	for(int i=1,a,b,c;i<=m;i++)
	{
		rd(a),rd(b),rd(c);
		w[b][a]=c;
	}
	km();
	ll ans=0;
	for(int i=1;i<=n;i++)
		ans+=lx[i]+ly[i];
	printf("%lld\n",ans);
	for(int i=1;i<=n1;i++)
		if(w[mat[i]][i])
			printf("%d ",mat[i]);
		else
			printf("0 ");
	return 0;
}