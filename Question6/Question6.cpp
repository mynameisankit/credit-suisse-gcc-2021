#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
using namespace std;

struct Node {
    string name;
    vector<int> department;
    int size;
    Node* parent;

    Node(string employee_name, int dept) {
        department = vector<int>(3, 0);
        department[dept - 1] = 1;
        name = employee_name;
        size = 1;
        parent = this;
    }
};

class UnionFind {
public:
    map<string, Node *> mapping;
    vector<int> limits;

    UnionFind(vector<pair<string, int>> &employees, vector<int> bounds) {
        //Make set operations
        for(int i = 0; i < (int)employees.size(); i++) {
            string curr = employees[i].first;
            int department = employees[i].second;
            
            mapping.insert({curr, new Node(curr, department)});
        }

        limits = bounds;
    }

    ~UnionFind() {
        for(auto it = mapping.begin(); it != mapping.end(); it++)
            delete (it->second);
    }

    Node* find(string &name) {
        Node* u = mapping.find(name)->second;

        if(u->parent == u)
            return u;
        else {
            u->parent = find(u->parent->name);
            
            // u->size = u->parent->size;
            // for(int i = 0; i < 3; i++)
            //     (u->department)[i] = (u->parent->department)[i];

            return u->parent;
        }
    }

    void set_union(string &u, string &v) {
        Node* par_u = find(u);
        Node* par_v = find(v);

        bool is_valid_union = true;
        
        //Check the sizes
        for(int i = 0; i < 4; i++) {
            int new_size;
            if(i == 0)
                new_size = par_u->size + par_v->size;
            else
                new_size = par_u->department[i - 1] + par_v->department[i - 1];

            is_valid_union &= (new_size <= limits[i]);
        }

        //Check if same parents or not
        is_valid_union &= (par_u->name != par_v->name);

        //If valid, then proceed
        if(is_valid_union) {
            if(par_u->size > par_v->size) {
                par_v->parent = par_u;
                
                par_u->size += par_v->size;
                for(int i = 0; i < 3; i++)
                    (par_u->department)[i] += (par_v->department)[i];
            }
            else {
                par_u->parent = par_v;
                
                par_v->size += par_u->size;
                for(int i = 0; i < 3; i++)
                    (par_v->department)[i] += (par_u->department)[i];
            }
        }

        return;
    }

    void print(void) {
        for(auto it = mapping.begin(); it != mapping.end(); it++) {
            Node* curr = it->second;
            
            cout << "[\n";
            cout << "\tName : " << curr->name << "\n";
            cout << "\tParent Name : " << curr->parent->name << "\n";
            cout << "\tSet Size : " << curr->size << "\n";
            cout << "\tDepartment 1 : " << curr->department[0] << "\n";
            cout << "\tDepartment 2 : " << curr->department[1] << "\n";
            cout << "\tDepartment 3 : " << curr->department[2] << "\n";
            cout << "],";
        }
        cout << "\n";
    }
};

void theHackathon(int n, int m, int a, int b, int f, int s, int t) {
    vector<pair<string, int>> employees(n);
    for(int i = 0; i < n; i++) {
        string name;
        int department;
        cin >> name >> department;
        employees[i] = {name, department};
    }

    UnionFind groups(employees, {b, f, s, t});

    string x, y;
    for(int i = 0; i < m; i++) {
        cin >> x >> y;
        groups.set_union(x, y);
    }
    
    int largest_grp = 0;
    for(int i = 0; i < n; i++)
        largest_grp = max<int>(groups.find(employees[i].first)->size, largest_grp);

    if(largest_grp >= a) {
        priority_queue <string, vector<string>, greater<string>> names;
        
        for(int i = 0; i < n; i++) {
            if(groups.find(employees[i].first)->size == largest_grp)
                names.emplace(employees[i].first);
        }

        //sort(names.begin(), names.end());
        // for(auto it = names.begin(); it != names.end(); it++)
        //     cout << *it << "\n";
        while(!names.empty()) {
            cout << names.top() << "\n";
            names.pop();
        }
    }
    else
        cout << "no groups\n";

    return;
}

/* Do not change - Preset */
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, a, b, f, s, t;
    cin >> n >> m >> a >> b >> f >> s >> t;

    theHackathon(n, m, a, b, f, s, t);

    return 0;
}