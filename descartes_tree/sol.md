# 一个和其他题解都不一样的~~乱搞~~做法
首先我们考虑直接按照笛卡尔树的定义去递归建树,那么就需要算$RMQ$,这样做是$O(nlogn)$的,显然会超时..  
直接去找每个点的左右儿子貌似很困难,于是就考虑去找每个点的父亲  
然后我画了几个例子..貌似找到了规律

## 结论1
**考虑节点$x$,令$a$表示满足$a<x$且$p_a<p_x$的最大的$a$(即$x$左侧第一个小于它的位置),令$b$表示满足$b>x$且$p_b<p_x$的最小$b$(即$x$右侧第一个小于它的位置),那么$x$在笛卡尔树上的的父亲$fa$一定是a或者b**

***证明***:反证法,若$fa$在$x$左侧且不是$a$,那么一定有$p_{fa}<p_x$,故$fa<a$(因为$(a,x)$中的元素权值都大于$p_x$),又因为要满足二叉搜索树的性质,故$a$一定在$x$的左子树上,这与小根堆的性质矛盾,所以若$fa$位于$x$左侧,一定有$fa=a$  
同理如果$fa$位于$x$右侧,一定有$fa=b$,得证

## 结论2
**进一步地,$fa$一定是$a$,$b$中权值较大的一个**

***证明***:反证法,不妨假设$p_a<p_b$,且$fa=a$,那么从$a$向祖先走,若从右儿子走向父亲,就记作***向左走***,否则记作***向右走***  
将第一次向右走时,走到的点记作$c$,那么根据中序遍历的原理,$c$一定是$x$的子树之后的第一个元素,且根据堆的性质有$p_c<p_x$,$x$的子树中的点权值都大于等于$x$,所以$c$就是$x$右侧第一个小于他的位置,也就是$c=b$  
所以有$p_a<p_b$,且b为a的祖先,这与小根堆的性质矛盾,故$fa\ne a$,结合结论1得知$fa=b$  
当$p_a>p_b$时,同理可得$fa=a$

## 做法
推出这个结论之后,就可以用单调栈去找出每个点左侧,右侧第一个权值小于它的位置,然后找出它的父亲,再判断它是左/右儿子就行,时间复杂度$O(n)$...有点卡常

## 代码:
```
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
void rd(int &x)//快速读入
{
	char c=0;
	x=0;
	while(c<'0'||c>'9')
		c=GC();
	while(c>='0'&&c<='9')
		x=x*10+(c&15),c=GC();
}
void init()//得到每个点左/右第一个小于它的位置
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
void solve()//计算每个点的父亲,判断左,右儿子,注意空儿子的情况
{
	LL ansl=0,ansr=0;
	for(int i=1;i<=n;i++)
		ansl^=i,ansr^=i;//先异或上所有空儿子的
	for(int i=1;i<=n;i++)
	{
		int tl=lm[i],tr=rm[i];
		if(tl&&tr)//左/右均有小于它的位置
		{
			if(p[tl]>p[tr])
				ansr^=tl^((LL)tl*(i+1));//再次异或,抵消空儿子的异或值
			else
				ansl^=tr^((LL)tr*(i+1));
		}
		else if(tl)//只有左侧有
			ansr^=tl^((LL)tl*(i+1));
		else//只有右侧有
			ansl^=tr^((LL)tr*(i+1));
	}
	printf("%lld %lld",ansl,ansr);
}
int main()
{
	rd(n);
	for(int i=1;i<=n;i++)
		rd(p[i]);
	init();
	solve();
	return 0;
}
```