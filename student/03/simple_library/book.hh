#ifndef BOOK_HH
#define BOOK_HH

#include <string>
#include <date.hh>

class Date;

class book
{
public:
    book(const std::string& writer, const std::string& name);

    void print();
    void loan(const Date& loan_date);
    void renew();
    void give_back();

private:
    const std::string writer_;
    const std::string name_;
    bool available_;
    Date loan_date_;
    Date expiry_date_;

};

#endif // BOOK_HH
