#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))
#define pb push_back
#define mp make_pair
#define rep(i,n) for(i=0;i<n;i++)
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

int main()
{
	std::ios::sync_with_stdio(0);
	int i,j,k,t,m,l,r,n;
    int S;
    cin>>S>>n;
    queue<pair<int, pair<int, int> > > q;
    vector<pair<int, pair<int, int> > > v(n);
    rep(i, n){
        cin>>j>>k;
        v[i]=mp(i, mp(j,k));
    }
    vector<int> res(n);
    j=0;
    while(j<n && j<S){
        q.push(v[j]);
        j++;
    }
    t=0;
    while(!q.empty()){
        int st=MAX(t, q.front().second.first);
        t = st+q.front().second.second;
        res[q.front().first]=st;
        q.pop();
        while(q.size()<S && j<n){
            if(v[j].second.first<t){
                res[j++]=-1;
            }else{
                q.push(v[j++]);
            }
        }
    }
    rep(i, n){
        cout<<res[i]<<endl;
    }

}
