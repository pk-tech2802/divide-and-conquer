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


const int maxN = 3e5+100 ;

struct node{
    ll val ;
    ll pos ;
    ll lmin=1e9,rmin=1e9,lmax=-1e9,rmax=-1e9 ;
} ;

node arr[maxN] ;
vector<node> mergeTree[4*maxN] ;
vector<int> adj[maxN] ;

void tie_up(node &a,node &b){
    adj[a.pos].pb(b.pos) ;
    adj[b.pos].pb(a.pos) ;
    // cout<<"tying up "<<a.val<<" , "<<b.val<<"\n";
    // cout<<"tying up pos "<<a.pos<<" , "<<b.pos<<"\n\n";
}

vector<node> merge(vector<node>&a,vector<node>&b){
    vector<node>c ; 
    int n = a.size(),m=b.size();
    int i = 0 ,j=0 ;

    // cout<<"vec a: ";
    // for(auto it : a){
    //     cout<<it.val<<" ";
    // }
    // cout<<"\n";
    // cout<<"vec b: ";
    // for(auto it : b){
    //     cout<<it.val<<" ";
    // }
    // cout<<"\n";

    i = 0,j=0 ;

    vi aidx,bidx ;
    while(i<n){
        if(a[i].val==a[i].rmin){
            aidx.pb(i) ;
        }
        i++;
    }
    while(j<m){
        if(b[j].val==b[j].lmax){
            bidx.pb(j);
        }
        j++ ;
    }

    auto bs1 = [&](int l,int r,int aptr){
        int ans = -1 ;
        while(l<=r){
            int mid = l+(r-l)/2 ;
            if(b[bidx[mid]].lmax < a[aidx[aptr]].rmax){
                // fail due to less maximum 
                l = mid + 1 ;
                continue;
            }

            if(b[bidx[mid]].lmax > a[aidx[aptr]].rmax && b[bidx[mid]].lmin>a[aidx[aptr]].rmin){
                // valid ans 
                ans = mid ; 
                l = mid + 1 ;
            }
            else{
                r = mid - 1 ;
            }
        }

        return ans ;
    } ;

    // cout<<"aidx vec : \n";
    // for(auto id : aidx){
    //     cout<<a[id].val<<"\n";
    // }


    for(int i=0;i<aidx.size();i++){
        int aptr = i,l=0,r=bidx.size()-1;
        int lastIdx = bs1(l,r,aptr) ;
        if(lastIdx!=-1){
            // cout<<"t1 : ";
            tie_up(a[aidx[aptr]],b[bidx[lastIdx]]);
        }
    }

    aidx.clear() ;
    bidx.clear() ;

    i=0,j=0 ;
    while(i<n){
        if(a[i].val==a[i].rmax){
            aidx.pb(i);
        }
        i++ ;
    }
    while(j<m){
        if(b[j].val==b[j].lmin){
            bidx.pb(j);
        }
        j++ ;
    }

    auto bs2 = [&](int l,int r,int aptr){
        int ans = -1 ;
        while(l<=r){
            int mid = l+(r-l)/2 ;
            if(b[bidx[mid]].lmin > a[aidx[aptr]].rmin){
                // fail due to greater min 
                l = mid + 1 ;
                continue;
            }

            if(b[bidx[mid]].lmin < a[aidx[aptr]].rmin && b[bidx[mid]].lmax<a[aidx[aptr]].rmax){
                // valid ans 
                ans = mid ; 
                l = mid + 1 ;
            }
            else{
                r = mid - 1 ;
            }
        }

        return ans ;
    } ;

    for(int i=0;i<aidx.size();i++){
        int aptr = i,l=0,r=bidx.size()-1;
        int lastIdx = bs2(l,r,aptr) ;
        if(lastIdx!=-1){
            // cout<<"t2 : ";
            tie_up(a[aidx[aptr]],b[bidx[lastIdx]]);
        }
    }

    // while(j<m){
    //     if(b[j].val==b[j].lmax){
    //         lastIdx = j ;
    //     }
    //     j++ ;
    // }

    // while(i>=0){
    //     if(a[i].rmin!=a[i].val){
    //         i-- ;
    //         continue;
    //     }
    //     if(a[i].rmax<b[lastIdx].val){
    //         tie_up(a[i],b[lastIdx]) ;
    //     }
    //     i-- ;
    // }




    ll mn1 = a[0].rmin,mx1=a[0].rmax,mn2=b[0].rmin,mx2=b[0].rmax;
    fo(i,0,n){
        a[i].rmax = max(a[i].rmax,mx2);
        a[i].rmin = min(a[i].rmin,mn2);
        c.pb(a[i]);
    }
    fo(j,0,m){
        b[j].lmax = max(b[j].lmax,mx1) ;
        b[j].lmin = min(b[j].lmin,mn1) ;
        c.pb(b[j]);
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

    int n ;
    cin>>n ;
    fo(i,1,n+1){
        node dm ;
        cin>>dm.val ;
        dm.pos = i ; 
        dm.lmax = dm.rmax = dm.lmin = dm.rmin = dm.val ;
        arr[i] = dm ;
    }
    build(1,1,n) ;

    fo(i,2,n+1){
        adj[i].pb(i-1);
        adj[i-1].pb(i);
    }

    vi vis(n+1,0);
    vi dist(n+1,1e9);
    queue<int> q ;
    q.push(1);
    vis[1] = 1 ;
    dist[1] = 0 ;
    while(!q.empty()){
        int node = q.front();
        q.pop() ;
        for(auto child : adj[node]){
            if(!vis[child]){
                dist[child] = dist[node]+1 ;
                vis[child] = 1 ;
                q.push(child) ;
            }
        }
    }

    cout<<dist[n]<<"\n";
    
    fo(i,1,n+1){
        adj[i].clear() ;
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
