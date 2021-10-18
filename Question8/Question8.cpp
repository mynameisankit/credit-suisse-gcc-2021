#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>

using namespace std;

#define undefined INT_MAX

int add(int a, int b) {
    return (a == undefined || b == undefined) ? 0 : a + b;
}

int maximizeReturns_helper(int pos, int k, int d, int D, int m, vector<int> &returns, vector<vector<vector<int>>> &ans) {    
    int n = returns.size();

    if(pos >= n)
        return (k == 0) ? 0 : undefined;
    else if(ans[pos][k][d] != -1)
        return ans[pos][k][d];
    else {
        int curr_ans = 0, temp;

        //If the multiplier is still applicable, then get multipled returns
        if(d == 0)
            curr_ans = max<int>(curr_ans, add(returns[pos], maximizeReturns_helper(pos + 1, k, 0, D, m, returns, ans)));
        //Otherwise get normal returns
        else
            curr_ans = max<int>(curr_ans, add(m*returns[pos], maximizeReturns_helper(pos + 1, k, d - 1, D, m, returns, ans)));

        //Make an investment or skip
        if(k > 0)
            curr_ans = max<int>(curr_ans, maximizeReturns_helper(pos + 1, k - 1, D, D, m, returns, ans));

        ans[pos][k][d] = curr_ans;
        return curr_ans;
    }
}

int calculateMaximizedReturns(int n, int k, int d, int m, vector<int> &returns) {    
    vector<vector<vector<int>>> ans(n, vector<vector<int>>(k + 1, vector<int>(d + 1, -1)));

    return maximizeReturns_helper(0, k, 0, d, m, returns, ans);
}

vector<string> split(const string& str, char delim) {
    vector<string> strings;
    size_t start;
    size_t end = 0;
    while ((start = str.find_first_not_of(delim, end)) != string::npos) {
        end = str.find(delim, start);
        strings.push_back(str.substr(start, end - start));
    }
    return strings;
}

vector<int> splitStringToInt(const string& str, char delim) {
    vector<int> strings;
    size_t start;
    size_t end = 0;
    while ((start = str.find_first_not_of(delim, end)) != string::npos) {
        end = str.find(delim, start);
        strings.push_back(stoi(str.substr(start, end - start)));
    }
    return strings;
}

void printVector(vector<int> vec) {
    for (vector<int>::const_iterator i = vec.begin(); i != vec.end(); ++i) {
        cout << *i << ' ';
    }
    cout << endl;
}

void printVector(vector<string> vec) {
    for (vector<string>::const_iterator i = vec.begin(); i != vec.end(); ++i) {
        cout << *i << ' ';
    }
    cout << endl;
}

int main() {
    string firstLine;
    getline(cin, firstLine);

    vector<int> firstLineVec = splitStringToInt(firstLine, ' ');
    int n = firstLineVec[0];
    int k = firstLineVec[1];
    int d = firstLineVec[2];
    int m = firstLineVec[3];

    string returns;
    getline(cin, returns);

    vector<int> returnsVec = splitStringToInt(returns, ' ');

    int result = calculateMaximizedReturns(n, k, d, m, returnsVec);

    // Do not remove below line
    cout << result << "\n";
    // Do not print anything after this line

    return 0;
}