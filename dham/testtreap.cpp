#include <bits/stdc++.h>
#include "dham.h"
#define endl '\n'

using namespace std;

vector<set<int>> E_adj, E_ms;
vector<array<int, 2>> E_list;

int main(void) {
    int n; cin >> n;
    vector<int> a(n); cin >> a[0];
    Node *root = new Node(a[0]);
    for(int i=1; i<n; ++i) {
        cin >> a[i];
        auto x = new Node(a[i]);
        root = ins(root, x, i);
    }
    for(int i=0; i<n; i++) cout << value(root, i) << " "; cout << endl;
    inorder(root); cout << endl;
    int l=0, r=1, k=0;
    while (l != r) {
        cin >> l >> r >> k;
        move(root, l, r, k);
        inorder(root); cout << endl;
    }
}

