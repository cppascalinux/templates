//2020.08.01
//luoguP6139 【模板】广义后缀自动机（广义 SAM） 广义sam模板题
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define LL long long
using namespace std;
int n,tot=1;
char ts[1000009];
int nxt[2000009][27];
int len[2000009],lnk[2000009];
void ins(char *s)
{
	int m=strlen(s+1),cur=1;
	for(int i=1;i<=m;i++)
	{
		int c=s[i]-'a'+1;
		// printf("c:%d\n",c);
		if(!nxt[cur][c])
			nxt[cur][c]=++tot;
		cur=nxt[cur][c];
	}
}
void add(int lst,int c)
{
	int cur=nxt[lst][c],p;
	len[cur]=len[lst]+1;
	for(p=lnk[lst];p&&!nxt[p][c];p=lnk[p])
		nxt[p][c]=cur;
	if(!p)
		return lnk[cur]=1,void();
	int q=nxt[p][c];
	if(len[q]==len[p]+1)
		return lnk[cur]=q,void();
	cerr<<1;
	int cln=++tot;
	len[cln]=len[p]+1,lnk[cln]=lnk[q];
	for(int i=1;i<=26;i++)
		if(len[nxt[q][i]])
			nxt[cln][i]=nxt[q][i];
	for(;p&&nxt[p][c]==q;p=lnk[p])
		nxt[p][c]=cln;
	lnk[q]=lnk[cur]=cln;
}
void build()
{
	queue<int> q;
	q.push(1);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		// printf("x:%d\n",x);
		for(int i=1;i<=26;i++)
			if(nxt[x][i])
				add(x,i),q.push(nxt[x][i]);
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("sam.in","r",stdin);
	freopen("sam.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",ts+1);
		ins(ts);
	}
	build();
	LL ans=0;
	// for(int i=1;i<=tot;i++)
	// 	printf("i:%d lnk:%d len:%d\n",i,lnk[i],len[i]);
	for(int i=2;i<=tot;i++)
		ans+=len[i]-len[lnk[i]];
	printf("%lld",ans);
	return 0;
}