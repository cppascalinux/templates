//2020.07.19
//luoguP5854 【模板】笛卡尔树 第一感觉是rmq递归建树...但那样是O(nlogn)的显然无法通过..
//不难证明一个点的父亲一定是他左侧/右侧第一个比他小的数..更确切的,一定是这两个数中较小的
//同时不难证明这样构造一个点至多有两个儿子..证明构造合法
//整个过程完全是使用反证法..还是不清楚为什么这么构造是对的...只知道不这样构造一定是错的
//这样就可以用单调增的栈去找左\右第一个小于他的元素..就搞定了O(n)
//标算更nb...直接用单调栈维护最右侧的一条链..每次在最右侧插入一个点就不断退栈直到满足堆的性质..然后把退出来的子树接到新点的左儿子上就行..O(n)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long
#define GC() (p1==p2&&(p2=(p1=buf1)+fread(buf1,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buf1[10000009];
int n;
int p[10000009];
int lm[10000009],rm[10000009],st[10000009];
void rd(int &x)
{
	char c=0;
	x=0;
	while(c<'0'||c>'9')
		c=GC();
	while(c>='0'&&c<='9')
		x=x*10+(c&15),c=GC();
}
void init()
{
	int tp=0;
	for(int i=n;i>=1;i--)
	{
		while(tp&&p[i]<p[st[tp]])
			lm[st[tp--]]=i;
		st[++tp]=i;
	}
	tp=0;
	for(int i=1;i<=n;i++)
	{
		while(tp&&p[i]<p[st[tp]])
			rm[st[tp--]]=i;
		st[++tp]=i;
	}
}
void solve()
{
	LL ansl=0,ansr=0;
	for(int i=1;i<=n;i++)
		ansl^=i,ansr^=i;
	for(int i=1;i<=n;i++)
	{
		int tl=lm[i],tr=rm[i];
		if(tl&&tr)
		{
			if(p[tl]>p[tr])
				ansr^=tl^((LL)tl*(i+1));
			else
				ansl^=tr^((LL)tr*(i+1));
		}
		else if(tl)
			ansr^=tl^((LL)tl*(i+1));
		else
			ansl^=tr^((LL)tr*(i+1));
	}
	printf("%lld %lld",ansl,ansr);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	rd(n);
	for(int i=1;i<=n;i++)
		rd(p[i]);
	init();
	solve();
	return 0;
}