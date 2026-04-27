// Дан список целых чисел. Построить дерево бинарного поиска. Определить высоту дерева.
// Вывести все четные листья. Если таких нет, вывести сообщение об этом.
// Найти средний по значению лист и удалить его "деда".
// 5 3 7 1 9 4 2 8 6 0

#include <iostream>
#include <vector>
using namespace std;

struct tree{
    int inf;
    tree *right;
    tree *left;
    tree *parent;
};

tree *node(int x){
    tree *n = new tree;
    n -> inf = x;
    n -> left = n -> right = NULL;
    n -> parent = NULL;
    return n;
}

void insert(tree *&tr, int x){
    tree *n = node(x);
    if(!tr){
        tr = n;
    }
    else{
        tree *y = tr;
        while(y){
            if (n -> inf > y -> inf){
                if (y -> right){
                    y = y -> right;
                }
                else {
                    n -> parent = y;
                    y -> right = n;
                    break;
                }
            }
            else if(n -> inf  < y -> inf){
                if (y -> left){
                    y = y -> left;
                }
                else{
                    n -> parent = y;
                    y -> left = n;
                    break;
                }
            }
            else{
                break;
            }
        }
    }
}
void inorder(tree *tr){
    if (tr){
        inorder(tr -> left);
        cout << tr -> inf << endl;
        inorder(tr -> right);
    }
}

tree *find(tree *tr, int x){
    if(!tr || x == tr -> inf){
        return tr;
    }
    if (x < tr -> inf){
        return find(tr -> left, x);
    }
    else{
        return find(tr -> right, x);
    }
}

tree *Min(tree *tr){
    if (!tr -> left){
        return tr;
    }
    else{
        return Min(tr -> left);
    }
}

tree *Max(tree *tr){
    if(!tr -> right) {
        return tr;
    }
    else{
        return Max(tr -> right);
    }
}

tree *Next(tree *tr, int x){
    tree *n = find(tr, x);
    if (n -> right){
        return Min(n -> right);
    }
    tree *y = n -> parent;
    while(y && n == y -> right){
        n = y;
        y = y -> parent;
    }
    return y;
}

tree *Prev(tree *tr, int x){
    tree *n = find(tr, x);
    if (n -> left){
        return Max(n -> left);
    } 
    tree *y = n -> parent;
    while (y && n == y -> left){
        n = y;
        y = y -> parent;
    }
    return y;
}

void Delete(tree *&tr, tree *v){
    tree *p = v -> parent;
    if(!p && !v -> left && !v -> right) {
        tr = NULL;
    }
    else if(!v -> left && !v -> right){
        if(p -> left == v){
            p -> left = NULL;
        }
        if(p -> right == v){
            p -> right = NULL;
        }
        delete v;
    }
    else if(!v -> left || !v -> right){
        if(!p){
            if(!v -> left){
                tr = v -> right;
                v -> parent = NULL;
            }
            else{
                tr = v -> left;
                v -> parent = NULL;
            }
        }
        else{
            if(!v -> left){
                if(p -> left == v){
                    p -> left = v -> right;
                }
                else{
                    p -> right = v -> right;
                }
                v -> right -> parent = p; 
            }
            else{
                if (p -> left == v){
                    p -> left = v -> left;
                }
                else{
                    p -> right = v -> left;
                }
                v -> left -> parent = p;
            }
            delete v;
        }
    }
    else{
        tree *succ = Next(tr, v -> inf);
        v -> inf = succ -> inf;
        if(succ -> parent -> left == succ){
            succ -> parent -> left = succ -> right;
        }
        if(succ -> right){
            succ -> right -> parent = succ -> parent;
        }
        else{
            succ -> parent -> right = succ -> right;
            if(succ -> right){
                succ -> right -> parent = succ -> parent;
            }
        }
        delete succ;
    }
}

int height(tree *tr){
    if(!tr){
        return 0;
    }
    int left = height(tr -> left);
    int right = height(tr -> right);
    return max(left, right) + 1;
}

void even_leaf(tree *tr, bool &found){
    if(!tr){
        return;
    }
    even_leaf(tr->left, found);
    even_leaf(tr->right, found);
    if(tr->left == NULL && tr->right == NULL && tr->inf % 2 == 0){
        cout << tr->inf << endl;
        found = true;
    }
}


void leaves_array(tree *tr, vector <tree*>&leaves){
    if(!tr){
        return ;
    }
    leaves_array(tr -> left, leaves);
    if(!tr -> left && !tr -> right){
        leaves.push_back(tr);
    }
    leaves_array(tr -> right, leaves);
}


void median_value(tree *&tr, vector <tree*>&temp){
    if (temp.empty()){
        return ;
    }
    tree *grandpa = NULL;
    tree *mid = temp[temp.size()/2];
    string answer;
    if(mid -> parent && mid -> parent -> parent){
        grandpa = mid -> parent -> parent;
    }
    if(grandpa -> parent == NULL){
        cout << "We should delete the root of the tree, do you want to procceed deletion? (y/n) ";
        cin >> answer;
        if(answer == "y"){
            Delete(tr, grandpa);
        }
        if(answer == "n"){
            cout << "No deletion" << endl;
            return ;
        }
    }
    if(grandpa){
        Delete(tr, grandpa); 
    }
    else{
        cout << "It seems that here's no grandfather ¯\\_(ツ)_/¯" << endl;
    }
    if(tr == NULL){
        cout << "You deleted the root!" << endl;
    }
}

int main(){
    tree *tr = NULL;
    bool found = false;
    int n, x;
    cout << "Your n = "; cin >> n;
    cout << "Please do not insert same digits mupltiple times!" << endl;
    for(int i = 0; i < n; i++){
        cout << i + 1 << " element = ";
        cin >> x;
        insert(tr, x);
    }

    cout << "Height of tree is " << height(tr) - 1 << endl << endl;
    even_leaf(tr, found);
    if(!found){
        cout << "No even leaves" << endl;
    }
    cout << endl;

    vector <tree*> leaves;
    leaves_array(tr, leaves);
    median_value(tr, leaves);

    inorder(tr);
    return 0;
}