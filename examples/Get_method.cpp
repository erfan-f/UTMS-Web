#include "Get_method.hpp"

Get::Get(std::string t , std::vector <std::string> cmds)
:Method(t,cmds) {}

Get::~Get() {}

void Get::Process_Cmd(std::string cmd_line ,std::vector<Major*> &majors ,std::vector<Unit*> &units ,std::vector<User*> &users ,std::vector<Course*> &courses, User **current_user,std::vector<std::string> &response)
{
	std::stringstream S(cmd_line);

	std::string temp_str,command;

	S >> temp_str >> command >> temp_str;

	if(command == COURSES_CMD)
	{
		HandleCourseCmd(S,courses,response);
	}
	else if(command == POST_CMD)
	{
		HandlePostCmd(S,users,current_user,response);
	}
	else if(command == PERSONAL_PAGE_CMD)
	{
		HandlePersonalPageCmd(S,users,response);
	}
	else if(command == NOTIFICATION_CMD)
	{
		HandleNotificationCmd(S,current_user,response);
	}
	else if(command == MY_COURSES_CMD)
	{
		HandleMyCoursesCmd(S,current_user,response);
	}
	else if(command == COURSE_CHANNEL_CMD)
	{
		HandleCourseChannelCmd(S,courses,current_user,response);
	}
	else if(command == COURSE_POST_CMD)
	{
		HandleCoursePostCmd(S,courses,current_user,response);
	}
}

void Get::HandleCourseCmd(std::stringstream &S ,std::vector<Course*> &courses,std::vector<std::string> &response)
{
	std::string id_argument,id,garbage_string;
	S >> id_argument >> id >> garbage_string;
	if(id_argument == "")
	{
		get_All_Courses_Info(courses,response);
	}
	else
	{
		if(id_argument != ID_ARGUMENT || id == "")
			throw ArgumentException(BAD_REQUEST_ERROR);

		if(!is_Number(id))
			throw ArgumentException(BAD_REQUEST_ERROR);

		if(std::stoll(id) <= 0)
			throw ArgumentException(BAD_REQUEST_ERROR);
		if(garbage_string != "")
			throw ArgumentException(BAD_REQUEST_ERROR);

		get_Course_Info(courses,id,response);
	}
}

void Get::HandlePostCmd(std::stringstream &S,std::vector<User*> &users,User **current_user,std::vector<std::string> &response)
{
	if( dynamic_cast<SystemOperator*>(*current_user) != NULL)
		throw AcessibilityException(PERMISSION_DENIED_ERROR);
	
	std::string argument_1,argument_2,input_1,input_2,garbage_string;
	std::string id,post_id;
	S >> argument_1 >> input_1 >> argument_2 >> input_2 >> garbage_string;
	if((argument_1 == ID_ARGUMENT || argument_1 == POST_ID_ARGUMENT ) && (argument_2 == ID_ARGUMENT || argument_2 == POST_ID_ARGUMENT))
	{
		if(argument_1 == ID_ARGUMENT)
		{
			id = input_1;
			post_id = input_2;
		}
		else
		{
			id = input_2;
			post_id = input_1;
		}
	}
	else
		throw ArgumentException(BAD_REQUEST_ERROR);

	if(!is_Number(id) || !is_Number(post_id))
		throw ArgumentException(BAD_REQUEST_ERROR);

	if(std::stoll(id) <0 || std::stoll(post_id) <=0)
		throw ArgumentException(BAD_REQUEST_ERROR);
	
	if(garbage_string != "")
		throw ArgumentException(BAD_REQUEST_ERROR);

	get_User_Post(users,id,post_id,response);
}

void Get::HandlePersonalPageCmd(std::stringstream &S,std::vector<User*> &users,std::vector<std::string> &response)
{
	std::string id_argument,id,garbage_string;
	S >> id_argument >> id >> garbage_string;
	if(id_argument != ID_ARGUMENT || id == "")
		throw ArgumentException(BAD_REQUEST_ERROR);

	if(!is_Number(id))
		throw ArgumentException(BAD_REQUEST_ERROR);
	if(std::stoll(id) < 0)
		throw ArgumentException(BAD_REQUEST_ERROR);
	if(garbage_string != "")
		throw ArgumentException(BAD_REQUEST_ERROR);

	get_Personal_Page(users,id,response);

}

