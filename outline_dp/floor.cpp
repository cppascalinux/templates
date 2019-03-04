#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#define mod 20110520
#define rg register int
using namespace std;
int n,m;
char s[110][110];
int mat[110][110];
int mul[20];
int f[177150],f1[177150];
void init()
{
	mul[0]=1;
	for(rg i=1;i<=12;i++)
		mul[i]=mul[i-1]*3;
}
void solve()
{
	f[0]=1;
	for(rg i=1;i<=n;i++)
	{
		for(rg j=1;j<=m;j++)
		{
			memset(f1,0,sizeof(f1));
			if(!mat[i][j])
				for(rg k=0;k<=mul[m+1]-1;k++)
				{
					int m=mul[j-1];
					int t=(k/m)%mul[2];
					int p=k-t*m;
					if(t==0)
						f1[k]=f[p+4*m]+f[p+2*m]+f[p+6*m];
					else if(t==1)
						f1[k]=f[p]+f[p+3*m];
					else if(t==2)
						f1[k]=f[p+m]+f[p+6*m];
					else if(t==3)
						f1[k]=f[p]+f[p+m];
					else if(t==6)
						f1[k]=f[p+2*m]+f[p+3*m];
					else if(t==8)
						f1[k]=f[p];
					while(f1[k]>=mod)
						f1[k]-=mod;
				}
			else
				for(rg k=0;k<=mul[m+1]-1;k++)
				{
					int t=(k/mul[j-1])%mul[2];
					if(t==0)
						f1[k]=f[k];
				}
			memcpy(f,f1,sizeof(f));
//			for(rg k=0;k<=mul[m+1]-1;k++)
//				printf("k:%d fk:%d\n",k,f[k]);
		}
		memset(f1,0,sizeof(f1));
		for(rg k=0;k<=mul[m]-1;k++)
			f1[k*3]=f[k];
		memcpy(f,f1,sizeof(f));
	}

}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("floor.in","r",stdin);
	freopen("floor.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	for(rg i=1;i<=n;i++)
		scanf("%s",s[i]);
	if(n<m)
	{
		for(rg i=1;i<=n;i++)
			for(rg j=1;j<=m;j++)
				if(s[i][j-1]=='*')
					mat[j][i]=1;
		swap(n,m);
	}
	else
		for(rg i=1;i<=n;i++)
			for(rg j=1;j<=m;j++)
				if(s[i][j-1]=='*')
					mat[i][j]=1;
	init();
	solve();
	printf("%d",f[0]);
	return 0;
}