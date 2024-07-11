#ifndef UNIT
#define UNIT

#include <string>
#include <vector>


class Unit
{
public:
	Unit(std::string n,std::string i,int c,std::string pr,std::vector<std::string> m_i);
	bool is_Valid_Id(std::string i);
	bool is_Valid_Major(std::string major_id);
	std::string get_Name();
	std::vector <std::string> get_Majors_Id();
	std::string get_Prerequisite();
private:
	std::string name;
	std::string id;
	int credit;
	std::string prerequisite;
	std::vector<std::string> majors_id;
};

#endif