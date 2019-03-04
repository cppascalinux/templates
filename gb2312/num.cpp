#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main()
{
	freopen("num.out","w",stdout);
	for(int i=-128;i<=-1;i++)
		for(int j=-128;j<=127;j++)
			printf("%c%c",(char)i,(char)j);
	return 0;
}