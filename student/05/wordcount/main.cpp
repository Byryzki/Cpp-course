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
        map<string, vector<int>> rivit;
        vector<string> sanat;
        std::string rivi;
        int rivinro = 1;

        while(getline(inf, rivi)) //rivi rekursio
        {
            size_t pos = 0;
            while((pos = rivi.find(" ")) != string::npos)
            {
                string sana = rivi.substr(0, pos);
                rivi.erase(0, pos+1);

                sanat.push_back(sana);

                if(rivit.find(sana) != rivit.end()) //onko sana jo?
                {
                    rivit.at(sana).push_back(rivinro);
                }
                else
                {
                    rivit.insert({sana, {rivinro}}); //uusi tietopari
                }
            }
            sanat.push_back(rivi);
            if(rivit.find(rivi) != rivit.end())
            {
                rivit.at(rivi).push_back(rivinro);
            }
            else
            {
                rivit.insert({rivi, {rivinro}}); //uusi tietopari
            }

            ++rivinro;
         }

         map<string, vector<int>>::iterator iter = rivit.begin();

         while(iter != rivit.end()) //määrä ja rivit
         {
            auto end = iter -> second.end(); // samojen rivinro poisto
            for (auto it = iter -> second.begin(); it != end; ++it)
            {
               end = std::remove(it + 1, end, *it);
            }
            iter -> second.erase(end, iter -> second.end());

            int maara = iter -> second.size(); //count(sanat.begin(), sanat.end(), iter -> first);

            cout << iter -> first << " " << maara << ": ";

            for(string::size_type i = 0; i < iter-> second.size(); ++i) //rivien tulostus
            {

                if(i+1 == iter-> second.size())
                {
                    cout << iter -> second.at(i) << endl;
                }
                else
                {
                cout << iter -> second.at(i) << ", ";
                }
            }
            ++iter;
         }

        }

   return 0;
}
