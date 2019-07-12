//2019.07.11
//luoguP2824 [HEOI2016/TJOI2016]排序 可以使用权值线段树去维护每一个有序段,再用一个set去维护所有的权值线段树,区间排序的时候将左,右端点的连续段分裂,
//再将内部的所有连续段合并,时间复杂度为O((n+q)logn),证明:单次分裂的复杂度为O(logn),至多产生logn个新节点,因此一共至多有(n+q)logn个节点,每次合并的时候,
//合并的时间复杂度为两棵树上都有的节点数目x,同时,合并一次,总节点个数-=x,使用势能分析,总时间复杂度=O(总点数)=O((n+q)logn)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<cassert>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
struct node
{
	int lm,rm,id,typ;
	node(){}
	node(int a,int b,int c,int d){lm=a,rm=b,id=c,typ=d;}
	bool operator <(const node &p) const{return rm<p.rm;}
};
int n,m,cnt;
int p[100009];
int lp[6000009],rp[6000009],sz[6000009];
void update(int a)
{
	sz[a]=sz[lp[a]]+sz[rp[a]];
}
void add(int &a,int l,int r,int pos,int val)
{
	a=++cnt;
	sz[a]+=val;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		add(lp[a],l,mid,pos,val);
	else
		add(rp[a],mid+1,r,pos,val);
}
int kth(int a,int l,int r,int k)
{
	if(l==r)
		return l;
	int lsz=sz[lp[a]];
	int mid=(l+r)>>1;
	if(k<=lsz)
		return kth(lp[a],l,mid,k);
	return kth(rp[a],mid+1,r,k-lsz);
}
int mrg(int a,int b,int l,int r)
{
	if(!a||!b)
		return a+b;
	if(l==r)
		return sz[a]+=sz[b],a;
	int mid=(l+r)>>1;
	lp[a]=mrg(lp[a],lp[b],l,mid);
	rp[a]=mrg(rp[a],rp[b],mid+1,r);
	update(a);
	return a;
}
pii splt(int a,int k,int l,int r)
{
	if(!a)
		return pii(0,0);
	if(l==r)
	{
		if(!k)
			return pii(0,a);
		return pii(a,0);
	}
	int mid=(l+r)>>1;
	if(k<=sz[lp[a]])
	{
		pii t=splt(lp[a],k,l,mid);
		int p=++cnt;
		lp[p]=t.fi;
		lp[a]=t.se;
		update(p),update(a);
		return pii(p,a);
	}
	else
	{
		pii t=splt(rp[a],k-sz[lp[a]],mid+1,r);
		int p=++cnt;
		rp[p]=t.se;
		rp[a]=t.fi;
		update(a),update(p);
		return pii(a,p);
	}
}
void solve()
{
	set<node> s;
	for(int i=1;i<=n;i++)
	{
		int rt=0;
		add(rt,1,n,p[i],1);
		s.insert(node(i,i,rt,0));
	}
	for(int i=1,a,b,c;i<=m;i++)
	{
		scanf("%d%d%d",&c,&a,&b);
		auto lit=s.lower_bound(node(0,a,0,0)),rit=s.lower_bound(node(0,b,0,0));
		if(lit==rit)
		{
			if(lit->typ==c)
				continue;
			if(lit->typ==0)
			{
				int ml=lit->lm,mr=lit->rm;
				pii t1=splt(lit->id,a-lit->lm,1,n);
				pii t2=splt(t1.se,b-a+1,1,n);
				s.erase(lit);
				if(ml<=a-1)
					s.insert(node(ml,a-1,t1.fi,c^1));
				if(b+1<=mr)
					s.insert(node(b+1,mr,t2.se,c^1));
				s.insert(node(a,b,t2.fi,c));
			}
			else
			{
				int ml=lit->lm,mr=lit->rm;
				pii t1=splt(lit->id,lit->rm-a+1,1,n);
				pii t2=splt(t1.fi,lit->rm-b,1,n);
				s.erase(lit);
				if(ml<=a-1)
					s.insert(node(ml,a-1,t1.se,c^1));
				if(b+1<=mr)
					s.insert(node(b+1,mr,t2.fi,c^1));
				s.insert(node(a,b,t2.se,c));
			}
			continue;
		}
		int cl=lit->typ,cr=rit->typ;
		int ml=lit->lm,mr=rit->rm;
		pii tl=splt(lit->id,cl?lit->rm-a+1:a-lit->lm,1,n);
		pii tr=splt(rit->id,cr?rit->rm-b:b-rit->lm+1,1,n);
		int nrt=mrg(cl?tl.fi:tl.se,cr?tr.se:tr.fi,1,n);
		for(auto it=++lit;it!=rit;it++)
			nrt=mrg(nrt,it->id,1,n);
		int lrt=cl?tl.se:tl.fi,rrt=cr?tr.fi:tr.se;
		s.erase(--lit,++rit);
		if(ml<=a-1)
			s.insert(node(ml,a-1,lrt,cl));
		if(b+1<=mr)
			s.insert(node(b+1,mr,rrt,cr));
		s.insert(node(a,b,nrt,c));
	}
	int v;
	scanf("%d",&v);
	auto it=s.lower_bound(node(0,v,0,0));
	int k=it->typ?it->rm-v+1:v-it->lm+1;
	printf("%d",kth(it->id,1,n,k));
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",p+i);
	solve();
	return 0;
}