#include <iostream>
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

void reverse(stack *&h){
    stack *res = NULL;
    while (h)
        push(res, pop(h));
    h = res;
}

stack* process(stack *&h){
    stack *tmp = NULL;

    if (!h){ 
        return tmp;
    }
    
    int min_val = h->inf;
    int max_val = h->inf;

    while (h){
        int x = pop(h);
        if (x < min_val){
            min_val = x;
        }
        if (x > max_val){
            max_val = x;
        }
        push(tmp, x);
    }

    reverse(tmp);
    h = tmp;
    tmp = NULL;

    //результат
    stack *res = NULL;
    while (h){
        int x = pop(h);

        if (x == min_val)
            push(res, max_val);

        push(res, x);
    }

    reverse(res);
    return res;
}

int main(){
    int n, x;
    stack *head = NULL;
    cout << "Insert amount of elements ";
    cin >> n;
    cout << "Enter elements of stack" << endl;
    for (int i = 0; i < n; i++){
        cin >> x;
        push(head, x);
    }

    reverse(head); 
    stack *res = process(head);

    cout << "Result" ;
    while (res)
        cout << pop(res) << " ";
    cout << endl;

    return 0;
}