#include<bits/stdc++.h>
using namespace std;
int read() {
    int q=0;char ch=' ';
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') q=q*10+ch-'0',ch=getchar();
    return q;
}
#define RI register int
const int mod=998244353,G=3,N=2100000;
int n;
int a[N],b[N],c[N],rev[N];
int ksm(int x,int y) {
    int re=1;
    for(;y;y>>=1,x=1LL*x*x%mod) if(y&1) re=1LL*re*x%mod;
    return re;
}
void NTT(int *a,int n,int x) {
    for(RI i=0;i<n;++i) if(i<rev[i]) swap(a[i],a[rev[i]]);
    for(RI i=1;i<n;i<<=1) {
        RI gn=ksm(G,(mod-1)/(i<<1));
        for(RI j=0;j<n;j+=(i<<1)) {
            RI t1,t2,g=1;
            for(RI k=0;k<i;++k,g=1LL*g*gn%mod) {
                t1=a[j+k],t2=1LL*g*a[j+k+i]%mod;
                a[j+k]=(t1+t2)%mod,a[j+k+i]=(t1-t2+mod)%mod;
            }
        }
    }
    if(x==1) return;
    int ny=ksm(n,mod-2); reverse(a+1,a+n);
    for(RI i=0;i<n;++i) a[i]=1LL*a[i]*ny%mod;
}
void work(int deg,int *a,int *b) {
    if(deg==1) {b[0]=ksm(a[0],mod-2);return;}
    work((deg+1)>>1,a,b);
    RI len=0,orz=1;
    while(orz<(deg<<1)) orz<<=1,++len;
    for(RI i=1;i<orz;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(len-1));
    for(RI i=0;i<deg;++i) c[i]=a[i];
    for(RI i=deg;i<orz;++i) c[i]=0;
    NTT(c,orz,1),NTT(b,orz,1);
    for(RI i=0;i<orz;++i)
        b[i]=1LL*(2-1LL*c[i]*b[i]%mod+mod)%mod*b[i]%mod;
    NTT(b,orz,-1);
    for(RI i=deg;i<orz;++i) b[i]=0;
}
int main()
{
	freopen("inv.in","r",stdin);
	freopen("std.out","w",stdout);
    n=read();
    for(RI i=0;i<n;++i) a[i]=read();
    work(n,a,b);
    for(RI i=0;i<n;++i) printf("%d ",b[i]);
    return 0;
}