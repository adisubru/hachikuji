#include <bits/stdc++.h>
#include "dham.h"

#define fast ios::sync_with_stdio(0); cin.tie(0);
using namespace std;

vector<set<int>> E_adj;
vector<array<int, 2> E_list;

int main(void) {
    fast;
    int n, m, ms; //size of vertex and edge set respectively
    cin >> n >> m >> ms;
    E_adj.resize(n);
    E.list.resize(m);
    for( int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        E_adj[u].insert(v);
        E_list.push_back({u, v});
    }
    vector<int> matching = phase1(n, ms);
    //temp = matching; checking if permutation is legit
    
    //still need to stress test phase1
    sort(temp.begin(), temp.end());
    for(int i=0; i<n; i++) {
        cout << i << " " << matching[i] << endl;
        //if(temp[i] != i) cout<<"\n\n";
    }
}

