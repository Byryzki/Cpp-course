#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

int main()
{
    std::string ifile;
    std::cout << "Input file: ";
    getline(std::cin, ifile);

    std::ifstream inf(ifile);

    if(not inf)
    {
        std::cout << "Error! The file " << ifile << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    else
    {
        map<string, int> montako;
        vector<int> rivit;
        std::string rivi;
        int rivinro = 1;

        while(getline(inf, rivi)) //rivi rekursio
        {
            size_t pos = 0;
            while((pos = rivi.find(" ")) != string::npos) // viimeinen sana puuttuu
            {
                string sana = rivi.substr(0, pos);
                rivi.erase(0, pos+1);

                if(montako.find(sana) != montako.end())
                {
                    montako.at(sana) += 1;
                }
                else
                {
                    montako.insert({sana, 1});

                }
            }

            if(montako.find(rivi) != montako.end())
            {
                montako.at(rivi) += 1;
            }
            else
            {
                montako.insert({rivi, 1});

            }

            rivinro += 1;
        }
        inf.close();

        map<string, int>::iterator iter = montako.begin();
        while(iter != montako.end())
        {
            cout << iter-> first << ": " << iter-> second << endl;
            ++iter;
        }
    }

    return 0;
}
