#ifndef METHOD
#define METHOD

#include <iostream>
#include <vector>
#include <string>
#include <sstream>


#include "exception.hpp"
#include "major.hpp"
#include "unit.hpp"
#include "user.hpp"
#include "professor.hpp"
#include "student.hpp"
#include "SystemOperator.hpp"
#include "commands.hpp"
#include "messages.hpp"
#include "course.hpp"
#include "arguments.hpp"
#include "io_Handler.hpp"


class Method
{
public:
	Method(std::string t , std::vector <std::string> cmds);
	virtual ~Method();
	virtual void Process_Cmd(std::string cmd_line ,std::vector<Major*> &majors ,std::vector<Unit*> &units ,std::vector<User*> &users 
								,std::vector<Course*> &courses, User **current_user,std::vector<std::string> &response) = 0;
	bool is_Number(std::string str);
	bool is_Equal(std::string m);
	bool is_Cmd_Valid(std::string cmd);

protected:
	std::string type;
	std::vector<std::string> commands;
	User* Find_User(std::vector<User*> users,std::string user_id);
	Unit* Find_Unit(std::vector<Unit*> units,std::string unit_id);
	Course* Find_Course(std::vector<Course*> courses,std::string course_id);

};
#endif