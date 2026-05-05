#include <iostream>
#include <fstream>
#include <map>
#include <list>
using namespace std;

map<int, list<pair<int, double>>> buildAdjList(int N, int M, ifstream& in, bool orient, bool isWeight){
    map<int, list<pair<int, double>>> l_Adj;
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
                if(l_Adj.find(y) == l_Adj.end()){
                    l_Adj[y].push_back(make_pair(0, 0));
                    auto it = l_Adj.find(y);
                    it -> second.erase(it -> second.begin());
                }
            }
        } 
        else if(fl){
            l_Adj[x].push_back(make_pair(y, w));
            l_Adj[y].push_back(make_pair(x, w));
        }
    }
    return l_Adj;
}

void printAdjList(map<int, list<pair<int, double>>>& l_Adj, bool isWeight){
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

void printUnadjVertex(map<int, list<pair<int, double>>>& l_Adj, int vertex){
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

void insertEdge(map<int, list<pair<int, double>>>& l_Adj, int vertex_1, int vertex_2){
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

void sdegApproach(map<int, list<pair<int, double>>>& l_Adj, int vertex){
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


int main(){
    int numTask;
    int N, M;
    bool orient, isWeight;
    cout << "What task(1-5) do you want to check? "; cin >> numTask;

    if(numTask == 1){
        ifstream in("graph.txt");
        in >> N >> M >> orient >> isWeight;
        auto l_Adj = buildAdjList(N, M, in, orient, isWeight);
        int vertex;
        cout << "Insert the vertex you want to find adjacency: "; cin >> vertex;
        printUnadjVertex(l_Adj, vertex);
        in.close();
    }
    else if(numTask == 2){
        ifstream in("graph_orient.txt");  
        in >> N >> M >> orient >> isWeight;
        auto l_Adj = buildAdjList(N, M, in, orient, isWeight);

        int vertex_A, vertex_B;
        cout << "Insert your vertex A from 0 to " << N - 1<< ": "; cin >> vertex_A; cout << endl;
        cout << "Insert your vertex B from 0 to " << N - 1<< ": "; cin >> vertex_B; cout << endl;
        printAdjList(l_Adj, isWeight);
        cout << endl;
        insertEdge(l_Adj, vertex_A, vertex_B);
        cout << endl;
        printAdjList(l_Adj, isWeight);
        in.close();
    }
    else if(numTask == 3){
        ifstream in("graph_orient.txt");  
        in >> N >> M >> orient >> isWeight;
        auto l_Adj = buildAdjList(N, M, in, orient, isWeight);

        int vertex;
        cout << "Insert the vertex for which you want to calculate the indegree: "; cin >> vertex;
        sdegApproach(l_Adj, vertex);
        cout << endl;
        printAdjList(l_Adj, isWeight);
        in.close();
    }


    
    return 0;
}