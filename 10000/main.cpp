#include "bits/stdc++.h"


#pragma GCC optimize("Ofast")


using namespace std;

#define endl            "\n"
#define all(v)          v.begin(), v.end()
#define debug(x)        cerr << #x << " is " << x << endl;
#define isOdd(n)        (n&1)
#define pow(n, m)       (ll)powl(n, m)
#define Unique(x)       x.erase(unique(all(x)), x.end())
#define clr(x, last)    memset(x, last, sizeof(x))

using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

const int N = 1e2 + 5, M = 1e5 + 5;

int ne, head[N], nxt[M], to[M];
pii dp[N];

void initGraph(int n){
    memset(head, -1, n * sizeof(head[0]));
    for (int i = 0; i < n; ++i) {
        dp[i] = {-1, 200};
    }
    ne = 0;
}

void addEdge(int f, int t){
    to[ne] = t;
    nxt[ne] = head[f];
    head[f] = ne++;
}

void addBidirectedEdge(int u, int v){
    addEdge(u, v);
    addEdge(v, u);
}

pii combine(pii a, pii b){
    if(a.first > b.first) return a;
    if(a.first < b.first) return b;
    return {a.first, min(a.second, b.second)};
}

pii dfs(int u){
    pii& ret = dp[u];
    if(~ret.first) return ret;
    ret = {0, u};
    for(int k = head[u]; ~k; k = nxt[k]){
        int v = to[k];
        pii df = dfs(v);
        df.first++;
        ret = combine(ret, df);
    }
    return ret;
}

int main()
{
    //ios_base::sync_with_stdio(0), cin.tie(0);

    int n, st, tc = 1;
    while (scanf("%d", &n), n){
        initGraph(n);

        scanf("%d", &st);
        printf("Case %d: The longest path from %d has length ", tc++, st);
        --st;
        int u, v;
        while (scanf("%d %d", &u, &v), u){
            addEdge(--u, --v);
        }
        printf("%d, finishing at %d.\n\n", dfs(st).first, dfs(st).second + 1);
    }
    return 0;
}
