#include <stdio.h>  
#include <math.h>    
#include <stdlib.h>    
#include <string.h>    
#include <iostream>    
#include <algorithm>   
#include <queue>   
#define mset(a,i) memset(a,i,sizeof(a))  
#define S1(n)    scanf("%d",&n)  
#define S2(n,m)  scanf("%d%d",&n,&m)  
#define P(n)     printf("%d\n",n)  
using namespace std;  
typedef long long ll;  
const int INF=0x3f3f3f3f;  
const int MAX=1e6+5;  
int n,m;  
struct node{  
    int u,v,w,next;  
}edge[6*MAX];  
int head[MAX];  
int d[MAX];//给点标号   
void add(int u,int v,int w)            //链式前向星建图   
{  
    static int cnt=0;  
    edge[cnt].v=v;  
    edge[cnt].w=w;  
    edge[cnt].next=head[u];  
    head[u]=cnt++;  
}  
int bfs(int s,int t)  
{  
    mset(d,0);  
    d[s]=1;  
    queue <int> q;  
    q.push(s);  
    while(!q.empty())  
    {  
        int u=q.front();  
        q.pop();  
        if(u==t) return 1;                  //到达汇点   
        for(int i=head[u];i!=-1;i=edge[i].next) //搜增广路   
        {  
            int v=edge[i].v;               //下一可连通点   
            int w=edge[i].w;               //当前流量   
            if(w&&d[v]==0)             //temp1没走到   
            {  
                d[v]=d[u]+1;            //点加1   
                if(v==t)                 //找到增广路   
                    return 1;  
                q.push(v);                 //入队列   
            }  
        }  
    }  
    return 0;  
}  
int dfs(int s,int t,int maxflow=INF)  
{  
    if(s==t)  
        return maxflow;  
    int i,j,ret=0;  
    for(i=head[s];i!=-1;i=edge[i].next)  
    {  
        int v=edge[i].v;            //下一个可连通点   
        int w=edge[i].w;            //当前点的流量   
        if(w&&d[v]==d[s]+1)  
        {  
            int temp=dfs(v,t,min(maxflow-ret,w)); //下一点，取最大流跟当前流量小的一个   
            edge[i].w-=temp;                  //正向相减   
            edge[i^1].w+=temp;                //反向弧相加   
            ret+=temp;                        //最大流   
            if(ret==maxflow)                  //下一点最大流等于这一点   
            return ret;  
        }  
    }  
    if(!ret)  
        d[s]=-1;  
    return ret;  
}  
  
int dinic(int s,int t)  
{  
    int ans=0;  
    while(bfs(s,t))  
    {  
        ans+=dfs(s,t);      //dfs返回每次的数量   
    }  
    return ans;  
}  
  
int main()  
{  
    S2(n,m);  
    mset(head,-1);  
    int s,t,cap;  
    for(int i=0;i<n;i++)//横边  
        for(int j=1;j<m;j++)  
        {  
            s=i*m+j;t=s+1;  
            S1(cap);  
            add(s,t,cap);  
            add(t,s,cap);  
        }  
    for(int i=0;i<n-1;i++)//纵边   
        for(int j=1;j<=m;j++)  
        {  
            s=i*m+j;t=s+m;  
            S1(cap);  
            add(s,t,cap);  
            add(t,s,cap);  
        }  
    for(int i=0;i<n-1;i++)//斜边  
        for(int j=1;j<m;j++)  
        {  
            s=i*m+j;t=s+m+1;  
            S1(cap);  
            add(s,t,cap);  
            add(t,s,cap);  
        }  
    int ans=dinic(1,n*m);  
    P(ans);  
    return 0;  
}  
