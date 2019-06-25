//2019.06.25
//luogu P3835 可持久化平衡树 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#define pii pair<int,int>
#define fi first
#define se second
#define inf 0x7FFFFFFF
using namespace std;
int n,cnt;
int rt[500009];
int v[10000009],ch[10000009][2],sz[10000009];
void update(int x)
{
	sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+1;
}
int cln(int x)
{
	int y=++cnt;
	v[y]=v[x],sz[y]=sz[x];
	ch[y][0]=ch[x][0],ch[y][1]=ch[x][1];
	return y;
}
int newnode(int val)
{
	v[++cnt]=val;
	sz[cnt]=1;
	return cnt;
}
pii split(int lscnt,int x,int val)
{
	if(!x)
		return pii(0,0);
	if(x<=lscnt)
		x=cln(x);
	if(val<v[x])
	{
		pii t=split(lscnt,ch[x][0],val);
		ch[x][0]=t.se;
		update(x);
		return pii(t.fi,x);
	}
	else
	{
		pii t=split(lscnt,ch[x][1],val);
		ch[x][1]=t.fi;
		update(x);
		return pii(x,t.se);
	}
}
int mrg(int lscnt,int x,int y)
{
	if(!x||!y)
		return x+y;
	if(rand()%(sz[x]+sz[y])<sz[x])
	{
		if(x<=lscnt)
			x=cln(x);
		ch[x][1]=mrg(lscnt,ch[x][1],y);
		update(x);
		return x;
	}
	else
	{
		if(x<=lscnt)
			y=cln(y);
		ch[y][0]=mrg(lscnt,x,ch[y][0]);
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
	if(lsz+1==k)
		return x;
	if(k<=lsz)
		return kth(ch[x][0],k);
	return kth(ch[x][1],k-lsz-1);
}
void ins(int lst,int cur,int val)
{
	int lscnt=cnt;
	rt[cur]=rt[lst];
	pii t=split(lscnt,rt[cur],val);
	int x=newnode(val);
	rt[cur]=mrg(lscnt,t.fi,x);
	rt[cur]=mrg(lscnt,rt[cur],t.se);
}
void del(int lst,int cur,int val)
{
	int lscnt=cnt;
	rt[cur]=rt[lst];
	pii t1=split(lscnt,rt[cur],val-1);
	pii t2=split(lscnt,t1.se,val);
	rt[cur]=mrg(lscnt,ch[t2.fi][0],ch[t2.fi][1]);
	rt[cur]=mrg(lscnt,t1.fi,rt[cur]);
	rt[cur]=mrg(lscnt,rt[cur],t2.se);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("treap.in","r",stdin);
	freopen("treap.out","w",stdout);
#endif
	scanf("%d",&n);
	ins(0,0,-inf);
	ins(0,0,inf);
	for(int i=1,a,b,c;i<=n;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		if(b==1)
			ins(a,i,c);
		else if(b==2)
			del(a,i,c);
		else if(b==3)
			rt[i]=rt[a],printf("%d\n",rnk(rt[i],c)-1);
		else if(b==4)
			rt[i]=rt[a],printf("%d\n",v[kth(rt[i],c+1)]);
		else if(b==5)
			rt[i]=rt[a],printf("%d\n",v[kth(rt[i],rnk(rt[i],c)-1)]);
		else if(b==6)
			rt[i]=rt[a],printf("%d\n",v[kth(rt[i],rnk(rt[i],c+1))]);
	}
	return 0;
}