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

void printUnadjVertex(int vertex){
    for(auto it = l_Adj.begin(); it != l_Adj.end(); it++){
        int v = it -> first;
        if(v == vertex){
            continue;
        }
        bool isAdj = false;
        for(auto it_1 = l_Adj[vertex].begin(); it_1 != l_Adj[vertex].end(); it_1++){
            if(it_1 -> first == v){
                isAdj = true;
                break;

            }
        }
        if(!isAdj){
            cout << v << " ";
        }
    }
    cout << endl;
    
}

void insertEdge(int vertex_1, int vertex_2){
    if(vertex_1 == vertex_2){
        cout << "Can't add loop!";
        return;
    }

    double w = 1.;
    for(auto it = l_Adj[vertex_1].begin(); it != l_Adj[vertex_1].end(); it++){
        if(it -> first == vertex_2){
            cout << "Edge already exists!";
            return;
        }
    }
    l_Adj[vertex_1].push_back(make_pair(vertex_2, w));
    if(l_Adj.find(vertex_2) == l_Adj.end()){
       l_Adj[vertex_2]; 
    }
}

void sdegApproach(int vertex){
    int k = 0;
    for(auto it = l_Adj.begin(); it != l_Adj.end(); it++){
        int v = it -> first;
        for(auto it_1 = l_Adj[v].begin(); it_1 != l_Adj[v].end(); it_1++){
            if(it_1 -> first == vertex){
                k++;
                break;

            }
        }
    }
    cout << k << endl;
}

void DFS(int vertex){
    used[vertex] = 1;
    path.push_back(vertex);
    for (auto it = l_Adj[vertex].begin(); it != l_Adj[vertex].end(); it++){
        if(!used[it -> first]){
            DFS(it -> first);
        }   
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

void dfs1(int vertex){
    used[vertex] = 1;
    for (auto it = l_Adj[vertex].begin(); it != l_Adj[vertex].end(); it++){
        int v = it -> first;
        if(!used[v]){
            dfs1(v);
        }
    }
    order.push_back(vertex);
}

void dfs2(int vertex){
    used[vertex] = 1;
    path.push_back(vertex);
    for (auto it = l_AdjT[vertex].begin(); it != l_AdjT[vertex].end(); it++){
        int v = it -> first;
        if(!used[v]){
            dfs2(v);
        }
    }
}


int main(){
    int numTask;
    cout << "What task(1-5) do you want to check? "; cin >> numTask;

    if(numTask == 1){
        ifstream in("graph.txt");
        in >> N >> M >> orient >> isWeight;
        buildAdjList(in);
        int vertex;
        cout << "Insert the vertex(0 - " << N - 1 <<") you want to find that don't have adjacency: "; cin >> vertex;
        printUnadjVertex(vertex);
        cout << endl;
        printAdjList();
        in.close();
    }

    else if(numTask == 2){
        ifstream in("graph_orient.txt");  
        in >> N >> M >> orient >> isWeight;
        buildAdjList(in);

        int vertex_A, vertex_B;
        cout << "Insert your vertex A from 0 to " << N - 1<< ": "; cin >> vertex_A; cout << endl;
        cout << "Insert your vertex B from 0 to " << N - 1<< ": "; cin >> vertex_B; cout << endl;
        printAdjList();
        cout << endl;
        insertEdge(vertex_A, vertex_B);
        cout << endl;
        printAdjList();
        in.close();
    }
    
    else if(numTask == 3){
        ifstream in("graph_orient.txt");  
        in >> N >> M >> orient >> isWeight;
        buildAdjList(in);

        int vertex;
        cout << "Insert the vertex(0 - " << N - 1<<") for which you want to calculate the indegree: "; cin >> vertex;
        sdegApproach(vertex);
        cout << endl;
        printAdjList();
        in.close();
    }
    else if(numTask == 4){
        ifstream in("graph.txt");  
        in >> N >> M >> orient >> isWeight;
        buildAdjList(in);

        for(auto it = l_Adj.begin(); it != l_Adj.end(); it++){
            pr[it -> first] = -1;
        }
        for(auto it = l_Adj.begin(); it != l_Adj.end(); it++){
            if(!used[it -> first]){
                findCycle(it -> first);
            }
        }
        for (int i = 0; i < cycles_sort.size(); i++){
            for (int j = i + 1; j < cycles_sort.size(); j++){
                if(cycles_sort[i] == cycles_sort[j]){
                    cycles.erase(cycles.begin() + j);
                    cycles_sort.erase(cycles_sort.begin() + j);
                    j--;
                }
            }
        }
        if (cycles.empty()){
            cout << "No cycles in graph" << endl;
        }
        else{
            for(auto& c : cycles){
                for(int v : c){
                    cout << v << " -> ";
                }
                cout << c[0] << endl;
            }
        }
    in.close(); 
    }
    else if(numTask == 5){
        ifstream in("graph_orient.txt");  
        in >> N >> M >> orient >> isWeight;
        buildAdjList(in);
        for(auto it = l_Adj.begin(); it != l_Adj.end(); it++){
            if(!used[it -> first]){
                dfs1(it -> first);
            }
        

        }
        used.clear();
        for(int i = order.size() - 1; i >= 0; i--){
            int v = order[i];
            if(!used[v]){
                path.clear();
                dfs2(v);
                for(int c : path){
                    cout << c << " ";
                }
                cout << endl;
            }
        }
        in.close();
    }
    return 0;
}