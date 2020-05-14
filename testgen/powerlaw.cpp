#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    //Number of vertices and edges
    double a = 3, b = 0.5;
    if(argc > 1) {
        a = atof( argv[1] );
    }
    if(argc > 2) {
        b = atof( argv[2] );
    }
    
    vector<int> vcopy[2];
    set<array<int, 2>> E;
    long maxdeg = exp(a/b), n=0, degsum=0;
    for(long x=6; x<=maxdeg; ++x) {
        int y = exp(a)/pow(x, b);
        for(int i=0; i<y; ++i) {
            //degseq.push_back(x);
            for(int j=0; j<x; ++j)
                vcopy[0].push_back(n);
            n++;
            degsum += x;
            //cerr << vcopy.size() << " " << degsum << endl;
        }
    }
    if (degsum%2) {
        //degseq.push_back(3);
        degsum += 3;
        for(int i=0; i<3; ++i)
            vcopy[0].push_back(n);
        n++;
    }
    int m = degsum/2;

    
    int iter = 0;
    while(iter < 100) {
        //creating the edge set
        int c = iter%2, n = (iter+1)%2;
        shuffle(vcopy[c].begin(), vcopy[c].end(), rng);
        vcopy[n].clear();
        for(int i=0; i<vcopy[c].size()-1; ++i) {
            array<int, 2> edge = {vcopy[c][i], vcopy[c][i+1]};
            if (E.find(edge) == E.end() && vcopy[c][i] != vcopy[c][i+1]) {
               E.insert(edge);
               //E.insert({vcopy[c][i+1], vcopy[c][i]});
               i++;
            }
            else {
                vcopy[n].push_back(vcopy[c][i]);
                if (i == vcopy[c].size()-2)
                    vcopy[n].push_back(vcopy[c][i+1]);
            }
        }
        cerr << iter << " " << vcopy[c].size() << " " << vcopy[n].size() << endl;
        iter++;
        if (vcopy[n].size() < 2) break;
    }
    
    cerr << a << " " << b << " " << a/b << " " << maxdeg << endl;
    cerr << n << " " << m << endl;
    cerr << E.size() <<  " " << iter << endl;

    vector<int> perm(n);
    for(int i=0; i<n; ++i) perm[i]=i;
    shuffle(perm.begin(), perm.end(), rng);
    cout << n << " " << E.size() << endl;
    //for(int i=0; i<n; ++i) cout << i << endl;
    for(auto it : E) cout << perm[it[0]] << " " << perm[it[1]] << endl;
}

