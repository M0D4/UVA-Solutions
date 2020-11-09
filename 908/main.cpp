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



typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;
typedef vector<int> vi;



struct DSU{

    const static int N = 1e6 + 5; //Maximum nodes

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

int n, m; //nodes, edges

ll MSP_cost, original_MSP;

vector<tuple<int, int, int>> edgeList;

void Kruskal(){
    MSP_cost = original_MSP = 0;

    DSU dsu(n);

    m = n - 1;

    while(m--){
        int u, v, c; cin >> u >> v >> c;
        original_MSP += c;
    }

    edgeList.clear();

    int k; cin >> k;
    while(k--){
        int u, v, c; cin >> u >> v >> c;
        --u, --v; //1-indexed
        edgeList.push_back(tie(c, u, v));
    }

    cin >> m;

    for(int i = 0; i < m; i++){
        int u, v, c; cin >> u >> v >> c;
        --u, --v; //1-indexed
        edgeList.push_back(tie(c, u, v));
    }

    sort(all(edgeList));//sort by weight

    m = edgeList.size();

    for(int i = 0; i < m; i++){
        int w, u, v; tie(w, u, v) = edgeList[i];
        if(!dsu.sameGroup(u, v)){//will not cause a cycle
            MSP_cost += w;
            dsu.mergeGroups(u, v);
        }
    }

    cout << original_MSP << endl << MSP_cost << endl;
}
int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

//    freopen("in.txt", "r", stdin);

    bool line = 0;
    while(cin >> n){
        if(line) cout << endl;
        line = 1;

        Kruskal();
    }
    return 0;
}
