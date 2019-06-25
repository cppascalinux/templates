//2019.06.25
//luogu P3369 普通平衡树 fhq treap
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n,cnt,rt;
int ch[100009][2],sz[100009],v[100009];
void update(int x)
{
	sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+1;
}
int newnode(int val)
{
	v[++cnt]=val;
	sz[cnt]=1;
	return cnt;
}
pii split(int x,int val)
{
	if(!x)
		return pii(0,0);
	if(val<v[x])
	{
		pii t=split(ch[x][0],val);
		ch[x][0]=t.se;
		update(x);
		return pii(t.fi,x);
	}
	else
	{
		pii t=split(ch[x][1],val);
		ch[x][1]=t.fi;
		update(x);
		return pii(x,t.se);
	}
}
int mrg(int x,int y)
{
	if(!x||!y)
		return x+y;
	if(rand()%(sz[x]+sz[y])<sz[x])
	{
		ch[x][1]=mrg(ch[x][1],y);
		update(x);
		return x;
	}
	else
	{
		ch[y][0]=mrg(x,ch[y][0]);
		update(y);
		return y;
	}
}
int rnk(int x,int val)
{
	if(!x)
		return 1;
	if(val<=v[x])
		return rnk(ch[x][0],val);
	return rnk(ch[x][1],val)+sz[ch[x][0]]+1;
}
int kth(int x,int k)
{
	int lsz=sz[ch[x][0]];
	if(k==lsz+1)
		return x;
	if(k<=lsz)
		return kth(ch[x][0],k);
	return kth(ch[x][1],k-lsz-1);
}
void dfs(int x)
{
	if(!x)
		return;
	dfs(ch[x][0]);
	printf("x:%d v:%d sz:%d\n",x,v[x],sz[x]);
	dfs(ch[x][1]);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("treap.in","r",stdin);
	freopen("treap.out","w",stdout);
#endif
	srand(20020618);
	scanf("%d",&n);
	for(int i=1,a,b;i<=n;i++)
	{
		scanf("%d%d",&a,&b);
		if(a==1)
		{
			pii t=split(rt,b);
			int x=newnode(b);
			rt=mrg(t.fi,x);
			rt=mrg(rt,t.se);
		}
		else if(a==2)
		{
			pii t1=split(rt,b-1);
			pii t2=split(t1.se,b);
			rt=mrg(ch[t2.fi][0],ch[t2.fi][1]);
			rt=mrg(t1.fi,rt);
			rt=mrg(rt,t2.se);
			// dfs(rt);
		}
		else if(a==3)
			printf("%d\n",rnk(rt,b));
		else if(a==4)
			printf("%d\n",v[kth(rt,b)]);
		else if(a==5)
			printf("%d\n",v[kth(rt,rnk(rt,b)-1)]);
		else if(a==6)
			printf("%d\n",v[kth(rt,rnk(rt,b+1))]);
	}
	return 0;
}