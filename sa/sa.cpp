//2019.04.05
//uoj35 后缀排序
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n;
char s[100009];
int sa[100009],t1[100009],t2[100009],rnk[100009],h[100009],c[100009];
void geth()
{
	for(int i=1;i<=n;i++)
		rnk[sa[i]]=i;
	int p=0;
	for(int i=1;i<=n;i++)
	{
		if(p)
			p--;
		int np=sa[rnk[i]-1];
		while(s[i+p]==s[np+p])
			p++;
		h[rnk[i]]=p;
	}
}
void getsa()
{
	int *x=t1,*y=t2;
	int m=26;
	for(int i=1;i<=n;i++)
		c[x[i]=s[i]]++;
	for(int i=1;i<=m;i++)
		c[i]+=c[i-1];
	for(int i=1;i<=n;i++)
		sa[c[x[i]]--]=i;
	// for(int i=1;i<=n;i++)
	// 	printf("%d ",sa[i]);
	// printf("\n");
	for(int k=1;k<=n;k<<=1)
	{
		int p=0;
		for(int i=n-k+1;i<=n;i++)
			y[++p]=i;
		for(int i=1;i<=n;i++)
			if(sa[i]>=k+1)
				y[++p]=sa[i]-k;
		// for(int i=1;i<=n;i++)
		// 	printf("%d ",y[i]);
		// printf("\n");
		memset(c,0,(m+1)<<2);
		for(int i=1;i<=n;i++)
			c[x[i]]++;
		for(int i=1;i<=m;i++)
			c[i]+=c[i-1];
		for(int i=n;i>=1;i--)
			sa[c[x[y[i]]]--]=y[i];
		p=0;
		for(int i=1;i<=n;i++)
			y[sa[i]]=x[sa[i]]==x[sa[i-1]]&&x[sa[i]+k]==x[sa[i-1]+k]?p:++p;
		swap(x,y);
		m=p;
		if(m>=n)
			break;
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sa.in","r",stdin);
	freopen("sa.out","w",stdout);
#endif
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
		s[i]-='a'-1;
	getsa();
	geth();
	for(int i=1;i<=n;i++)
		printf("%d ",sa[i]);
	printf("\n");
	for(int i=2;i<=n;i++)
		printf("%d ",h[i]);
	return 0;
}