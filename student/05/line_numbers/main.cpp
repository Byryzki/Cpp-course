#include <iostream>
#include <fstream>
#include <string>


int main()
{
    std::string tnimi;
    std::cout << "Input file: ";
    getline(std::cin, tnimi);

    std::string uusinimi;
    std::cout << "Output file: ";
    getline(std::cin, uusinimi);

    std::ifstream tiedosto(tnimi);
    if(not tiedosto)
    {
        std::cout << "virhe" << std::endl;
    }
    else
    {
        std::string rivi;
        int rivinro = 1;

        std::ofstream uusit(uusinimi);

        while(getline(tiedosto, rivi))
        {
            uusit << rivinro << " " << rivi << std::endl;

            rivinro += 1;
        }

        tiedosto.close();
        uusit.close();
    }

    return 0;
}
