#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
struct Dinic {
    struct Edge {
        int to, rev;
        ll c, oc;
        ll flow() { return max(oc - c, 0LL); } // if you need flows
    };
    vi lvl, ptr, q;
    vector<vector<Edge>> adj;
    Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
    void addEdge(int a, int b, ll c, int rcap = 0) {
        adj[a].push_back({b, sz(adj[b]), c, c});
        adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
    }
    ll dfs(int v, int t, ll f) {
        if (v == t || !f) return f;
        for (int& i = ptr[v]; i < sz(adj[v]); i++) {
            Edge& e = adj[v][i];
            if (lvl[e.to] == lvl[v] + 1)
                if (ll p = dfs(e.to, t, min(f, e.c))) {
                    e.c -= p, adj[e.to][e.rev].c += p;
                    return p;
                }
        }
        return 0;
    }
    ll calc(int s, int t) {
        ll flow = 0; q[0] = s;
        rep(L,0,31) do { // 'int L=30' maybe faster for random data
            lvl = ptr = vi(sz(q));
            int qi = 0, qe = lvl[s] = 1;
            while (qi < qe && !lvl[t]) {
                int v = q[qi++];
                trav(e, adj[v])
                    if (!lvl[e.to] && e.c >> (30 - L))
                        q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
            }
            while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
        } while (lvl[t]);
        return flow;
    }
};

int phase1(vector< array<int, 2> > E, int n, int ms) {
    int m = E.size();
    
    // random permutation and it's inverse
    vector<int> sigma(n), sigmai(n);
    for(int i=0; i<n; i++) sigma[i]=i;
    random_shuffle(sigma.begin(), sigma.end());
    for(int i=0; i<n; i++) sigmai[sigma[i]] = i;

    // Creating a edge set with avg in/out-degree 10
    set< array<int, 2> > Ep, Em, Ecap;
    vector<int> dEp(n), dEm(n);
    for(int i=0; i<ms; i++) {
        auto e = E[i];
        if(dEp[e[0]] < 10) {
            Ep.insert({e[0], sigma[e[1]]});
            dEp[e[0]]++;
        }
    }
    for(int i=0; i<ms; i++) {
        auto e = E[i];
        array<int, 2> ecap = {e[0], sigma[e[1]]};
        if( (dEm[sigma[e[1]]] < 10) && (Ep.find(ecap) != Ep.end()) ){
            Em.insert(ecap);
            dEm[ecap[1]]++;
        }
    }
    Ecap = Ep;
    //set_union(Ep.begin(), Ep.end(), Em.begin(), Em.end(), Ecap);

    // Create the bipartite graph, and find maximum matching
    Dinic F(2*n + 2);
    for(auto it : Ep) {
        F.addEdge(it[0], it[1] + n, 1);
        F.addEdge(it[1], it[0] + n, 1);
    }
    for(int i=0; i<n; i++) {
        F.addEdge(2*n, i, 1);
        F.addEdge(n + i, 2*n + 1, 1);
    }
    return flow = F.calc(2*n, 2*n + 1);
    
}

