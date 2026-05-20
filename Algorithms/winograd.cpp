#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> matrixCreate(int m, int n){
    vector<vector<int>> matrix(m ,vector<int>(n));
    int x;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            cout << "element[" << i << "][" << j << "] = ";
            cin >> x;
            matrix[i][j] = x;
        }
    }
    cout << endl;
    return matrix;
}

void printMatrix(vector<vector<int>> &matrix){
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<int>> winogradAlg(vector<vector<int>> &matrix_frs, vector<vector<int>> &matrix_sec){
    int m = matrix_frs.size();
    int n = matrix_frs[0].size();
    int p = matrix_sec[0].size();
    int half = n / 2;
    vector<vector<int>> matrix_res(m, vector<int>(p, 0));

    vector<int> rowSum(m, 0);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < half; j++){
            rowSum[i] += matrix_frs[i][2*j] * matrix_frs[i][2*j+1];
        }
    }

    vector<int> colSum(p, 0);
    for(int i = 0; i < p; i++){
        for(int j = 0; j < half; j++){
            colSum[i] += matrix_sec[2*j][i] * matrix_sec[2*j+1][i];
        }
    }
    for(int i = 0; i < m; i++){
        for(int j = 0; j < p; j++){
            matrix_res[i][j] = -rowSum[i] - colSum[j];
            for(int k = 0; k < half; k++){
                matrix_res[i][j] += (matrix_frs[i][2*k] + matrix_sec[2*k+1][j]) * (matrix_frs[i][2*k+1] + matrix_sec[2*k][j]);
            }
        }
    }
    if(n % 2 != 0){
        for(int i = 0; i < m; i++){
            for(int j = 0; j < p; j++){
                matrix_res[i][j] += matrix_frs[i][n-1] * matrix_sec[n-1][j];
            }
        }
    }
    return matrix_res;
}

int main(){
    int m, n, k, p;
    
    cout << "Enter size of your matrix 1" << endl << "Strings m = "; cin >> m;
    cout << "Columns n = "; cin >> n;
    vector<vector<int>> matrix_frs = matrixCreate(m, n);

    cout << "Enter size of your matrix 2(Please enter the same number to field n!)" << endl << "Strings n = "; cin >> k;
    if(k != n){
        cout << "I said you to enter the same number!";
        return 0;
    }
    cout << "Columns p = "; cin >> p;
    vector<vector<int>> matrix_sec = matrixCreate(k, p);
    


    printMatrix(matrix_frs);
    printMatrix(matrix_sec);

    vector<vector<int>> matrix_res = winogradAlg(matrix_frs, matrix_sec);
    printMatrix(matrix_res);
    return 0;
}