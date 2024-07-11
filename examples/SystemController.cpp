#include "SystemController.hpp"

SystemController::SystemController()
{
	users.push_back(new SystemOperator(OPERATOR_NAME,OPERATOR_ID,OPERATOR_PASSWORD));

	methods.push_back(new Post(POST_MTHD,{LOGIN_CMD,LOGOUT_CMD,POST_CMD,CONNECT_CMD,COURSE_OFFER_CMD
											,PROFILE_PHOTO_CMD,COURSE_POST_CMD,TA_FORM_CMD,TA_REQUEST_CMD,CLOSE_TA_FORM_CMD}));
	methods.push_back(new Get(GET_MTHD,{COURSES_CMD,PERSONAL_PAGE_CMD,POST_CMD,NOTIFICATION_CMD,MY_COURSES_CMD,COURSE_CHANNEL_CMD,COURSE_POST_CMD}));
	methods.push_back(new Put(PUT_MTHD,{MY_COURSES_CMD}));
	methods.push_back(new Delete(DELETE_MTHD,{POST_CMD,MY_COURSES_CMD}));

}

SystemController::~SystemController() {}


void SystemController::Read_Majors(std::string file_path)
{
	std::string  name,id;

	std::fstream fin;
	fin.open(file_path,std::ios::in);

	std::string temp_str;
	getline(fin,temp_str);

	while(getline(fin,temp_str))
	{
		std::stringstream S(temp_str);
		getline(S,id,SEPRATOR);
		getline(S,name,SEPRATOR);

		Add_Major(name,id);
	}
}

void SystemController::Read_Units(std::string file_path)
{
	std::string  name,id,credit,prerequisite,majors_id_str;
	std::vector<std::string> majors_id;

	std::fstream fin;
	fin.open(file_path,std::ios::in);

	std::string temp_str;
	getline(fin,temp_str);

	while(getline(fin,temp_str))
	{
		std::stringstream S(temp_str);
		getline(S,id,SEPRATOR);
		getline(S,name,SEPRATOR);
		getline(S,credit,SEPRATOR);
		getline(S,prerequisite,SEPRATOR);
		getline(S,majors_id_str,SEPRATOR);

		std::stringstream S2(majors_id_str);
		while(getline(S2,temp_str,IN_LINE_SEPRATOR))
		{
			majors_id.push_back(temp_str);
		}

		Add_Unit(name,id,std::stoll(credit),prerequisite,majors_id);
		majors_id.clear();
	}
}

void SystemController::Read_Professor(std::string file_path)
{

	std::string  name,id,major,major_id,position,password;

	std::fstream fin;
	fin.open(file_path,std::ios::in);

	std::string temp_str;
	getline(fin,temp_str);

	while(getline(fin,temp_str))
	{
		std::stringstream S(temp_str);
		getline(S,id,SEPRATOR);
		getline(S,name,SEPRATOR);
		getline(S,major_id,SEPRATOR);
		getline(S,position,SEPRATOR);
		getline(S,password,SEPRATOR);

		major = Specify_Major(major_id);

		Add_Professor(name,id,major,major_id,position,password);
	}
}

void SystemController::Read_Student(std::string file_path)
{

	std::string  name,id,major,major_id,semester,password;

	std::fstream fin;
	fin.open(file_path,std::ios::in);

	std::string temp_str;
	getline(fin,temp_str);

	while(getline(fin,temp_str))
	{
		std::stringstream S(temp_str);
		getline(S,id,SEPRATOR);
		getline(S,name,SEPRATOR);
		getline(S,major_id,SEPRATOR);
		getline(S,semester,SEPRATOR);
		getline(S,password,SEPRATOR);

		major = Specify_Major(major_id);
		
		Add_Student(name,id,major,major_id,semester,password);
	}
}



void SystemController::Add_Major(std::string name,std::string id)
{
	Major *m = new Major(name,id);
	majors.push_back(m);
}

void SystemController::Add_Unit(std::string name,std::string id,int credit,std::string prerequisite,std::vector<std::string> majors_id)
{
	Unit *u = new Unit(name,id,credit,prerequisite,majors_id);
	units.push_back(u);
}

void SystemController::Add_Professor(std::string name,std::string id,std::string major,std::string major_id,std::string position,std::string password)
{
	Professor *p = new Professor(name,id,major,major_id,position,password);
	users.push_back(p);
}

void SystemController::Add_Student(std::string name,std::string id,std::string major,std::string major_id,std::string semester,std::string password)
{
	Student *s = new Student(name,id,major,major_id,semester,password);
	users.push_back(s);
}

