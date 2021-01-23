#include <iostream>

using namespace std;

int sihti(int balls, int drawn){
    // lukujen tarkastus

    if(balls < 0){
        cout << "The number of balls must be a positive number." << endl;
        return false;
    }
    else{
        if(balls < drawn){
            cout << "The maximum number of drawn balls is the total amount of balls." << endl;
            return false;
        }
        else{
            return true;
        }
    }
}

int laskuri(int balls, int drawn){
    unsigned long int result = 0;
    unsigned long long fact = 1;
    unsigned long long fact2 = 1;
    unsigned long long fact3 = 1;

    for(int i = 1; i<= balls; ++i){
        fact *= i;
    }
    for(int i = 1; i<= drawn; ++i){
        fact2 *= i;
    }
    for(int i = 1; i<= balls-drawn; ++i){
        fact3 *= i;
    }
    result = fact / (fact3 * fact2);

    return result;
}

int main()
{
    cout << "Enter the total number of lottery balls: ";
    int balls = 0;
    cin >> balls;

    cout << "Enter the number of drawn balls: ";
    int drawn = 0;
    cin >> drawn;

    if(sihti(balls, drawn)){
        cout << "The probability of guessing all " << drawn << " balls correctly is " << "1/" << laskuri(balls, drawn) << endl;
    }
    else{

    }


    return 0;
}
