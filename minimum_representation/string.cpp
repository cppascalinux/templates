//2020.08.10
//luoguP1368 工艺 /【模板】最小表示法 奇怪的比较方式..利用之前比较的信息跳过一些比较..两个前缀指针i,j都单调向前移动,每次长度指针k增加x,
//i和j中至少有1个也会增加x,于是k至多增加2n,总时间复杂度O(n)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n;
int s[300009];
void solve()
{
	int p1=1,p2=2,l=0;
	while(p1<=n&&p2<=n&&l<=n)
	{
		// printf("p1:%d p2:%d l:%d\n",p1,p2,l);
		int k1=(p1+l-1)%n+1,k2=(p2+l-1)%n+1;
		if(s[k1]==s[k2])
			l++;
		else
		{
			s[k1]>s[k2]?p1+=l+1:p2+=l+1;
			l=0;
			if(p1==p2)
				p1++;
		}
	}
	int ansp=min(p1,p2);
	for(int i=0;i<=n-1;i++)
		printf("%d ",s[(ansp+i-1)%n+1]);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",s+i);
	solve();
	return 0;
}