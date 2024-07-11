#ifndef SYSTEM_CONTROLLER
#define SYSTEM_CONTROLLER

#include "iostream"
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

#include "exception.hpp"
#include "major.hpp"
#include "unit.hpp"
#include "user.hpp"
#include "professor.hpp"
#include "student.hpp"
#include "messages.hpp"
#include "SystemOperator.hpp"
#include "course.hpp"
#include "Post_method.hpp"
#include "Get_method.hpp"
#include "Put_method.hpp"
#include "Delete_method.hpp"


const std::string OPERATOR_NAME = "UT_account";
const std::string OPERATOR_ID = "0";
const std::string OPERATOR_PASSWORD = "UT_account";

const char SEPRATOR = ',';
const char IN_LINE_SEPRATOR = ';';

const int NUM_OF_METHOD = 4;
const std::string POST_MTHD = "POST";
const std::string GET_MTHD = "GET";
const std::string PUT_MTHD = "PUT";
const std::string DELETE_MTHD = "DELETE";

const std::string OPERATOR_ARGUMANT = "?";

const std::string TEACHER_TYPE = "professor";
const std::string STUDENT_TYPE = "student";
const std::string OPERATOR_TYPE = "admin";


class SystemController
{
public:
	SystemController();
	~SystemController();
	void Read_Majors(std::string file_path);
	void Read_Units(std::string file_path);
	void Read_Professor(std::string file_path);
	void Read_Student(std::string file_path);
	void Connect_to_All_User();
	void Handle_Cmd(std::string cmd_line,std::vector<std::string> &response,std::string sessionId);
	void Add_User_SessionId(std::string sessionId);
	void Delete_Current_User_Profile_photo(std::string sessionId);
	std::string get_Current_User_Type(std::string sessionId);
	std::vector<std::string>get_Current_User_Page_Info(std::string sessionId);
	std::vector<std::string> get_Users_Id();
	User* set_User(std::string sessionId);
	void Free_Allocated_Memory();
	

private:
	std::vector<User*> users;
	std::vector<Major*> majors;
	std::vector<Unit*> units;
	std::vector<Course*> courses;
	std::vector<Method*> methods;
	std::vector<std::string> user_cmds;
	User *current_user;
	std::map<std::string,User *> users_sessionId;

	void Add_Major(std::string name,std::string id);
	void Add_Unit(std::string name,std::string id,int credit,std::string prerequisite,std::vector<std::string> majors_id);
	void Add_Professor(std::string name,std::string id,std::string major,std::string major_id,std::string position,std::string password);
	void Add_Student(std::string name,std::string id,std::string major,std::string major_id,std::string semester,std::string password);
	Method* Specify_Method(std::string method_type);
	std::string Specify_Major(std::string id);
};

#endif