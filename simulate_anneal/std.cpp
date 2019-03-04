#include<cstdio>
#include<cmath>
#include<ctime>
#include<cstdlib>
#define RG register
#define R RG long double
#define RD T*(rand()*2-RAND_MAX)//生成一个-T到T的随机变动距离
//以前写的是T*((double)rand()/RAND_MAX*2-1)，总是WA（可能是先除后乘掉精度了），然后就参考了YL的写法
const int N=1009;
const long double D=0.97,EPS=1e-14;//更新后二分出了保证极高正确率和较高效率的参数
double x[N],y[N],w[N];
int n;
inline long double calc(R x0,R y0){
    R res=0,dx,dy;
    for(RG int i=1;i<=n;++i){//函数求值
        dx=x[i]-x0;dy=y[i]-y0;
        res+=sqrt(dx*dx+dy*dy)*w[i];
    }
    return res;
}
int main(){
	freopen("sa.in","r",stdin);
	freopen("std.out","w",stdout);
    R T,x0,y0,x1,y1,res,ans,best,bx=0,by=0;
    RG int i,times=1;//一次的正确率很高的，不放心也可以调大
    scanf("%d",&n);
    for(i=1;i<=n;++i){
        scanf("%lf%lf%lf",&x[i],&y[i],&w[i]);
        bx+=x[i];by+=y[i];
    }//初始横纵坐标均选择平均值
    best=ans=calc(bx/=n,by/=n);
    // srand(time(NULL));
    while(times--/*clock()<CLOCKS_PER_SEC*0.9*/){//比赛的时候试试注释里写的，卡时还是靠谱些
        ans=best;x0=bx;y0=by;
        for(T=100000;T>EPS;T*=D){
            x1=x0+RD;y1=y0+RD;
            res=calc(x1,y1);
            if(best>res)
                best=res,bx=x1,by=y1;//更新最优答案
            if(ans>res||exp((ans-res)/T)>(long double)rand()/RAND_MAX)
                ans=res,x0=x1,y0=y1;//接受新解
        }
    };
    printf("%.3Lf %.3Lf\n",bx,by);
    return 0;
}