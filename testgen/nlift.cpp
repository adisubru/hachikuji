#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int h = 3, n = 100;
    if (argc > 1) {
        h = atoi( argv[1] );
    }
    if (argc > 2) {
        n = atoi( argv[2] );
    }
    // create Kh
    set<array<int, 2>> Ek, E;
    for(int i=0; i<h; ++i) {
        for(int j=i+1; j<h; ++j) {
            Ek.insert({i, j});
            Ek.insert({j, i});
        }
    }

    // Lift it
    for(auto it : Ek) {
        vector<int> u(n), v(n);
        for(int i=0; i<n; ++i) {
            u[i] = it[0]*n + i;
            v[i] = it[1]*n + i;
        }
        shuffle(u.begin(), u.end(), rng);
        shuffle(v.begin(), v.end(), rng);
        for(int i=0; i<n; i++) {
            E.insert({u[i], v[i]});
        }
    }

    cout << n*h << " " << E.size() << endl;
    for(auto it : E) cout << it[0] << " " << it[1] << endl;
}

