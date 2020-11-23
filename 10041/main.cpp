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
typedef vector<int> vi;
typedef long double ld;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tii;


int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        int a[n];
        for(auto &i: a) cin >> i;
        sort(a, a + n);
        int sum = 0, mn = 1e9;
        for(int j = 1; j < 30000; j++){
            sum = 0;
            for(int i = 0; i < n; i++)
                sum += abs(a[i] - j);
            mn = min(mn, sum);
        }
        cout << mn << endl;
    }
    return 0;
}
