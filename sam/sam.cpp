#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define rg register int
using namespace std;
int n,m,tot,last,sum;
char s[1000010];
int len[2000010],link[2000010],cnt[2000010],a[2000010][30];
int head[2000010],next[2000010],edge[2000010];
void add(int x)
{
	int cur=++tot;
	len[cur]=len[last]+1;
	cnt[cur]=1;
	int p;
	for(p=last;~p&&!a[p][x];p=link[p])
		a[p][x]=cur;
	if(~p)
	{
		int q=a[p][x];
		if(len[p]+1==len[q])
			link[cur]=q;
		else
		{
			int c=++tot;
			len[c]=len[p]+1;
			link[c]=link[q];
			memcpy(a[c],a[q],sizeof(a[c]));
			for(;~p&&a[p][x]==q;p=link[p])
				a[p][x]=c;
			link[q]=link[cur]=c;
		}
	}
	last=cur;
}
void ins(int a,int b)
{
	edge[++sum]=b;
	next[sum]=head[a];
	head[a]=sum;
}
void dfs(int x)
{
	for(int i=head[x];i;i=next[i])
	{
		dfs(edge[i]);
		cnt[x]+=cnt[edge[i]];
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("sam.in","r",stdin);
	freopen("sam.out","w",stdout);
	#endif
	fread(s,1,1000000,stdin);
	n=strlen(s);
	for(rg i=n;i>=1;i--)
		s[i]=s[i-1]-'a'+1;
	link[0]=-1;
	for(rg i=1;i<=n;i++)
		add(s[i]);
	for(rg i=1;i<=tot;i++)
		ins(link[i],i);
	dfs(0);
	ll ans=0;
	for(rg i=1;i<=tot;i++)
		if(cnt[i]>1)
			ans=max(ans,(ll)len[i]*cnt[i]);
	printf("%lld",ans);
	return 0;
}