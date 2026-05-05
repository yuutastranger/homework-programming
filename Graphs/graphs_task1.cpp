#include <iostream>
#include <fstream>
#include <map>
#include <list>
using namespace std;

map<int, list<pair<int, double>>> buildAdjList(int N, int M, ifstream& in, bool orient, bool isWeight){
    map<int, list<pair<int, double>>> l_Adj;
    int x, y;
    double w;

    for (int i = 0; i < M; i++){
        in >> x >> y;
        w = 1.0;
        if (isWeight){
            in >> w;
        }
        auto it_x = l_Adj.find(x);
        bool fl = true;

        if (it_x != l_Adj.end()){
            for (auto it_y = it_x -> second.begin(); it_y != it_x -> second.end(); it_y++){
                if (it_y -> first == y){
                    fl = false;
                    break;
                }
            }
        }

        if (orient){
            if (fl){
                l_Adj[x].push_back(make_pair(y, w));
                if (l_Adj.find(y) == l_Adj.end()){
                    l_Adj[y].push_back(make_pair(0, 0));
                    auto it = l_Adj.find(y);
                    it -> second.erase(it -> second.begin());
                }
            }
        } 
        else if (fl){
            l_Adj[x].push_back(make_pair(y, w));
            l_Adj[y].push_back(make_pair(x, w));
        }
    }
    return l_Adj;
}

void printAdjList(map<int, list<pair<int, double>>>& l_Adj, bool isWeight){
    for (auto it = l_Adj.begin(); it != l_Adj.end(); it++){
        cout << it -> first << ": ";
        if (isWeight){
            for (auto it_1 = it -> second.begin(); it_1 != it -> second.end(); it_1++){
                cout << "{" << it_1 -> first << ", " << it_1  ->  second << "} ";
            }
        }
        else{
            for (auto it_1 = it  ->  second.begin(); it_1 != it -> second.end(); it_1++){
                cout << it_1 -> first << " ";
            }
        }
        cout << endl;
    }
}

int main(){
    ifstream in("graph.txt");
    int N, M;
    bool orient, isWeight;
    in >> N >> M >> orient >> isWeight;

    auto l_Adj = buildAdjList(N, M, in, orient, isWeight);
    printAdjList(l_Adj, isWeight);
    return 0;
}