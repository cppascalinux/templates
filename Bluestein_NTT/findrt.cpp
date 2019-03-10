#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 950009857
#define ll long long
using namespace std;
int main()
{
	freopen("rt.out","w",stdout);
	for(int i=2;i<=1000;i++)
	{
		int fg=1,sm=1;
		for(int j=1;j<=mod-2;j++)
		{
			sm=(ll)sm*i%mod;
			if(sm==1)
			{
				fprintf(stderr,"i:%d j:%d\n",i,j);
				fg=0;
				break;
			}
		}
		if(fg)
		{
			printf("%d",i);
			return 0;
		}
	}
	return 0;
}