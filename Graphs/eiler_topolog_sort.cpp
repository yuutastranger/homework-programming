#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

map<int, list<pair<int, double>>> l_Adj;
map<int, list<pair<int, double>>> l_AdjT;
map<int, bool> used;
map<int, int> pr; 
vector<int> path, order;
vector<vector<int>> cycles;
vector<vector<int>> cycles_sort;
int N, M;
bool orient, isWeight;


struct stack{
    int inf;
    stack *next;
};

void push(stack *&h, int x){
    stack *r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

int pop(stack *&h){
    int i = h->inf;
    stack *r = h;
    h = h->next;
    delete r;
    return i;
}

void reverse(stack *&h){
    stack *head1 = NULL;
    while (h){
        push(head1, pop(h));
    }
    h = head1;
}


void buildAdjList(ifstream& in){
    int x, y;
    double w;

    for(int i = 0; i < M; i++){
        in >> x >> y;
        w = 1.0;
        if(isWeight){
            in >> w;
        }
        auto it_x = l_Adj.find(x);
        bool fl = true;

        if(it_x != l_Adj.end()){
            for(auto it_y = it_x -> second.begin(); it_y != it_x -> second.end(); it_y++){
                if(it_y -> first == y){
                    fl = false;
                    break;
                }
            }
        }

        if(orient){
            if(fl){
                l_Adj[x].push_back(make_pair(y, w));
                l_AdjT[y].push_back(make_pair(x, w));
                if(l_Adj.find(y) == l_Adj.end()){
                    l_Adj[y].push_back(make_pair(0, 0));
                    auto it = l_Adj.find(y);
                    it->second.erase(it->second.begin());
                }
                if(l_AdjT.find(x) == l_AdjT.end()){
                    l_AdjT[x].push_back(make_pair(0, 0));
                    auto it = l_AdjT.find(x);
                    it->second.erase(it->second.begin());
                }
            }
        }
        else if(fl){
            l_Adj[x].push_back(make_pair(y, w));
            l_Adj[y].push_back(make_pair(x, w));
        }
    }
}

void printAdjList(){
    for(auto it = l_Adj.begin(); it != l_Adj.end(); it++){
        cout << it -> first << ": ";
        if(isWeight){
            for(auto it_1 = it -> second.begin(); it_1 != it -> second.end(); it_1++){
                cout << "{" << it_1 -> first << ", " << it_1  ->  second << "} ";
            }
        }
        else{
            for(auto it_1 = it  ->  second.begin(); it_1 != it -> second.end(); it_1++){
                cout << it_1 -> first << " ";
            }
        }
        cout << endl;
    }
}
void addCycle(int s_vertex, int e_vertex){
    int cur = e_vertex;
    vector<int> tmp;
    while(cur != s_vertex){
        tmp.push_back(cur);
        cur = pr[cur];
    }
    tmp.push_back(s_vertex);
    reverse(tmp.begin(), tmp.end());
    if(tmp.size() < 3){

        return;
    }
    cycles.push_back(tmp);
    sort(tmp.begin(), tmp.end());
    cycles_sort.push_back(tmp);
}

void findCycle(int vertex){
    used[vertex] = 1;
    for (auto it = l_Adj[vertex].begin(); it != l_Adj[vertex].end(); it++){
        int v = it -> first;
        if(pr[v] == vertex){
            continue;
        } 
        if(!used[v]){
            pr[v] = vertex;
            findCycle(v);
        }  
        else{
            addCycle(v, vertex);
        }
    }
    used[vertex] = 0;
}
void eiler(){
    int v1 = -1, v2 = -1;
    for (auto it = l_Adj.begin(); it != l_Adj.end(); it++){
        int v = it -> first;
        if(it -> second.size() % 2 != 0){
            if (v1 == -1){
                v1 = v;
            }
            else if(v2 == -1){
                v2 = v;
            }
            else{
                cout << "No Eiler cycle";
                return;
            }
        }
    }
    if (v1 != -1){
        l_Adj[v1].push_back({v2, 0});
        l_Adj[v2].push_back({v1, 0});
    }
    stack* vertexes = NULL;
    vector<int> res;
    int start = v1;
    if(v1 == -1){
        start = l_Adj.begin() -> first;
    }
    push(vertexes, start);
    while(vertexes){
        int head = vertexes -> inf;
        if(!l_Adj[head].empty()){
            int u = l_Adj[head].front().first;
            push(vertexes, u);
            l_Adj[head].erase(l_Adj[head].begin());
            for(auto it = l_Adj[u].begin(); it != l_Adj[u].end(); it++){
                if(it -> first == head){
                    l_Adj[u].erase(it);
                    break;
                }
            }
        }
        else{
            res.push_back(pop(vertexes));
        }
    }

    if(v1 != -1){
        for(int i = 0; i < res.size(); i++){
            if(res[i] == v1 && res[i + 1] == v2 || res[i] == v2 && res[i + 1] == v1){
                vector<int> temp;
                for(int j = i + 1; j < res.size(); j++){
                    temp.push_back(res[j]);
                }
                for(int j = 1; j <= i; j++){
                    temp.push_back(res[j]);
                }
                res = temp;
                break;
            }
        }
    }
    bool hasEdges = false;
    for(auto it = l_Adj.begin(); it != l_Adj.end(); it++){
        if(!it -> second.empty()){
            hasEdges = true;
            break;
        }
    }
    if(hasEdges){
        cout << "Graph is not connected, no Eiler cycle" << endl;
        return;
    }
    for(int i = 0; i < res.size(); i++){
        cout << res[i];
        if(i + 1 < res.size()){
            cout << " -> ";
        }
    }
}

void topolog(int vertex){
    
    used[vertex] = 1;
    for (auto it = l_Adj[vertex].begin(); it != l_Adj[vertex].end(); it++){
        int v = it -> first;
        if(!used[v]){
            topolog(v);
        }
    }
    order.push_back(vertex);
}

int main(){
    int choice;
    cout << "Enter what task do you want to check(1 - Eiler, 2 - Topological sort with cycle(3 - without cycle): "; cin >> choice;
    if(choice == 1){
        ifstream in("graph_eiler.txt");
        in >> N >> M >> orient >> isWeight;
        buildAdjList(in);
        eiler();
    }
    else if(choice == 2){
        ifstream in("graph_orient.txt");
        in >> N >> M >> orient >> isWeight;
        buildAdjList(in);
        printAdjList();
        cout << endl;
        bool hasCycle = false;
        for(auto it = l_Adj.begin(); it != l_Adj.end(); it++){
            pr[it -> first] = -1;
        }
        for(auto it = l_Adj.begin(); it != l_Adj.end(); it++){
            if(!used[it -> first]){
                findCycle(it -> first);
            }
        }
        if(!cycles.empty()){
            cout << "Graph has cycles, topological sort is impossible" << endl;
            return 0;
        }
        used.clear(); 
        for(auto it = l_Adj.begin(); it != l_Adj.end(); it++){
            if(!used[it -> first]){   
                topolog(it -> first);
            }
        }
        for (int i = order.size() - 1; i >= 0; i--){
            cout << order[i];
            if(i > 0){
                cout << " -> ";
            }
        }
    }

    else if(choice == 3){
        ifstream in("graph_orient_without_cycles.txt");
        in >> N >> M >> orient >> isWeight;
        buildAdjList(in);
        printAdjList();
        cout << endl;
        bool hasCycle = false;
        for(auto it = l_Adj.begin(); it != l_Adj.end(); it++){
            pr[it -> first] = -1;
        }
        for(auto it = l_Adj.begin(); it != l_Adj.end(); it++){
            if(!used[it -> first]){
                findCycle(it -> first);
            }
        }
        if(!cycles.empty()){
            cout << "Graph has cycles, topological sort is impossible" << endl;
            return 0;
        }
        used.clear(); 
        for(auto it = l_Adj.begin(); it != l_Adj.end(); it++){
            if(!used[it -> first]){   
                topolog(it -> first);
            }
        }
        for (int i = order.size() - 1; i >= 0; i--){
            cout << order[i];
            if(i > 0){
                cout << " -> ";
            }
        }
    }
    return 0;
}