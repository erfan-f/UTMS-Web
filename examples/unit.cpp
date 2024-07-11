#include "unit.hpp"

Unit::Unit(std::string n,std::string i,int c,std::string pr,std::vector<std::string> m_i)
{
	name = n;
	id = i;
	credit = c;
	prerequisite = pr;
	majors_id = m_i;
}

bool Unit::is_Valid_Id(std::string i)
{
	if(id == i)
		return true;
	return false;
}

std::string Unit::get_Name()
{
	return name;
}

std::vector <std::string> Unit::get_Majors_Id()
{
	return majors_id;
}

std::string Unit::get_Prerequisite()
{
	return prerequisite;
}


bool Unit::is_Valid_Major(std::string major_id)
{
	for(int i=0 ; i<majors_id.size(); i++)
	{
		if(major_id == majors_id[i])
			return true;
	}
	return false;
}