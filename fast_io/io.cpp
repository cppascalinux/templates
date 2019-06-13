#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#define gc() (p1==p2&&(p2=(p1=buf1)+fread(buf1,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define flush() (fwrite(buf2,1,p3-buf2,stdout),p4=(p3=buf2)+10000000)
#define pc(x) (p3==p4&&(flush(),0)?EOF:*p3++=x)
using namespace std;
char buf1[10000009],buf2[10000009],*p1,*p2,*p3=buf2,*p4=buf2;
int s[10000009];
template<class T>
void rd(T &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
template<class T>
void pt(T x)
{
	if(x>=10)
		pt(x/10);
	pc(x%10+'0');
}
int main()
{
	freopen("io.in","r",stdin);
	freopen("io.out","w",stdout);
	int n;
	rd(n);
	// printf("n:%d\n",n);
	for(int i=1;i<=n;i++)
		rd(s[i]);
	for(int i=n;i>=1;i--)
		pt(s[i]),pc('\n');
		// printf("%d\n",rand());
	flush();
	return 0;
}