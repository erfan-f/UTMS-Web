#include "method.hpp"

Method::Method(std::string t , std::vector <std::string> cmds)
{
	type = t;
	commands = cmds;

}

Method::~Method() {}

User* Method::Find_User(std::vector<User*> users,std::string user_id)
{
	User *user;
	bool id_validation = false;
	for(int i=0 ; i<users.size() ; i++)
	{
		if(users[i]->is_Valid_Id(user_id))
		{
			id_validation =true;
			user = users[i];
			break;
		}	
	}
	if(!id_validation)
		throw AvailabilityException(NOT_FOUND_ERROR);

	return user;
}

Unit* Method::Find_Unit(std::vector<Unit*> units,std::string unit_id)
{
	Unit *unit;
	bool id_validation = false;

	for(int i=0 ; i<units.size() ; i++)
	{
		if(units[i]->is_Valid_Id(unit_id))
		{
			id_validation = true;
			unit = units[i];
			break;
		}
	}
	if(!id_validation)
		throw AvailabilityException(NOT_FOUND_ERROR);

	return unit;
}

Course* Method::Find_Course(std::vector<Course*> courses,std::string course_id)
{
	Course *course;
	bool id_validation = false;

	for(int i=0 ; i<courses.size() ; i++)
	{
		if(courses[i]->is_Valid_Id(course_id))
		{
			id_validation = true;
			course = courses[i];
			break;
		}
	}
	if(!id_validation)
		throw AvailabilityException(NOT_FOUND_ERROR);

	return course;
}


bool Method::is_Equal(std::string m)
{
	if(type == m)
		return true;
	return false;
}

bool Method::is_Cmd_Valid(std::string cmd)
{
	for(int i=0 ; i<commands.size() ; i++)
	{
		if(cmd == commands[i])
			return true;
	}
	return false;
}

bool Method::is_Number(std::string str)
{
	if(str.length() == 0)
		return false;
		
    for(int i=0 ; i<str.length() ; i++)
    {
        if(str[i] < 48 || str[i] > 57)
            return false;
    }
    return true;
}


