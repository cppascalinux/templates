//luogu3805
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
using namespace std;
int n;
char p[11000009],s[22000009];
int f[22000009];
void init()
{
	s[0]='@';
	for(rg i=0;i<n;i++)
	{
		s[i*2+1]='#';
		s[i*2+2]=p[i];
	}
	s[n*2+1]='#';
	n=n*2+1;
}
void solve()
{
	int mx=0,id=0;
	for(rg i=1;i<=n;i++)
	{
		int &p=f[i];
		if(i<mx)
			p=min(mx-i,f[2*id-i]);
		else
			p=1;
		while(s[i+p]==s[i-p])
			p++;
		if(i+p>mx)
		{
			mx=i+p;
			id=i;
		}
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("manacher.in","r",stdin);
	freopen("manacher.out","w",stdout);
	#endif
	scanf("%s",p);
	n=strlen(p);
	init();
	solve();
	int ans=0;
	for(rg i=1;i<=n;i++)
		ans=max(ans,f[i]-1);
	printf("%d",ans);
	return 0;
}