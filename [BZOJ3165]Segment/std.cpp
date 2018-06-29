#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
inline void read(ll &x){
    x=0;char ch;bool flag = false;
    while(ch=getchar(),ch<'!');if(ch == '-') ch=getchar(),flag = true;
    while(x=10*x+ch-'0',ch=getchar(),ch>'!');if(flag) x=-x;
}
const ll maxn = 100010;
const ll maxp = 40010;
const double eps = 1e-9;
inline ll dcmp(double x){
    return (x > eps) - (x < -eps);
}
struct Node{
    double k,b;ll id;
    bool vis;
    Node(){id = 0;k = b = 0;}
}T[maxn<<2];
ll L,R,idx;double K,B;
inline void solve(ll rt,ll l,ll r){
    if(T[rt].vis == false){
        T[rt].k = K;T[rt].b = B;
        T[rt].id = idx;
        T[rt].vis = true;
        return ;
    }
    double y0 = T[rt].k*l + T[rt].b;
    double y1 = K*l + B;
    double y2 = T[rt].k*r + T[rt].b;
    double y3 = K*r + B;
    if(dcmp(y1-y0) > 0 && dcmp(y3 - y2) > 0){
        if(dcmp(K-T[rt].k) == 0 && dcmp(B - T[rt].b) == 0) return;
        T[rt].k = K;T[rt].b = B;
        T[rt].id = idx;
        return ;
    }
    if(dcmp(y1-y0) <= 0 && dcmp(y3 - y2) <= 0) return ;
    ll mid = l+r >> 1;
    solve(rt<<1,l,mid);solve(rt<<1|1,mid+1,r);
}
inline void insert(ll rt,ll l,ll r){
    if(L <= l && r <= R){
        solve(rt,l,r);
        return ;
    }
    ll mid = l+r >> 1;
    if(L <= mid) insert(rt<<1,l,mid);
    if(R >  mid) insert(rt<<1|1,mid+1,r);
}
inline void insert(ll x0,ll x1,ll y0,ll y1,ll num){
    L = x0;R = x1;K = (double)(y1-y0)/(double)(x1-x0);
    B = y0 - x0*K;idx = num;insert(1,1,maxp);
    //printf("%lld %lld %lf %lf\n", L, R, K, B);
}
typedef pair<ll,ll> pa;
double ans;ll ans_id;
inline void query(ll rt,ll l,ll r,ll pos){
    double x = T[rt].k*pos + T[rt].b;
    if(dcmp(x-ans) == 1 || (dcmp(x-ans) == 0 && T[rt].id < ans_id)) ans = x,ans_id = T[rt].id;
    if(l == r) return ;
    ll mid = l+r >> 1;
    if(pos <= mid) query(rt<<1,l,mid,pos);
    else query(rt<<1|1,mid+1,r,pos);
}
ll a[maxn],id[maxn];
int main(){
    ll n;read(n);
    ll lastans = 0;
    ll op,x0,y0,x1,y1,x;
    ll num = 0;
    while(n--){
        read(op);
        if(op == 0){
            read(x);
            x = ((x +lastans-1)%39989+1);
            // printf("%lld\n", x);
            ans = ans_id = 0;
            query(1,1,maxp,x);
            if(ans < a[x] || (ans == a[x] && id[x] < ans_id)) ans_id = id[x];
            printf("%d\n",lastans = ans_id);
        }else if(op == 1){
            ++ num;
            read(x0);read(y0);read(x1);read(y1);
            x0 = (x0+lastans-1)%39989+1;
            y0 = (y0+lastans-1)%1000000000+1;
            x1 = (x1+lastans-1)%39989+1;
            y1 = (y1+lastans-1)%1000000000+1;
            // printf("%lld %lld %lld %lld\n", x0, y0, x1, y1);
            if(x0 > x1) swap(x0,x1),swap(y0,y1);
            if(x0 == x1 ){
                if(max(y0,y1) > a[x0]) a[x0] = max(y0,y1),id[x0] = num;
            }else insert(x0,x1,y0,y1,num);
        }
    }   
    getchar();getchar();
    return 0;
}
