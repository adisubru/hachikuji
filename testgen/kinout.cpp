#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int n = 100, in = 10, out=10;
    if (argc > 1) {
        n = atoi( argv[1] );
    }
    if (argc > 2) {
        in = atoi( argv[2] );
    }
    if (argc > 3) {
        out = atoi( argv[3] );
    }
    if (in > n || out > n) {
        cerr << "k cannot be greater than n\n";
        return 0;
    }
    
    set<array<int, 2>> E;
    vector<int> perm(n);
    for(int i=0; i<n; ++i) perm[i]=i;
    //shuffle(perm.begin(), perm.end(), rng);
    for(int i=0; i<n; ++i) {
        for(int j=0; j<in; ++j) {
            int x = uniform_int_distribution<int>(0, n)(rng);
            if (E.find({x, i}) == E.end())
                E.insert({x, i});
            else 
                j--;
        }
        
        for(int j=0; j<out; ++j) {
            int x = uniform_int_distribution<int>(0, n)(rng);
            if (E.find({i, x}) == E.end())
                E.insert({i, x});
            else 
                j--;
        }
    } 

    cout << n << " " << E.size() << endl;
    for(auto it : E) cout << perm[it[0]] << " " << perm[it[1]] << endl;
    //for(auto it : E) cout << it[0] << " " << it[1] << endl;
}