void Get::HandleNotificationCmd(std::stringstream &S,User **current_user,std::vector<std::string> &response)
{
	std::string argument_str;
	S >> argument_str;
	
	if(argument_str != "")
		throw ArgumentException(BAD_REQUEST_ERROR);
	
	response.push_back((*current_user)->get_Notifications());
}

void Get::HandleMyCoursesCmd(std::stringstream &S,User **current_user,std::vector<std::string> &response)
{
	std::string argument_str;
	S >> argument_str;
	if(argument_str != "")
		throw ArgumentException(BAD_REQUEST_ERROR);

	Student *student = dynamic_cast<Student*>(*current_user);
	if(student == NULL)
		throw AcessibilityException(PERMISSION_DENIED_ERROR);

	response.push_back(student->get_Courses_Info());
}

void Get::HandleCourseChannelCmd(std::stringstream &S ,std::vector<Course*> &courses,User **current_user,std::vector<std::string> &response)
{
	std::string course_id_argument,course_id,garbage_str;

	S >> course_id_argument >> course_id >> garbage_str;

	if( course_id_argument != ID_ARGUMENT || !is_Number(course_id) || course_id == ""  || garbage_str != "")
		throw ArgumentException(BAD_REQUEST_ERROR);

	Course *course = Find_Course(courses,course_id);

	if(!course->is_Allowed_to_View_Channel((*current_user)->get_Id()))
		throw AcessibilityException(PERMISSION_DENIED_ERROR);

	response.push_back(course->get_Channel_Info());
}

void Get::HandleCoursePostCmd(std::stringstream &S ,std::vector<Course*> &courses,User **current_user,std::vector<std::string> &response)
{
	std::string argument,garbage_str;
	std::string course_id,post_id;
	bool course_id_is_entered = false;
	bool post_id_is_entered = false;

	for(int i=0 ; i<2 ; i++)
	{
		S >> argument;
		if(argument == ID_ARGUMENT && !course_id_is_entered)
		{
			S >> course_id;
			course_id_is_entered = true;
		}
		else if(argument == POST_ID_ARGUMENT && !post_id_is_entered)
		{
			S >> post_id;
			post_id_is_entered = true;
		}
		else
			throw ArgumentException(BAD_REQUEST_ERROR);

		argument = "";
	}

	S >> garbage_str;
	if(garbage_str != ""  || !is_Number(course_id) || course_id == "" || post_id == "" )
		throw ArgumentException(BAD_REQUEST_ERROR);

	Course *course = Find_Course(courses,course_id);

	std::string course_info = course->get_All_Info();
	std::string post_info = course->get_Channel_Post(post_id);

	if(!course->is_Allowed_to_View_Channel((*current_user)->get_Id()))
		throw AcessibilityException(PERMISSION_DENIED_ERROR);

	response.push_back(course_info);	
	response.push_back(post_info);	
}


void Get::get_All_Courses_Info(std::vector<Course*> courses , std::vector<std::string> &response)
{	
	if(courses.size() == 0)
		throw CommandException(EMPTY_ERROR);

	for(int i=0 ; i<courses.size(); i++)
	{
		response.push_back(courses[i]->get_Info());
	}
	
}

void Get::get_Course_Info(std::vector<Course*> courses , std::string course_id,std::vector<std::string> &response)
{
	Course *target_course = Find_Course(courses,course_id);
	
	response.push_back(target_course->get_All_Info());
}


void Get::get_Personal_Page(std::vector<User*> users,std::string user_id,std::vector<std::string> &response)
{
	User *user = Find_User(users,user_id);

	response.push_back(user->get_Page_Info());
	response.push_back(user->get_Profile_Photo());

}


void Get::get_User_Post(std::vector<User*> users,std::string user_id,std::string post_id,std::vector<std::string> &response)
{
	User *user = Find_User(users,user_id);
	response.push_back(user->get_Post(post_id));
}