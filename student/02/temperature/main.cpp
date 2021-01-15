#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";
    int temp = 0;
    cin >> temp;

    double cel = (temp - 32) / 1.8;
    double far = temp * 1.8 +32;

    cout << temp << " degrees Celsius is " << far << " degrees Fahrenheit" << endl;
    cout << temp << " degrees Fahrenheit is " << cel << " degrees Celsius" << endl;

    return 0;
}
