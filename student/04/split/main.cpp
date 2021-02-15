#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

// TODO: Implement split function here
// Do not change main function
vector<string> split(string txt, char erotin, bool eityh = false){

    vector<string> vec;
    char merkki;
    string merkit = "";

    for(string::size_type i = 0; i < txt.size(); i++)
    {
        merkki = txt.at(i);
        if(merkki == erotin)
        {
            if(eityh == true and merkit == "")
            {
                continue;
            }
            else
            {
                vec.push_back(merkit);
                merkit = "";
            }
        }
        else
        {
            merkit += merkki;
        }
    }

    vec.push_back(merkit);
    return vec;
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
