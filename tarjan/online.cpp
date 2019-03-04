#include<iostream>  
#include<cstdio>  
#include<algorithm>  
#include<cstring>  
#include<stack>  
#include<vector>  
using namespace std;  
#define maxn 7500  
#define inf 0x3f3f3f3f  
int n,m;  
int g[maxn][maxn];  
int c; 
int low[maxn],pre[maxn];  
stack<int>s;  
int bc;  
vector<int>bcc[maxn];  
int dfs(int u,int fa){  
     low[u]=pre[u]=++c;  
     s.push(u);  
     for(int v=1;v<=n;v++){  
        if(!g[u][v])continue;  
        if(!pre[v]){  
            int lowv=dfs(v,u);  
            low[u]=min(low[u],lowv);  
            if(lowv>=pre[u]){  
                bc++;  
                bcc[bc].clear();  
                int tmp=-1;  
                while(!s.empty()){  
                    tmp=s.top();  
                    s.pop();  
                    bcc[bc].push_back(tmp);  
                    if(tmp==u)break;  
                }  
                if(tmp!=-1)s.push(tmp);  //割顶要加回去，任意割顶至少是两个不同双联通分量的公共点  
            }  
        }  
       else if(pre[v]<pre[u]&&fa!=v){  
            low[u]=min(low[u],pre[v]);  
        }  
     }  
     return low[u];  
}  
void inital(){  
    c=0;  
    bc=0;  
    memset(pre,0,sizeof pre);  
    memset(low,inf,sizeof low);  
    while(!s.empty()){  
        s.pop();  
    }  
}  
int main()  
{  
	freopen("bcc.in","r",stdin);
	freopen("bcc.out","w",stdout);
    int u,v;   
    while(~scanf("%d%d",&n,&m)){  
        inital();  
        for(int i=0;i<m;i++){  
            scanf("%d%d",&u,&v);  
            g[u][v]=g[v][u]=1;  
        }  
        for(int i=1;i<=n;i++){  
            if(!pre[i])dfs(i,-1);  
        }  
         for(int i=1;i<=n;i++){  
            printf("%d %d\n",pre[i],low[i]);  
        }  
  
        printf("下面是点联通分量%d:\n",bc);  
        for(int i=1;i<=bc;i++){  
            printf("%d:",i);  
            for(int j=0;j<bcc[i].size();j++){  
                printf("%d ",bcc[i][j]);  
            }  
            printf("\n");  
        }  
  
    }  
	return 0;
}  