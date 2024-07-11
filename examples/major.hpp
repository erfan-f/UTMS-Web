#ifndef MAJOR
#define MAJOR

#include <iostream>
#include <string>

class Major
{
public:
	Major(std::string n , std::string i);
	~Major();
	bool is_Valid_Id(std::string i);
	std::string get_Name();
private:
	std::string name;
	std::string id;
};

#endif