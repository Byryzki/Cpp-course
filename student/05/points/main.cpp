#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

int main()
{
    string ifile;
    cout << "Input file: ";
    getline(cin, ifile);

    map <string, int> bongot;
    char deli = ':';

    ifstream inf(ifile);
    if(not inf)
    {
        cout << "Error! The file " << ifile << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    else
    {
        string rivi;

        while(getline(inf, rivi))
        {
            string name = rivi.substr(0, rivi.find(deli));
            string points = rivi.substr(rivi.find(deli)+1, string::npos);
            int point = stoi(points);

            if(bongot.find(name) != bongot.end())
            {
                bongot.at(name) += point;
            }
            else
            {
                bongot.insert({name, point});
            }
        }
        inf.close();

        cout << "Final scores:" << endl;

        map<string, int>::iterator iter = bongot.begin();
        while(iter != bongot.end())
        {
            cout << iter-> first << ": " << iter-> second << endl;
            ++iter;
        }

    }
    return 0;
}
