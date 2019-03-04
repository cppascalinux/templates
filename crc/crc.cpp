#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define uc unsigned char
#define ui unsigned int
#define ull unsigned long long
using namespace std;
uc s[1000009];
ui crc(int n,uc *s)
{
	ui k0=0x4C11DB7U;
	uc key[32];
	for(int i=0;i<32;i++)
		if(k0&(1U<<i))
			key[i]=1;
		else
			key[i]=0;
	uc *ans=(uc*)calloc(n*8+32,1);
	int cur=32;
	for(int i=n-1;i>=0;i--)
	{
		for(int j=0;j<=7;j++)
			ans[cur+7-j]=(s[i]>>j)&1;
		cur+=8;
	}
	for(int i=n*8+32-1;i>=n*8;i--)
		ans[i]^=1;
	for(int i=n*8+32-1;i>=32;i--)
	{
		if(ans[i])
			for(int j=31;j>=0;j--)
				ans[i+j-32]^=key[j];
	}
	for(int i=0;i<32;i++)
		ans[i]^=1;
	ui ret=0;
	for(int i=0;i<=15;i++)
		swap(ans[i],ans[31-i]);
	for(int i=0;i<32;i++)
		ret|=ans[i]<<i;
	free(ans);
	return ret;
}
int main()
{
	freopen("crc.in","r",stdin);
	freopen("crc.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i=0,a;i<n;i++)
	{
		scanf("%d",&a);
		s[i]=a;
	}
	printf("%u",crc(n,s));
	return 0;
}