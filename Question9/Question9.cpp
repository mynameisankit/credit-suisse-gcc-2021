#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define undefined INT_MAX

int add(int a, int b) {
    return (a == INT_MAX || b == INT_MAX) ? INT_MAX : (a + b);
}

int minTime_helper(int pos, int mask_bankers, int c, int b, vector<vector<int>> &time, vector<vector<int>> &dp) {
    if(pos == c) 
        return 0;
    else if(dp[pos][mask_bankers] != -1) 
        return dp[pos][mask_bankers];
    else {
        int curr_ans = undefined;

        //Choose a banker and use him
        for(int i = 0; i < b; i++) {
            //If we have already used this banker, then skip
            if(mask_bankers & ( 1 << i ))
                continue;

            //Otherwise, use this banker
            int new_mask = mask_bankers | (1 << i);

            //Use the banker till jth position            
            int curr_sum = 0;
            for(int j = pos; j < c; j++) {
                curr_sum += time[i][j];
                curr_ans = min(curr_ans, add(minTime_helper(j + 1, new_mask, c, b, time, dp), curr_sum));
            }
        }

        dp[pos][mask_bankers] = curr_ans;
        return curr_ans;
    }
}

int bankersAndClients(int c, int b, vector<vector<int>> &time) {
    vector<vector<int>> dp(c, vector<int>(1024, -1));
    return minTime_helper(0, 0, c, b, time, dp);
}

int main(){
    int b,c;
    cin >> c>>b;
    int answer;
    vector<vector<int>> time(b,vector<int>(c));
    for(int i = 0; i < b; i++){
        
        for(int j = 0;j < c;j++){
          cin>>time[i][j];
        }
    }
	answer = bankersAndClients(c,b,time);
    // Do not remove below line
    cout << answer << endl;
    // Do not print anything after this line
        
    return 0;
}