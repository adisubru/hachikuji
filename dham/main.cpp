#include <bits/stdc++.h>
#include "dham.h"

#define fast ios::sync_with_stdio(0); cin.tie(0);
using namespace std;

vector<set<int>> E_adj, E_ms;
vector<array<int, 2>> E_list;

int numcycles(vector<int> &p) {
    vector<int> used(size(p));
    int ans = 0;
    for(unsigned int it=0; it<p.size(); ++it) {
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

bool checkvalid(vector<int> &p) {
    if (p.empty())
        return false;
    for(unsigned int i=0; i<p.size(); i++) {
        if (E_adj[i].find(p[i]) == E_adj[i].end()) {
            fprintf(stderr, "Edge (%d, %d) not in graph\n", i, p[i]);
            return false;
        }
    }
    return true;
}

int main(void) {
    fast;
    auto start = chrono::high_resolution_clock::now(); 
    int n, m, ms; //size of vertex and edge set respectively
    cin >> n >> m >> ms;
    E_adj.resize(n); E_ms.resize(n);
    for( int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v; 
        E_adj[u].insert(v);
        E_list.push_back({u, v});
        if (i <= ms) E_ms[u].insert(v);
    }
    
    bool valid = true;
    vector<int> matching = phase1(n, ms);
    int cyc = numcycles(matching);
    cerr << "p1 num cycles = " << cyc << endl;
    valid = valid && checkvalid(matching);

    if (cyc > 1) phase2(matching);
    cyc = numcycles(matching);
    cerr << "p2 num cycles = " << numcycles(matching) << endl;
    valid = valid && checkvalid(matching);
    
    if (cyc > 1) phase3(matching);
    cyc = numcycles(matching);
    cerr << "p3 num cycles = " << numcycles(matching) << endl;
    valid = valid && checkvalid(matching);

    if (valid) {
        auto stop = chrono::high_resolution_clock::now(); 
        auto time = chrono::duration_cast<chrono::milliseconds>(stop - start);
        fprintf(stdout, "%d %ld %d %d\n", 1, time.count(), ms, m);
    }
    else {
        cout << "0/n";
    }
    /*for(int i=0; i<n; i++) {
        cout << i << " " << matching[i] << endl;
        }*/
}

