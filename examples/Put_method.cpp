#include "Put_method.hpp"


Put::Put(std::string t , std::vector <std::string> cmds)
:Method(t,cmds) {}

Put::~Put() {}

void Put::Process_Cmd(std::string cmd_line ,std::vector<Major*> &majors ,std::vector<Unit*> &units ,std::vector<User*> &users ,std::vector<Course*> &courses, User **current_user,std::vector<std::string> &response)
{
    std::stringstream S(cmd_line);

	std::string temp_str , command;

	S >> temp_str;
	S >> command;
	S >> temp_str;

    if(command == MY_COURSES_CMD)
    {
       HandleMyCoursesCmd(S,courses,current_user,response);
    }
}

void Put::HandleMyCoursesCmd(std::stringstream &S ,std::vector<Course*> &courses,User **current_user,std::vector<std::string> &response)
{
    std::string id_argument,id,garbage_string;
    S >> id_argument >> id >> garbage_string;

    if(id_argument != ID_ARGUMENT || id == "")
        throw ArgumentException(BAD_REQUEST_ERROR);

    if(!is_Number(id))
        throw ArgumentException(BAD_REQUEST_ERROR);

    if(stoll(id) <= 0)
        throw ArgumentException(BAD_REQUEST_ERROR);
    if(garbage_string != "")
        throw ArgumentException(BAD_REQUEST_ERROR);

    Course *target_course;
    target_course = Find_Course(courses,id);

    Student *student = dynamic_cast<Student*>(*current_user);
    if(student == NULL)
        throw AcessibilityException(PERMISSION_DENIED_ERROR);

    if(!student->is_Allowed_to_Take(target_course))
        throw AcessibilityException(PERMISSION_DENIED_ERROR);

    target_course->Add_Student(student->get_Id());

    std::ostringstream os;
    os << DONE_MESSAGE << std::endl;
    response.push_back(os.str());
}

