#include<iostream>
#include<cstdio>
#include<random>
#include<cstdlib>
using namespace std;
int main()
{
	random_device rnd;
	freopen("sais.in","w",stdout);
	int n=1000000;
	for(int i=1;i<=n;i++)
		printf("%c",rnd()%2+'a');
	return 0;
}