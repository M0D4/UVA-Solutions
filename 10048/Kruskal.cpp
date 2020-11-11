#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")


using namespace std;

#define sc              scanf
#define endl            "\n"
#define sz(x)          (int) (x.size())
#define all(v)          v.begin(), v.end()
#define isOdd(n)       (n&1)
#define pow(n, m)      (ll)powl(n, m)
#define clr(x, val)     memset(x, val, sizeof(x))
#define numOfDigits(x)  (x ? (ll)(log10(x)) + 1 : 1)


typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tii;
typedef vector<int> vi;



const int N = 1e2 + 5; //nodes

struct DSU{

    int parent[N], groupSize[N];
    int groupCnt;

    DSU(int n){
        groupCnt = n;
        for(int i = 0; i < n; i++){
            parent[i] = i;
            groupSize[i] = 1;
        }
    }

    int findLeader(int i){
        if(parent[i] == i) return i;

        return parent[i] = findLeader(parent[i]);
    }

    bool sameGroup(int x, int y){
        return findLeader(x) == findLeader(y);
    }

    void mergeGroups(int x, int y){//merge to one component
        int leaderX = findLeader(x);
        int leaderY = findLeader(y);

        if(leaderX == leaderY) return;

        groupCnt--;

        if(groupSize[leaderX] > groupSize[leaderY]){
            parent[leaderY] = leaderX;
            groupSize[leaderX] += groupSize[leaderY];
        }else{
            parent[leaderX] = leaderY;
            groupSize[leaderY] += groupSize[leaderX];
        }
    }

    int getSize(int x){//size of group
        return groupSize[findLeader(x)];
    }
};

int n, m, q; //nodes, edges

int adj[N][N];

void Kruskal(){

    clr(adj, -1);

    DSU dsu(n);
    vector<tuple<int, int, int>> edgeList(m);

    for(int i = 0; i < m; i++){
        int u, v, w; cin >> u >> v >> w;
            --u, --v; //1-indexed
        edgeList[i] = tie(w, u, v);
    }
    sort(all(edgeList));//sort by w

    for(int i = 0; i < m; i++){
        int w, u, v; tie(w, u, v) = edgeList[i];
        if(!dsu.sameGroup(u, v)){//will not cause a cycle
            adj[u][v] = adj[v][u] = w;
            dsu.mergeGroups(u, v);
        }
    }
    while(q--){
        int u, v; cin >> u >> v;
        --u, --v;

        priority_queue<pii, vector<pii>, greater<pii>> q;
        q.push({0, u}); //minimax, vertex

        int minimax[n]; clr(minimax, -1);
        bool found = false;

        while(q.size()){
            int w, ver; tie(w, ver) = q.top();
            q.pop();

            if(minimax[ver] >= w) continue;
            minimax[ver] = w;

            if(ver == v){
                found = true;
                break;
            }

            for(int i = 0; i < n; i++){
                if(~adj[ver][i] && minimax[i] < adj[ver][i])
                    q.push({adj[ver][i], i});
            }
        }
        int mx = *max_element(minimax, minimax + n);
        if(~mx && found) cout << mx << endl;
        else cout << "no path" << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int testCase = 1;
    while(cin >> n >> m >> q && n){
        if(testCase > 1) cout << endl;

        cout << "Case #" << testCase++ << endl;
        Kruskal();
    }
    return 0;
}
