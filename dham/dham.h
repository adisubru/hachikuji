#include <bits/stdc++.h>
using namespace std;

extern vector<set<int>> E_adj;
extern vector<array<int, 2> E_list;

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

vector<int> phase1(int n, int ms) {
    int m = E_list.size();
    
    // random permutation and it's inverse
    vector<int> sigma(n), sigmai(n);
    for(int i=0; i<n; i++) sigma[i]=i;
    random_shuffle(sigma.begin(), sigma.end());
    for(int i=0; i<n; i++) sigmai[sigma[i]] = i;

    // Creating a edge set with avg in/out-degree 10
    set< array<int, 2> > Ep, Em, Ecap;
    vector<int> dEp(n), dEm(n);
    for(int i=0; i<ms; i++) {
        auto e = E_list[i];
        if(dEp[e[0]] < 10) {
            Ep.insert({e[0], sigma[e[1]]});
            dEp[e[0]]++;
        }
    }
    for(int i=0; i<ms; i++) {
        auto e = E_list[i];
        array<int, 2> ecap = {e[0], sigma[e[1]]};
        if( (dEm[sigma[e[1]]] < 10) && (Ep.find(ecap) != Ep.end()) ){
            Em.insert(ecap);
            dEm[ecap[1]]++;
        }
    }
    Ecap = Ep;
    Ecap.insert(Em.begin(), Em.end());
    
    // Create the bipartite graph, and find maximum matching
    Dinic F(2*n + 2);
    vector<int> psi(n, 2*n+3), phi(n, 2*n+1);
    for(auto it : Ecap) {
        F.addEdge(it[0], it[1] + n, 1);
        F.addEdge(it[1], it[0] + n, 1);
    }
    for(int i=0; i<n; i++) {
        F.addEdge(2*n, i, 1);
        F.addEdge(n + i, 2*n + 1, 1);
    }
    F.calc(2*n, 2*n + 1);
    for(int i=0; i<n; i++) {
        for(auto it : F.adj[i]) {
            if(it.flow() == 1) {
                psi[i] = it.to - n;
                break;
            }
            else {
                phi[i] = psi[sigmai[i]];
            }
        }
        if(psi[i] == 2*n+3) {
            //time to break, it's all lost, no Hamiltonian cyale
            break;
        }
    }
    return phi;
}

struct DSU {
    vector<int> parent, size;
    void initialize(int n) {
        parent.resize(n);
        size.resize(n);
    }
    void make_set(int x) {
        size[x] = 1;
        parent[x] = x;
    }
    int find(int x) {
        if(parent[x] == x)
            return x;
        return find(parent[x]);
    }
    void union(int a, int b) {
        a = find(a); b = find(b);
        if(a != b) {
            if(size[a] < size[b])
                swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
}cycle;

void phase2(vector<int> &phi) {
    int n = phi.size();
    int m2 = ceil(n*log2(n)*5.0/6.0);
    
    cycle.initialize(n);
    vector<int> phi_i(n);
    for(int i=0; i<n; ++i) cycle.make_set(i);
    for(int i=0; i<n; ++i) {
        cycle.union(i, phi[i]);
        phi_i[phi[i]] = i;
    }
    bool flag = true;
    while(flag) {
        flag = false;
        for(int i=0; i<m2; ++i) {
            int x = E_list[i][0], y = E_list[i][1], z = phi_i[E_list[i][1]], w = phi[E_list[i][0]];
            if(cycle.find(x) != cycle.find(y) && Es.find({z, w}) != Es.end() ) {
                cycle.union(x, y);
                phi[x] = y; phi_i[y] = x;
                phi[z] = w; phi_i[w] = z;
                flag = true;
                break;
            }
        }
    }
}

bool findcycle(int C1, int Ci, int i, vector<int> &phi) {
    int xj = i, xj1 = phi[i], n = phi,size();
    //redefine E_adj for this function. or maybe static, cuz for every call of this function
    
    //create set rho0
    set<list<int>> rho;
    for(auto it : E[xj]) {
        if(cycles.find(it) == cycles.find(C1) ) {
        	list<int> temp;
        	for(int i=xj1; phi[i] != it; i = phi[i]) {
        		temp.push_back(i);
        		if( i == xj ) {
        			temp.push_back(it);
        			i = it;
        		}
        	}
        	rho.insert(temp);
        }
    }


    int T = ceil((2.0*log2(n))/(3.0*log2(log2(n))));
    for(int t=0; t<T; ++t) {
    	set<list<int>> rho1;
    	for(auto it : rho) {
    		if(E_adj[it.last()].find(it.front()) != E_adj[it.last()].end()) {
    			//succesfully terminate and update phi
    		}
    		int uq = it.last();
    		for(auto ua : E_adj[uq]) {
    			//somehow get ua-1
    			
    		}
    	}
    }
    return true;
}

void phase3(vector<int> &phi) {
    int n = phi.size(), max=0;
    map<int, int> C;
    for(int i=0; i<n; ++i) {
        C[cycle.find(i)]++;
        if( C[max] > C[cycle.find(i)] )
           max = cycle.find(i);
    }
    C.erase(max); 

    for(auto it : C) {
        bool outcome = false;
        for(int i=it.first; phi[i] != it.first; i = phi[i]) {
            outcome = findcycle(max, it.first, i, phi);
            if(outcome) {
            	cycles.union(max, it.first);
                break;
            }
        }
        if(!outcome) {
            //terminate!! no solution
            return;
        }
    }
}
