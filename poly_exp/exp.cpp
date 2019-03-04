#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 998244353
#define ll long long
using namespace std;
int n,len;
int f[1050000],g[1050000],h[1050000],tf[1050000],tg[1050000],th[1050000];
int rt[2][1050000],mp[1050000],iv[1050000];
int qpow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=(ll)a*a%mod)
        if(b&1)
            ans=(ll)ans*a%mod;
    return ans;
}
void init(int bit)
{
    len=1<<bit;
    for(int i=0;i<len;i++)
        mp[i]=(mp[i>>1]>>1)|((i&1)<<(bit-1));
    rt[0][0]=rt[1][0]=1;
    rt[0][1]=qpow(3,119*(1<<(23-bit)));
    for(int i=2;i<len;i++)
        rt[0][i]=(ll)rt[0][i-1]*rt[0][1]%mod;
    for(int i=1;i<len;i++)
        rt[1][i]=rt[0][len-i];
}
void fft(int *s,int c)
{
    for(int i=0;i<len;i++)
        if(i<mp[i])
            swap(s[i],s[mp[i]]);
    for(int l=2;l<=len;l<<=1)
    {
        int d=l>>1,sp=len/l;
        for(int j=0;j<len;j+=l)
            for(int i=0;i<d;i++)
            {
                int t=(ll)rt[c][sp*i]*s[i+j+d]%mod;
                s[i+j+d]=(s[i+j]-t+mod)%mod;
                s[i+j]=(s[i+j]+t)%mod;
            }
    }
    if(c)
        for(int i=0;i<len;i++)
            s[i]=(ll)s[i]*iv[len]%mod;
}
void dif(int *s,int l)
{
    for(int i=0;i<l-1;i++)
        s[i]=(ll)s[i+1]*(i+1)%mod;
    s[l-1]=0;
}
void ing(int *s,int l)
{
    for(int i=l-1;i>=1;i--)
        s[i]=(ll)s[i-1]*iv[i]%mod;
    s[0]=0;
}
void getinv(int *f,int *g,int l)
{
    g[0]=1;
    memset(tf,0,sizeof(tf));
    for(int i=1;(1<<i)<2*l;i++)
    {
        init(i+1);
        memcpy(tf,f,len<<1);
        fft(tf,0);
        fft(g,0);
        for(int j=0;j<len;j++)
            g[j]=g[j]*(2-(ll)g[j]*tf[j]%mod+mod)%mod;
        fft(g,1);
        for(int j=len>>1;j<len;j++)
            g[j]=0;
    }
    for(int i=l;i<len;i++)
        g[i]=0;
}
void getlog(int *f,int *g,int l)
{
    getinv(f,g,l);
    dif(f,l);
    int bit=0;
    while(1<<bit<2*l)
        bit++;
    init(bit);
    for(int i=l;i<len;i++)
        f[i]=0;
	// for(int i=0;i<l;i++)
	// 	printf("i:%d f:%d g:%d\n",i,f[i],g[i]);
    fft(f,0);
    fft(g,0);
    for(int i=0;i<len;i++)
        g[i]=(ll)g[i]*f[i]%mod;
    fft(g,1);
    ing(g,l);
    for(int i=l;i<len;i++)
        g[i]=0;
}
void getexp()
{
    h[0]=1;
    for(int i=1;1<<i<2*n;i++)
    {
        // printf("\ni:%d\n",i);
        int l=1<<(i+1);
        memset(th,0,l<<2);
        memcpy(th,h,l);
        memset(g,0,l<<2);
        getlog(th,g,l>>1);
		// for(int j=0;j<l;j++)
		// 	printf("j:%d g:%d\n",j,g[j]);
        for(int j=1;j<l>>1;j++)
            g[j]=(-g[j]+f[j]+mod)%mod;
        g[0]=1;
        // for(int j=0;j<l;j++)
        // 	printf("l:%d j:%d h:%d g:%d\n",l,j,h[j],g[j]);
        init(i+1);
        // for(int j=l>>1;j<l;j++)
        // 	h[j]=0;
        fft(h,0);
        fft(g,0);
        for(int j=0;j<l;j++)
            h[j]=(ll)g[j]*h[j]%mod;
        fft(h,1);
        for(int j=l>>1;j<l;j++)
            h[j]=0;
        // for(int j=0;j<l;j++)
        // 	printf("j:%d h:%d\n",j,h[j]);
    }
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("exp.in","r",stdin);
    freopen("exp.out","w",stdout);
#endif
    iv[1]=1;
    for(int i=2;i<1050000;i++)
        iv[i]=(ll)(mod-mod/i)*iv[mod%i]%mod;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",f+i);
    // for(int i=0;i<n;i++)
    // 	printf("i:%d f:%d\n",i,f[i]);
    getexp();
    for(int i=0;i<n;i++)
        printf("%d ",h[i]);
    return 0;
}