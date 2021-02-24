#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
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

using Network = std::map<std::string, std::vector<std::string>>;

void store(Network& mp, const std::string& id1, std::string& id2)
{
    if(mp.count(id1) == 0) // luodaan tyhjät sisäkkäiset tietoparit
    {
        mp[id1] = {};
    }
    if(mp.count(id2) == 0)
    {
        mp[id2] = {};
    }

    mp.at(id1).push_back(id2);
}

void print(Network& mp, const std::string& nykyid, const int depth = 0)
{
   for(int i = 0; i < depth; ++i)
   {
       std::cout << "..";
   }

   std::cout << nykyid << std::endl;
   for(const std::string& child : mp.at(nykyid))
   {
       print(mp, child, depth + 1);
   }

}

int count(const Network& mp, const std::string& nykyid, bool cntself = false)
{
    int childcount = 0;
    if(cntself)
    {
        childcount = 1;
    }

    for(const std::string& child : mp.at(nykyid))
    {
        childcount += count(mp, child, true);
    }

    return childcount;
}

int depth(const Network& mp, const std::string& nykyid, int depthtmp = 1)
{
    int maxchilddepth = depthtmp;

    for(const std::string& child : mp.at(nykyid))
    {
        int current_childdepth = depth(mp, child, depthtmp + 1);
        maxchilddepth = std::max(maxchilddepth, current_childdepth);
    }

    return maxchilddepth;
}

int main()
{
    // TODO: Implement the datastructure here
    Network verkosto;
    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            store(verkosto, id1, id2);

        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!

            print(verkosto, id);

        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::cout << count(verkosto, id) << std::endl;

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::cout << depth(verkosto, id) << std::endl;

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
