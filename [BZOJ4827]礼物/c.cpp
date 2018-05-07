#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define maxn 50010
#define inf 2147483647
#define pi acos(-1)
using namespace std;
int n,m;
int q[maxn],w[maxn],tmp1[maxn],tmp2[maxn];
struct complex{
    double x,y;
    complex (double xx=0,double yy=0) {x=xx,y=yy;}
}a[maxn*4],b[maxn*4];
complex operator + (complex a,complex b)
{
    return complex(a.x+b.x,a.y+b.y);
}
complex operator - (complex a,complex b)
{
    return complex(a.x-b.x,a.y-b.y);
}
complex operator * (complex a,complex b)
{
    return complex(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);
}
int r[maxn*4],limit;
void fft(complex *A,int type)
{
    for(int i=0;i<limit;i++)
    {
	if(i<r[i])  swap(A[i],A[r[i]]);
    }
    for(int mid=1;mid<limit;mid*=2)
    {
	complex Wn=complex(cos(pi/mid),type*sin(pi/mid));
	for(int j=0;j<limit;j+=2*mid)
	{
	    complex w=complex(1,0);
	    for(int k=0;k<mid;k++,w=w*Wn)
	    {
		complex x=A[j+k];
		complex y=w*A[j+k+mid];
		A[j+k]=x+y;
		A[j+k+mid]=x-y;
	    }
	}
    }
}
void solve()
{
    limit=1;
    int len=0;
    while(limit<=2*n)
    {
	limit*=2;
	len++;
    }
    memset(r,0,sizeof(r));
    for(int i=0;i<limit;i++)   r[i]=(r[i/2]/2)+((i&1)<<(len-1));
    fft(a,1);
    fft(b,1);
    for(int i=0;i<limit;i++)   a[i]=a[i]*b[i];
    fft(a,-1);
}
int ans[maxn*4];
int sum=inf;
int cnt=0;
int c;
int main()
{
    scanf("%d%d",&n,&m);
    n--;
    for(int i=0;i<=n;i++)    scanf("%d",&tmp1[i]);
    for(int i=0;i<=n;i++)    scanf("%d",&tmp2[i]);
    for(int i=0;i<=n;i++)    cnt-=tmp1[i];
    for(int i=0;i<=n;i++)    cnt+=tmp2[i];
    if(cnt>0)   c=(int)((double)cnt/(double)(n+1)+0.5);
    else   c=(int)((double)cnt/(double)(n+1)-0.5);
    memset(ans,0,sizeof(ans));
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    for(int j=0;j<=n;j++)   q[j]=tmp1[j]+c;
    for(int j=0;j<=n;j++)   w[j]=tmp2[j];
    for(int j=0;j<=n;j++)   a[j].x=(double)q[j];
    for(int j=0;j<=n;j++)   b[j].x=(double)w[n-j];

    solve();
    for(int j=0;j<=n;j++)   ans[j]-=(int)(a[n-j].x/(double)limit+0.5);
    for (int i = 0;i <= n; ++i) printf("%d ", ans[i]);printf("\n");
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    for(int j=0;j<=n;j++)   a[j].x=(double)q[n-j];
    for(int j=0;j<=n;j++)   b[j].x=(double)w[j];
    for (int i = 0;i <= n; ++i) printf("%lf %lf\n", a[i].x, b[i].x);
    solve();
    int ansx=inf;
    for(int j=0;j<=n;j++)   ans[j]-=(int)(a[j-1].x/(double)limit+0.5);
    for (int i = 0;i <= n; ++i) printf("%d ", -ans[i]);printf("\n");
    for(int j=0;j<=n;j++)   ansx=min(ansx,ans[j]);
    ansx*=2;
    for(int j=0;j<=n;j++)   ansx+=q[j]*q[j]+w[j]*w[j];
    sum=min(ansx,sum);
    printf("%d\n",sum);
    return 0;
}
