#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <functional>
#include <numeric>
#include <set>
#include <map>
#include <fstream>
#include <string>
#include <list>
#include <cstdlib>
#include <ctime>

using namespace std;


void alphabet(vector <string> &alp){
    cout << "This is your present alphabet: " << endl;
    int k = 0;
    for(int i = 0; i < alp.size(); i++){
        cout << alp[i] << " ";
        k++;
        if(k == alp.size() / 2){
            cout << endl;
        }
    }
    cout << endl << endl;

}

void print_vec(vector<string> &vec){
    for(int i = 0; i < vec.size(); i++){
        cout << vec[i];
    }
    cout << endl << endl;
}

int main(){
    int lvl; int difficulty;
    cout << "Choose your difficulty" <<  endl << "1 - Easy; 2 - Normal; 3 - Hard" << endl << endl; cin >> difficulty;
    if(difficulty == 1){
        lvl = 8;
    }
    if(difficulty == 2){
        lvl = 6;
    }
    if(difficulty == 3){
        lvl = 4;
    }
    system("cls");

    srand(static_cast<unsigned int>(std::time(nullptr)));

    vector <string> alp = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
    vector <string> words = {"remember", "programmer", "nutshell", "something", "saturday", "overheated", "business", "complicated", "heathens", "windflower"};
    vector <string> pseudo_word;
    vector <string> w_word; 

    int it_word = rand()% words.size();
    string h_word = words[it_word];
    string mb_word;
    bool win_flag = false;
    int counter = 0;
    bool choice = false;
    w_word.resize(h_word.length());

    for(int i = 0; i < h_word.length(); i++){
        w_word[i] = h_word[i];
    }

    for(int i = 0; i <  w_word.size(); i++){
        pseudo_word.push_back("_");
    }

    

    for(int i = 0; i < pseudo_word.size(); i++){
        if(counter == lvl){
            break;
        }
        alphabet(alp);

        string letter;
       
    
        cout << "Your word right now: ";
        for(int i = 0; i < pseudo_word.size(); i++){
                cout << pseudo_word[i] << " ";
            }

        cout << endl << endl << "Counter of failed tries now is " << counter << endl << endl << "Please pick any letter or insert full word: ";
        cin >> letter;
        if(letter.length() > 1){
            choice = true;
            mb_word = letter;
            break;
        }
        bool flag = true;
        int k_let = 0;
        
        for(int hk = 0; hk < w_word.size(); hk++){
            if(w_word[hk] == letter){
                pseudo_word[hk] = letter;
                k_let++;
            }
            auto it_al = find(alp.begin(), alp.end(), letter);
            if(it_al != alp.end()) {
                *it_al = "_"; 
            }
        }

        auto it = find(pseudo_word.begin(), pseudo_word.end(), "_");
        if(it == pseudo_word.end()){
            win_flag = true;
            break;
        }
        system("cls");
        if(k_let == 0){
            counter++;
            flag = false;
            cout << "Oops, wrong letter, now you're closer to be the hangman" << endl << endl;
        }
        if(flag){
            cout << "Good, you answered the right letter!"<< endl << endl;
        }
        

    }
    
    if(choice){
        if(mb_word == h_word){
            win_flag = true;
        }
           
    }
    
    if(win_flag){
        system("cls");
        cout << "Congrats, you won! Here's your word: ";
        print_vec(w_word);
        system("pause");
        return 0;
    }
    else{
        system("cls");
        cout << "Game over man, now you're the hangman" << endl << endl;
        print_vec(w_word);
        cout << endl;
        system("pause");
        return 0;
    }
    system("pause");
    return 0;
}