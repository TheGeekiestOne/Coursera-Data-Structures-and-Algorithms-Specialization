#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))
#define pb push_back
#define mp make_pair
#define rep(i,n) for(int i=0;i<n;i++)
#define repr(i,j,n) for(i=j;i<=n;i++)
#define endl '\n'
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vector<int> > graph;
const ll maxn = (ll) 1e5+9;
const ll mod = (ll) 1e9+7;

//ll a[maxn];
//ll dp[1024][1024];
graph adj(maxn);

int dfs(int r){
    if(adj[r].size()==0) return 1;
    else{
        int maxv=0;
        rep(i, adj[r].size()){
            int j=adj[r][i];
            maxv=MAX(maxv, dfs(j));
        }
        return 1+maxv;
    }
}

int main()
{
	std::ios::sync_with_stdio(0);
	ll i,j,k,t,q,m,l,n;
    cin>>n;
    int p[n];
    int r;
    rep(i, n){
        cin>>p[i];
        if(p[i]==-1) r=i;
        else adj[p[i]].pb(i);
    }
    cout<<dfs(r)<<endl;
}
