/*
    Pyry Laine 050282836
    RASSE -projekti
 */


#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>

// The most magnificent function in this whole program.
// Prints a RASSE
void print_rasse()
{
    std::cout <<
                 "=====//==================//===\n"
                 "  __<<__________________<<__   \n"
                 " | ____ ____ ____ ____ ____ |  \n"
                 " | |  | |  | |  | |  | |  | |  \n"
                 " |_|__|_|__|_|__|_|__|_|__|_|  \n"
                 ".|                  RASSE   |. \n"
                 ":|__________________________|: \n"
                 "___(o)(o)___(o)(o)___(o)(o)____\n"
                 "-------------------------------" << std::endl;
}

// Short and sweet main.


int main()
{
    print_rasse();

    std::map<std::string, std::map<std::string, int>> reitit;
    std::map<std::string, std::map<std::string, int>>::iterator ylaiter;
    std::map<std::string, int>::iterator alaiter;

    std::string ifile;
    std::cout << "Give a name for input file: ";
    getline(std::cin, ifile);

    std::ifstream inf(ifile);

    if(not inf) // onnistuuko tiedoston avaus?
    {
        std::cout << "Error! The file " << ifile << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }

    else
    {
        std::string rivi;


        while(getline(inf, rivi)) //rivi rekursio
        {
            std::vector<std::string> rivi_termit;

            size_t pos = 0;
            while((pos = rivi.find(";")) != std::string::npos) // termien rekursio
            {
                std::string sana = rivi.substr(0, pos);
                rivi.erase(0, pos+1);

                rivi_termit.push_back(sana);
            }

            if(rivi_termit.size() > 3 or rivi_termit.size() < 2 or rivi_termit.at(0) == "") //formaattitestit
            {
                std::cout << "Error: Invalid format in file." << std::endl;
                return EXIT_FAILURE;
            }
            else
            {
               if(reitit.find(rivi_termit.at(0)) == reitit.end()) // linja ei vielä ylämapissa
               {
                   reitit.insert({rivi_termit.at(0), {rivi_termit.at(1), rivi_termit.at(2)}}); // lisää tarkastus samoille alamapin termeille
               }
               else // linja jo ylämapissa
               {
                   if(rivi_termit.at(2) == "") // jos rivi koostuu kahdesta termistä
                   {
                       reitit[rivi_termit.at(0)][rivi_termit.at(1)] = 0;
                   }
                   else
                   {
                       reitit[rivi_termit.at(0)][rivi_termit.at(1)] = stoi(rivi_termit.at(2));
                   }
               }
            }
        }
    }
    return EXIT_SUCCESS;
}
