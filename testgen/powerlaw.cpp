#include <bits/stdc++.h>
#include "jngen.h"
using namespace std;

int main(int argc, char **argv) {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    //Number of vertices and edges
    int a = 100, degsum = 0;
    double b = 0.4;
    if(argc > 1) {
        a = atoi( argv[1] );
    }
    if(argc > 2) {
        b = atof( argv[2] );
    }
    
    vector<int> degseq, vcopy, vcopy2;
    set<array<int, 2>> E;
    long maxdeg = exp(a/b), vno=0;
    cerr << a << " " << b << " " << a/b << " " << maxdeg << endl;
    for(long x=2; x<=maxdeg; ++x) {
        int y = a - b * log(x);
        for(int i=0; i<=y; ++i) {
            degseq.push_back(x);
            for(int j=0; j<y; ++j)
                vcopy.push_back(vno);
            vno++;
            degsum += x;
        }
    }
    if (degsum%2) {
        degseq.push_back(3);
        degsum += 3;
        for(int i=0; i<3; ++i)
            vcopy.push_back(vno);
    }
    int m = degsum/2;

    cerr << degseq.size() << " " << m << endl;
    //for(auto it : degseq) cerr << it << " ";
    
    shuffle(vcopy.begin(), vcopy.end(), rng);

    for(int i=0; i<vcopy.size()-1; ++i) {
        array<int, 2> edge = {vcopy[i], vcopy[i+1]};
        if (E.find(edge) == E.end()) {
           E.insert(edge);
           i++;
        }
        else {
            vcopy2.push_back(vcopy[i]);
        }
    }
    cerr << m << " " << E.size() << " " << vcopy2.size();
}

