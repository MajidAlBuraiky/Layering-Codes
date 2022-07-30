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

struct layer{
    
    db slope, ycept, strt, ed;
    ll idx;
    
};

bool cmp(pair<pair<db, db>, pair<ll, db> > a, pair<pair<db, db>, pair<ll, db> > b){
    
    return a.s.s < b.s.s;
}


bool cmp2(layer a, layer b){

    return a.ycept < b.ycept;
}

bool cmp3(layer a, layer b){

    return a.strt < b.strt;
}


bool lsort(vector<layer> a, vector<layer> b){
    
    for(ll i = 0; i < min(sz(a), sz(b)); i++){
        
        return a[i].ycept < b[i].ycept;
    }
}

void pr(vector<vector<layer>> lay){
    
    for(ll i = 0; i < sz(lay); i++){
        
        cout<<"N_"<<i<<"\n";
        for(ll j = 0; j < sz(lay[i]); j++){
            
            if(lay[i][j].ed <= 9){
                
                // cout<<lay[i][j].f.f<<"x + "<<lay[i][j].f.s<<"\n";
                cout<<lay[i][j].slope<<"x + "<<lay[i][j].ycept<<" on range ";
                cout<<lay[i][j].strt<<" < x < "<<lay[i][j].ed<<"\n";
            }
        }
        
        cout<<"\n\n";
    }
}

vector<pair<db, db> > sol(vector<pair<db, db> > vec, bool mark, bool mark2){
    
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
    
    //actually making the looking up line thingy
    //ech capacites
    //layers
    //things
    
    vector<vector<layer> > lay(n+1);
    
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
        
        layer inf;
        inf.slope = vec[val].f, inf.ycept = vec[val].s, inf.strt = x, inf.ed = xval, inf.idx = val;
        if(mark2)lay[i+1].pb(inf);
        //.f.f is slope, .f.s is ycept, .s.f is strt, .s.s is end 
        
        // instead of doing this try to divide just that layer and ignore the other lines 
        // and intersects 
        //and then sort each one and resort by y intercept 
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
        
        layer inf;
        inf.slope = vec[val].f, inf.ycept = vec[val].s, inf.strt = x, inf.ed = BIGINF, inf.idx = val;
        if(mark2)lay[i+1].pb(inf);
        

    }    
    
    if(mark2){
        
        
        // update y-intercept for each line to intersection with 7 (not actual y axis) 
        
        
        for(ll i = 1; i <= n; i++){
        
            sort(all(lay[i]), cmp2);//cmp2 sorts by ycept
        }
        
        sort(all(lay), lsort);
        // sorts layers by smallest ycept 
        
        
        for(ll i = 1; i <= n; i++){
        
            sort(all(lay[i]), cmp3);//cmp3 sorts by strt val of range in each layer 
        }
            
        // pr(lay, n);//prints
            
        for(db d = 1; d <= 100; d++){
            
            db k = (d*d + d*3)/2 - 1;
            
            
            if(k < sz(lay)){
                
                cout<<k<<":\n";
                for(ll j = 0; j < sz(lay[k]); j++){
                    
                    // lay[k][j].slope/=d;
                    // lay[k][j].ycept/=d;
                    vec2[lay[k][j].idx].f/=d;
                    vec2[lay[k][j].idx].s/=d;
                }
            }
        }
                
        for(ll i = 1; i <= n; i++){
        
            sort(all(lay[i]), cmp2);//cmp2 sorts by ycept
        }
        
        sort(all(lay), lsort);//lsort sorts the vectors by slope
        // why not sort by ycept too?
        
        
        for(ll i = 1; i <= n; i++){
        
            sort(all(lay[i]), cmp3);//cmp3 sorts by strt val
        }
        
        pr(lay);    
    }
    

    
    return vec2;
}

void solve(){
    
    vector<pair<db, db> > vec;
    
    //creating the lines 
    for(ll i = 0; i <= 50; i++){
        for(ll j = 0; j <= 50; j++){
            
            if(i+j==0)continue;    
            vec.pb({i, j});
        }
    }
    
    // sort(all(vec));
    
    //getting the lines after the first change
    
    // mark 1 is the first layering
    // mark2 is the second type (dividing each layer and ignoring non useful lines)
    vector<pair<db, db> > altered = sol(vec, 1, 0);
    
    // cout<<sz(altered)<<"\n";    
    //just for printing the relayered ones
    vector<pair<db, db> > temp = sol(altered, 0, 0);    
}


int main(){
	Speeed
	
    ll t=1;
    // cin>>t;
    
    while(t--){
        
        solve();
    }
}
