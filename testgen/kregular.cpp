#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    // A k regular graph with n vertices
    int n = 100, k = 10;
    if (argc > 1) {
        n = atoi( argv[1] );
    }
    if (argc > 2) {
        k = atoi( argv[2] );
    }
    if (k > n) {
        cerr << "k cannot be greater than n\n";
        return 0;
    }

    set<array<int, 2>> E;
    vector<int> perm(n);
    for(int i=0; i<n; ++i) perm[i]=i;
    for(int i=0; i<k; ++i) {
        shuffle(perm.begin(), perm.end(), rng);
        // need to check for repeated edges. low probablity, but can still happen
        for(int j=0; j<n; ++j) {
            E.insert({j, perm[j]});
        }
    }

    cout << n << " " << E.size() << endl;
    for(auto it : E) cout << perm[it[0]] << " " << perm[it[1]] << endl;
}

