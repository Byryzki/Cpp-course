#include <iostream>
#include <string>
#include <vector>

using namespace std;

// TODO: Implement split function here
// Do not change main function
vector<string> split(string txt, char erotin, bool eityh = false){
    if(eityh == false){
        vector<string> eka;
        for(int i = 0; i < int(txt.size()); ++i){
            string sana = "";
            if(char (txt[i]) == erotin){
                eka.push_back(sana);
                sana = "";

            }
            else{
                sana += txt[i];
            }
        }
    }

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
