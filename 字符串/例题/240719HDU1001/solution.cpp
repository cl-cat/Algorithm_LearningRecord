#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct strHash {
    static vector<vector<int>> power;
    constexpr static array<int, 2> mod = { 1000000007, 1000000009 }, base = { 991, 19 };

    int n;
    vector<vector<int>> hash;
    strHash(const string& s) : n(s.size()), hash(2, vector<int>(n)) {
        extend(n);
        hash[0][0] = s[0], hash[1][0] = s[0];
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < 2; ++j) {
                hash[j][i] = (1ll * hash[j][i - 1] * base[j] % mod[j] + s[i]) % mod[j];
            }
        }
    }

    void extend(int n) {
        int m = power[0].size();
        if (n < m) return;
        power[0].resize(n + 1);
        power[1].resize(n + 1);
        for (int i = m; i <= n; ++i) {
            for (int j = 0; j < 2; ++j) {
                power[j][i] = 1ll * power[j][i - 1] * base[j] % mod[j];
            }
        }
    }

    array<i64, 2> get(const int& l, const int& r) {
        if (l > r) {
            return { 0, 0 };
        }
        array<i64, 3> res = { hash[0][r], hash[1][r], r - l + 1 };
        if (l > 0) {
            for (int i = 0; i < 2; ++i) {
                res[i] = (hash[i][r] - 1ll * hash[i][l - 1] * power[i][r - l + 1] % mod[i] + mod[i]) % mod[i];
            }
        }
        return { (res[0] << 30) + res[1], res[2] };
    }


    static array<i64, 2> merge(const vector<array<int, 2>>& a) {
        int m = a.size();
        array<i64, 3> res{ a[m - 1][0] >> 30, a[m - 1][0], a[m - 1][1] };
        for (int i = m - 2; i >= 0; --i) {
            for (int j = 0; j < 2; ++j) {
                res[j] = (1ll * a[i][j] * power[j][res[2]] % mod[j] + res[j]) % mod[j];
            }
            res[2] += a[i][2];
        }
        return { (res[0] << 30) + res[1], res[2] };
    };
};
vector<vector<int>> strHash::power(2, vector<int>(1, 1));

void solve() {
    string a, b;
    cin >> a >> b;

    int n = a.size(), m = b.size();

    set<i64> st;
    strHash sh(a + a);
    for (int i = 0; i < n; ++i) {
        st.insert(sh.get(i, i + n - 1)[0]);
    }

    int ans = 0;
    strHash th(b);
    for (int i = 0; i < m; ++i) {
        if (i + n - 1 >= m) {
            break;
        }
        if (st.count(th.get(i, i + n - 1)[0]) > 0) {
            ans++;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}