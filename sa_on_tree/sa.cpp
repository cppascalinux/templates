//2020.07.29
//luoguP5353 树上后缀排序 把后缀排序倍增的过程搬到树上..
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int n,*rnk,tp;
char s[500009];
int f[500009][20];
int dep[500009],dfn[500009];
int sa[500009],p1[500009],p2[500009],buc[500009];
vector<int> e[500009];
void dfs(int x,int fa)
{
	dep[x]=dep[fa]+1;
	f[x][0]=fa;
	dfn[x]=++tp;
	for(int i=1;i<=19;i++)
		f[x][i]=f[f[x][i-1]][i-1];
	for(auto t:e[x])
		dfs(t,x);
}
bool cmp(int a,int b)
{
	if(rnk[a]!=rnk[b])
		return rnk[a]<rnk[b];
	return dfn[a]<dfn[b];
}
void getsa()
{
	int m=127,*x=p1,*y=p2;
	for(int i=1;i<=n;i++) buc[x[i]=s[i]]++;
	for(int i=1;i<=m;i++) buc[i]+=buc[i-1];
	for(int i=n;i>=1;i--) sa[buc[x[i]]--]=i;
	for(int a=0,d=1;d<=n;a++,d<<=1)
	{
		int p=0;
		memset(buc,0,(m+1)*4);
		for(int i=1;i<=n;i++)
			if(dep[i]<=d)
				y[++p]=i;
			else
				buc[x[f[i][a]]]++;
		buc[0]=p;
		for(int i=1;i<=m;i++)
			buc[i]+=buc[i-1];
		for(int i=n;i>=1;i--)
			if(dep[i]>=d+1)
				y[buc[x[f[i][a]]]--]=i;
		memset(buc,0,(m+1)*4);
		for(int i=1;i<=n;i++)
			buc[x[i]]++;
		for(int i=1;i<=m;i++)
			buc[i]+=buc[i-1];
		for(int i=n;i>=1;i--)
			sa[buc[x[y[i]]]--]=y[i];
		p=0;
		swap(x,y);
		for(int i=1;i<=n;i++)
			x[sa[i]]=y[sa[i]]==y[sa[i-1]]&&y[f[sa[i]][a]]==y[f[sa[i-1]][a]]?p:++p;
		rnk=x;
		if((m=p)==n)
			break;
	}
	sort(sa+1,sa+n+1,cmp);
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d sa:%d rnk:%d\n",i,sa[i],rnk[sa[i]]);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("sa.in","r",stdin);
	freopen("sa.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=2,a;i<=n;i++)
	{
		scanf("%d",&a);
		e[a].push_back(i);
	}
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
		sort(e[i].begin(),e[i].end());
	dfs(1,0);
	getsa();
	for(int i=1;i<=n;i++)
		printf("%d ",sa[i]);
	return 0;
}