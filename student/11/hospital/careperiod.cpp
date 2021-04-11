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
    caretakers_.insert({caretaker, true});
}

void CarePeriod::print_careperiod()
{
    if(end_.is_default())   //kyseinen hoitojakso kesken
    {
        std::cout << "* Care period: ";
        start_.print();
        std::cout << " - " << std::endl;
    }
    else
    {
        std::cout << "* Care period: ";
        start_.print();
        std::cout << " - ";
        end_.print();
        std::cout << std::endl;
    }

    std::cout << "  - Staff: ";
    if(caretakers_.size() == 0)
    {
        std::cout << "None" << std::endl;
    }
    else
    {
        for(auto caretaker : caretakers_)
        {
            std::cout << caretaker.first << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "* Medicines:";
    patient_-> print_medicines("  - ");
}
