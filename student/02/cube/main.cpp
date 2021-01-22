#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a number: ";
    int nro = 0;
    cin >> nro;
    int cube = nro*nro*nro;
    int test = (cube/nro)/nro;

    if (test != nro){
        cout << "The cube of " << nro << " is not " << cube << "." << endl;
    }
    else{
        cout << "Error! The cube of " << nro << " is " << cube << "." << endl;
    }

    return 0;
}
