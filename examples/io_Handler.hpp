#ifndef IOHANDLER
#define IOHANDLER

#include <iostream>
#include <vector>

class IOHandler
{
public:
    IOHandler();
    ~IOHandler();
    void Print_Data(std::vector <std::string> data_vector);
    void Print_Data(std::string data_string);
    void Print_Error(std::string error_text);
    bool get_Command_Line(std::string &cmd_line);
    std::string get_Word();
};


#endif