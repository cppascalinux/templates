#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#define pre(x) kth(root,rank(root,x)-1)
#define next(x) kth(root,rank(root,x+1))
#define update(x) s[x]=s[ch[x][0]]+s[ch[x][1]]+cnt[x]
using namespace std;
int n,tot,root;
int ch[100010][2],rnd[100010],val[100010],s[100010],cnt[100010];
void rotate(int &p,int k)
{
	int x=ch[p][k];
	ch[p][k]=ch[x][k^1];
	ch[x][k^1]=p;
	update(p);
	update(x);
	p=x;
}
void insert(int &p,int x)
{
	if(!p)
	{
		p=++tot;
		val[p]=x;
		cnt[p]=1;
		rnd[p]=rand();
	}
	else if(val[p]==x)
		cnt[p]++;
	else
	{
		int d=x>val[p];
		insert(ch[p][d],x);
		if(rnd[ch[p][d]]>rnd[p])
			rotate(p,d);
	}
	update(p);
}
void del(int &p,int x)
{
	if(val[p]==x)
	{
		if(cnt[p]>1)
			cnt[p]--;
		else if(!(ch[p][0]&&ch[p][1]))
			p=ch[p][0]|ch[p][1];
		else
		{
		//	cnt[p]=0;
			int d=rnd[ch[p][1]]>rnd[ch[p][0]];
			rotate(p,d);
			del(ch[p][d^1],x);
		}
	}
	else
	{
		int d=x>val[p];
		del(ch[p][d],x);
	}
	update(p);
}
int rank(int p,int x)
{
	if(x==val[p]||!p)
		return s[ch[p][0]]+1;
	if(x<val[p])
		return rank(ch[p][0],x);
	return s[ch[p][0]]+cnt[p]+rank(ch[p][1],x);
}
int kth(int p,int x)
{
	int sum=s[ch[p][0]];
	if(x>=sum+1&&x<=sum+cnt[p])
		return val[p];
	if(x<=sum)
		return kth(ch[p][0],x);
	return kth(ch[p][1],x-sum-cnt[p]);
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("treap.in","r",stdin);
	freopen("treap.out","w",stdout);
	#endif
	srand(time(0));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		// printf("a:%d ",a);
		if(a==1)
			insert(root,b);
		else if(a==2)
			del(root,b);
		else if(a==3)
			printf("%d\n",rank(root,b));
		else if(a==4)
			printf("%d\n",kth(root,b));
		else if(a==5)
			printf("%d\n",pre(b));
		else if(a==6)
			printf("%d\n",next(b));
	//	fflush(stdout);
	}
	return 0;
}