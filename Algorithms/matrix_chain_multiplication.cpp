#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void matrixChainMult(vector<int> &dims, vector<vector<int>> &dp, vector<vector<int>> &s){
    int n = dims.size() - 1;
    for(int len = 2; len <= n; len++){
        for(int i = 1; i <= n - len + 1; i++){
            int j = i + len - 1;    
            dp[i][j] = INT_MAX;
            for(int k = i; k < j; k++){
                int cost = dp[i][k] + dp[k+1][j] + dims[i-1] * dims[k] * dims[j]; 
                if(cost < dp[i][j]){
                    dp[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }
}

void printBrackets(vector<vector<int>> &s, int i, int j){
    if(i == j){
        cout << "A" << i;
        return;
    }
    cout << "(";
    printBrackets(s, i, s[i][j]);
    printBrackets(s, s[i][j] + 1, j);
    cout << ")";
}

int main(){
    int n;
    cout << "Amount of matrices: "; cin >> n;
    vector<int> dims(n + 1);
    cout << "Enter " << n + 1 << " dimensions: ";
    for(int i = 0; i <= n; i++) cin >> dims[i];

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> s(n + 1, vector<int>(n + 1, 0));

    matrixChainMult(dims, dp, s);

    cout << "Minimum of multiplications: " << dp[1][n] << endl;
    cout << "Brackets: ";
    printBrackets(s, 1, n);
    cout << endl;

    return 0;
}