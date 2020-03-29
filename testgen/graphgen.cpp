#include <bits/stdc++.h>
#include "jngen.h"
using namespace std;

int main(int argc, char **argv) {
    //Number of vertices and edges
    int n = 100, c = 0, d = 1, m;
    if(argc > 1) {
        n = atoi( argv[1] );
    }
    if(argc > 2) {
        c = atoi( argv[2] );
    }
    if(argc > 3) {
        d = atoi( argv[3] );
    }
    m = (double)n * log2(n) + c;

    cout << n << " " << m << "\n";
    //Generate the random digraph using jngen and check degree constraint
    bool flag = true;
    auto g = Graph();
    while (flag) {
        g = Graph::random(n, m).directed().allowAntiparallel().connected().g().shuffled();
        flag = false;
        
        vector<int> indegree(n);
        for(int i=0; i<n; i++) {
            for(auto it : g.edges(i)) {
                indegree[it]++;
            }
            if(g.edges().size() < d) {
                flag = true;
                break;
            }
        }
        for(auto it : indegree) {
            if(it < d) {
                flag = true;
                break;
            }
        }
    }
    cout << g << endl;
    
}

