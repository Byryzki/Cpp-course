/* Class CarePeriod
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a patient's care period in hospital.
 *
 * Note: Students need to implement almost all of this class by themselves.
 * */
#ifndef CAREPERIOD_HH
#define CAREPERIOD_HH

#include "person.hh"
#include "date.hh"
#include <string>

class CarePeriod
{
public:
    // Constructor, start date given as a string (ddmmyyyy).
    CarePeriod(const std::string& start, Person* patient);

    // Constructor, start date given as a Date object.
    CarePeriod(const Date& start, Person* patient);

    // Destructor.
    ~CarePeriod();

    // More public methods
    void get_end(Date &today);

    std::map<std::string, bool> get_caretakers();

    void add_caretaker(std::string caretaker);

    void print_careperiod();

    bool print_per_caretaker(std::string caretaker);

    std::vector<std::string> print_medicine();

private:
    Person* patient_;
    Date start_;
    Date end_;

    // More attributes and methods
    std::map<std::string, bool> caretakers_;    //yksittäisen hoitojakson hoitajat

};

#endif // CAREPERIOD_HH
