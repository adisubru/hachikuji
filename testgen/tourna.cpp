#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int n = 100;
    if (argc > 1) {
        n = atoi( argv[1] );
    }
    set<array<int, 2>> E;
    for(int i=0; i<n; ++i) {
        for(int j=i+1; j<n; ++j) {
            if (i == j) continue;
            int dir = uniform_int_distribution<int>(0, 1)(rng);
            if (dir)
                E.insert({i, j});
            else
                E.insert({j, i});
        }
    }

    cout << n << " " << E.size() << endl;
    for(auto it : E) cout << it[0] << " " << it[1] << endl;
}

