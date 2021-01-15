#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";
    int temp = 0;
    cin >> temp;

    double cel = (temp - 32) / 1.8;
    double far = temp * 1.8 +32;

    cout << temp << " degrees Celsius is " << far << " degrees in Farenheit" << endl;
    cout << temp << " degrees Farenheit is " << cel << " degrees in Celsius" << endl;

    return 0;
}
