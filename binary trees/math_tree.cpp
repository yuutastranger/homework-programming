#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

struct tree{
    char inf;
    tree *right;
    tree *left;
    tree *parent;
};

tree *node(char x){
    tree *n = new tree;
    n -> inf = x;
    n -> left = n -> right = NULL;
    n -> parent = NULL;
    return n;
}

tree *createTree(string str){
    tree *tr = NULL;
    for(int i = 0; i < str.length(); i++){
        tree *n = node(str[i]);
        if(str[i] == '-' || str[i] == '+'){
            tr -> parent = n;
            n -> left = tr;
            tr = n;
        }
        else if(str[i] == '/' || str[i] == '*'){
            if(isdigit(tr -> inf)){
                tr -> parent = n;
                n -> left = tr;
                tr = n;
            }
            else{
                n -> parent = tr;
                n -> left = tr -> right;
                tr -> right -> parent = n;
                tr -> right = n;
            }
        }
        else{
            if(!tr){
                tr = n;
            }
            else{
                if(!tr -> right){
                    n -> parent = tr;
                    n -> left = tr -> right;
                    tr -> right = n;
                }
                else{
                    tree *x = tr -> right;
                    while(x -> right){
                        x = x -> right;
                    }
                    n -> parent = x -> parent;
                    x -> right = n;
                }
            }
        }
    }
    return tr;
    
}

void postorder(tree *tr){
    if(tr){
        postorder(tr -> left);
        postorder(tr -> right);
        cout << tr -> inf;
    }
}

void preorder(tree *tr){
    if(tr){
        cout << tr -> inf;
        preorder(tr -> left);
        preorder(tr -> right);
    }
}


int main(){
    string str;
    getline(cin, str);
    string sign = "+-/*0123456789()";
    bool fl = true;
    for(int i = 0; i < str.length(); i++){
        if(sign.find_first_of(str[i]) == string::npos){
            fl = false;
            break;
        }
    }
    if(!fl){
        cout << "Error";
    }
    else{
        tree *tr = createTree(str);
        cout << "Prefix notation: "; preorder(tr); cout << endl;
        cout << "Postfix notation: "; postorder(tr); cout << endl;
    }
    return 0;
}