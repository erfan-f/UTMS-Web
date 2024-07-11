#include "major.hpp"

Major::Major(std::string n , std::string i)
{
	name = n;
	id =i;
}

Major::~Major() {}

bool Major::is_Valid_Id(std::string i)
{
	if(id == i)
		return true;
	return false;
}

std::string Major::get_Name()
{
	return name;
}
