//luogu3375 【模板】KMP字符串匹配 拓展kmp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,cnt;
char s[1000009],t[1000009];
int f[1000009],g[1000009];
int tmp[1000009],nxt[1000009];
void init()
{
	t[m+1]=127;
	int mx=0,id=1;
	for(int i=2;i<=m;i++)
	{
		int &p=f[i];
		p=min(max(0,mx-i+1),f[i-id+1]);
		// printf("i:%d p:%d mx:%d id:%d\n",i,p,mx,id);
		while(t[p+1]==t[i+p])
			p++;
		if(i+p-1>mx)
		{
			mx=i+p-1;
			id=i;
		}
	}
	// f[1]=m;
	// for(int i=1;i<=m;i++)
	// 	printf("i:%d f:%d\n",i,f[i]);
}
void solve()
{
	int mx=0,id=1;
	for(int i=1;i<=n;i++)
	{
		int &p=g[i];
		p=min(max(0,mx-i+1),f[i-id+1]);
		while(t[p+1]==s[i+p])
			p++;
		if(i+p-1>mx)
		{
			mx=i+p-1;
			id=i;
		}
	}
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d g:%d\n",i,g[i]);
}
void output()
{
	for(int i=1;i<=n;i++)
		if(g[i]==m)
			printf("%d\n",i);
	memset(tmp,0x7F,sizeof(tmp));
	for(int i=1;i<=m;i++)
		if(f[i])
			tmp[i+f[i]-1]=min(tmp[i+f[i]-1],i);
	for(int i=m;i>=1;i--)
		tmp[i]=min(tmp[i],tmp[i+1]);
	for(int i=1;i<=m;i++)
		nxt[i]=max(0,i-tmp[i]+1);
	for(int i=1;i<=m;i++)
		printf("%d ",nxt[i]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("kmp.in","r",stdin);
	freopen("kmp.out","w",stdout);
#endif
	scanf("%s%s",s+1,t+1);
	n=strlen(s+1);
	m=strlen(t+1);
	init();
	solve();
	output();
	return 0;
}