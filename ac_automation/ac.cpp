#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,tot,ans;
char m[110],s[1000010];
int last[500010],f[500010],vist[500010];
int a[500010][30];
int q[500010],l,r=-1;
void add()
{
	int len=strlen(m),now=0;
	for(int i=len;i>=1;i--)
		m[i]=m[i-1]-'a'+1;
	for(int i=1;i<=len;i++)
	{
		if(!a[now][m[i]])
			a[now][m[i]]=++tot;
		now=a[now][m[i]];
	}
	last[now]++;
}
void get()
{
	int x;
	q[++r]=0;
	while(l<=r)
	{
		x=q[l++];
		for(int i=1;i<=26;i++)
			if(a[x][i])
			{
				int j=f[x];
				while(j&&!a[j][i])
					j=f[j];
				if(x)
					f[a[x][i]]=a[j][i];
				q[++r]=a[x][i];
			}
	}
}
void solve()
{
	int len=strlen(s),j=0;
	for(int i=len;i>=1;i--)
		s[i]=s[i-1]-'a'+1;
	for(int i=1;i<=len;i++)
	{
		while(j&&!a[j][s[i]])
			j=f[j];
		j=a[j][s[i]];
		for(int k=j;k&&!vist[k];k=f[k])
		{
			ans+=last[k];
			last[k]=0;
			vist[k]=1;
		}
	}
}
void clr()
{
	memset(a,0,sizeof(a));
	memset(last,0,sizeof(last));
	memset(f,0,sizeof(f));
	memset(vist,0,sizeof(vist));
	tot=ans=0;
	l=0;
	r=-1;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("ac.in","r",stdin);
	freopen("ac.out","w",stdout);
#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%s",m);
			add();
		}
		scanf("%s",s);
		get();
	//	for(int i=1;i<=tot;i++)
	//		printf("i:%d f:%d\n",i,f[i]);
		solve();
		printf("%d\n",ans);
		clr();
	}
	return 0;
}