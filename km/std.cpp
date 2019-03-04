#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=405;
const ll inf=~0U>>1;
int n,nl,nr,m,z,py,x,y,i,j,p,lk[N],pre[N];
bool vy[N];
int lx[N],ly[N],d,w[N][N],slk[N];ll ans;
int main(){
	freopen("km.in","r",stdin);
	freopen("std.out","w",stdout);
	scanf("%d%d%d",&nl,&nr,&m);
	n=max(nl,nr);
	while(m--)scanf("%d%d%d",&x,&y,&z),w[y][x]=max(w[y][x],z);
	for(i=1;i<=n;i++)for(j=1;j<=n;j++)lx[i]=max(lx[i],w[i][j]);
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++)slk[j]=inf,vy[j]=0;
		for(lk[py=0]=i;lk[py];py=p){
			vy[py]=1;d=inf;x=lk[py];
			for(y=1;y<=n;y++)if(!vy[y]){
				if(lx[x]+ly[y]-w[x][y]<slk[y])slk[y]=lx[x]+ly[y]-w[x][y],pre[y]=py;
				if(slk[y]<d)d=slk[y],p=y/* ,pre[y]=py */;
			}
			// pre[p]=py;
			for(y=0;y<=n;y++)if(vy[y])lx[lk[y]]-=d,ly[y]+=d;else slk[y]-=d;
		}
		for(;py;py=pre[py])lk[py]=lk[pre[py]];
	}
	for(i=1;i<=n;i++)ans+=lx[i]+ly[i];
	printf("%lld\n",ans);
	for(i=1;i<=nl;i++)printf("%d ",w[lk[i]][i]?lk[i]:0);
}