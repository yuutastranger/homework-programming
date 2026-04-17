#include <iostream>
#include <string>
using namespace std;

struct stack {
    int inf;
    stack *next;
};

void push(stack *&h, int x){
    stack *r = new stack;
    r -> inf = x;
    r -> next = h;
    h = r;
}

int pop(stack *&h){
    int i = h -> inf;
    stack *r = h;
    h = h -> next;
    delete r;
    return i;
}
int priority(char opr){
    if (opr == '+' || opr == '-'){
        return 1;
    }
    if(opr == '*' || opr == '/'){
        return 2;
    }
    return 0;
}
string postfix(string input_str){
    stack *num = NULL;
    string res = "";

    for(int i = 0; i < input_str.length(); i++){
        char symbol = input_str[i];

        if (symbol == ' '){ 
            continue;
        }
        if (isdigit(symbol)){
            res += symbol;
        }
        else if(symbol == '('){
            push(num, symbol);
        }
        else if(symbol == ')'){
            while(num != NULL && num -> inf != '('){
                res += pop(num);
            }
            if (num != NULL){
                pop(num);
            }
        }
        else if(symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/'){

            if (num == NULL){
                push(num, symbol);
            }
            else if (priority(symbol) > priority(num -> inf)){
                push(num, symbol);
            }
            else{
                while(num != NULL && priority(symbol) <= priority(num -> inf)){
                    res += pop(num);
                }
                push(num, symbol);
            }
        }
    }
    while (num != NULL){
        res += pop(num);
    }

    return res;
}

int main() {
    string input_string;
    cout << "Write down your mathematical string: ";
    getline(cin, input_string);  
    cout << postfix(input_string);
    return 0;
}