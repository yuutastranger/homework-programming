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

queue* process(queue *&h, queue *&t){
    queue *res_h = NULL, *res_t = NULL;
    if (!h){
        return res_h;
    } 
    
    int last; //последний элемент
    queue *tmp_h = NULL, *tmp_t = NULL;

    while (h){
        int x = pop(h, t);
        last = x;
        push(tmp_h, tmp_t, x);
    }

    while (tmp_h){
        push(h, t, pop(tmp_h, tmp_t));
    }
    int max_val = h->inf; //нахождение максимума
    while (h){
        int x = pop(h, t);
        if (x > max_val)
            max_val = x;
        push(tmp_h, tmp_t, x);
    }

    while (tmp_h)
        push(h, t, pop(tmp_h, tmp_t));

    //пишем все в результат
    while (h){
        int x = pop(h, t);
        push(res_h, res_t, x);

        if (x == last)
            push(res_h, res_t, max_val);
    }
    return res_h;
}

int main(){
    int n, x;
    queue *h = NULL, *t = NULL;

    cout << "INSERT AMOUNT OF ELEMENTS ";
    cin >> n;

    cout << "INSERT ELEMETS FOR QUEUE " << endl;
    for (int i = 0; i < n; i++){
        cin >> x;
        push(h, t, x);
    }
    queue *res = process(h, t);
    cout << "Result ";
    while (res)
        cout << pop(res, t) << " ";
    cout << endl;

    return 0;
}