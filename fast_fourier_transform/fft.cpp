//2018.12.14
//lougu3803 【模板】多项式乘法（FFT）
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define rg register int
#define rc register char
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p1)?EOF:*p1++)
#define db double
#define eps 1e-6
#define pi 3.1415926535897932384626433832795
using namespace std;
int n,m,l1,l2;
char *p1,*p2,buffer[10000009];
int mp[2100000];
struct comp
{
	db x,y;
	comp(){}
	comp(db a,db b){x=a,y=b;}
	comp operator +(comp p){return comp(x+p.x,y+p.y);}
	comp operator -(comp p){return comp(x-p.x,y-p.y);}
	comp operator *(comp p){return comp(x*p.x-y*p.y,x*p.y+y*p.x);}
}omg[2][2100000],sm1[2100000],sm2[2100000];
void init()
{
	while((1<<m)<n)
		m++;
	n=1<<m;
	for(rg i=0;i<n;i++)
		omg[0][i]=comp(cos(2*pi*i/n),sin(2*pi*i/n));
	for(rg i=0;i<n;i++)
		omg[1][i]=omg[0][(n-i)%n];
	for(rg i=0;i<n;i++)
		mp[i]=(mp[i>>1]>>1)|((i&1)<<(m-1));
	// printf("n:%d m:%d\n",n,m);
	// for(rg i=0;i<n;i++)
	// 	printf("i:%d mp:%d\n",i,mp[i]);
}
void fft(int c,comp *s)
{
	for(rg i=0;i<n;i++)
		if(i<mp[i])
			swap(s[i],s[mp[i]]);
	for(rg l=2;l<=n;l<<=1)
	{
		int p=l/2;
		for(rg j=0;j<n;j+=l)
			for(rg i=0;i<p;i++)
			{
				comp t=omg[c][n/l*i]*s[i+j+p];
				s[i+j+p]=s[i+j]-t;
				s[i+j]=s[i+j]+t;
			}
	}
}
void read(int &x)
{
	rc ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("fft.in","r",stdin);
	freopen("fft.out","w",stdout);
#endif
	read(l1),read(l2);
	l1++,l2++;
	int a;
	for(rg i=0;i<l1;i++)
	{
		read(a);
		sm1[i].x=a;
	}
	for(rg i=0;i<l2;i++)
	{
		read(a);
		sm2[i].x=a;
	}
	n=l1+l2-1;
	init();
	fft(0,sm1);
	fft(0,sm2);
	for(rg i=0;i<n;i++)
		sm1[i]=sm1[i]*sm2[i];
	fft(1,sm1);
	for(rg i=0;i<l1+l2-1;i++)
		printf("%d ",(int)(sm1[i].x/n+eps));
	return 0;
}