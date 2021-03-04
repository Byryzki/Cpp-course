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
#include <set>
#include <iomanip>

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
std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    // jakaa tiedostorivin termit käytettävään muotoon

    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }

    return result;
}

int LINE(std::map<std::string, std::map<std::string, double>> routes, std::string line)
{
    for(std::map<std::string, double>::iterator i = routes[line].begin(); i != routes[line].end(); i++) // lisää loop alamapille.
    {
        std::cout << " - " << i -> first << " : " << i -> second << std::endl;
    }

    return 0;
}

int LINES(std::map<std::string, std::map<std::string, double>> routes)
{
    for(std::map<std::string, std::map<std::string, double>>::iterator i = routes.begin(); i != routes.end(); i++)
    {
        std::cout << i -> first << std::endl;
    }

    return 0;
}

int UI(std::map<std::string, std::map<std::string, double>> routes)
{
    while(true)
    {
        std::cout << "tramway> ";
        std::string command;
        getline(std::cin, command);

        std::vector<std::string> cmd = split(command, ' ', true);

        /* cmd.at(0): komento, cmd.at(1): linja tai pysäkki yms. */
        if(cmd.at(0) == "LINES")
        {
            std::cout << "All tramlines in alphabetical order:" << std::endl;
            LINES(routes);
        }

        else if(cmd.at(0) == "LINE")
        {
            std::cout << "Line " << cmd.at(1) << " goes through these stops in the order they are listed:" << std::endl;
            LINE(routes, cmd.at(1));
        }

        else if(cmd.at(0) == "STOPS")
        {

        }

        else if(cmd.at(0) == "STOP")
        {

        }

        else if(cmd.at(0) == "DISTANCE")
        {

        }

        else if(cmd.at(0) == "ADDLINE")
        {

        }

        else if(cmd.at(0) == "ADDSTOP")
        {

        }

        else if(cmd.at(0) == "REMOVE")
        {

        }
        else
        {
            std::cout << "Error: Invalid input." << std::endl;
        }

    }
    return EXIT_SUCCESS;
}

bool duplicates(std::map<std::string, std::map<std::string, double>> routes, std::vector<std::string> row_terms)
{
    // tutkii onko linjalla sama pysäkki monesti.
    std::map<std::string, double>::iterator stopiter;

    if(routes.find(row_terms.at(0)) != routes.end()) //linja löytyy
    {
        for(auto stop : routes[row_terms.at(0)])
        {
           if(stop.first == row_terms.at(1)) //sama pysäkki monesti linjalla
           {
                 return false;
           }

           if(stop.second == stod(row_terms.at(2))) //sama etäisyys monesti linjalla
           {
                 return false;
           }
        }

    }


    return true; // ei samoja linjalla
}

bool row_check(std::vector<std::string> row_terms)
{
    // tutkii onko tiedostorivissä oikea määrä termejä

    if(row_terms.size() == 3 or row_terms.size() == 2)
    {
        if(row_terms.at(0) != "" and row_terms.at(1) != "")
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    else
    {
    return true;
    }
}

int map_n_check(std::map<std::string, std::map<std::string, double>>& routes)
{
    // suorittaa tiedostoon liittyvät tarkistukset ja luo sisäkkäiset tietorakenteet

    std::string ifile;
    std::cout << "Give a name for input file: ";
    getline(std::cin, ifile);

    std::ifstream inf(ifile);

    if(inf) // onnistuuko tiedoston avaus?
    {
        std::string row;

        while(getline(inf, row)) //riviloop
        {
            std::vector<std::string> row_terms = split(row, ';', true); //termivectori

            if(row_check(row_terms))
            {
                return EXIT_FAILURE;
            }

            /* 1. rowterm: linja, 2. rowterm: pysäkki, 3. rowterm: etäisyys (double) */
            double distance;

            if(row_terms.size() == 2) //etäisyys tyhjä
            {
                distance = 0.0;
            }
            else
            {
                distance = stod(row_terms.at(2));
            }

            if(duplicates(routes, row_terms) == false)
            {
                std::cout << "Error: Stop/line already exists." << std::endl;
                return EXIT_FAILURE;
            }
            if(routes.find(row_terms.at(0)) != routes.end()) //pysäkki on ylämapissa?
            {
                if(routes[row_terms.at(0)].find(row_terms.at(1)) != routes[row_terms.at(0)].end())
                {
                    continue;
                }
            }
            else
            {
                routes[row_terms.at(0)][row_terms.at(1)] = distance; // tietopari alamappiin
            }
        }

    }
    else
    {
        std::cout << "Error! The file could not be read." << std::endl;
        return EXIT_FAILURE;
    }
    
    inf.close();

    return 0;
}

int main()
{
    print_rasse();
    
    std::map<std::string, std::map<std::string, double>> routes;
    map_n_check(routes);

    UI(routes);


    return EXIT_SUCCESS;
}
