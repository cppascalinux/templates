//2020.07.20
//luoguP5854 【模板】笛卡尔树 大概就是找出每个点的支配范围,这一定就是它子树的范围(不难证明)
//然后自下而上合并就行
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define GC() (p1==p2&&(p2=(p1=buf1)+fread(buf1,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define LL long long
using namespace std;
char *p1,*p2,buf1[10000009];
int n;
int p[10000009],pos[10000009];
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
	int *tp=st;
	for(int i=1;i<=n;i++)
		lm[i]=1,rm[i]=n;
	for(int i=n;i>=1;i--)
	{
		while(tp!=st&&p[i]<p[*tp])
			lm[*tp--]=i+1;
		*++tp=i;
	}
	tp=st;
	for(int i=1;i<=n;i++)
	{
		while(tp!=st&&p[i]<p[*tp])
			rm[*tp--]=i-1;
		*++tp=i;
	}
}
void solve()
{
	LL ansl=0,ansr=0;
	for(int i=n;i>=1;i--)
	{
		int t=pos[i],tl=lm[t],tr=rm[t];
		int &sl=st[tl],&sr=st[tr];
		st[t]=0;
		ansl^=(LL)t*(sl+1);
		ansr^=(LL)t*(sr+1);
		sl=sr=t;
	}
	printf("%lld %lld\n",ansl,ansr);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("tree.in","r",stdin);
	freopen("tree1.out","w",stdout);
#endif
	rd(n);
	for(int i=1;i<=n;i++)
		rd(p[i]),pos[p[i]]=i;
	init();
	solve();
	return 0;
}