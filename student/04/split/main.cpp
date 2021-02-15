#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

// TODO: Implement split function here
// Do not change main function
vector<string> split(string txt, char erotin, bool eityh = false){

    size_t start;
    size_t end = 0;
    vector<string> valmis;
    vector<string> valmis2;

    while ((start = txt.find_first_not_of(erotin, end)) != string::npos) //tallentaa merkkijono kerrallaan vektoriin valmis
    {
        end = txt.find(erotin, start);
        valmis.push_back(txt.substr(start, end - start));

        if(txt.substr(start, end - start).find_first_not_of(" ") != string::npos){
            valmis2.push_back(txt.substr(start, end - start));
        }
    }

    if(eityh == true){
     return valmis2;
    }
    else{

    }
    return valmis;
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
