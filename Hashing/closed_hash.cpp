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

struct HashCell{
    People data;
    bool occupied = false;
};

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

int h1(int salary, int M){
    return salary % M;
}

int h2(int year, int M){
    return 1 + (year % (M - 1));
}

int h(int salary, int year, int i, int M){
    return (h1(salary, M) + i * h2(year, M)) % M;
}

vector<HashCell> buildHash(vector<People> &A, int M){
    vector<HashCell> table(M);
    for (int i = 0; i < A.size(); i++){
        int j = 0;
        while (j < M){
            int k = h(A[i].Salary, A[i].DateOfBirth.yy, j, M);
            if (!table[k].occupied){
                table[k].data = A[i];
                table[k].occupied = true;
                break;
            }
            j++;
        }
    }
    return table;
}

void printPerson(People &p){
    cout << p.Surname
    << " | " << p.Position
    << " | " << setfill('0') << setw(2) << p.DateOfBirth.dd
    << "." << setw(2) << p.DateOfBirth.mm
    << "." << p.DateOfBirth.yy
    << " | experience: " << p.Experience
    << " | salary: " << p.Salary << endl;
}

void printHash(vector<HashCell> &table){
    for (int i = 0; i < table.size(); i++){
        cout << "[" << i << "] ";
        if (!table[i].occupied){
            cout << "NULL" << endl;
        }
        else{
            printPerson(table[i].data);
        }
    }
}

void searchByYear(vector<HashCell> &table, int M, int salary, int year){
    cout << "Finding salary " << salary << ", year " << year << endl;
    int i = 0;
    bool found = false;
    while (i < M){
        int k = h(salary, year, i, M);
        if (!table[k].occupied){
            break;
        }
        if (table[k].data.Salary == salary && table[k].data.DateOfBirth.yy == year){
            printPerson(table[k].data);
            found = true;
            break;
        }
        i++;
    }
    if (!found){
        cout << "Unable to find records" << endl;
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
    cout << "2. Find employee by salary and birth year" << endl;
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1){
        printHash(table);
    }
    else if (choice == 2){
        int salary, year;
        cout << "Enter salary: "; cin >> salary;
        cout << "Enter birth year: "; cin >> year;
        searchByYear(table, M, salary, year);
    }

    return 0;
}