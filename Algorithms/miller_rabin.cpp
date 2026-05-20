#include <iostream>
#include <vector>
using namespace std;

long long power(long long base, long long exp, long long mod){
    long long result = 1;
    base %= mod;
    while(exp > 0){
        if(exp % 2 == 1){
            result = result * base % mod;
        }
        base = base * base % mod;
        exp /= 2;
    }
    return result;
}

bool millerRabin(long long n){
    if(n < 2){
        return false;
    }
    if(n == 2 || n == 3){
        return true;
    }
    if(n % 2 == 0){
        return false;
    }
    vector<int> a = {2, 3, 5, 7, 11, 13, 37};

    long long d = n - 1;
    long long s = 0;
    while(d % 2 == 0){
        d /= 2;
        s++;
    }
    for(int i = 0; i < a.size(); i++){
        if(a[i] >= n){
            continue;
        } 
        long long x = power(a[i], d, n);
        if(x == 1 || x == n - 1){
            continue;
        }
        bool composite = true;
        for(int j = 0; j < s - 1; j++){
            x = power(x, 2, n);
            if(x == n - 1){
                composite = false;
                break;
            }
        }
        if(composite){
            return false;
         } 
    }
    return true;
}

int main(){
    long long n;
    cout << "Enter the number = ";
    cin >> n;
    if(millerRabin(n))
        cout << "Prime";
    else
        cout << "Composite";
    return 0;
}