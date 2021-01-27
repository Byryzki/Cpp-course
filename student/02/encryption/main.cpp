#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int angli(string word){
    int check = 0;

    for(string::size_type i = 0; i < word.size(); ++i){
        if(not islower(word[i])){
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return EXIT_FAILURE;
        }

        else{
            if(not isascii(word[i])){
                cout << "Error! The encryption key must contain only lower case characters." << endl;
                return EXIT_FAILURE;
            }
            else{
                char c = word[i];
                check+= int(c);
            }
        }
    }
    if(check == 2847){

    return EXIT_SUCCESS;
    }

   return EXIT_FAILURE;
}

int ascii(string word){

    for(string::size_type i = 0; i < word.size(); ++i){
        if(not islower(word[i])){
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return EXIT_FAILURE;
        }

        else{
            if(not isascii(word[i])){
                cout << "Error! The encryption key must contain only lower case characters." << endl;
                return EXIT_FAILURE;
            }
            else{

            }
      }
    }


    return EXIT_SUCCESS;
}

int translate(string key, string txt){
    string enc = "";
    string aakkoset = "abcdefghijklmnopqrstuvwzyx";

    for(string::size_type i = 0; i < txt.size(); ++i){
        for(string::size_type a = 0; a < key.size(); ++a){
            if(aakkoset[a] == txt[i]){
                enc += key[a];
            }
            else{

            }
        }
    }
    cout << "Encrypted text: " << enc << endl;

    return 0;
}

int main(){
    cout << "Enter the encryption key: ";
    string key = ""; // lisää qwertyuiopasdfghjklzxcvbnm valmiiksi testattaessa
    cin >> key;
    int len = key.length();

    if(len != 26){
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;
    }
    else{
        if(angli(key) == EXIT_SUCCESS){
            cout << "Enter the text to be encrypted: ";
            string txt = "";
            cin >> txt;

            if(ascii(txt) == EXIT_SUCCESS){
                // täysin onnistuneen syötön jälkeen.
                // ei suostu välittämään salattavan virheistä

                translate(key, txt);

        }
            else{

        }
    }
  }
    return 0;
}

