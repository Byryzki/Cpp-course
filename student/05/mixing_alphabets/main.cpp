#include <iostream>
#include <string>
#include <algorithm>
#include <random>

int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word;
    std::vector <std::string> kumma;

    while (std::cin >> word)
    {
        if (word == "END")
        {
            std::vector<std::string>::iterator lapi = kumma.begin();

            while(lapi != kumma.end())
            {
                std::cout << *lapi << std::endl;
                ++lapi;
            }

            return EXIT_SUCCESS;
        }

        // TODO: implement your solution here
        shuffle(++word.begin(), --word.end(), generator);
        kumma.push_back(word);
    }

}
