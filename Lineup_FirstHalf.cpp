#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
#define pb push_back
#define sz(vec) ((ll)vec.size())
#define all(vec) vec.begin(), vec.end()
#define f first
#define s second
const int MOD = 1e9 + 7;
const ll BIGINF = ((ll)1e18) + 7;
#define Speeed ios::sync_with_stdio(0);cin.tie(NULL); cout.tie(NULL);

bool cmp(pair<pair<db, db>, pair<ll, db> > a, pair<pair<db, db>, pair<ll, db> > b){
    
    return a.s.s < b.s.s;
}

vector<pair<db, db> > sol(vector<pair<db, db> > vec, bool mark){
    
    ll n = sz(vec); 
    vector<pair<pair<db, db>, pair<ll, db> >  > rev;
    vector<pair<db, pair<db, pair<db, db>>>> ans;
    map<ll, set<pair<db, ll> > > mp;
    
    //the lines
    vector<pair<db, db> > vec2 = vec;

    sort(all(vec));

    for(ll i = 0; i < n; i++){
        
        if(mark)
        cout<<vec[i].f<<"x + "<<vec[i].s<<"\n";
        
        rev.pb({{vec[i].s, vec[i].f}, {i, vec[i].f * 7 + vec[i].s}});
    }
        
    //find intersections
    for(ll i = 0; i < n; i++){
        for(ll j = i+1; j < n; j++){
            
            db m1 = vec[i].f, m2 = vec[j].f, b1 = vec[i].s, b2 = vec[j].s;
            
            if(m1 == m2)continue;
            db cx = (b2 - b1) / (m1 - m2), cy = m1 * cx + b1;
            
            ll mn = m1, pos = i, pos2 = j;
            if(m2 < mn){
                
                pos = j;
                pos2 = i;
            }
            
            if(cx>=0)ans.pb({cy, {cx, {pos+1, pos2+1}} });
        }
    }
    
    sort(all(ans));    
    // here we are sorting by how close to 7 we are for each line
    sort(all(rev), cmp);    
    //sorting intersections for each line by xvalue of intersection 
    for(auto x: ans){
        
        ll idx1 = x.s.s.f, idx2 = x.s.s.s;
        idx1--, idx2--;
        mp[idx1].insert({x.s.f, idx2});
        mp[idx2].insert({x.s.f, idx1});
    }
    
    if(mark)cout<<"\n\n\n";
    
    for(ll i = 0; i < n; i++){
        
        db x = 7;
        ll val = rev[i].s.f;
        if(mark)cout<<"N_"<<i+1<<":\n";
        
        while(true){
            
        if(mp[val].upper_bound({x, BIGINF})==mp[val].end())break;
        
        db xval = (*mp[val].upper_bound({x, BIGINF})).f;
        db idx = (*mp[val].upper_bound({x, BIGINF})).s;
            
        if(mark){
            
            if(x>=7 and x<=9 and xval>=7 and xval<=9){
                
                cout<<vec[val].f<<"x + "<<vec[val].s;
                cout<<" on range "<<x<<" < x < "<<xval<<"\n";
            }
        }
        
        val = idx;
        x = xval;
    }
        
        if(mark){
            
            if(x>=7 and x<=9){
                
                cout<<vec[val].f<<"x + "<<vec[val].s;
                cout<<" on range "<<x<<" < x < "<<"INF\n\n";
            }
            
            else cout<<vec[val].f<<"x + "<<vec[val].s<<" on range INF < x < INF\n\n";
        }
    }    

    return vec2;
}

void solve(){
    
    vector<pair<db, db> > vec;
    //creating the lines 
    for(ll i = 0; i <= 70; i++){
        for(ll j = 0; j <= 70; j++){
            
            if(i+j==0)continue;    
            vec.pb({i, j});
        }
    }
    vector<pair<db, db> > altered = sol(vec, 1);
}

int main(){
	Speeed
	
    ll t=1;
    // cin>>t;
    
    while(t--){
        
        solve();
    }
}
