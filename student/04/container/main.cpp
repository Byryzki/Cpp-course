#include <cstdlib>
#include <iostream>
#include <vector>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        // TODO: Implement your solution here
        ints.push_back(new_integer);

    }
}

// TODO: Implement your solution here
bool same_values(std::vector<int> integers){
    int samat = 0;
    int pituus = integers.size();

    for(int alkio : integers){
        if(alkio == integers.front()){
            samat += 1;
        }
        else{

        }
    }
    if(samat == pituus){
        return true;
    }
    else{

    }

    return false;
}

bool is_ordered_non_strict_ascending(std::vector<int> integers){
    int on = 0;

    for(int i = 0; i < int (integers.size()); ++i){
        if(i == 0){
            on += 1;
        }
        else if(i != 0 and integers[i] >= integers[i-1]){
            on += 1;
        }
        else{

        }
    }
    if(on == int (integers.size())){
        return true;
    }
    return false;
}

bool is_arithmetic_series(std::vector<int> integers){
    int on = 0;
    int oikea = integers[1] - integers[0];

    for(int i = 0; i < int (integers.size()); ++i){
        if(i == 0){
            on += 1;
        }
        else if(i != 0 and integers[i] - integers[i-1] == oikea){
            on += 1;
        }
        else{

        }
    }
    if(on == int (integers.size())){
        return true;
    }
    return false;
}

bool is_geometric_series(std::vector<int> integers){
    int on = 0;
    int oikea = integers[1] / integers[0];

    for(int i = 0; i < int (integers.size()); ++i){
        if(i == 0){
            on += 1;
        }
        else if(i != 0 and integers[i] / integers[i-1] == oikea){
            on += 1;
        }
        else{

        }
    }
    if(on == int (integers.size())){
        return true;
    }
    return false;
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
