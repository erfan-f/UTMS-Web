#include "Delete_method.hpp"

Delete::Delete(std::string t , std::vector <std::string> cmds)
:Method(t,cmds) {}

Delete::~Delete() {}

void Delete::Process_Cmd(std::string cmd_line ,std::vector<Major*> &majors ,std::vector<Unit*> &units ,std::vector<User*> &users ,std::vector<Course*> &courses, User **current_user,std::vector<std::string> &response)
{
    std::stringstream S(cmd_line);

	std::string temp_str,command;

	S >> temp_str >> command >> temp_str;

    if(command == POST_CMD)
    {
        HandlePostCmd(S,current_user,response);
    }
    else if(command == MY_COURSES_CMD)
    {
        HandleMyCoursesCmd(S,current_user,response);
    }
}


void Delete::HandlePostCmd(std::stringstream &S,User **current_user,std::vector<std::string> &response)
{

    std::string id_operator,id,garbage_string;

    S >> id_operator >> id >> garbage_string;
    
    if(id_operator != ID_ARGUMENT || id == "")
        throw ArgumentException(BAD_REQUEST_ERROR);

    if(!is_Number(id))
        throw ArgumentException(BAD_REQUEST_ERROR);

    if(std::stoll(id) <= 0)
        throw ArgumentException(BAD_REQUEST_ERROR);

    if(garbage_string != "")
        throw ArgumentException(BAD_REQUEST_ERROR);

    (*current_user)->Delete_Post(id);
    
    std::ostringstream os;
    os << DONE_MESSAGE << std::endl;
    response.push_back(os.str());
}



void Delete::HandleMyCoursesCmd(std::stringstream &S,User **current_user,std::vector<std::string> &response)
{
    std::string id_operator,id,garbage_string;

    S >> id_operator >> id >> garbage_string;
    
    if(id_operator != ID_ARGUMENT || id == "")
        throw ArgumentException(BAD_REQUEST_ERROR);

    if(!is_Number(id))
        throw ArgumentException(BAD_REQUEST_ERROR);

    if(std::stoll(id) <= 0)
        throw ArgumentException(BAD_REQUEST_ERROR);

    if(garbage_string != "")
        throw ArgumentException(BAD_REQUEST_ERROR);

    Student* student= dynamic_cast<Student*>(*current_user);
    if(student == NULL)
        throw AcessibilityException(PERMISSION_DENIED_ERROR);
        
    student->Delete_Course(id);

    std::ostringstream os;
    os << DONE_MESSAGE << std::endl;
    response.push_back(os.str());
}