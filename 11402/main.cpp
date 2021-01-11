#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")


using namespace std;

#define sc              scanf
#define endl            "\n"
#define sz(x)           (int) (x.size())
#define all(v)          v.begin(), v.end()
#define isOdd(n)        (n&1)
#define pow(n, m)       (ll)powl(n, m)
#define clr(x, val)     memset(x, val, sizeof(x))


typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tii;

const int N = 1024000 + 5;


int seg[N * 4]; // holds the number of Buccaneer
char lazy[N * 4];
string s;

void flip(char &c){
    if(c == 'I') c = '?';
    else if(c == '?') c = 'I';
    else if(c == 'F') c = 'E';
    else c = 'F';
}

void push(int &node, int &st, int &ed){
    if(lazy[node] == '?') return;

    if(lazy[node] == 'I'){
        //flip
        seg[node] = (ed - st + 1) - seg[node];
    }
    else if(lazy[node] == 'F'){
        //to buccaneer
        seg[node] = (ed - st + 1);
    }else if(lazy[node] == 'E'){
        //to barbary
        seg[node] = 0;
    }

    if(st != ed){
        if(lazy[node] == 'I') flip(lazy[node * 2]), flip(lazy[node * 2 + 1]);
        else lazy[node * 2] = lazy[node * 2 + 1] = lazy[node];
    }

    lazy[node] = '?';
}

void build(int node, int st, int ed){
    if(st == ed){
        seg[node] = s[st] == '1';
        return;
    }

    build(node * 2, st, (st + ed) / 2);
    build(node * 2 + 1, (st + ed) / 2 + 1, ed);

    seg[node] = (seg[node * 2] + seg[node * 2 + 1]);
}

void update(int node, int st, int ed, int &l, int &r, char &type){
    push(node, st, ed);

    if(st > r || ed < l) return;
    if(st >= l && ed <= r){
        if(type == 'I') flip(lazy[node]);
        else lazy[node] = type;
        push(node, st, ed);
        return;
    }

    update(node * 2, st, (st + ed) / 2, l, r, type);
    update(node * 2 + 1, (st + ed) / 2 + 1, ed, l, r, type);

    seg[node] = (seg[node * 2] + seg[node * 2 + 1]);
}

int query(int node, int st, int ed, int &l, int &r){
    push(node, st, ed);
    if(st > r || ed < l) return 0;
    if(st >= l && ed <= r) return seg[node];

    return query(node * 2, st, (st + ed) / 2, l, r) +
           query(node * 2 + 1, (st + ed) / 2 + 1, ed, l, r);
}

int n;

void update(int l, int r, char type){
    update(1, 0, n - 1, l, r, type);
}

int query(int l, int r){
    return query(1, 0, n - 1, l, r);
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int t, tc = 1; cin >> t;

    while(t--){
        cout << "Case " << tc++ << ":\n";

        s = "";
        int m; cin >> m;
        while(m--){
            int mul; string x; cin >> mul >> x;
            while(mul--) s += x;
        }

        n = s.size();

        for(int i = 1; i <= 4 * n; i++)
            seg[i] = 0, lazy[i] = '?';

        build(1, 0, n - 1);

        int q, qq = 1; cin >> q;
        while(q--){
            char type; int l, r; cin >> type >> l >> r;

            if(type == 'S') cout << "Q" << qq++ << ": " << query(l, r) << endl;
            else update(l, r, type);
        }
    }
    return 0;
}
