#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
using namespace std;
char s[1000010],p[1000010];
int f[1000010];
int ans[1000010],tot;
int n,m;
void get()
{
	m=strlen(p);
	int j=0;
	for(rg i=m;i>=1;i--)
		p[i]=p[i-1]-'a'+1;
	for(rg i=2;i<=m;i++)
	{
		while(j&&p[i]^p[j+1])
			j=f[j];
		if(p[i]==p[j+1])
			j++;
		f[i]=j;
	}
}
void kmp()
{
	n=strlen(s);
	int j=0;
	for(rg i=n;i>=1;i--)
		s[i]=s[i-1]-'a'+1;
	for(rg i=1;i<=n;i++)
	{
		while(j&&s[i]^p[j+1])
			j=f[j];
		if(s[i]==p[j+1])
			j++;
		if(j==m)
			ans[++tot]=i-m+1;
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("kmp.in","r",stdin);
	freopen("kmp.out","w",stdout);
#endif
	scanf("%s%s",s,p);
	get();
	kmp();
	for(rg i=1;i<=tot;i++)
		printf("%d\n",ans[i]);
	for(rg i=1;i<=m;i++)
		printf("%d ",f[i]);
	return 0;
}