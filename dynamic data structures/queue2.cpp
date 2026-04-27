#include <iostream>
using namespace std;

struct queue{
    int inf;
    queue *next;
};

void push(queue *&h, queue *&t, int x){
    queue *r = new queue;
    r->inf = x;
    r->next = NULL;

    if (!h && !t){
        h = t = r;
    }
    else{
        t->next = r;
        t = r;
    }
}

int pop(queue *&h, queue *&t){
    queue *r = h;
    int i = h->inf;
    h = h->next;
    if (!h){
        t = NULL;
    }
    delete r;
    return i;
}

queue* removeDuplicates(queue *&h, queue *&t){
    queue *res_h = NULL, *res_t = NULL;

    if (!h){ 
        return res_h;
    }
    int prev = pop(h, t);
    push(res_h, res_t, prev);

    while (h){
        int x = pop(h, t);
        if (x != prev){
            push(res_h, res_t, x);
            prev = x;
        }
    }
    return res_h;
}

int main(){
    int n, x;
    queue *h = NULL, *t = NULL;
    cout << "Insert amount of elements ";
    cin >> n;
    cout << "Insert elements for queue " << endl;

    for (int i = 0; i < n; i++){
        cin >> x;
        push(h, t, x);
    }

    queue *res = removeDuplicates(h, t);

    cout << "Result ";
    while (res)
        cout << pop(res, t) << " ";
    cout << endl;

    return 0;
}