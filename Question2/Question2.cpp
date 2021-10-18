#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <queue>
#include <sstream>
#include <typeinfo>
#include <bits/stdc++.h>
using namespace std;
 
int stock_helper(int pos, int z, vector<int> &security_value, vector<vector<int>>& ans) {
    int n = security_value.size();
    
    if(pos >= n) 
        return 0;
    else if(ans[pos][z] != -1)
        return ans[pos][z];
    else {
        int curr_ans = 0;
        
        for(int i = 0; z > 0 && i <= pos + 1; i++) {
            int money_rem = z - i*security_value[pos];
        
            if(money_rem >= 0)
                curr_ans = max<int>(curr_ans, i + stock_helper(pos + 1, money_rem, security_value, ans));
        }
        
        ans[pos][z] = curr_ans;
        return curr_ans;
    }
}
 
int securitiesBuying(int z, vector<int> security_value) {
    int n = security_value.size();
    vector<vector<int>> ans(n, vector<int>(z + 1, -1));
    return stock_helper(0, z, security_value, ans);
}
 
int main() {
    int z;
    cin>>z;
    vector<int> input_data;
    string buffer;
    int data;
    getline(cin, buffer);
    getline(cin, buffer);
    istringstream iss(buffer);
 
    while (iss >> data) {
        input_data.push_back(data);
    }
    
    int no_of_stocks_purchased = securitiesBuying(z, input_data);
    cout << no_of_stocks_purchased;
    
    return 0;
}