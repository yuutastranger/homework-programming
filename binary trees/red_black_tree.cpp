#include <iostream>
#include <vector>
using namespace std;

enum Color {RED, BLACK};

struct tree{
    int inf;
    Color color;
    tree *left, *right, *parent;
};

tree *node(tree *p, int x){
    tree *n = new tree;
    n -> inf = x;
    n -> color = RED;
    n -> left = n -> right = NULL;
    n -> parent = p;
    return n;
}

tree *root_node(int x){
    tree *n = new tree;
    n -> inf = x;
    n -> color = BLACK;
    n -> left = n -> right = n -> parent = NULL;
    return n;
}

tree *grandparent(tree *x){
    if(x && x -> parent){
        return x -> parent -> parent;
    }
    return NULL;
}

tree *uncle_of(tree *x){
    tree *g = grandparent(x);
    if(!g){
        return NULL;
    }
    if(x -> parent == g -> left){
        return g -> right;
    }
    else{
        return g -> left;
    }
}

tree *sibling(tree *x){
    if(!x || !x -> parent){
        return NULL;
    }
    if(x == x -> parent -> left){
        return x -> parent -> right;
    }
    else{
        return x -> parent -> left;
    }
}

tree *Min(tree *x){
    while(x -> left){
        x = x -> left;
    }
    return x;
}

tree *Max(tree *x){
    while(x -> right){
        x = x -> right;
    }
    return x;
}

tree *find(tree *tr, int x){
    if(!tr || tr -> inf == x){
        return tr;
    }
    if(x < tr -> inf){
        return find(tr -> left, x);
    }
    else{
        return find(tr -> right, x);
    }
}

void rotate_left(tree *&tr, tree *x){
    tree *y = x -> right;
    x -> right = y -> left;
    if(y -> left){
        y -> left -> parent = x;
    }
    y -> parent = x -> parent;
    if(!x -> parent){
        tr = y;
    }
    else if(x == x -> parent -> left){
        x -> parent -> left = y;
    }
    else{
        x -> parent -> right = y;
    }
    y -> left = x;
    x -> parent = y;
    if(!y -> parent){
        y -> color = BLACK;
    }
}

void rotate_right(tree *&tr, tree *x){
    tree *y = x -> left;
    x -> left = y -> right;
    if(y -> right){
        y -> right -> parent = x;
    }
    y -> parent = x -> parent;
    if(!x -> parent){
        tr = y;
    }
    else if(x == x -> parent -> left){
        x -> parent -> left = y;
    }
    else x -> parent -> right = y;
    y -> right = x;
    x -> parent = y;
    if(!y -> parent){
        y -> color = BLACK;
    }
}

void insert_case1(tree *&tr, tree *x);
void insert_case2(tree *&tr, tree *x);
void insert_case3(tree *&tr, tree *x);
void insert_case4(tree *&tr, tree *x);
void insert_case5(tree *&tr, tree *x);

void insert_case1(tree *&tr, tree *x){
    if(!x -> parent){
        x -> color = BLACK;
    }
    else{
        insert_case2(tr, x);
    }
}

void insert_case2(tree *&tr, tree *x){
    if(x -> parent -> color == RED){
        insert_case3(tr, x);
    }   
    else{
        return;
    }
}

void insert_case3(tree *&tr, tree *x){
    tree *u = uncle_of(x);
    tree *g = grandparent(x);
    if(u && u -> color == RED){
        x -> parent -> color = BLACK;
        u -> color = BLACK;
        g -> color = RED;
        insert_case1(tr, g);
    }
    else{
        insert_case4(tr, x);
    }
}

void insert_case4(tree *&tr, tree *x){
    tree *g = grandparent(x);
    if(x == x -> parent -> right && x -> parent == g -> left){
        rotate_left(tr, x -> parent);
        x = x -> left;
    }
    else if(x == x -> parent -> left && x -> parent == g -> right){
        rotate_right(tr, x -> parent);
        x = x -> right;
    }
    insert_case5(tr, x);
}

void insert_case5(tree *&tr, tree *x){
    tree *g = grandparent(x);
    x -> parent -> color = BLACK;
    g -> color = RED;
    if(x == x -> parent -> left){
        rotate_right(tr, g);
    }
    else{
        rotate_left(tr, g);
    }
}

void insert(tree *&tr, tree *prev, int x){
    if(x < prev -> inf && !prev -> left){
        prev -> left = node(prev, x);
        insert_case1(tr, prev -> left);
    }
    else{
        if(x > prev -> inf && !prev -> right){
            prev -> right = node(prev, x);
            insert_case1(tr, prev -> right);  
        }
        else{
            if(x < prev -> inf && prev -> left){
                insert(tr, prev -> left, x);
            }
            else{
                if(x > prev -> inf && prev -> right){
                    insert(tr, prev -> right, x);
                }
            }
        }
    }
}

void add(tree *&tr, int x){
    if(!tr){
        tr = root_node(x);
    }
    else{
        insert(tr, tr, x);
    }
}

void delete_case1(tree *&tr, tree *x);
void delete_case2(tree *&tr, tree *x);
void delete_case3(tree *&tr, tree *x);
void delete_case4(tree *&tr, tree *x);
void delete_case5(tree *&tr, tree *x);
void delete_case6(tree *&tr, tree *x);

void delete_case1(tree *&tr, tree *x){
    if(!x -> parent){
        if(x -> left){
            tr = x -> left;
        }
        else{
            tr = x -> right;
        }
    }
    else{
        delete_case2(tr, x);
    }
}

