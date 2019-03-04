//2019.01.18
//uoj80 二分图最大权匹配 km算法 o(n^4)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define inf 0x7FFFFFFF
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,del;
int w[409][409];
int lx[409],ly[409],vx[409],vy[409],mat[409];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
int dfs(int x)
{
	if(vx[x])
		return 0;
	vx[x]=1;
	for(int y=1;y<=n;y++)
		if(lx[x]+ly[y]==w[x][y])
		{
			vy[y]=1;
			if(!mat[y]||dfs(mat[y]))
			{
				mat[y]=x;
				return 1;
			}
		}
		else
			del=min(del,lx[x]+ly[y]-w[x][y]);
	return 0;
}
void km()
{
	for(int x=1;x<=n;x++)
		for(int y=1;y<=n;y++)
			lx[x]=max(lx[x],w[x][y]);
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d lx:%d\n",i,lx[i]);
	for(int i=1;i<=n;i++)
		while(1)
		{
			memset(vx,0,(n+1)<<2);
			memset(vy,0,(n+1)<<2);
			del=inf;
			if(dfs(i))
				break;
			for(int j=1;j<=n;j++)
			{
				if(vx[j])
					lx[j]-=del;
				if(vy[j])
					ly[j]+=del;
			}
		}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("km.in","r",stdin);
	freopen("km.out","w",stdout);
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
		ans+=w[mat[i]][i];
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d lx:%d ly:%d\n",i,lx[i],ly[i]);
	printf("%lld\n",ans);
	for(int i=1;i<=n1;i++)
		if(w[mat[i]][i])
			printf("%d ",mat[i]);
		else
			printf("0 ");
	return 0;
}