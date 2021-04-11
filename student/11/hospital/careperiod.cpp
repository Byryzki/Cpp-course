#include "careperiod.hh"
#include "utils.hh"
#include <iostream>

CarePeriod::CarePeriod(const std::string& start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::CarePeriod(const Date &start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::~CarePeriod()
{
}

void CarePeriod::get_end(Date &today)
{
    end_ = today;
}

void CarePeriod::get_caretakers()
{

}

void CarePeriod::add_caretaker(std::string caretaker)
{
    bool replicant(false);
    for(auto employee : caretakers_)    //etsii päällekkäisyyden
    {
        if(employee == caretaker)
        {
            replicant = true;
            break;
        }
    }

    if(replicant)
    {
    }
    else
    {
        caretakers_.push_back(caretaker);
    }
}
