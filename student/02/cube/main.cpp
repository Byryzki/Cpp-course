#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a number: ";
    int nro = 0;
    cin >> nro;

    if(nro == 0){
            cout << "The cube of " << nro << " is " << nro << "." << endl;
   }
    else{
        int cube = nro*nro*nro;
        int test = (cube/nro)/nro;
    if (test != nro){
        cout << "Error! The cube of " << nro << " is not " << cube << "." << endl;
    }

    else{
        cout << "The cube of " << nro << " is " << cube << "." << endl;
    }
   }

    return 0;
}
