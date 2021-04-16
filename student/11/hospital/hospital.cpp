#include "hospital.hh"
#include "person.hh"
#include "utils.hh"
#include <iostream>
#include <set>

Hospital::Hospital()
{
}

Hospital::~Hospital()
{
    // Deallocating staff
    for( std::map<std::string, Person*>::iterator
         iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        delete iter->second;
    }

    // Remember to deallocate patients also
    for( std::map<std::string, Person*>::iterator
         iter = current_patients_.begin();
         iter != current_patients_.end();
         ++iter )
    {
        delete iter->second;
    }
}

void Hospital::recruit(Params params)
{
    std::string specialist_id = params.at(0);
    if( staff_.find(specialist_id) != staff_.end() )
    {
        std::cout << ALREADY_EXISTS << specialist_id << std::endl;
        return;
    }
    Person *new_specialist = new Person(specialist_id);
    staff_.insert({specialist_id, new_specialist});
    std::cout << STAFF_RECRUITED << std::endl;
}

void Hospital::enter(Params params)
{
    std::string patient_id(params.at(0));

    if(current_patients_.find(patient_id) != current_patients_.end()) // potilas jo hoidossa
    {
        std::cout << ALREADY_EXISTS << patient_id << std::endl;
        return;
    }

    Person *new_patient = new Person(patient_id);    //uusi potilas
    current_patients_.insert({patient_id, new_patient});

    CarePeriod *new_careperiod = new CarePeriod(utils::today, new_patient); //uuden potilaan uusi hoitojakso

    if(carehistory_.find(patient_id) != carehistory_.end()) //jos aikaisempia hoitoja
    {
        carehistory_[patient_id].push_back(new_careperiod);
    }
    else
    {
        std::vector<CarePeriod*> care_history;
        care_history.push_back(new_careperiod);

        carehistory_.insert({patient_id, care_history});    //uusi potilas ja hoitohistoria
    }

    std::cout << PATIENT_ENTERED << std::endl;
    return;
}

void Hospital::leave(Params params)
{
    std::string patient_id(params.at(0));

    if(current_patients_.find(patient_id) == current_patients_.end())   //potilas ei hoidossa
    {
        std::cout << CANT_FIND << patient_id <<std::endl;
        return;
    }
    else
    {
        current_patients_.erase(patient_id);    //potilas pois hoidettavista
    }

    carehistory_[patient_id].back() -> get_end(utils::today); //vanhalle hoitojaksolle päättymispv
    std::cout << PATIENT_LEFT << std::endl;

    return;
}

void Hospital::assign_staff(Params params)
{
    std::string caretaker_id(params.at(0));
    std::string patient_id(params.at(1));

    if(staff_.find(caretaker_id) == staff_.end())  //jos hoitaja puuttuu
    {
        std::cout << CANT_FIND << caretaker_id <<std::endl;
        return;
    }
    else if(current_patients_.find(patient_id) == current_patients_.end())  //jos potilas puuttuu
    {
        std::cout << CANT_FIND << patient_id <<std::endl;
        return;
    }
    else
    {
        carehistory_[patient_id].back() -> add_caretaker(caretaker_id);
        std::cout << STAFF_ASSIGNED << patient_id << std::endl;
        return;
    }
}

void Hospital::add_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string strength = params.at(1);
    std::string dosage = params.at(2);
    std::string patient = params.at(3);
    if( not utils::is_numeric(strength, true) or
        not utils::is_numeric(dosage, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->add_medicine(medicine, stoi(strength), stoi(dosage));
    std::cout << MEDICINE_ADDED << patient << std::endl;
}

void Hospital::remove_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string patient = params.at(1);
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->remove_medicine(medicine);
    std::cout << MEDICINE_REMOVED << patient << std::endl;
}

void Hospital::print_patient_info(Params params)
{
    std::string patient_id(params.at(0));

    if(current_patients_.find(patient_id) == current_patients_.end()) // potilas ei hoidossa
    {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }

    for(auto carep : carehistory_[patient_id])  //käy läpi potilaan hoitojaksot
    {
        carep -> print_careperiod();
    }
}

void Hospital::print_care_periods_per_staff(Params params)
{
    std::string caretaker_id(params.at(0));
    bool has_patients(false);

    if(staff_.find(caretaker_id) == staff_.end()) // hoitajaa ei ole
    {
        std::cout << CANT_FIND << caretaker_id << std::endl;
        return;
    }

    for(auto i = carehistory_.rbegin(); i != carehistory_.rend(); ++i)
    {
        std::string patient = i -> first;
        for(auto carep : carehistory_[patient])
        {
            if(carep -> print_per_caretaker(caretaker_id))
            {
                has_patients = true;
            }
        }
    }
    if(!has_patients)
    {
        std::cout << "None" << std::endl;
    }
}

void Hospital::print_all_medicines(Params)
{
    std::map<std::string, std::vector<std::string>> all_medicines;

    for(auto patient : carehistory_)
    {
        for(auto medptr : patient.second)    //yhden potilaan yksi hoitojakso
        {
            std::vector<std::string> meds = medptr -> print_medicine();

            for(auto const &medicine : meds)
            {
                if(all_medicines.find(medicine) != all_medicines.end()) //jos lääkkeen käyttäjiä
                {
                    all_medicines[medicine].push_back(patient.first);
                }
                else
                {
                    std::vector<std::string> patients;
                    patients.push_back(patient.first);

                    all_medicines.insert({medicine, patients});    //uusi lääke
                }
            }
        }
    }

    for(auto const &medicine : all_medicines)
    {
        std::cout << medicine.first << " prescribed for" << std::endl;
        for(auto const & patient_id : medicine.second)
        {
            std::cout << "* " << patient_id << std::endl;
        }
    }

    if(all_medicines.size() == 0)
    {
        std::cout << "None" << std::endl;
    }
}

void Hospital::print_all_staff(Params)
{
    if( staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }
    for( std::map<std::string, Person*>::const_iterator iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        std::cout << iter->first << std::endl;
    }
}

void Hospital::print_all_patients(Params)
{
    if(carehistory_.empty())
    {
        std::cout << "None" << std::endl;
    }

    for(auto patient : carehistory_)
    {
        std::cout << patient.first << std::endl;
        for(auto carep : patient.second)
        {
            carep -> print_careperiod();
        }
    }
}

void Hospital::print_current_patients(Params)
{
    if( current_patients_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }

    for(auto patient : current_patients_)
    {
        std::cout << patient.first << std::endl;
        for(auto carep : carehistory_[patient.first])
        {
            carep -> print_careperiod();
        }
    }
}

void Hospital::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not utils::is_numeric(day, false) or
        not utils::is_numeric(month, false) or
        not utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::advance_date(Params params)
{
    std::string amount = params.at(0);
    if( not utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}
