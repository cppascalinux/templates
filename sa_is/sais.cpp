//2020.07.27
//luoguP3809 【模板】后缀排序 sa-is后缀数组诱导排序构造..大概就是把所有后缀按照和下一个后缀的大小关系分成L和S两部分
//然后就有若干段连续的S和L..把每一段S的第一个位置称作LMS位置,然后如果知道了所有LMS后缀的排名,就可以通过诱导排序求出
//所有后缀的排名...然后可以对所有LMS子串进行排名,并按排名得到新的字符串,对新得到的字符串递归进行后缀排序
//LMS子串的排名也可以通过诱导排序得到...定义LMS前缀为一个位置向右延伸到第一个LMS位置形成的子串,考虑对LMS子串进行诱导排序
//首先把所有LMS位置的LMS前缀放进桶里,然后从前往后扫得到所有L位置的排名,再从后往前扫得到所有S位置的排名
//最后再顺着扫一遍得到所有位置的真正排名..两个LMS子串相等当且仅当所有字符都相等且对应位置的后缀类型相等
//这样不难证明不会出现一个LMS子串是另一个的前缀的情况..然后两个LMS子串要么完全相等，要么可以直接比较大小
//LMS子串的排名就是LMS前缀的排名..所以递归进行后缀排序得到LMS后缀排名的方法是正确的
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define VI vector<int>
#define PB push_back
#define LMS(x) (typ[x]&&!typ[x-1])
using namespace std;
int buc[1000009][2],tp[1000009];
char s0[1000009];
int cmp(VI &s,VI &typ,int x,int y)
{
	int tme=0;
	for(;tme<2;x++,y++)
	{
		if(s[x]!=s[y]||typ[x]!=typ[y])
			return 1;
		if(LMS(x)||LMS(y))
			tme++;
	}
	return 0;
}
void getsa(int n,int m,VI &s,VI &sa)
{
	VI typ(n+2),rnk(n+2),ord(1);
	int nxn=0;
	for(int i=n-1;i>=1;i--)
		typ[i]=s[i]==s[i+1]?typ[i+1]:(s[i]<s[i+1]);
	typ[0]=typ[n+1]=1;
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d typ:%d\n",i,typ[i]);

	for(int i=1;i<=m;i++)
		buc[i][0]=buc[i][1]=0;
	int bk=0;
	for(int i=1;i<=n;i++)
		if(++buc[s[i]][typ[i]]>1)
			bk=1;
	for(int i=1;i<=m;i++)
		buc[i][0]+=buc[i-1][1],buc[i][1]+=buc[i][0];
	if(!bk)
	{
		for(int i=1;i<=n;i++)
			sa[buc[s[i]][typ[i]]]=i;
		return;
	}
	for(int i=1;i<=m;i++)
		tp[i]=buc[i][0];
	for(int i=1;i<=n;i++)
		if(LMS(i))
			sa[++tp[s[i]]]=i,ord.PB(i),nxn++;
	for(int i=1;i<=m;i++)
		tp[i]=buc[i-1][1];

	sa[0]=n+1;
	for(int i=0;i<=n;i++)
	{
		if(sa[i]&&typ[sa[i]-1]==0)
			sa[++tp[s[sa[i]-1]]]=sa[i]-1;
		// printf("i:%d s:%c sa:%d typ:%d tp:%d\n",i,s[sa[i]-1],sa[i],typ[i],tp[s[sa[i]-1]]);
	}
	// for(int i=0;i<=n;i++)
	// 	printf("i:%d sa:%d\n",i,sa[i]);
	for(int i=1;i<=m;i++)
		tp[i]=buc[i][1];
	for(int i=n;i>=1;i--)
		if(sa[i]&&typ[sa[i]-1]==1)
			sa[tp[s[sa[i]-1]]--]=sa[i]-1;

	int lst=0,nxm=0;
	for(int i=1;i<=n;i++)
		if(LMS(sa[i]))
		{
			int pos=sa[i];
			if(!lst||(lst&&cmp(s,typ,pos,lst)))
				nxm++;
			rnk[pos]=nxm;
			lst=pos;
		}
	if(!lst)
		return;
	// printf("nxn:%d nxm:%d\n",nxn,nxm);
	// for(int i=1;i<=nxn;i++)
	// 	printf("i:%d ord:%d rnk:%d\n",i,ord[i],rnk[ord[i]]);
	VI nxs(1),nxsa(nxn+2);
	for(int i=1;i<=nxn;i++)
		nxs.PB(rnk[ord[i]]);
	nxs.PB(0);
	getsa(nxn,nxm,nxs,nxsa);
	// for(int i=1;i<=nxn;i++)
	// 	printf("i:%d nxsa:%d\n",i,nxsa[i]);
	for(int i=1;i<=m;i++)
		buc[i][0]=buc[i][1]=0;
	for(int i=1;i<=n;i++)
		buc[s[i]][typ[i]]++;
	for(int i=1;i<=m;i++)
		buc[i][0]+=buc[i-1][1],buc[i][1]+=buc[i][0];
	for(int i=1;i<=m;i++)
		tp[i]=buc[i][0];
	for(int i=1;i<=n;i++)
		sa[i]=0;
	for(int i=1;i<=nxn;i++)
		sa[++tp[s[ord[nxsa[i]]]]]=ord[nxsa[i]];
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d sa:%d\n",i,sa[i]);
	for(int i=1;i<=m;i++)
		tp[i]=buc[i-1][1];

	sa[0]=n+1;
	for(int i=0;i<=n;i++)
		if(sa[i]&&typ[sa[i]-1]==0)
			sa[++tp[s[sa[i]-1]]]=sa[i]-1;
	for(int i=1;i<=m;i++)
		tp[i]=buc[i][1];
	for(int i=n;i>=1;i--)
		if(sa[i]&&typ[sa[i]-1]==1)
			sa[tp[s[sa[i]-1]]--]=sa[i]-1;
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("sais.in","r",stdin);
	freopen("sais.out","w",stdout);
#endif
	scanf("%s",s0+1);
	int n=strlen(s0+1);
	VI s(n+2),sa(n+2);
	for(int i=1;i<=n;i++)
		s[i]=s0[i];
	getsa(n,127,s,sa);
	for(int i=1;i<=n;i++)
		printf("%d ",sa[i]);
	return 0;
}