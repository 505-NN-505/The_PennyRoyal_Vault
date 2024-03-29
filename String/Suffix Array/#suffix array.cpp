#include <bits/stdc++.h>

// code n drink Pennyroyal tea
#ifdef Pennyroyal
#include <debug.h>
#else
#define debug(...)
#define sdebug(...)
#endif

using namespace std;

namespace sar {
    vector<vector<int>> c;
    vector<int> sort_cyclic_shifts(const string &s) {
        int n = s.size();
        const int alphabet = 256;
        vector<int> p(n), cnt(alphabet, 0);

        c.clear();
        c.emplace_back();
        c[0].resize(n);

        for (int i = 0; i < n; i++)         cnt[s[i]]++;
        for (int i = 1; i < alphabet; i++)  cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; i++)         p[--cnt[s[i]]] = i;

        c[0][p[0]] = 0;
        int classes = 1;

        for (int i = 1; i < n; i++) {
            if (s[p[i]] != s[p[i - 1]]) classes++;
            c[0][p[i]] = classes - 1;
        }

        vector<int> pn(n), cn(n);
        cnt.resize(n);

        for (int h = 0; (1 << h) < n; h++) {
            for (int i = 0; i < n; i++) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0)  pn[i] += n;
            }

            fill(cnt.begin(), cnt.end(), 0);

            /// radix sort
            for (int i = 0; i < n; i++)         cnt[c[h][pn[i]]]++;
            for (int i = 1; i < classes; i++)   cnt[i] += cnt[i-1];
            for (int i = n - 1; i >= 0; i--)    p[--cnt[c[h][pn[i]]]] = pn[i];
            
            cn[p[0]] = 0;
            classes = 1;

            for (int i = 1; i < n; i++) {
                pair<int, int> cur = {c[h][p[i]], c[h][(p[i] + (1<<h))%n]};
                pair<int, int> prev = {c[h][p[i-1]], c[h][(p[i-1] + (1<<h))%n]};
                if (cur != prev) ++classes;
                cn[p[i]] = classes - 1;
            }

            c.push_back(cn);
        }
        return p;
    }
    
    vector<int> suffix_array_construction(string s) {
        s += "!";
        auto sorted_shifts = sort_cyclic_shifts(s);
        sorted_shifts.erase(sorted_shifts.begin());
        return sorted_shifts;
    }

    /// LCP between the ith and jth (i != j) suffix of the STRING
    int suffixLCP(int i, int j) {
        assert(i != j);
        int log_n = c.size() - 1;
        int ans = 0;
        for (int k = log_n; k >= 0; k--) {
            if (c[k][i] == c[k][j]) {
                ans += 1 << k;
                i += 1 << k;
                j += 1 << k;
            }
        }
        return ans;
    }
}

vector<int> lcp_construction(const string &s, const vector<int> &sa) {
    int n = s.size();
    vector<int> rank(n, 0);
    vector<int> lcp(n-1, 0);

    for (int i = 0; i < n; i++)
        rank[sa[i]] = i;

    for (int i = 0, k = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }

        int j = sa[rank[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k]) k++;
        lcp[rank[i]] = k;
        if (k)  k--;
    }
    return lcp;
}

using namespace sar;

void solve(void) {
    string s = "aabaca";
    auto i = suffix_array_construction(s);
}

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}