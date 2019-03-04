#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<stack>
#include<vector>
using namespace std;  
const int maxn = 110;  
const int maxm = 10010;  
struct node  
{  
    int u, v, next;  
}edge[maxm], tp;  
int n, m;   //点数，边数   
int head[maxn], no;  
int add_bcc[maxn];//去掉该点之后能增加的bcc数目  
int index; //时间戳   
int yltd;   //图的初始连通分量   
int num[maxn], low[maxn];//时间戳和能回到的最早时间戳   
int iscut[maxn];//是否为割点   
int bccno[maxn], bcc_cnt; //bccno[i]表示i属于哪个bcc   
stack<node> S;    //存储bcc边   
vector<int> bcc[maxn];  
inline void init()  
{  
    no = 0;  
    memset(head, -1, sizeof head);  
}  
inline void add(int u, int v)  
{  
    edge[no].u = u; edge[no].v = v;  
    edge[no].next = head[u]; head[u] = no++;  
    edge[no].u = v; edge[no].v = u;  
    edge[no].next = head[v]; head[v] = no++;  
}  
inline void input()  
{  
    int u, v;  
    for(int i = 1; i <= m; ++i)  
    {  
        scanf("%d %d", &u, &v);  
        add(u, v);  
    }  
}  
void tarjan(int cur, int father)  
{  
    int child = 0;  
    num[cur] = low[cur] = ++index;  
    int k = head[cur];  
	printf("cur:%d\n",cur);
    while(k != -1)  
    {  
        int v = edge[k].v;   
        if(!num[v])  
        {  
            S.push(edge[k]);  
            ++child;  
            tarjan(v, cur);  
            low[cur] = min(low[cur], low[v]);  
            if(low[v] >= num[cur])     
            //把更节点看做普通的节点，对根节点这个条件是一定满足的，  
            //可以实现把回溯到根节点剩下的出栈，其实这就是一个新的双连通分量   
            {  
                iscut[cur] = 1;  
                ++add_bcc[cur];  
                ++bcc_cnt;//准备把新的双连通分量加入bcc   
                bcc[bcc_cnt].clear();  
                while(true)  
                {  
                    tp = S.top(); S.pop();  
                    if(bccno[tp.u] != bcc_cnt)  
                    {  
                        bcc[bcc_cnt].push_back(tp.u);  
                        bccno[tp.u] = bcc_cnt;  
                    }  
                    if(bccno[tp.v] != bcc_cnt)  
                    {  
                        bcc[bcc_cnt].push_back(tp.v);  
                        bccno[tp.v] = bcc_cnt;  
                    }  
                    if(tp.u == edge[k].u && tp.v == edge[k].v) break;  
                }  
            }  
        }  
        else if(num[v] < num[cur] && edge[k].v != father)  
        {  
            //num[v] < num[cur]的判断是为了防止当前cur为割点，然后它刚访问的一个双连通分量里有一个较深的点  
            //访问过了。然后再从cur访问，如果不判断就会将这个点加入S，造成错误，见上图。   
            //可以看到时间戳走到6再次回溯到2时，还能通过2对2-4这条边进行一次尝试，不判断的话4会被加到S  
            S.push(edge[k]);  
            low[cur] = min(low[cur], num[v]);  
        }  
        k = edge[k].next;  
    }  
    if(father < 0)  
    {  
        //把根节点看做普通节点了，所以下面最后的特殊判断必需。   
        if(child > 1) iscut[cur] = 1, add_bcc[cur] = child-1;  
        else iscut[cur] = 0, add_bcc[cur] = 0;  
    }  
}  
void Find_Cut(int l, int r)  
{  
    index = bcc_cnt = yltd = 0;  
    memset(add_bcc, 0, sizeof add_bcc);  
    memset(num, 0, sizeof num);  
    memset(iscut, 0, sizeof iscut);  
    memset(bccno, 0, sizeof bccno);  
    memset(low, 0, sizeof low);  
    for(int i = l; i <= r; ++i)  
    {  
        if(!num[i]) tarjan(i, -1), ++yltd;  
    }  
}  
void PutAll(int l, int r)  
{  
    for(int i = l; i <= r; ++i)  
    {  
        if(iscut[i]) printf("%d是割点，", i);  
        printf("去掉点%d之后有%d个双连通分量\n", i, add_bcc[i]+yltd);  
    }  
}  
void PutBcc()  
{  
    printf("有%d个BCC\n", bcc_cnt);  
    for(int i = 1; i <= bcc_cnt; ++i)  
    {  
        printf("BCC%d有%d个点: ", i, bcc[i].size());    
        for(int j = 0; j < bcc[i].size(); ++j) printf("%d ", bcc[i][j]);    
        printf("\n");    
    }  
}  
int main()  
{  
	freopen("bcc.in","r",stdin);
	freopen("bcc.out","w",stdout);
    while(~scanf("%d %d", &n, &m))  
    {  
        init();  
        input();  
        Find_Cut(1, n);  
        PutAll(1, n);  
        PutBcc();  
    }   
    return 0;  
}  