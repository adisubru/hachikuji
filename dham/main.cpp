#include <bits/stdc++.h>
#include "dham.h"

#define fast ios::sync_with_stdio(0); cin.tie(0);
using namespace std;

vector<set<int>> E_adj, E_ms;
vector<array<int, 2>> E_list;

int numcycles(vector<int> &p) {
    vector<int> used(size(p));
    int ans = 0;
    for(int it=0; it<size(p); ++it) {
        if (used[it])
            continue;
        ans++;
        int i = it;
        while(!used[i]) {
            used[i] = 1;
            i = p[i];
        }
    }
    return ans;
}

int main(void) {
    fast;
    int n, m, ms; //size of vertex and edge set respectively
    cin >> n >> m >> ms;
    E_adj.resize(n); E_ms.resize(n);
    //E_list.resize(m);
    for( int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v; 
        E_adj[u].insert(v);
        E_list.push_back({u, v});
        if (i <= ms) E_ms[u].insert(v);
    }
    vector<int> matching = phase1(n, ms);
    int cyc = numcycles(matching);
    cerr << "p1 num cycles = " << cyc << endl;
    if (cyc > 1) phase2(matching);
    cyc = numcycles(matching);
    cerr << "p2 num cycles = " << numcycles(matching) << endl;
    if (cyc > 1) phase3(matching);
    cyc = numcycles(matching);
    cerr << "p3 num cycles = " << numcycles(matching) << endl;
    
    
    vector<int> temp = matching; //checking if permutation is legit
    sort(temp.begin(), temp.end());
    for(int i=0; i<n; i++) {
        cout << i << " " << matching[i] << endl;
        if(temp[i] != i) cout<<"\n\n";
    }
}

