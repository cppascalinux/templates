#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main()
{
	freopen("png.in","w",stdout);
	int r=5000,c=5000;
	printf("%d %d\n",r,c);
	for(int i=0;i<3;i++)
	{
		for(int j=1;j<=r;j++)
		{
			for(int k=1;k<=c;k++)
				printf("%d ",rand()%256);
			printf("\n");
		}
		printf("\n");
	}
	return 0;
}