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

void printUnadjPicks(map<int, list<pair<int, double>>>& l_Adj, int pick){
    for(auto it = l_Adj.begin(); it != l_Adj.end(); it++){
        int v = it -> first;
        if(v == pick){
            continue;
        }
        bool isAdj = false;
        for(auto it_1 = l_Adj[pick].begin(); it_1 != l_Adj[pick].end(); it_1++){
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

void insertEdge(map<int, list<pair<int, double>>>& l_Adj, int pick_1, int pick_2){
    if(pick_1 == pick_2){
        cout << "Can't add loop!";
        return;
    }

    double w = 1.;
    for(auto it = l_Adj[pick_1].begin(); it != l_Adj[pick_1].end(); it++){
        if(it -> first == pick_2){
            cout << "Edge already exists!";
            return;
        }
    }
    l_Adj[pick_1].push_back(make_pair(pick_2, w));
    if(l_Adj.find(pick_2) == l_Adj.end()){
       l_Adj[pick_2]; 
    }
    
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
        int pick;
        cout << "Insert the pick you want to find adjacency: "; cin >> pick;
        printUnadjPicks(l_Adj, pick);
        in.close();
    }
    else if(numTask == 2){
        ifstream in("graph_orient.txt");  
        in >> N >> M >> orient >> isWeight;
        auto l_Adj = buildAdjList(N, M, in, orient, isWeight);

        int pick_A, pick_B;
        cout << "Insert your pick A from 0 to " << N - 1<< ": "; cin >> pick_A; cout << endl;
        cout << "Insert your pick B from 0 to " << N - 1<< ": "; cin >> pick_B; cout << endl;
        printAdjList(l_Adj, isWeight);
        cout << endl;
        insertEdge(l_Adj, pick_A, pick_B);
        cout << endl;
        printAdjList(l_Adj, isWeight);
    }



    
    return 0;
}