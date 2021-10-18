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

int totalPairs(int n, vector<int>& values) {
    int pairs = 0;

    stack<int> monotone;

    for(int i = 0; i < n; i++) {
        int curr_value = values[i];

        if(monotone.empty())
            monotone.push(curr_value);
        else {
            int curr_top = monotone.top();
            //Prev to handle equal values
            //int prev_top = undefined;

            while(!monotone.empty() && curr_value > curr_top) {
                monotone.pop();
                
                // if(prev_top != curr_top)
                pairs++;
                
                //prev_top = curr_top;

                if(!monotone.empty())
                    curr_top = monotone.top();
            }

            pairs += !monotone.empty();
            monotone.push(curr_value);
        }
    }

    return pairs;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> values(n);
    for (int i = 0; i < n; ++i) {
       cin >> values[i];
    }
	
    int answer = totalPairs(n, values);
    // Do not remove below line
    
    cout << answer << endl;
    // Do not print anything after this line
        
    return 0;
}
