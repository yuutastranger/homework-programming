// Дан список целых чисел. Построить AVL дерево
// Определить высоту дерева. Вывести элементы дерева в порядке возрастания.
#include <iostream>
using namespace std;

struct tree{
    int inf;
    int height;
    tree *left;
    tree *right;
    tree *parent;
};

tree *node(int x){
    tree *n = new tree;
    n -> inf = x;
    n -> height = 0;
    n -> left = n -> right = NULL;
    n -> parent = NULL;
    return n;
}

int getHeight(tree *tr){
    if(!tr){
        return -1;
    }
    return tr -> height;
}

void updateHeight(tree *tr){
    if(tr){
        tr -> height = max(getHeight(tr -> left), getHeight(tr -> right)) + 1;
    }
}

int balanceFactor(tree *tr){
    if(!tr){
        return 0;
    }
    return getHeight(tr -> left) - getHeight(tr -> right);
}

void rotateRight(tree *&root, tree *y){
    tree *x = y -> left;
    tree *temp = x -> right;
    x -> parent = y -> parent;

    if(!y -> parent){
        root = x;
    }
    else if(y == y -> parent -> left){
        y -> parent -> left = x;
    }
    else{
        y -> parent -> right = x;
    }

    x -> right = y;
    y -> parent = x;
    y -> left = temp;

    if(temp){
        temp -> parent = y;
    }

    updateHeight(y);
    updateHeight(x);
}

void rotateLeft(tree *&root, tree *x){
    tree *y = x -> right;
    tree *temp = y -> left;
    y -> parent = x -> parent;

    if(!x -> parent){
        root = y;
    }
    else if(x == x -> parent -> left){
        x -> parent -> left = y;
    }
    else{
        x -> parent -> right = y;
    }

    y -> left = x;
    x -> parent = y;
    x -> right = temp;

    if(temp){
        temp -> parent = x;
    }

    updateHeight(x);
    updateHeight(y);
}

void balance(tree *&root, tree *n){
    while(n){
        updateHeight(n);
        int bf = balanceFactor(n);
        if(bf > 1){
            if(balanceFactor(n -> left) < 0){
                rotateLeft(root, n -> left);
            }
            rotateRight(root, n);
            return;
        }
        if(bf < -1){
            if(balanceFactor(n -> right) > 0){
                rotateRight(root, n -> right);
            }
            rotateLeft(root, n);
            return;
        }
        n = n -> parent;
    }
}

void insert(tree *&tr, int x){
    tree *n = node(x);
    if(!tr){
        tr = n;
        return;
    }
    tree *y = tr;
    while(y){
        if(n -> inf > y -> inf){
            if(y -> right){
                y = y -> right;
            }
            else{
                n -> parent = y;
                y -> right = n;
                break;
            }
        }
        else if(n -> inf < y -> inf){
            if(y -> left){
                y = y -> left;
            }
            else{
                n -> parent = y;
                y -> left = n;
                break;
            }
        }
        else{
            delete n;
            return;
        }
    }
    balance(tr, n -> parent);
}

void inorder(tree *tr){
    if(tr){
        inorder(tr -> left);
        cout << tr -> inf << endl;
        inorder(tr -> right);    }
}

int main(){
    tree *tr = NULL;
    int n, x;
    cout << "n = "; cin >> n;
    cout << "Please don't insert same digits multiple times" << endl;
    for(int i = 0; i < n; i++){
        cout << i + 1 << " element = ";
        cin >> x;
        insert(tr, x);
    }
    cout << endl;
    cout << "Height of tree = " << getHeight(tr) << endl << endl;
    cout << "Inorder traversal:" << endl;
    inorder(tr);

    return 0;
}