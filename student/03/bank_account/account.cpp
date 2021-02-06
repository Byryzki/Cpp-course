#include "account.hh"
#include <iostream>

using namespace std;

Account::Account(const std::string& owner, bool has_credit, int money, int credit):
    owner_(owner), has_credit_(has_credit), money_(money), credit_(credit)
{
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);

    Account::iban_ = iban_;
}

void Account::print() const{
    cout<< owner_ << " : " << iban_ << " : " << money_ << " euros" << endl;
}

void Account::set_credit_limit(int raha){
    credit_ += raha;
}

void Account::save_money(int raha){
    money_ += raha;
}

void Account::take_money(int raha){
    if(has_credit_ == false and money_ - raha < 0){
        cout << "Cannot take money: balance underflow" << endl;
    }
    else if(has_credit_ == true and money_ + credit_ - raha < 0){
        cout << "Cannot take money: balance underflow" << endl;
    }
    else{
        money_ -= raha;
        cout << raha << " euros taken: new balance of "<< iban_ << " is " << money_ << " euros" << endl;
    }

}

void Account::transfer_to(Account& object, int raha){
    if(has_credit_ == false and money_ - raha < 0){
        cout << "Cannot take money: balance underflow" << endl;
        cout << "Transfer from " << iban_ << " failed" << endl;
     }
    else if(has_credit_ == true and money_ + credit_ - raha < 0){
        cout << "Cannot take money: credit limit overflow" << endl;
        cout << "Transfer from " << iban_ << " failed" << endl;
    }
    else if(has_credit_ == true and money_ + credit_ - raha > 0){
        money_ -= raha;
        object.save_money(raha);
        cout << raha << " euros taken: new balance of " << iban_ << " is " << money_ << " euros" << endl;

    }
    else{
        money_ -= raha;
        object.save_money(raha);
        cout << raha << "euros taken: new balance of " << iban_ << " is " << money_ << "euros" << endl;
    }




}
