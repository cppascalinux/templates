#include<bits/stdc++.h>
using namespace std;

struct point{
    double x,y;
    point friend operator -(point a,point b)
    {return {a.x-b.x,a.y-b.y};}
}p[105],s[105];
double dis(point a,point b)
{
    point c=a-b;
    return sqrt(c.x*c.x+c.y*c.y);
}
double X(point a,point b)
{
    return a.x*b.y-a.y*b.x;
}
int cmp(point a,point b)
{
    double x=X(a-p[1],b-p[1]);
    
    if(x>0) return 1;
    if(x==0&&dis(a,p[1])<dis(b,p[1])) return 1;
    return 0;
}
double multi(point p1,point p2,point p3)
{
    return X(p2-p1,p3-p1);
}
int main()
{
    int N;
	freopen("hull.in","r",stdin);
	freopen("std.out","w",stdout);
    while(scanf("%d",&N),N)
    {
        for(int i=1;i<=N;i++) cin>>p[i].x>>p[i].y;
        
        if(N==1)
        {
            printf("0.00\n");
            continue;
        }
        else if(N==2)
        {
            printf("%.2lf\n",dis(p[1],p[2]));
            continue;
        }
        
        int k=1;
        for(int i=2;i<=N;i++)
        if(p[i].y<p[k].y||(p[i].y==p[k].y&&p[i].x<p[k].x))k=i;
        swap(p[1],p[k]);
        
        sort(p+2,p+1+N,cmp);
        
        s[1]=p[1];
        s[2]=p[2];
        int t=2;
        for(int i=3;i<=N;i++)
        {
            while(t>=2&&multi(s[t-1],s[t],p[i])<=0) t--;
            s[++t]=p[i];
        }
        double sum=0;
        for(int i=1;i<t;i++)
        {
            sum+=dis(s[i],s[i+1]);
        }
        printf("%.2lf\n",sum+dis(s[1],s[t]));
    }
    return 0;
}