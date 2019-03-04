#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define inf 0x7F7F7F7F
#define rg register int
#define rc register char
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define cp(x,y) {sum[x]=sum[y];lp[x]=lp[y];rp[x]=rp[y];}
using namespace std;
char *p1,*p2,buffer[10000010];
int n,m,q,tot,totn,tots;
int h[200009];
int fat[200009];
int head[200009],edge[200009],nxt[200009];
int val[200009];
int st[200009],ed[200009];
int sq[100009],top;
int f[200009][21];
int root[100009],sum[3100009],lp[3100009],rp[3100009];
struct node
{
	int u,v,l;
	bool operator < (const node &o) const
	{
		return l<o.l;
	}
}e[500009];
void read(int &x)
{
	rc ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void ins(int a,int b)
{
	edge[++tot]=b;
	nxt[tot]=head[a];
	head[a]=tot;
}
int find(int x)
{
	if(x==fat[x])
		return x;
	return fat[x]=find(fat[x]);
}
void init()
{
	sort(e+1,e+m+1);
	for(rg i=1;i<=n<<1;++i)
		fat[i]=i;
	int fx,fy;
	totn=n;
	for(rg i=1;i<=m;++i)
	{
		fx=find(e[i].u);
		fy=find(e[i].v);
		if(fx^fy)
		{
			++totn;
			val[totn]=e[i].l;
			ins(totn,fx);
			ins(totn,fy);
			fat[fx]=fat[fy]=totn;
		}
	}
	for(rg i=1;i<=n;++i)
	{
		int t=find(i);
		if(t^totn)
		{
			++totn;
			val[totn]=inf;
			ins(totn,totn-1);
			ins(totn,t);
			fat[t]=fat[totn-1]=totn;
		}
	}
}
void dfs(int x,int fa)
{
	f[x][0]=fa;
	for(rg i=1;i<=18;++i)
		f[x][i]=f[f[x][i-1]][i-1];
	st[x]=inf;
	if(x<=n)
	{
		sq[++top]=h[x];
		st[x]=ed[x]=top;
	}
	for(int i=head[x];i;i=nxt[i])
	{
		dfs(edge[i],x);
		st[x]=min(st[x],st[edge[i]]);
		ed[x]=max(ed[x],ed[edge[i]]);
	}
}
void add(int &a,int l,int r,int x)
{
	int p=++tots;
	cp(p,a);
	a=p;
	sum[a]++;
	if(l^r)
	{
		int mid=(l+r)>>1;
		if(x<=mid)
			add(lp[a],l,mid,x);
		else
			add(rp[a],mid+1,r,x);
	}
}
int ask(int la,int ra,int l,int r,int k)
{
	if(l==r)
		return l;
	int ls=sum[lp[ra]]-sum[lp[la]];
	int mid=(l+r)>>1;
	if(k<=ls)
		return ask(lp[la],lp[ra],l,mid,k);
	return ask(rp[la],rp[ra],mid+1,r,k-ls);
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("peak.in","r",stdin);
	freopen("peak.out","w",stdout);
	char *pp=(char*)malloc(256<<20)+(256<<20);
	__asm__("movl %0,%%esp"::"r"(pp));
	#endif
	read(n);
	read(m);
	read(q);
	for(rg i=1;i<=n;++i)
		read(h[i]);
	int a,b,c;
	for(rg i=1;i<=m;++i)
	{
		read(e[i].u);
		read(e[i].v);
		read(e[i].l);
	}
	init();
	// for(rg i=1;i<=totn;++i)
	// 	printf("i:%d val:%d\n",i,val[i]);
	val[0]=inf;
	dfs(totn,0);
	// // for(rg i=1;i<=totn;++i)
	// // 	printf("i:%d st:%d ed:%d\n",i,st[i],ed[i]);
	// // for(rg i=1;i<=top;++i)
	// // 	printf("%d ",sq[i]);
	// // printf("\n");
	for(rg i=1;i<=n;++i)
	{
		root[i]=root[i-1];
		add(root[i],0,1000000000,sq[i]);
	}
	int last=0;
	for(rg i=1;i<=q;++i)
	{
		read(a);
		read(b);
		read(c);
		if(~last)
		{
			a^=last;
			b^=last;
			c^=last;
		}
		for(rg j=18;j>=0;--j)
			if(val[f[a][j]]<=b)
				a=f[a][j];
		if(c<1||c>ed[a]-st[a]+1)
		{
			last=-1;
			printf("-1\n");
			continue;
		}
		last=ask(root[st[a]-1],root[ed[a]],0,1000000000,ed[a]-st[a]+1-c+1);
		printf("%d\n",last);
	}
	return 0;
}