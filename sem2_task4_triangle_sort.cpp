#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

ifstream in("in_matrix.txt");
ofstream out("out_matrix.txt");

void heapify(vector<int>& a, int heap_size, int i) {
    while (true) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < heap_size && a[left] > a[largest]) {
            largest = left;
        }
        if (right < heap_size && a[right] > a[largest]) {
            largest = right;
        }
        if (largest == i) {
            break;
        }
        swap(a[i], a[largest]);
        i = largest;
    }
}

void heap_sort(vector<int>& a) {
    int n = a.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(a, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

void shell_sort(vector<int>& a, bool ascending) {
    int n = a.size();
    vector<int> gaps;

    int pow3 = 1;
    while (true) {
        pow3 *= 3;
        int gap = pow3 - 1; 
        if (gap > n) {
            break;
        }
        gaps.push_back(gap);
    }

    if (gaps.back() != 1) {
        gaps.push_back(1); //добавляем специально эту 1 чтоб соседние элементы проверитьи упорядочить до конца, а то вдруг не попадет к нам что то
    }

    for (int g = gaps.size() - 1; g >= 0; g--) {
        int step = gaps[g];
        for (int i = 0; i <= n - 1 - step; i++) {
            int j = i;
            if (ascending) {
                while (j >= 0 && a[j] > a[j + step]) {
                    swap(a[j], a[j + step]);
                    j -= step;
                }
            } 
            else {
                while (j >= 0 && a[j] < a[j + step]) {
                    swap(a[j], a[j + step]);
                    j -= step;
                }
            }
        }
    }
}

void odd_even_sort(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i <= n - 1; i++) {
        if (i % 2 == 0) {
            for (int j = 2; j <= n - 1; j += 2) {
                if (a[j - 1] > a[j]) {
                    swap(a[j - 1], a[j]);
                }
            }
        } 
        else {
            for (int j = 1; j <= n - 1; j += 2) {
                if (a[j - 1] > a[j]) {
                    swap(a[j - 1], a[j]);
                }
            }
        }
    }
}

void final_triangle(vector<vector<int>>& matrix) {
    int n = matrix.size();

    for (int j = 0; j < n; j++) {
        vector<int> column(n);
        for (int i = 0; i < n; i++) {
            column[i] = matrix[i][j];
        }
        heap_sort(column);
        for (int i = 0; i < n; i++) {
            matrix[i][j] = column[i];
        }
    }
}

void final_shell(vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        bool ascending = ((i + 1) % 2 != 0);
        shell_sort(matrix[i], ascending);
    }
}

void final_odd_even(vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<int> diagonal;

    
    diagonal.clear();
    for (int i = 0; i < n; i++) {
        diagonal.push_back(matrix[i][i]);
    }
    odd_even_sort(diagonal);
    for (int i = 0; i < n; i++) {
        matrix[i][i] = diagonal[i];
    }

    for (int k = 1; k <= n - 1; k++) {
        diagonal.clear();
        for (int i = 0; i < n; i++) {
            if (k + i < n) {
                diagonal.push_back(matrix[i][k + i]);
            }
        }
        odd_even_sort(diagonal);
        int L = 0;
        for (int i = 0; i < n; i++) {
            if (k + i < n) {
                matrix[i][k + i] = diagonal[L];
                L++;
            }
        }

        diagonal.clear();
        for (int j = 0; j < n; j++) {
            if (k + j < n) {
                diagonal.push_back(matrix[k + j][j]);
            }
        }
        odd_even_sort(diagonal);
        L = 0;
        for (int j = 0; j < n; j++) {
            if (k + j < n) {
                matrix[k + j][j] = diagonal[L];
                L++;
            }
        }
    }
}

int main() {
    int n = 0;
    in >> n;
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            in >> matrix[i][j];
        }
    }

    cout << "Choose your sort(Tringle = 5, Shell = 7, Odd_even = 12): ";
    int t = 0;
    cin >> t;

    if (t == 5) {
        final_triangle(matrix);
    } else if (t == 7) {
        final_shell(matrix);
    } else if (t == 12) {
        final_odd_even(matrix);
    }

    out << n << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            out << matrix[i][j];
            if(j + 1 < n){
                out << " ";
            }
            else{
                out << "\n";
            }
        }
    }

    return 0;
}
