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
    while (h){
        push(head1, pop(h));
    }
    h = head1;
}

stack* reorder(stack *&h){
    stack *singleDigits = NULL;   
    stack *doubleDigits = NULL;  

    //поделим числа на две группы
    while(h){
        int x = pop(h);
        if (x < 10)
            push(singleDigits, x);
        else
            push(doubleDigits, x);
    }

    reverse(singleDigits);
    reverse(doubleDigits);

    // этап объединения двух стеков
    stack *res = NULL;
    while (singleDigits){
        push(res, pop(singleDigits));
    }
    while (doubleDigits){
        push(res, pop(doubleDigits));
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
        push(head, abs(x));
    }

    reverse(head);
    stack *res = reorder(head);
    cout << "Result is ";

    while (res)
        cout << pop(res) << " ";
    cout << endl;

    return 0;
}