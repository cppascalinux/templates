#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
using namespace std;
int n,m,k,tot=1;
int in[100009],out[100009];
int hd[100009],eg[400009],nxt[400009];
int cur[100009];
int ans[400009],top;
int vist[400009];
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs(int x)
{
	// printf("x:%d\n{\n",x);
	for(int &i=cur[x];i;i=nxt[i])
		if(!vist[i])
		{
			int t=i;
			vist[i]=1;
			if(k==1)
				vist[i^1]=1;
			dfs(eg[i]);
			ans[++top]=t;
		}
	// printf("}\n");
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("path.in","r",stdin);
	freopen("path.out","w",stdout);
	#endif
	scanf("%d%d%d",&k,&n,&m);
	// if(m==0)
	// {
	// 	printf("YES\n");
	// 	return 0;
	// }
	int a,b;
	for(rg i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		if(k==1)
		{
			ins(a,b);
			ins(b,a);
			in[a]++;
			in[b]++;
		}
		else
		{
			ins(a,b);
			in[b]++;
			out[a]++;
		}
	}
	if(k==1)
	{
		for(rg i=1;i<=n;i++)
		{
			// printf("i:%d in:%d\n",i,in[i]);
			if((in[i]&1))
			{
				printf("NO");
				return 0;
			}
		}
	}
	else
	{
		for(rg i=1;i<=n;i++)
			if(in[i]^out[i])
			{
				printf("NO");
				return 0;
			}
	}
	for(rg i=1;i<=n;i++)
		cur[i]=hd[i];
	for(rg i=1;i<=n;i++)
		if(in[i])
		{
			dfs(i);
			break;
		}
	if(top<m)
	{
		printf("NO");
		return 0;
	}
	printf("YES\n");
	if(k==1)
		for(rg i=top;i>=1;i--)
		{
			if(ans[i]&1)
				printf("%d ",-(ans[i]>>1));
			else
				printf("%d ",ans[i]>>1);
		}
	else
		for(rg i=top;i>=1;i--)
			printf("%d ",ans[i]-1);
	return 0;
}