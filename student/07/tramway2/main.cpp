/*
    Ohjelman kirjoittaja
    Nimi: Pyry Laine
    Opiskelijanro: 050282836
    GIT-käyttäjätunnus: smpyla
    Sähköposti: pyry.j.laine@tuni.fi

    RASSE -projekti
    Tämä ohjelma simuloi pysäkkitieto-ohjelmaa tulevalle Tampereen raitiovaunulle. Ohjelmaan syötetään
    vapaavalintainen, mutta määrämuotoinen tekstitiedosto, josta ohjelma tallentaa sisäkkäiseen tietorakenteeseensa
    pysäkin linjan, nimen ja sen etäisyyden ns. lähtöpysäkistä. Tiedoston syötön jälkeen käyttäjä voi
    lisätä, poistaa tai tutkia haluamaansa pysäkkiä tai linjaa kahdeksalla eri komennolla:
     LINES: ohjelma tulostaa kaikki linjat aakkosjärjestyksessä.
    LINE <linja>: tulostaa tiedoston määrittämässä järjestyksessä pysäkin ja sen etäisyyden lähtöpysäkistä.
    STOPS: tulostaa aakkosjärjestyksessä kaikki pysäkit.
    STOP <pysäkki>: tulostaa aakkosjärjestyksessä linjat, joihin pysäkki sisältyy.
    DISTANCE <linja><pysäkki1><pysäkki2>: etäisyys kahden samalla linjalla sijaitsevan pysäkin välillä.
    ADDLINE <linja>: lisätään kokonaan uusi linja (ei sisällä pysäkkejä).
    ADDSTOP <linja><pysäkki>: lisää pysäkin tiettyyn linjaan.
    REMOVE <pysäkki>: poistaa kyseisen pysäkin kaikista linjoista.
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
#include<bits/stdc++.h>

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

std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    // jakaa tiedostorivin termit vektoriin

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

// kaksi seuraavaa apufunktioita termien vertailuun
bool double_compare(std::pair<std::string, double>& a, std::pair<std::string, double>& b)
{
    return a.second < b.second;
}

bool str_compare(std::string a, std::string b)
{
    return a < b;
}

std::vector<std::pair<std::string, double>> value_sort(std::map<std::string, double> line)
{
    // Luo listan linjan pysäkeistä etäisyysjärjestyksessä

    std::vector<std::pair<std::string, double>> sorted;
    for(auto& stop : line)
    {
        sorted.push_back(stop);
    }

    sort(sorted.begin(), sorted.end(), double_compare);

    return sorted;
}

void LINE(std::map<std::string, std::map<std::string, double>> routes, std::string line)
{   
    if(routes.find(line) != routes.end())
    {
         std::cout << "Line " << line << " goes through these stops in the order they are listed:" << std::endl;

        std::vector<std::pair<std::string, double>> sorted = value_sort(routes[line]);
        for(auto stop : sorted)
        {
            std::cout << " - " << stop.first << " : " << stop.second << std::endl;
        }
    }
    else
    {
        std::cout << "Error: Line could not be found." << std::endl;
    }
}

void LINES(std::map<std::string, std::map<std::string, double>> routes)
{
    for(std::map<std::string, std::map<std::string, double>>::iterator line = routes.begin(); line != routes.end(); line++)
    {
        std::cout << line -> first << std::endl;
    }
}

void STOPS(std::map<std::string, std::map<std::string, double>> routes)
{
    std::vector<std::string> submap;

    for(std::map<std::string, std::map<std::string, double>>::iterator line = routes.begin(); line != routes.end(); line++)
    {
        for(std::map<std::string, double>::iterator stop = routes[line -> first].begin(); stop != routes[line -> first].end(); stop++)
        {
            submap.push_back(stop -> first);
        }
    }

    // aakkosjärjestys ja toisto pois
    sort(submap.begin(), submap.end(), str_compare);
    std::vector<std::string>::iterator stops = std::unique(submap.begin(), submap.end());
    submap.resize(std::distance(submap.begin(), stops));

    for(stops = submap.begin(); stops != submap.end(); ++stops)
    {
        std::cout << *stops << std::endl;
    }
}

void STOP(std::map<std::string, std::map<std::string, double>> routes, std::string target)
{
    std::vector<std::string> lines;
    bool empty = true;

    for(std::map<std::string, std::map<std::string, double>>::iterator line = routes.begin(); line != routes.end(); line++)
    {
        for(std::map<std::string, double>::iterator stop = routes[line -> first].begin(); stop != routes[line -> first].end(); stop++)
        {
            if(stop -> first == target)
            {
                empty = false;
                lines.push_back(line -> first);
            }
        }
    }
    if(empty) // tuntematon pysäkki
    {
        std::cout << "Error: Stop could not be found." << std::endl;
    }
    else
    {
        std::cout << "Stop " << target << " can be found on the following lines:" << std::endl;
        for(auto& i : lines)
        {
            std::cout << " - " << i << std::endl;
        }
    }
}

void DISTANCE(std::map<std::string, std::map<std::string, double>> routes, std::string line, std::string stop1, std::string stop2)
{
    if(routes.find(line) != routes.end()) // linja löytyy
    {
        double a = 200 , b = -100;
        double distance;

        std::vector<std::pair<std::string, double>> sorted = value_sort(routes[line]);
        for(auto stop : sorted)
        {
            if(stop.first == stop1)
            {
                b = stop.second;
            }
            else if(stop.first == stop2)
            {
                a = stop.second;
            }
    }

        distance = a - b;
        if(distance >= 100)
        {
            std::cout << "Error: Stop could not be found" << std::endl;
        }
        else
        {
            std::cout << "Distance between " << stop1 << " and " << stop2 << " is " << distance << std::endl;
        }
    }
    else
    {
        std::cout << "Error: Line could not be found." << std::endl;
    }
}

void ADDLINE(std::map<std::string, std::map<std::string, double>>& routes, std::string line)
{
    if(routes.find(line) == routes.end())
    {
        routes[line] = {}; // uusi tietopari ylämappiin
        std::cout << "Line was added." << std::endl;
    }
    else
    {
        std::cout << "Error: Stop/line already exists." << std::endl;
    }
}

void ADDSTOP(std::map<std::string, std::map<std::string, double>>& routes, std::string line, std::string new_stop, double distance)
{
    bool error = false;

    for(std::map<std::string, double>::iterator stop = routes[line].begin(); stop != routes[line].end(); stop++)
    {
        if(stop -> first == new_stop)
        {
            error = true;
        }
        else if(stop -> second == distance)
        {
            error = true;
        }
    }

    if(error == false) // ei päällekkäisyyksiä alamapissa
    {
        if(routes.find(line) != routes.end()) // linja on ylämapissa
        {
            routes[line][new_stop] = distance; // uusi tietopari alamappiin
            std::cout << "Stop was added." << std::endl;
        }
        else
        {
            std::cout << "Error: Stop/line already exists." << std::endl;
        }
    }
    else
    {
        std::cout << "Error: Stop/line already exists." << std::endl;
    }
}

void REMOVE(std::map<std::string, std::map<std::string, double>>& routes, std::string dstop)
{
    bool empty = true;
    for(std::map<std::string, std::map<std::string, double>>::iterator line = routes.begin(); line != routes.end(); line++) // käydään läpi linjojen pysäkit
    {
        const auto hit = routes[line -> first].find(dstop);
        if(hit != routes[line -> first].end())
        {
            routes[line -> first].erase(hit);
            empty = false;
        }
    }

    if(empty)
    {
        std::cout << "Error: Stop could not be found." << std::endl;
    }
    else
    {
        std::cout << "Stop was removed from all lines." << std::endl;
    }

}

std::vector<std::string> name_repair(std::string command, char del)
{
    // mikäli lainausmerkillinen nimi, poistaa ne ja yhdistää nimen yhdeksi termiksi.

    bool quote = false;

    for(auto& mark : command)
    {
        if(mark == del)
        {
            quote = true;
            break;
        }
    }
    command.erase(std::remove(command.begin(), command.end(), del), command.end()); // lainausmerkkien poisto

    std::vector<std::string> cmd = split(command, ' ', true);
    std::vector<std::string> repaired;

    transform(cmd.at(0).begin(), cmd.at(0).end(), cmd.at(0).begin(), ::tolower);

    if(quote) // toimenpiteet mikäli erotinmerkkejä
    {
        std::string name;
        if(cmd.size() == 3)
        {
            name = cmd.at(1) + ' ' + cmd.at(2);

            repaired.push_back(cmd.at(0));
            repaired.push_back(name);
        }
        return repaired;
    }
    else
    {
        return cmd;
    }
}

void UI(std::map<std::string, std::map<std::string, double>> routes)
{
    // ohjelman käyttöjärjestelmä

    if(routes.size() > 0)
    {
        while(true)
        {
            std::cout << "tramway> ";
            std::string command;
            getline(std::cin, command);

            std::vector<std::string> cmd = name_repair(command, '"');

            /* cmd.at(0): komento, cmd.at(1): linja tai pysäkki yms. */
            if(cmd.at(0) == "lines")
            {
                if(cmd.size() == 1)
                {
                    std::cout << "All tramlines in alphabetical order:" << std::endl;
                    LINES(routes);
                }
                else
                {
                    std::cout << "Error: Invalid input." << std::endl;
                }
            }

            else if(cmd.at(0) == "line")
            {
                if(cmd.size() == 2)
                {
                    LINE(routes, cmd.at(1));
                }
                else
                {
                    std::cout << "Error: Invalid input." << std::endl;
                }
            }

            else if(cmd.at(0) == "stops")
            {
                if(cmd.size() == 1)
                {
                    std::cout << "All stops in alphabetical order:" << std::endl;
                    STOPS(routes);
                }
                else
                {
                    std::cout << "Error: Invalid input." << std::endl;
                }
            }

            else if(cmd.at(0) == "stop")
            {
                if(cmd.size() == 2)
                {
                    STOP(routes, cmd.at(1));
                }
                else
                {
                    std::cout << "Error: Invalid input." << std::endl;
                }
            }

            else if(cmd.at(0) == "distance")
            {
                if(cmd.size() == 4)
                {
                    DISTANCE(routes, cmd.at(1), cmd.at(2), cmd.at(3));
                }
                else
                {
                    std::cout << "Error: Invalid input." << std::endl;
                }
            }

            else if(cmd.at(0) == "addline")
            {
                if(cmd.size() == 2)
                {
                    ADDLINE(routes, cmd.at(1));
                }
                else
                {
                    std::cout << "Error: Invalid input." << std::endl;
                }
            }

            else if(cmd.at(0) == "addstop")
            {
                if(cmd.size() == 4)
                {
                    ADDSTOP(routes, cmd.at(1), cmd.at(2), stod(cmd.at(3)));
                }
                else
                {
                    std::cout << "Error: Invalid input." << std::endl;
                }
            }

            else if(cmd.at(0) == "remove")
            {
                if(cmd.size() == 2)
                {
                    REMOVE(routes, cmd.at(1));
                }
                else
                {
                    std::cout << "Error: Invalid input." << std::endl;
                }
            }
            else if(cmd.at(0) == "quit")
            {
                break;
            }
            else
            {
                std::cout << "Error: Invalid input." << std::endl;
            }

        }
    }
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

bool map_n_check(std::map<std::string, std::map<std::string, double>>& routes)
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
                std::cout << "Error: Invalid format in file." << std::endl;
                return false;
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
                return false;
            }
            if(routes.find(row_terms.at(0)) != routes.end()) //linja on ylämapissa?
            {
                routes[row_terms.at(0)].insert({row_terms.at(1) , distance}); // tietorakenteeseen lisäys
            }
            else // uusi linja
            {
                routes[row_terms.at(0)][row_terms.at(1)] = distance; // uuteen linjaan lisäys
            }
        }

    }
    else
    {
        std::cout << "Error: File could not be read." << std::endl;
        return false;
    }
    
    inf.close();

    return true;
}

// Short and sweet main.
int main()
{
    print_rasse();
    
    std::map<std::string, std::map<std::string, double>> routes;
    if(map_n_check(routes))
    {
        UI(routes);
    }
    else
    {
        return 1;
    }
    return 0;
}
