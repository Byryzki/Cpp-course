#include <iostream>

using namespace std;

int main()
{
    cout << "How many numbers would you like to have? ";
    int amount = 0;
    cin >> amount;

    int lap = 1;
    while (lap <= amount){
        if (lap % 3 == 0 and lap % 7 != 0) {
            cout << "zip" << endl;
        }
        else if (lap % 7 == 0 and lap % 3 != 0){
            cout << "boing" << endl;
        }
        else if (lap % 7 == 0 and lap % 3 == 0){
            cout << "zip boing" << endl;
        }
        else cout << lap << endl;
        lap += 1;

    }

}
