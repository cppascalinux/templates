#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define inf 0x7FFFFFFF
#define rm 100000000
#define update(x) s[x]=s[ch[x][0]]+s[ch[x][1]]+1;
using namespace std;
int n,m,tot1,tot2,tmp,tmpl,tmpr;
int root[3000010],lp[3000010],rp[3000010],vist[3000010];
int ch[9000010][2],f[9000010],val[9000010],s[9000010];
int num[50010];
void rotate(int x)
{
    int y=f[x],z=f[f[x]];
    int kx=x==ch[y][1],ky=y==ch[z][1];
    f[x]=z;
    f[y]=x;
    f[ch[x][kx^1]]=y;
    ch[z][ky]=x;
    ch[y][kx]=ch[x][kx^1];
    ch[x][kx^1]=y;
    update(y);
    update(x);
}
void splay(int c,int x,int fa)
{
    while(f[x]^fa)
    {
        int y=f[x],z=f[f[x]];
        if(z^fa)
            (x==ch[y][1])^(y==ch[z][1])?rotate(x):rotate(y);
        rotate(x);
    }
    if(!fa)
        root[c]=x;
}
void insert(int c,int x)
{
    int p=root[c],fa=0;
    while(p)
    {
        fa=p;
        p=ch[p][x>val[p]];
    }
    p=++tot2;
    if(fa)
        ch[fa][x>val[fa]]=p;
    f[p]=fa;
    ch[p][0]=ch[p][1]=0;
    val[p]=x;
    s[p]=1;
    splay(c,p,0);
}
void find(int c,int x)
{
    int p=root[c];
    while(x^val[p]&&ch[p][x>val[p]])
        p=ch[p][x>val[p]];
    splay(c,p,0);
}
int next(int c,int x,int k)
{
    find(c,x);
    int p=root[c];
    if(val[p]<x&&!k)
        return p;
    if(val[p]>x&&k)
        return p;
    p=ch[p][k];
    while(ch[p][k^1])
        p=ch[p][k^1];
    return p;
}
void del(int c,int x)
{
    int l=next(c,x,0);
    int r=next(c,x,1);
    splay(c,l,0);
    splay(c,r,l);
    ch[r][0]=0;
    update(r);
    update(l);
}
void add(int a,int l,int r,int x,int id)
{
    if(!vist[a])
    {
        vist[a]=1;
        insert(a,0);
        insert(a,n+1);
    }
    insert(a,id);
    if(l==r)
        return;
    int mid=(l+r)>>1;
    if(x<=mid)
    {
        if(!lp[a])
            lp[a]=++tot1;
        add(lp[a],l,mid,x,id);
    }
    else
    {
        if(!rp[a])
            rp[a]=++tot1;
        add(rp[a],mid+1,r,x,id);
    }
}
void erase(int a,int l,int r,int x,int id)
{
    if(!a)
        return;
    del(a,id);
    if(l==r)
        return;
    int mid=(l+r)>>1;
    if(x<=mid)
        erase(lp[a],l,mid,x,id);
    else
        erase(rp[a],mid+1,r,x,id);
}
int getsum(int a,int l,int r)
{
    if(!a)
        return 0;
    int ll=next(a,l,0);
    int rr=next(a,r,1);
    splay(a,ll,0);
    splay(a,rr,ll);
    return s[ch[rr][0]];
}
void dfs(int x)
{
    if(!x)
        return;
    dfs(ch[x][0]);
    printf("%d ",val[x]);
    dfs(ch[x][1]);
}
void init()
{
    tot1=1;
    for(int i=1;i<=n;i++)
        add(1,0,rm,num[i],i);
    /* for(int i=1;i<=tot1;i++)
    {
        printf("i:%d\n",i);
        dfs(root[i]);
        printf("\n");
    } */
}
int rank(int a,int l,int r,int ll,int rr,int x)
{
    if(l==r)
        return 1;
    int mid=(l+r)>>1;
    if(x<=mid)
        return rank(lp[a],l,mid,ll,rr,x);
    return getsum(lp[a],ll,rr)+rank(rp[a],mid+1,r,ll,rr,x);
}
int kth(int a,int l,int r,int ll,int rr,int x)
{
    if(l==r)
        return l;
    int mid=(l+r)>>1;
    int cnt=getsum(lp[a],ll,rr);
    if(x<=cnt)
        return kth(lp[a],l,mid,ll,rr,x);
    return kth(rp[a],mid+1,r,ll,rr,x-cnt);
}
void getprev(int a,int l,int r,int ll,int rr,int x)
{
    if(l==r)
        return;
    int mid=(l+r)>>1;
    if(x<=mid)
        getprev(lp[a],l,mid,ll,rr,x);
    else
    {
        if(getsum(lp[a],ll,rr))
        {
            tmp=lp[a];
            tmpl=l;
            tmpr=mid;
        }
        getprev(rp[a],mid+1,r,ll,rr,x);
    }
}
void getnext(int a,int l,int r,int ll,int rr,int x)
{
    if(l==r)
        return;
    int mid=(l+r)>>1;
    if(x>=mid+1)
        getnext(rp[a],mid+1,r,ll,rr,x);
    else
    {
        if(getsum(rp[a],ll,rr))
        {
            tmp=rp[a];
            tmpl=mid+1;
            tmpr=r;
        }
        getnext(lp[a],l,mid,ll,rr,x);
    }
}
int solveprev(int ll,int rr,int x)
{
    tmp=0;
    getprev(1,0,rm,ll,rr,x);
    if(!tmp)
        return -inf;
    int p=tmp,l=tmpl,r=tmpr;
    // printf("p:%d l:%d r:%d\n",p,l,r);
    while(l^r)
    {
        int mid=(l+r)>>1;
        if(getsum(rp[p],ll,rr))
        {
            p=rp[p];
            l=mid+1;
        }
        else
        {
            p=lp[p];
            r=mid;
        }
    }
    return l;
}
int solvenext(int ll,int rr,int x)
{
    tmp=0;
    getnext(1,0,rm,ll,rr,x);
    if(!tmp)
        return inf;
    int p=tmp,l=tmpl,r=tmpr;
    // printf("p:%d l:%d r:%d\n",p,l,r);
    while(l^r)
    {
        int mid=(l+r)>>1;
        if(getsum(lp[p],ll,rr))
        {
            p=lp[p];
            r=mid;
        }
        else
        {
            p=rp[p];
            l=mid+1;
        }
    }
    return l;
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("tree.in","r",stdin);
    freopen("splay.out","w",stdout);
    #endif
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",num+i);
    init();
    for(int i=1;i<=m;i++)
    {
        int a,b,c,d;
        scanf("%d",&a);
        if(a==1)
        {
            scanf("%d%d%d",&b,&c,&d);
            printf("%d\n",rank(1,0,rm,b,c,d));
        }
        else if(a==2)
        {
            scanf("%d%d%d",&b,&c,&d);
            printf("%d\n",kth(1,0,rm,b,c,d));
        }
        else if(a==3)
        {
            scanf("%d%d",&b,&c);
            erase(1,0,rm,num[b],b);
            num[b]=c;
            add(1,0,rm,c,b);
        }
        else if(a==4)
        {
            scanf("%d%d%d",&b,&c,&d);
            printf("%d\n",solveprev(b,c,d));
        }
        else
        {
            scanf("%d%d%d",&b,&c,&d);
            printf("%d\n",solvenext(b,c,d));
        }
    }
    return 0;
}