void SystemController::Add_User_SessionId(std::string sessionId)
{
	users_sessionId[sessionId] = current_user;
}

void SystemController::Handle_Cmd(std::string cmd_line,std::vector<std::string> &response,std::string sessionId)
{
	std::stringstream S(cmd_line);

	std::string method_type , command , operator_argument;

	S >> method_type;
	S >> command;
	S >> operator_argument;

	if(method_type == "")
		return;
	Method *method = Specify_Method(method_type);
	

	if(!method->is_Cmd_Valid(command))
	{
		throw CommandException(NOT_FOUND_ERROR);
	}
	if(operator_argument != OPERATOR_ARGUMANT)
		throw CommandException(BAD_REQUEST_ERROR);

	current_user = set_User(sessionId);

	if(command == LOGIN_CMD)
	{
		if(current_user != NULL)
		{
			if(current_user->is_LoggedIn())
				throw AcessibilityException(PERMISSION_DENIED_ERROR);
		}

		method->Process_Cmd(cmd_line,majors,units,users,courses,&current_user,response);
		Add_User_SessionId(sessionId);
	}
	else
	{
		current_user = set_User(sessionId);
		if(current_user == NULL)
			throw AcessibilityException(PERMISSION_DENIED_ERROR);
		
		if(current_user->Comamnd_Permision_Check(command))
			method->Process_Cmd(cmd_line,majors,units,users,courses,&current_user,response);
		else	
			throw AcessibilityException(PERMISSION_DENIED_ERROR);
	}
	current_user = NULL;
}

std::string SystemController::get_Current_User_Type(std::string sessionId)
{
	current_user = set_User(sessionId);
	Professor *professor = dynamic_cast<Professor*>(current_user);
	if(professor != NULL)
	{
		current_user = NULL;
		return TEACHER_TYPE;
	}
	Student *student = dynamic_cast<Student*>(current_user);
	if(student != NULL)
	{
		current_user = NULL;
		return STUDENT_TYPE;
	}
	current_user = NULL;
	return OPERATOR_TYPE;
}

Method* SystemController::Specify_Method(std::string method_type)
{
	for(int i=0 ; i<methods.size() ; i++)
	{
		if(methods[i]->is_Equal(method_type))
		{
			return methods[i];
		}
	}
	throw MethodException(BAD_REQUEST_ERROR);
}

std::string SystemController::Specify_Major(std::string id)
{

	std::string major;
	for(int i=0 ; i<majors.size() ; i++)
	{
		if(majors[i]->is_Valid_Id(id))
		{
			major = majors[i]->get_Name();
			break;
		}
	}
	return major;
}

void SystemController::Connect_to_All_User()
{
	for(int i=1 ; i<users.size() ; i++)
	{
		users[i]->Connect(users[0]);
		users[0]->Connect(users[i]);
	}
}

void SystemController::Free_Allocated_Memory()
{

	for(int i=0 ; i<users.size()  ; i++)
	{
		users[i]->Free_Allocated_Memory();
		delete users[i];
	}
	for(int i=0 ; i<majors.size() ; i++)
		delete majors[i];
	for(int i=0 ; i<units.size() ; i++)
		delete units[i];
	for(int i=0 ; i<courses.size() ; i++)
	{
		courses[i]->Free_Allocated_Memory();
		delete courses[i];
	}
	for(int i=0 ; i<methods.size() ; i++)
		delete methods[i];
}


std::vector<std::string> SystemController::get_Current_User_Page_Info(std::string sessionId)
{
	current_user = set_User(sessionId);
	std::vector<std::string> info;
	info.push_back(current_user->get_Id());
	info.push_back(current_user->get_Name());
	info.push_back(current_user->get_Major());
	info.push_back(current_user->get_Profile_Photo());
	info.push_back(std::to_string(current_user->get_Num_of_Post()));
	current_user = NULL;
	return info;
}

User* SystemController::set_User(std::string sessionId)
{
	std::map<std::string,User*>::iterator itr;
    for (itr = users_sessionId.begin(); itr != users_sessionId.end(); ++itr)
	{
		if(itr->first == sessionId)
			return itr->second;
    }
	return NULL;
}


std::vector<std::string> SystemController::get_Users_Id()
{
	std::vector<std::string> users_id;
	for(int i=0 ; i<users.size() ; i++)
	{
		users_id.push_back(users[i]->get_Id());
	}
	return users_id;
}

void  SystemController::Delete_Current_User_Profile_photo(std::string sessionId)
{
	current_user = set_User(sessionId);
	current_user->Delete_Profile_Photo();
	current_user = NULL;
}
