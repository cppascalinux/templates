#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define uc unsigned char
#define ui unsigned int
using namespace std;
uc s[1000009];
ui adler(int n,uc *s)
{
	ui a=1,b=0;
	const ui mod=65521;
	for(int i=0;i<n;i++)
	{
		a=(a+s[i])%mod;
		b=(b+a)%mod;
	}
	return a+b*65536;
}
int main()
{
	freopen("adler.in","r",stdin);
	freopen("adler.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i=0,a;i<n;i++)
	{
		scanf("%d",&a);
		s[i]=a;
	}
	printf("%u",adler(n,s));
	return 0;
}