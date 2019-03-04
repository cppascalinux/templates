#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,r;
char p[10010][60];
char s[1000010];
int t1[1000010],t2[1000010],sa[1000010],c[30],rank[1000010],k[1000010];
void build()
{
	int *x=t1,*y=t2;
	m=26;
	n=strlen(s);
	for(int i=n;i>=1;i--)
			s[i]=s[i-1]-'a'+1;
	memset(c,0,sizeof(c));
	for(int i=1;i<=n;i++)
			c[x[i]=s[i]]++;
	for(int i=1;i<=m;i++)
			c[i]+=c[i-1];
	for(int i=n;i>=1;i--)
		sa[c[x[i]]--]=i;
	for(int k=1;k<=n;k<<=1)
	{
		int p=0;
		for(int i=n-k+1;i<=n;i++)
			y[++p]=i;
		for(int i=1;i<=n;i++)
			if(sa[i]>=k+1)
				y[++p]=sa[i]-k;
		memset(c,0,sizeof(c));
		for(int i=1;i<=n;i++)
			c[x[y[i]]]++;
		for(int i=1;i<=m;i++)
			c[i]+=c[i-1];
		for(int i=n;i>=1;i--)
			sa[c[x[y[i]]]--]=y[i];
		swap(x,y);
		p=0;
		for(int i=1;i<=n;i++)
			x[sa[i]]=y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]?p:++p;
		if(p>=n)
			break;
		m=p;
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("sa.in","r",stdin);
	freopen("sa.out","w",stdout);
	#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&r);
		for(int i=1;i<=r;i++)
			scanf("%s",p[i]);
		scanf("%s",s);
		build();
		for(int i=1;i<=r;i++)
			match(p[i]);
		printf("%d\n",ans);
		clr();
	}
	return 0;
}