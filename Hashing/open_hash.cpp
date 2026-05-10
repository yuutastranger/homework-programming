#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

ifstream in("sotrudniki_predpriyatiya.txt");


struct Date{
    int dd, mm, yy;
};

struct People{
    string Surname;
    string Position;
    Date DateOfBirth;
    int Experience;
    int Salary;
};

struct list{
    People data;
    list *next;
    list *prev;
};


void push_back(list *&h, list *&t, People x){
    list *r = new list;
    r -> data = x;
    r -> next = NULL;
    if(!h && !t){
        r -> prev = NULL;
        h = r;
    }
    else{
        t -> next = r;
        r -> prev = t;
    }
    t = r;
}

list *find(list *h,  int salary){
    list *p = h;
    while (p){
        if (p -> data.Salary == salary){
            break;
        }
        p = p -> next;
    }
    return p;
}

void del_node (list *&h, list *&t, list *r){
    if (r == h && r == t){
        h = t = NULL;
    }
    else if (r == h){
        h = h -> next;
        h -> prev = NULL;
    }
    else if (r == t){
        t = t -> prev;
        t -> next  = NULL;
    }
    else{
        r -> next -> prev = r -> prev;
        r -> prev -> next = r -> next;
    }
    delete r;
}


void del_list(list* &h, list* &t){
    while (h){
        list *p = h;
        h = h ->  next;
        h -> prev = NULL;
        delete p;
    }
}


string normalize_date_str(string &s){
    int d = 0, m = 0, y = 0;
    char dot1 = 0, dot2 = 0;
    istringstream iss(s);
    if (!(iss >> d >> dot1 >> m >> dot2 >> y)){
        return s;
    }
    ostringstream oss;
    if (d < 10){
        oss << '0';
    }
    oss << d << '.';
    if (m < 10){
        oss << '0';
    }
    oss << m << '.' << y;
    return oss.str();
}


Date str_to_date(string str){ 
    Date x;
    str = normalize_date_str(str);
    string temp = str.substr(0, 2);
    x.dd = atoi(temp.c_str());
    temp = str.substr(3, 2);  
    x.mm = atoi(temp.c_str());
    temp = str.substr(6, 4); 
    x.yy = atoi(temp.c_str());
    return x;
}

vector<People> read_file(){ 
    vector<People> x;
    People temp;
    while (in.peek() != EOF){
        temp.Position.clear();
        in >> temp.Surname;       
        string word;
        while (in >> word){
            if (word.find('.') != string::npos || word.find('-') != string::npos){
                temp.DateOfBirth = str_to_date(word);
                break;
            }
            if (!temp.Position.empty()){
                temp.Position += " ";
            }
            temp.Position += word;
        }
        
        in >> temp.Experience;   
        in >> temp.Salary;       
        
        if (in){
            x.push_back(temp);
        } 
        else{
            break;
        }
    }
    return x;
}

struct HashCell{
    list* head = NULL;
    list* tail = NULL;
};

int h(int x, int M){
    return x % M;
}

vector<HashCell> buildHash(vector<People> &A, int M){
    vector<HashCell> table(M);
    for (int i = 0; i < A.size(); i++){
        int k = h(A[i].Salary, M);
        push_back(table[k].head, table[k].tail, A[i]);
    }
    return table;
}

void printPerson(People &p){
    cout  << p.Surname
    << " | " << p.Position
    << " | " << setfill('0') << setw(2) << p.DateOfBirth.dd
    << "." << setw(2) << p.DateOfBirth.mm
    << "." << p.DateOfBirth.yy
    << " | experience: " << p.Experience
    << " | salary: " << p.Salary << endl;
}

void printHash(vector<HashCell> &table){
    for (int i = 0; i < table.size(); i++){
        cout << "[" <<  i << "]";
        if (!table[i].head){
            cout << "NULL" << endl;
        } 
        else{
            cout << endl;
            list* p = table[i].head;
            while (p){
                printPerson(p -> data);
                p = p -> next;
            }
        }
    }
}

void searchBySalary(vector<HashCell> &table, int M, int salary){
    int k = h(salary, M);
    cout << "Finding salary " << salary << " in cell " << k << endl;
    list* p = table[k].head;
    bool found = false;
    while (p){
        if (p -> data.Salary == salary){
            printPerson(p -> data);
            found = true;
        }
        p = p -> next;
    }
    if (!found){
        cout << "Unable to find records with this salary" << endl;
    }
}


void deleteBySalary(vector<HashCell> &table, int M, int salary){
    int k = h(salary, M);
    cout << "Deleting salary " << salary << " in cell " << k << endl;
    list* p = table[k].head;
    int count = 0;
    while (p){
        list* next = p -> next;
        if (p -> data.Salary == salary){
            del_node(table[k].head, table[k].tail, p);
            count++;
        }
        p = next;
    }
    if (count == 0){
        cout << "No records by this salary" << endl;
    }
    else{
        cout << "Deleted records: " << count << endl;
    }
}

int main(){
    vector<People> data = read_file();

    int M;
    cout << "Enter size(M) of hash-table (recommended prime number, e.g. 31): ";
    cin >> M;

    vector<HashCell> table = buildHash(data, M);
    int choice;
   
    cout << "1. Print hash-table" << endl;
    cout << "2. Find employees by salary" << endl;
    cout << "3. Delete all records with this salary" << endl;
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1){
        printHash(table);
    } 
    else if (choice == 2){
        int salary;
        cout << "Enter salary for search: "; cin >> salary;
        searchBySalary(table, M, salary);
    } 
    else if (choice == 3){
        int salary;
        cout << "Enter salary to delete: "; cin >> salary;
        deleteBySalary(table, M, salary);
    }
    
    for (int i = 0; i < table.size(); i++)
        del_list(table[i].head, table[i].tail);
    return 0;
}