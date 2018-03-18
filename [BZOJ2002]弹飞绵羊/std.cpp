#include<iostream>
#include<cstdio>
#define N 200005
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m;
int next[N],c[N][2],fa[N],size[N],st[N];
bool rev[N];
inline bool isroot(int k)
{
    return c[fa[k]][0]!=k&&c[fa[k]][1]!=k;
}
inline void pushup(int x)
{
    size[x]=size[c[x][0]]+size[c[x][1]]+1;
}
void pushdown(int k)
{
    int l=c[k][0],r=c[k][1];
    if(rev[k])
    {
        rev[k]^=1;rev[l]^=1;rev[r]^=1;
        swap(c[k][0],c[k][1]);
    }
}
void rotate(int x)
{
    int y=fa[x],z=fa[y],l,r;
    if(c[y][0]==x)l=0;else l=1;r=l^1;
    if(!isroot(y))
    {
        if(c[z][0]==y)c[z][0]=x;else c[z][1]=x;
    }
    fa[x]=z;fa[y]=x;fa[c[x][r]]=y;
    c[y][l]=c[x][r];c[x][r]=y;
    pushup(y);pushup(x);
}
void splay(int x)
{
    int top=0;st[++top]=x;
    for(int i=x;!isroot(i);i=fa[i])
    {
        st[++top]=fa[i];
    }
    for(int i=top;i;i--)pushdown(st[i]);
    while(!isroot(x))
    {
        int y=fa[x],z=fa[y];
        if(!isroot(y))
        {
            if(c[y][0]==x^c[z][0]==y)rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
}
void access(int x)
{
    int t=0;
    while(x)
    {
        splay(x);
        c[x][1]=t;
        t=x;x=fa[x];
    }
}
void rever(int x)
{
    access(x);splay(x);rev[x]^=1;
}
void link(int x,int y)
{
    rever(x);fa[x]=y;splay(x);
}
void cut(int x,int y)
{
    rever(x);access(y);splay(y);c[y][0]=fa[x]=0;
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++)
    {
	int x=read();
	fa[i]=x+i;size[i]=1;
	if(fa[i]>n+1)fa[i]=n+1;
	next[i]=fa[i];
    }
    size[n+1]=1;
    m=read();
    for(int i=1;i<=m;i++)
    {
	int f=read();
	if(f==1)
	{
	    rever(n+1);
	    int x=read();x++;
	    access(x);splay(x);printf("%d\n",size[c[x][0]]);
	}
	else 
	{
	    int x=read(),y=read();x++;
	    int t=min(n+1,x+y);
	    cut(x,next[x]);link(x,t);next[x]=t;
	}
    }
    return 0;
}
