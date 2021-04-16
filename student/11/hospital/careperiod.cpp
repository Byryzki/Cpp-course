#include "person.hh"
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

std::map<std::string, bool> CarePeriod::get_caretakers()
{
    return caretakers_;
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

bool CarePeriod::print_per_caretaker(std::string caretaker)
{
    bool has_patients(false);
    for(auto const &staff : caretakers_)
    {
        if(staff.first == caretaker)
        {
            has_patients = true;
            if(end_.is_default())   //kyseinen hoitojakso kesken
            {
                start_.print();
                std::cout << " - " << std::endl;
            }
            else
            {
                start_.print();
                std::cout << " - ";
                end_.print();
                std::cout << std::endl;
            }

            std::cout << "* Patient: " << patient_->get_id() << std::endl;
        }
    }
    return has_patients;
}

std::vector<std::string> CarePeriod::print_medicine()
{
    return patient_ -> get_medicines();
}
