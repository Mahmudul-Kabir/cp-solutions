/*
    
    Note        :           My first centroid decomposition problem. Not OC. Had to lookup for basic ideas. 
 
    Link        :           https://cses.fi/problemset/task/2080/
 
*/



#include "bits/stdc++.h"
 
#define sp <<" "
#define el <<"\n"
#define S second
#define F first
#define pb push_back
#define all(ar) ar.begin(),ar.end() 
#define pii pair<ll,ll> 
 
 
using namespace std;
using ll = long long;
using ld = long double;
 
const ll mod = 1000000007;
const ll oo = 3372036000000000;
const ll si = 200005;
 
#define vvi vector<vector<ll>> 
 
struct cen_dec{
    vvi &g; 
    ll n,mcen,k,ans = 0,sol,mxd;  
    ll cnt[si]; 
    bitset<si> ded; 
    void dfs(ll v,ll p,vector<ll> &sz){
        sz[v] = 1; 
        for(ll r: g[v]){
            if(r == p || ded[r]) continue; 
            dfs(r,v,sz); 
            sz[v] += sz[r]; 
        }
        return; 
    }
    ll find_cen(ll v, ll p, ll lim, vector<ll> &sz){
        for(ll r: g[v]){
            if(r == p || ded[r]) continue; 
            if(sz[r] > lim) return find_cen(r,v,lim,sz); 
        }
        return v; 
    }
    void count(ll v,ll p,ll dep,bool op){
        if(dep > k) return; 
        mxd = max(mxd,dep);
        if(op) cnt[dep]++;
        else ans += cnt[k - dep]; 
        for(ll r: g[v]){
            if(r == p || ded[r]) continue; 
            count(r,v,dep+1,op); 
        }
        return; 
    }
    ll decompose(ll root){
        static vector<ll> sz(n); 
        dfs(root,-1,sz);
        ll lim = (sz[root])/2;  
        ll cen = find_cen(root,-1,lim,sz);  
        ded[cen] = 1;
        cnt[0]++;
        mxd = 0;
        for(ll r: g[cen]){
            if(!ded[r]){
                count(r,cen,1,0); 
                count(r,cen,1,1);
            }
        }
        //cout<<cen sp<<sol el; 
        for(int i = 0; i <= mxd; i++) cnt[i]=0;
        for(ll r: g[cen]){
            if(!ded[r]) decompose(r); 
        }
        return cen; 
    }
    cen_dec(vvi &tree,ll x) : g(tree){ 
        k = x;  
        n = g.size();  
        mcen = decompose(1); 
        return;  
    }
};
 
vvi g; 
ll n,k; 
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
//*
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
//*/
    cin>>n>>k; 
    g.assign(n+1,{}); 
    for(ll i = 1; i < n; i++){
        ll a,b; cin>>a>>b; 
        g[a].pb(b); 
        g[b].pb(a); 
    }
    cen_dec mau(g,k); 
    cout<<mau.ans el; 
    return 0;
}
