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



struct DSU{

    const static int N = 1e4 + 5; //nodes

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




void Kruskal(){

    int n, m; //nodes, edges

    ll MSP_cost = 0;

    cin >> n >> m;
    DSU dsu(n + 2);

    vector<tuple<int, int, int>> edgeList(m);

    map<string, int> mp;

    int city_id = 1;

    for(int i = 0; i < m; i++){
        string s, t; int w; cin >> s >> t >> w;

        if(!mp[s]) mp[s] = city_id++;
        if(!mp[t]) mp[t] = city_id++;

        int u = mp[s], v = mp[t];

        edgeList[i] = tie(w, u, v);
    }
    sort(all(edgeList));//sort by w

    for(int i = 0; i < m; i++){
        int w, u, v; tie(w, u, v) = edgeList[i];
        if(!dsu.sameGroup(u, v)){//will not cause a cycle
            MSP_cost += w;
            dsu.mergeGroups(u, v);
        }
    }
    cout <<  MSP_cost << endl;
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int t; cin >> t;
    while(t--){
        Kruskal();
        if(t) cout << endl;
    }
    return 0;
}
