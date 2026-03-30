#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
ifstream in("sotrudniki_predpriyatiya.txt");
ofstream out("sorted.txt");


struct date {
    int dd;
    int mm;
    int yy;
};

struct people {
    string Surname;
    string Position;
    date DateOfBirth;
    int Experience;
    int Salary;
};

string normalize_date_str(string& s) {
    int d = 0, m = 0, y = 0;
    char dot1 = 0, dot2 = 0;
    istringstream iss(s);
    if (!(iss >> d >> dot1 >> m >> dot2 >> y)) {
        return s;
    }
    ostringstream oss;
    if (d < 10) {
        oss << '0';
    }
    oss << d << '.';
    if (m < 10) {
        oss << '0';
    }
    oss << m << '.' << y;
    return oss.str();
}
date str_to_date(string str) { 
    date x;
    str = normalize_date_str(str);
    string temp = str.substr(0, 2); 
    x.dd = atoi(temp.c_str());
    temp = str.substr(3, 2); 
    x.mm = atoi(temp.c_str());
    temp = str.substr(6, 4); 
    x.yy = atoi(temp.c_str());
    return x;
}
vector<people> in_file() {
    vector<people> x;
    people temp;
    while (in.peek() != EOF) {
        temp.Position.clear();
        in >> temp.Surname;      
        string word;
        while (in >> word) {

            if (word.find('.') != string::npos || word.find('-') != string::npos) {
                temp.DateOfBirth = str_to_date(word);
                break;
            }
            if (!temp.Position.empty()) {
                temp.Position += " ";
            }
            temp.Position += word;
        }
        in >> temp.Experience;   
        in >> temp.Salary;       
        if (in) {
            x.push_back(temp);
        } 
        else {
            break;
        }
    }
    return x;
}
bool operator < (people a, people b) {
    if (a.Salary < b.Salary) {
        return true;
    }
    if (a.Salary == b.Salary && a.DateOfBirth.yy < b.DateOfBirth.yy) {
        return true;
    }
    if (a.Salary == b.Salary && a.DateOfBirth.yy == b.DateOfBirth.yy && a.Experience < a.Experience) {
        return true;
    }
    return false;
}
void selection_sort(vector<people>& a) {
    for (int i = 0; i < a.size() - 1; i++) {
        int min = i;
        for (int j = i + 1; j < a.size(); j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }
        if (min != i) {
            swap(a[i], a[min]);
        }
    }
}
void print(people x) { 
    out <<  left << setw(20)  << x.Surname ;
    out << left <<  setw(30) << x.Position ;

    if (x.DateOfBirth.dd < 10) {
        out << '0' << x.DateOfBirth.dd << '.';
    } 
    else {
        out << x.DateOfBirth.dd << '.';
    }
    if (x.DateOfBirth.mm < 10) {
        out << '0' << x.DateOfBirth.mm << '.';
    } 
    else {
        out << x.DateOfBirth.mm << '.';
    }
    out << left << setw(18) << x.DateOfBirth.yy;
    out << left << setw(16) << x.Experience;
    out << left << setw(12) << x.Salary << endl;
}

int main() {
    vector<people> data = in_file();
    selection_sort(data);
    out << left << setw(20) << "Surname";
    out << left << setw(30) << "Position";
    out << left << setw(24) << "Date of birth";
    out << left << setw(16) << "Experience" ;
    out << left << setw(12) << "Salary" 
        << endl;
    for (int i = 0; i < data.size(); ++i) {
        print(data[i] );
    }
    return 0;
}
