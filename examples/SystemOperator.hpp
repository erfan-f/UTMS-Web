#ifndef SYSTEMOP
#define SYSTEMOP

#include "user.hpp"



class SystemOperator : public User
{
public:
    SystemOperator(std::string n , std::string i , std::string pass);
    ~SystemOperator();
    std::string get_Info();
    std::string get_Page_Info();
    
};

#endif
