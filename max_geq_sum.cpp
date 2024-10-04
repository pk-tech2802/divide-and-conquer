#include <bits/stdc++.h>
using namespace std;
#define fo(i, s, e) for (int i = s; i < e; i++)
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
#define ld long double
#define ff first
#define ss second
#define in insert
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define pb push_back
#define yes cout << "YES\n"
#define no cout << "NO\n"
using vi = vector<int>;
using vl = vector<ll>;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<ll>>;
ll mod = 1e9 + 7;
#define add(a, b) (((a % mod) + (b % mod)) % mod)
#define mul(a, b) (((a % mod) * (b % mod)) % mod)
#define sub(a, b) (((a % mod) - (b % mod) + mod) % mod)


const int maxN = 2e5+100 ;

struct node{
    ll val ;
    ll lsum=0,rsum=0,lmax=-1e9,rmax=-1e9 ;
} ;

node arr[maxN] ;
vector<node> mergeTree[4*maxN] ;

bool flag ;


vector<node> merge(vector<node>&a,vector<node>&b){
    vector<node>c ; 
    int n = a.size(),m=b.size();
    int i = 0 ,j=0 ;
    vl pre(m) ;
    pre[0] = b[0].lsum;
    fo(i,1,m){
        pre[i] = max(pre[i-1],b[i].lsum) ;
    }

    vl post(n) ;
    post[n-1] = a[n-1].rsum ;
    for(int i=n-2;i>=0;i--){
        post[i] = max(post[i+1],a[i].rsum) ;
    }

    i = n-1,j=0 ;
    while(i>=0){
        if(a[i].val<=0 || a[i].rmax!=a[i].val){
            i-- ;
            continue;
        }
        while(j<m && b[j].lmax<=a[i].val){
            j++ ;
        }
        if(j!=0){
            ll maxSum = pre[j-1]+a[i].rsum ;
            if(maxSum>a[i].val){
                flag = 0 ;
            }
        }
        i-- ; 
    }

    j=0,i=n-1 ;
    while(j<m){
        if(b[j].val<=0 || b[j].lmax!=b[j].val){
            j++ ;
            continue; 
        }
        while(i>=0 && a[i].rmax<=b[j].val){
            i-- ;
        }
        if(i!=n-1){
            ll maxSum = post[i+1]+b[j].lsum ;
            if(maxSum>b[j].val){
                flag = 0 ;
            }
        }
        j++ ;
    }

    ll s1=0,s2=0,m1=-1e9,m2=-1e9;
    fo(i,0,n){
        s1 += a[i].val ;
        m1 = max(m1,a[i].val) ;
    }
    fo(j,0,m){
        s2 += b[j].val ;
        m2 = max(m2,b[j].val);
    }

    fo(i,0,n){
        a[i].rsum += s2 ;
        a[i].rmax = max(a[i].rmax,m2) ;
        c.pb(a[i]) ;
    }

    fo(j,0,m){
        b[j].lsum += s1 ;
        b[j].lmax = max(b[j].lmax,m1) ;
        c.pb(b[j]) ;
    }

    return c ; 
}

void build(int si,int ss,int se){
    if(ss==se){
        mergeTree[si] = {arr[ss]} ;
        return ;
    }
    int mid = ss+(se-ss)/2 ;
    build(2*si,ss,mid) ;
    build(2*si+1,mid+1,se) ;
    mergeTree[si] = merge(mergeTree[2*si],mergeTree[2*si+1]) ;

    return ;
}


void solve(){
    flag = 1 ;
    int n ;
    cin>>n ;
    fo(i,0,n){
        node dm ;
        cin>>dm.val ;
        dm.lmax = dm.rmax = dm.lsum = dm.rsum = dm.val ;
        arr[i] = dm ;
    }
    build(1,0,n-1) ;
    if(flag){
        yes ;
    }
    else{
        no ;
    }
}
int main()
{
    FASTIO;
    int tt = 1;
    cin >> tt;

    while (tt--)
    {
        solve() ;
    }

    return 0;
}
 
