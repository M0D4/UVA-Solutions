#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")


using namespace std;

#define sc              scanf
#define endl            "\n"
#define sz(x)          (int) (x.size())
#define all(v)          v.begin(), v.end()
#define isOdd(n)       (n&1)
//#define pow(n, m)      (ll)powl(n, m)
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



double calcDistance(double x1, double y1, double x2, double y2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
void Kruskal(){

    int n; //nodes

    cin >> n;
    DSU dsu(n + 2);

    pair<double, double> a[n];

    for(auto &i: a) cin >> i.first >> i.second;

    vector<tuple<double, int, int>> edgeList;

    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            double w = calcDistance(a[i].first, a[i].second, a[j].first, a[j].second);
            edgeList.push_back(tie(w, i, j));
        }
    }

    sort(all(edgeList));//sort by w

    int m = edgeList.size();

    double MST = 0;
    for(int i = 0; i < m; i++){
        double w; int u, v; tie(w, u, v) = edgeList[i];
        if(!dsu.sameGroup(u, v)){//will not cause a cycle
            dsu.mergeGroups(u, v);
            MST += w;
        }
    }
    cout << MST << endl;
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    cout << fixed << setprecision(2);

    int t; cin >> t;
    while(t--){
        Kruskal();
        if(t) cout << endl;
    }
    return 0;
}
