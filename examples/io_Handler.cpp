#include "io_Handler.hpp"

IOHandler::IOHandler () {}

IOHandler::~IOHandler() {}

void IOHandler::Print_Data(std::vector <std::string> data_vector)
{
    for(int i=0 ; i<data_vector.size() ; i++)
	    std::cout << data_vector[i] ;
}

void IOHandler::Print_Data(std::string data_string)
{
    std::cout << data_string;
}


void  IOHandler::Print_Error(std::string error_text)
{
    std::cerr << error_text << std::endl;
}


bool IOHandler::get_Command_Line(std::string &cmd_line)
{
   if(getline(std::cin,cmd_line))
        return true;

    return false;
}

std::string IOHandler::get_Word()
{
    std::string word;
    std::cin >> word;
    return word;
}