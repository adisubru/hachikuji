#include <bits/stdc++.h>
#include "phase1.h"

#define fast ios::sync_with_stdio(0); cin.tie(0);
using namespace std;

int main(void) {
    fast;
    int n, m; //size of vertex and edge set respectively
    cin >> n >> m;
    vector < vector<int> > E(n), Er(n); //Adjacency list of th graph
    vector < array<int, 2> > Edges(n); //Edges in random order
    for( int i=0; i<n; i++) {
        int u, v;
        cin >> u >> v;
        E[u].push_back(v);
        Edges.push_back({u, v});
    }
    cout << phase1();

}

