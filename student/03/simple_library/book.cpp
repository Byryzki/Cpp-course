#include "book.hh"
#include "date.hh"
#include <string>
#include <iostream>

using namespace std;

Book::Book(const string& writer, const string& name):
        writer_(writer), name_(name), available_(true), loan_date_(Date(1,1,1)), expiry_date_(Date(1,1,1))

{


}

void Book::print(){
    cout << writer_ << " : " << name_ << endl;
    if(available_ == false){
        cout << "- loaned: ";
        loan_date_.print();
        cout << "- to be returned: ";
        expiry_date_.print();

    }
    else if(available_ == true){
        cout << "- available" << endl;
    }
}

void Book::loan(const Date& loan_date){
    if(available_ == false){
        cout << "Already loaned: cannot be loaned" << endl;
        return;
    }
    else{
        available_ = false;
        loan_date_ = loan_date;
        expiry_date_ = loan_date;
        expiry_date_.advance(28);
    }
}

void Book::renew(){
    if(available_ == true){
        cout << "Not loaned: cannot be renewed" << endl;
        return;
    }
    else{
        expiry_date_.advance(28);
    }
}

void Book::give_back(){
    available_ = true;
}
