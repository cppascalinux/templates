//2020.07.29
//luoguP3804 【模板】后缀自动机 (SAM)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define LL long long
using namespace std;
int n,tot=1,lst=1;
LL ans;
char s[1000009];
int nxt[2000009][27];
int sz[2000009],lnk[2000009],len[2000009];
vector<int> e[2000009];
void add(int c)
{
	int cur=++tot,p=lst;
	len[cur]=len[lst]+1,sz[cur]=1,lst=cur;
	for(;p&&!nxt[p][c];p=lnk[p])
		nxt[p][c]=cur;
	if(!p)
		return lnk[cur]=1,void();
	int q=nxt[p][c];
	if(len[q]==len[p]+1)
		return lnk[cur]=q,void();
	int cln=++tot;
	len[cln]=len[p]+1,lnk[cln]=lnk[q];
	memcpy(nxt[cln],nxt[q],27*4);
	for(;p&&nxt[p][c]==q;p=lnk[p])
		nxt[p][c]=cln;
	lnk[cur]=lnk[q]=cln;
}
void dfs(int x)
{
	for(auto t:e[x])
		dfs(t),sz[x]+=sz[t];
	if(sz[x]>1)
		ans=max(ans,(LL)sz[x]*len[x]);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("sam.in","r",stdin);
	freopen("sam.out","w",stdout);
#endif
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
		add(s[i]-'a'+1);
	for(int i=2;i<=tot;i++)
		e[lnk[i]].push_back(i);
	dfs(1);
	printf("%lld",ans);
	return 0;
}