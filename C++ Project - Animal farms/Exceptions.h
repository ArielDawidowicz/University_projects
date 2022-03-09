#ifndef UNTITLED_EXCEPTIONS_H
#define UNTITLED_EXCEPTIONS_H
#include <iostream>
#include <exception>
using namespace std;

class CowException : public  exception{
public:
    virtual const char* what() const throw(){return "Insert valid number of cow farms";}
};

class SheepException : public  exception{
public:
    virtual const char* what() const throw(){return "Insert valid number of sheep farms";}
};

class ChickenException : public  exception{
public:
    virtual const char* what() const throw(){return "Insert valid number of chicken farms";}
};


#endif //UNTITLED_EXCEPTIONS_H