void delete_case2(tree *&tr, tree *x){
    tree *s = sibling(x);
    if(s && s -> color == RED){
        x -> parent -> color = RED;
        s -> color = BLACK;
        if(x == x -> parent -> left){
            rotate_left(tr, x -> parent);
        }
        else{
            rotate_right(tr, x -> parent);
        }
    }
    delete_case3(tr, x);
}

void delete_case3(tree *&tr, tree *x){
    tree *s = sibling(x);
    bool sl_black =(!s -> left  || s -> left -> color  == BLACK);
    bool sr_black =(!s -> right || s -> right -> color == BLACK);
    if(x -> parent -> color == BLACK && s -> color == BLACK && sl_black && sr_black){
        s -> color = RED;
        delete_case1(tr, x -> parent);
    }
    else{
        delete_case4(tr, x);
    }
}

void delete_case4(tree *&tr, tree *x){
    tree *s = sibling(x);
    bool sl_black =(!s -> left  || s -> left -> color  == BLACK);
    bool sr_black =(!s -> right || s -> right -> color == BLACK);
    if(x -> parent -> color == RED && s -> color == BLACK && sl_black && sr_black){
        s -> color = RED;
        x -> parent -> color = BLACK;
    }
    else{
        delete_case5(tr, x);
    }
}

void delete_case5(tree *&tr, tree *x){
    tree *s = sibling(x);
    if(s && s -> color == BLACK){
        bool sl_red =(s -> left  && s -> left -> color  == RED);
        bool sr_red =(s -> right && s -> right -> color == RED);
        bool sl_black =(!s -> left  || s -> left -> color  == BLACK);
        bool sr_black =(!s -> right || s -> right -> color == BLACK);
        if(x == x -> parent -> left && sl_red && sr_black){
            s -> color = RED;
            s -> left -> color = BLACK;
            rotate_right(tr, s);
        }
        else if(x == x -> parent -> right && sr_red && sl_black){
            s -> color = RED;
            s -> right -> color = BLACK;
            rotate_left(tr, s);
        }
    }
    delete_case6(tr, x);
}

void delete_case6(tree *&tr, tree *x){
    tree *s = sibling(x);
    s -> color = x -> parent -> color;
    x -> parent -> color = BLACK;
    if(x == x -> parent -> left){
        if(s -> right) s -> right -> color = BLACK;
        rotate_left(tr, x -> parent);
    }
    else{
        s -> left -> color = BLACK;
        rotate_right(tr, x -> parent);
    }
}

void replace(tree *&tr, tree *x){
    tree *ch;
    if(x -> left){
        ch = x -> left;
        ch -> parent = x -> parent;
        if(x -> parent){
            if(x == x -> parent -> left){
                x -> parent -> left = ch;
            }
            else{
                x -> parent -> right = ch;
            }
        }
    }
    else{
        ch = x -> right;
        ch -> parent = x -> parent;
        if(x -> parent){
            if(x == x -> parent -> left){
                x -> parent -> left = ch;
            }
            else{
                x -> parent -> right = ch;
            }
        }
    }

}

void Delete(tree *&tr, tree *x){
    if(x -> left && x -> right){
        tree *buf;
        if(x -> inf <= tr -> inf){
            buf = Max(x -> left);
        }
        else{
            buf = Min(x -> right);
        }
        x -> inf = buf -> inf;
        x = buf;
    }

    if(x -> left || x -> right){
        tree *ch;
        if(x -> left){
            ch = x -> left;
        }
        else{
            ch = x -> right;
        }
        replace(tr, x);
        if(x -> color == BLACK){
            if(ch -> color == RED){
                ch -> color = BLACK;
            }
            else{
                delete_case1(tr, ch);
            }
        }
        delete x;
        return;
    }

    if(x -> color == BLACK){
        delete_case1(tr, x);
        if(x -> parent){ 
            if(x == x -> parent -> left){
                x -> parent -> left = NULL;
            }
            else{
                x -> parent -> right = NULL;
            }
        }
    }
    else{
        if(x -> parent){
            if(x == x -> parent -> left){
                x -> parent -> left = NULL;
            }
            else{
                x -> parent -> right = NULL;
            }
        }
    }
    delete x;
}

void inorder(tree *tr){
    if(tr){
        inorder(tr -> left);
        cout << tr -> inf << "(" << (tr -> color == RED ? "R" : "B") << ")" << endl;
        inorder(tr -> right);
    }
}

void path_to_leaf(tree *start){
    if(!start){
        return;
    }
    tree *cur = start;
    cout << cur -> inf;
    while(cur -> left || cur -> right){
        if(cur -> left){
            cur = cur -> left;
        }
        else{
            cur = cur -> right;
        }
        cout << " -> " << cur -> inf;
    }
    cout << endl;
}

int main(){
    tree *tr = NULL;
    int n, x;
    cout << "n = "; cin >> n;
    cout << "Please do not insert same digits multiple times!" << endl;
    for(int i = 0; i < n; i++){
        cout << i + 1 << " element = "; cin >> x;
        add(tr, x);
    }

    cout << "Inorder traversal:" << endl;
    inorder(tr);

    cout << "Enter node \"a\" for path to leaf: ";
    cin >> x;
    tree *node_a = find(tr, x);
    if(!node_a){
        cout << "Node " << x << " not found" << endl;
    }
    else{
        cout << "Path from " << x << " to leaf: ";
        path_to_leaf(node_a);
    }

    cout << "Enter element to delete: "; cin >> x;
    tree *to_del = find(tr, x);
    if(!to_del){
        cout << "Element not found" << endl;
    }
    else{
        Delete(tr, to_del);
        cout << "Inorder after deletion:" << endl;
        inorder(tr);
    }

    return 0;
}
