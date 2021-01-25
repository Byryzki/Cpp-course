#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int angli(string word){
    int i=0;
    int len = word.length();

    for(i = 0; i <= len; i++){
        if(isupper(word[i])){
                cout << "Error! The encryption key must contain only lower case characters." << endl;
                return false;
        }
        else{
            char check = word[i];
            int count = 0;

            for (int i = 0; i <= len; i++)
                {
                    if (word[i] ==  check)
                    {
                        ++ count;
                    }
                }

            if(count != 1){
                cout << "Error! The encryption key must contain all alphabets a-z." << endl;
                return false;
            }
            else{

            }
        }
    }
    return true;
}

int ascii(string word){
    int len = word.length();

    for(int i=0; i <= len; i++){
        if(islower(word[i])){
            char ch = word[i];
            int chnro = static_cast< int >( ch );

            if(chnro < 97 or chnro > 122){
                cout << "Error! The encryption key must contain only lower case characters." << endl;
                return false;
                }
            else{
                return true;
            }
        }
            else{
                   cout << "Error! The encryption key must contain only lower case characters." << endl;
                   return false;
                }

    }
    return 0;
}

int translate(string key, string txt){
    int len = key.length();
    string enc = "";

    for(int i = 0; i <= len; i++){
        int place = char(txt[i])-97;

        char letter = key[place];
        enc += letter;
    }
    cout << "Encrypted text: " << enc << endl;

    return 0;
}

int main(){
    cout << "Enter the encryption key: ";
    string key = ""; // lisää valmiiksi testattaessa
    cin >> key;
    int len = key.length();

    if(len != 26){
        cout << "Error! The encryption key must contain 26 characters." << endl;
    }
    else{
        if(angli(key)){
            cout << "Enter the text to be encrypted: ";
            string txt = "";
            cin >> txt;

            if(ascii(txt)){
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

