#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define ui unsigned int
#define uc unsigned char
using namespace std;
int r,c,ldat;
uc cl[5009][5009][3];
uc sig[8]={0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A};
uc ihdr[25];
uc idat[100000009];
uc buffer[1000000009];
uc iend[12]={0,0,0,0,0x49,0x45,0x4E,0x44,0xAE,0x42,0x60,0x82};
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
	assert(ans);
	int pos=32;
	for(int i=n-1;i>=0;i--)
	{
		for(int j=0;j<=7;j++)
			ans[pos+7-j]=(s[i]>>j)&1;
		pos+=8;
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
void open(ui x,int d,int l,uc *s)
{
	for(int i=0;i<l;i++)
	{
		s[i]=x&0xFF;
		x>>=8;
	}
	if(d)
		for(int i=0;i<l>>1;i++)
			swap(s[i],s[l-1-i]);
}
void getihdr(uc *s)
{
	s[3]=13;
	s[4]='I';
	s[5]='H';
	s[6]='D';
	s[7]='R';
	int pos=8;
	open(c,1,4,s+pos);
	pos+=4;
	open(r,1,4,s+pos);
	pos+=4;
	s[pos++]=8;
	s[pos++]=2;
	pos+=3;
	ui t=crc(17,s+4);
	open(t,1,4,s+pos);
}
void getidat(uc *s)
{
	s[4]='I';
	s[5]='D';
	s[6]='A';
	s[7]='T';
	ui pos=8;
	uc *raw=(uc*)calloc((c*3+1)*r,1);
	int tmp=0;
	for(int i=1;i<=r;i++)
	{
		raw[tmp++]=0;
		for(int j=1;j<=c;j++)
			for(int k=0;k<3;k++)
				raw[tmp++]=cl[i][j][k];
	}
	ui adl=adler(tmp,raw);
	free(raw);
	s[pos++]=0x78;
	// s[pos++]=0xDA;
	s[pos++]=0x01;
	for(int i=1;i<=r;i++)
	{
		s[pos++]=i==r?1:0;
		ui tl=c*3+1;
		open(tl,0,2,s+pos);
		pos+=2;
		s[pos]=s[pos-2]^0xFF;
		s[pos+1]=s[pos-1]^0xFF;
		pos+=2;
		s[pos++]=0;
		for(int j=1;j<=c;j++)
			for(int k=0;k<3;k++)
				s[pos++]=cl[i][j][k];
	}
	fprintf(stderr,"%u",pos);
	fflush(stderr);
	open(adl,1,4,s+pos);
	pos+=4;//data chunk end
	open(pos-8,1,4,s);
	adl=crc(pos-4,s+4);
	fprintf(stderr,"crcdone");
	fflush(stderr);
	open(adl,1,4,s+pos);
	pos+=4;
	ldat=pos;
}
int main()
{
	freopen("png.in","r",stdin);
	freopen("out.png","wb",stdout);
	scanf("%d%d",&r,&c);
	for(int i=0;i<3;i++)
		for(int j=1;j<=r;j++)
			for(int k=1,t;k<=c;k++)
			{
				scanf("%d",&t);
				cl[j][k][i]=t;
			}
	getihdr(ihdr);
	getidat(idat);
	// ui tmp=crc(4,iend+4);
	// open(tmp,1,4,iend+8);
	for(int i=0;i<8;i++)
		putchar(sig[i]);
	for(int i=0;i<25;i++)
		putchar(ihdr[i]);
	for(int i=0;i<ldat;i++)
		putchar(idat[i]);
	for(int i=0;i<12;i++)
		putchar(iend[i]);
	return 0;
}