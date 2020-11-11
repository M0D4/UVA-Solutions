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




int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int n, m, q;
    int testCase = 1;
    while(cin >> n >> m >> q && n){
        if(testCase > 1) cout << endl;

        int dp[n][n];
        clr(dp, 0x3f);
        while(m--){
            int u, v, c; cin >> u >> v >> c;
            --u, --v;
            dp[u][v] = dp[v][u] = c;
        }

        for(int i = 0; i < n; i++)
            dp[i][i] = 0;

        //floyd (Minimax)
        for(int k = 0; k < n; k++)
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    dp[i][j] = min(dp[i][j], max(dp[i][k] , dp[j][k]));

        cout << "Case #" << testCase++ << endl;
        while(q--){
            int u, v; cin >> u >> v;
            --u, --v;
            if(dp[u][v] > 1e7) cout << "no path" << endl;
            else cout << dp[u][v] << endl;
        }
    }
    return 0;
}
