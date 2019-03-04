#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
int main()
{
	int *l=(int*)malloc(256<<20);
	__asm__("movl %0,%%ip"::"r"(l));
	return 0;
}