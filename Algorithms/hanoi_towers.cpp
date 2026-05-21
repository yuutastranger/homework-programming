#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;


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

int stackSize(stack *h){
    int count = 0;
    while(h != NULL){
        h = h -> next; 
        count++; 
    }
    return count;
}


void screenPrint(stack *fr_t, stack *sc_t, stack *th_t, int n){
    auto toVector = [](stack *h){
        vector<int> v;
        while(h != NULL){
            v.push_back(h -> inf);
            h = h -> next;
        }
        reverse(v.begin(), v.end());
        return v;
    };

    vector<int> t1 = toVector(fr_t);
    vector<int> t2 = toVector(sc_t);
    vector<int> t3 = toVector(th_t);
    int width = n * 2;
    int half = width / 2;

    for(int row = n - 1; row >= 0; row--){
        auto printRow = [&](vector<int> &t){
            int disk = (row < t.size()) ? t[row] : 0;
            if(disk == 0){
                for(int i = 0; i < half; i++){
                    cout << " ";
                }
                cout << "||";
                for(int i = 0; i < half; i++){
                    cout << " ";
                }
            }
            else{
                int diskWidth = disk * 2;
                int spaces = (width - diskWidth) / 2;
                int leftHalf = diskWidth / 2;
                int rightHalf = diskWidth - leftHalf;
                for(int i = 0; i < spaces; i++){
                    cout << " ";
                }
                for(int i = 0; i < leftHalf; i++){
                    cout << "0";
                }
                cout << "||";
                for(int i = 0; i < rightHalf; i++){
                    cout << "0";
                }
                for(int i = 0; i < spaces; i++){
                    cout << " ";
                }
            }
        };

        printRow(t1);
        cout << "     ";
        printRow(t2);
        cout << "     ";
        printRow(t3);
        cout << endl;
    }

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < width + 2; j++){
            cout << "=";
        }
        if(i < 2){
            cout << "     ";
        }
    }
    cout << endl;
}

bool towerCorrection(int &tower, int &disk, stack *&fr_t, stack *&sc_t, stack *&th_t){
    cout << "Where do you want to get the disk from? " << ((fr_t) ? "1 " : "") << ((sc_t) ? "2 " : "") << ((th_t) ? "3 " : "") << endl;
    cin >> tower;

    if(tower == 1 && fr_t){
        disk = pop(fr_t);
        return true;
    }
    else if(tower == 2 && sc_t){
        disk = pop(sc_t);
        return true;
    }
    else if(tower == 3 && th_t){
        disk = pop(th_t);
        return true;
    }
    return false;
}

bool moveCorrection(int &move, int &disk, int tower, stack *&fr_t, stack *&sc_t, stack *&th_t){
    cout << "Where do you want to put the disk? " << ((1 != tower) ? "1 " : "") << ((2 != tower) ? "2 " : "") << ((3 != tower) ? "3 " : "") << endl;
    cin >> move;
    
    if(move == tower){
        return false;
    }
    if(move == 1 && (fr_t == NULL || fr_t -> inf > disk)){
        push(fr_t, disk);
        return true;
    }
    else if(move == 2 && (sc_t == NULL || sc_t -> inf > disk)){
        push(sc_t, disk);
        return true;
    }
    else if(move == 3 && (th_t == NULL || th_t -> inf > disk)){
        push(th_t, disk);
        return true;
    }
    return false;
}

void hanoiGame(int n){
    stack *fr_t = NULL;
    stack *sc_t = NULL;
    stack *th_t = NULL;
    for(int i = 0; i < n; i++){
        push(fr_t, n - i);
    }
    screenPrint(fr_t, sc_t, th_t, n);
    bool fl = false;

    while(stackSize(sc_t) != n && stackSize(th_t) != n){
        int move, tower, disk;

        while(!towerCorrection(tower, disk, fr_t, sc_t, th_t)){
            screenPrint(fr_t, sc_t, th_t, n);
            cout << "Error! Tower is empty or wrong number. Try again" << endl;
        }

        while(!moveCorrection(move, disk, tower, fr_t, sc_t, th_t)){
            screenPrint(fr_t, sc_t, th_t, n);
            cout << "Error! Can't place bigger disk on smaller one or wrong number. Try again" << endl;
        }

        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        screenPrint(fr_t, sc_t, th_t, n);
        if(stackSize(sc_t) == n || stackSize(th_t) == n){
            fl = true;
            break;
        }
    }

    if(fl == true){
        cout << "Congrats! You won!" << endl;
    }
}

int main(){
    int n;
    cout << "Please enter number of disks you want to play from 4 to 10: "; cin >> n;
    hanoiGame(n);
    system("pause");
    return 0;
}