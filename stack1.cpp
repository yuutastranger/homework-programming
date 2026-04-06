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
    stack *head1 = NULL;
    while (h)
        push(head1, pop(h));
    h = head1;
}

stack* reorder(stack *&h){
    stack *single = NULL;   
    stack *doubleDigits = NULL;  

    //поделим числа на две группы
    while(h){
        int x = pop(h);
        if (x < 10)
            push(single, x);
        else
            push(doubleDigits, x);
    }

    
    reverse(single);
    reverse(doubleDigits);

    // этап объединения
    stack *res = NULL;
    while (single)
        push(res, pop(single));
    while (doubleDigits)
        push(res, pop(doubleDigits));
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
    stack *res = reorder(head);
    cout << "Result is ";

    while (res)
        cout << pop(res) << " ";
    cout << endl;

    return 0;
}