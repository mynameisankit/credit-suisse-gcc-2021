#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")

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

#define LIMIT 1000000007

int power(long long int base, int exponent, int MOD) {
    if(base == 0 || base == 1)
		return base % MOD;

    if(exponent == 0)
		return 1;
 
    long long int res = 1;
 
    while(exponent) {
        if(exponent % 2)
            res = (res * base) % MOD;

        base = (base * base) % MOD;
		exponent /= 2;
    }

    return res;
}

struct Node {
    int num, rank;
    Node* parent; 

    Node(int &num) {
        this->num = num;
        parent = this;
        rank = 0;
    }
};

class UnionFind {
public:
    vector<Node *> mapping;

    UnionFind(int n) {
        mapping = vector<Node *>(n + 1, nullptr);
    }

    void make_set(int node) {
        if(mapping[node] == nullptr)
            mapping[node] = new Node(node);

        return;
    }

    Node* find(int u) {
        Node* curr = mapping[u];

        if(curr->parent == curr) 
            return curr;
        else {
            curr->parent = find(curr->parent->num);
            return curr->parent;
        }
    }

    Node* set_union(int u, int v) {
        Node* par_u = find(u);
        Node* par_v = find(v);

        //If they are in the same group, then skip
        if(par_u == par_v)
            return par_u;

        if(par_u->rank > par_v->rank) {
            par_v->parent = par_u;
            return par_u;
        }
        else {
            if(par_u->rank == par_v->rank)
                par_v->rank += 1;

            par_u->parent = par_v;
            return par_v;
        }
    }
};

class Prime_Factorization {
public:
    vector<int> spf;
    int MAXN;

    Prime_Factorization(int n) {
        MAXN = n + 1;

        spf = vector<int>(MAXN);
        
        spf[1] = 1;
        for (int i = 2; i < MAXN; i++)
            spf[i] = i;

        for (int i = 4; i < MAXN; i += 2)
            spf[i] = 2;
 
        for (int i = 3; i*i < MAXN; i++) {
            if (spf[i] == i) {
                for (int j = i*i; j < MAXN; j += i)
                    if (spf[j]==j)
                        spf[j] = i;
            }
        }
    }

    list<int> getFactorization(int x) {
        list<int> ret;
        
        while (x != 1) {
            ret.push_back(spf[x]);
            x = x / spf[x];
        }

        return ret;
    }
};

void countStablePartitions(int n, vector<int>& values) {
    bool does_array_have_one = false;
    int arr_max = INT_MIN;
    
    for(int i = 0; i < n; i++) {
        if(values[i] == 1)
            does_array_have_one = true;

        arr_max = max<int>(arr_max, values[i]);
    }
    
    UnionFind *groups = new UnionFind(arr_max);
    Prime_Factorization *factorization = new Prime_Factorization(arr_max);

    //Make groups with common factors
    for(int i = 0; i < n; i++) {
        int curr_value = values[i];
        
        if(curr_value == 1)
            continue;

        groups->make_set(values[i]);

        list<int> factors = factorization->getFactorization(curr_value);
        for(list<int>::iterator it = factors.begin(); it != factors.end(); it++) {
            groups->make_set(*it);
            groups->set_union(*it, values[i]);
        }
    }

    set<Node *> distinct_set_rep;
    for(int i = 0; i < values.size(); i++) {
        if(values[i] == 1)
            continue;
        
        distinct_set_rep.insert(groups->find(values[i]));
    }

    int count = distinct_set_rep.size();
    if(does_array_have_one)
        count += 1;

    int ans = power(2, count, LIMIT) - 2;

    if(ans == 0) 
        cout << "NO\n0\n";
    else
        cout << "YES\n" << ans << "\n";

    return;
}

int main() {
   int n;
   cin >> n;
   
   vector<int> values(n);
   for (int i = 0; i < n; ++i) {
        cin >> values[i];
   }

   countStablePartitions(n, values);
   return 0;
}