#include <bits/stdc++.h>
using namespace std;

int maxProfit_helper(int pos1, int pos2, int maxSum, vector<int> &a, vector<int> &b, vector<vector<int>> &ans) {
    int n = a.size();
    int m = b.size();
    
    if(ans[pos1][pos2] != -1)
        return ans[pos1][pos2];
    else {
        int curr_ans = 0;
        
        //Either pick from stack 1 or stack 2 (if possible)
        if(pos1 < n && maxSum - a[pos1] >= 0)
            curr_ans = max<int>(curr_ans, 1 + maxProfit_helper(pos1 + 1, pos2, maxSum - a[pos1], a, b, ans));
        
        if(pos2 < m && maxSum - b[pos2] >= 0)
            curr_ans = max<int>(curr_ans, 1 + maxProfit_helper(pos1, pos2 + 1, maxSum - b[pos2], a, b, ans));
        
        ans[pos1][pos2] = curr_ans;
        return curr_ans;
    }
}

int portfolio_profit_maximisation(int maxSum, vector<int> a, vector<int> b) {
    int n = a.size();
    int m = b.size();
    vector<vector<int>> ans(n + 1, vector<int>(m + 1, -1));
    return maxProfit_helper(0, 0, maxSum, a, b, ans);
}

int main() {
    ios::sync_with_stdio(false);

    int n, m, x;
    cin >> n >> m >> x;

    vector<int> a(n);
    vector<int> b(m);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    int result = portfolio_profit_maximisation(x, a, b);
    cout << result;
    return 0;
}