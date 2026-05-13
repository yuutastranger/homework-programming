#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;


map<int, list<pair<int, double>>> l_Adj;
map<int, int> pr; 
map<int, bool> used;
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

        if(fl){
            l_Adj[x].push_back(make_pair(y, w));
            l_Adj[y].push_back(make_pair(x, w));
        }
    }
}


void deikstrasAlg(int vertex){
    map<int, double> dist;
    for(auto it = l_Adj.begin(); it != l_Adj.end(); it++){
        dist[it -> first] = INT_MAX;
        pr[it -> first] = -1;
    }
    dist[vertex] = 0;
    for(int i = 0; i < l_Adj.size(); i++){
        int u = -1;
        for(auto it = l_Adj.begin(); it != l_Adj.end(); it++){
            int v = it -> first;
            if(!used[v] && (u == -1 || dist[v] < dist[u])){
               u = v;
            }
        }
        if(dist[u] == INT_MAX){
            break;
        }
        used[u] = 1;
        for(auto it = l_Adj[u].begin(); it != l_Adj[u].end(); it++){
            int to = it -> first;
            double w = it -> second;
            if(dist[u] + w < dist[to]){
                dist[to] = dist[u] + w;
                pr[to] = u;
            }
        }
    }
    for(auto it = l_Adj.begin(); it != l_Adj.end(); it++){
        int v = it -> first;
        if(v == vertex){
            continue;
        }
        cout << "To vertex " << v <<  " distance = " << dist[v] << endl << "Path: ";
        vector<int> p;
        int cur = v;
        while(cur != -1){
            p.push_back(cur);
            cur = pr[cur]; 
        }
        reverse(p.begin(), p.end());
        for(int i = 0; i < p.size(); i++){
            cout << p[i];
            if(i + 1 < p.size()){
                cout << " -> ";
            }
            
        }
        cout << endl;
    }
}


int main(){
    ifstream in("graph_weight.txt");
    in >> N >> M >> orient >> isWeight;
    buildAdjList(in);
    

    int vertex;
    cout << "Enter start vertex(0 - " << N - 1 << "): "; 
    cin >> vertex;
    
    deikstrasAlg(vertex);
    in.close();
    return 0;
}