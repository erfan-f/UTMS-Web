#include "professor.hpp"

Professor::Professor(std::string n,std::string i,std::string m,std::string m_i,std::string po,std::string p)
:User(n,i,m,m_i,p)
{
	position = po;
	user_type = USER_TYPE_1;
	profile_photo_path = DEFAULT_PROFESSOR_PROFILE_PHOTO;

	valid_cmds.push_back(LOGIN_CMD);
	valid_cmds.push_back(LOGOUT_CMD);
	valid_cmds.push_back(COURSES_CMD);
	valid_cmds.push_back(POST_CMD);
	valid_cmds.push_back(PERSONAL_PAGE_CMD);
	valid_cmds.push_back(CONNECT_CMD);
	valid_cmds.push_back(NOTIFICATION_CMD);
	valid_cmds.push_back(PROFILE_PHOTO_CMD);
	valid_cmds.push_back(COURSE_CHANNEL_CMD);
	valid_cmds.push_back(COURSE_POST_CMD);
	valid_cmds.push_back(TA_FORM_CMD);
	valid_cmds.push_back(CLOSE_TA_FORM_CMD);
}

Professor::~Professor() {}


void Professor::Add_New_Course(Course *new_course)
{
	courses.push_back(new_course);
}

bool Professor::is_Free(std::string time)
{
	for(int i=0 ; i<courses.size() ; i++)
	{
		if(courses[i]->is_Interrupted(time))
			return false;
	}
	return true;
}


std::string Professor::get_Info()
{
	std::ostringstream S;
	S << name << SPACE_CHAR << major << SPACE_CHAR << position << SPACE_CHAR;
	for(int i=0 ; i<courses.size() ; i++)
	{
		S << courses[i]->get_Name();
		if(i != courses.size() - 1)
			S << WORD_SEPRATOR;
	}

	S << std::endl;

	return S.str();
}

std::string Professor::get_Page_Info()
{
	std::ostringstream S;

	S << get_Info();
	
	Sort_Posts();

	for(int j=0 ; j<posts.size() ; j++)
	{
		S << posts[j]->get_Info();
	}	
	
	return S.str();
}


bool Professor::Do_You_Offer(Course* course)
{
	for(int i=0 ; i<courses.size() ; i++)
	{
		if(courses[i] == course)
			return true;
	}
	return false;
}

void Professor::Delete_Form(TA_Form *form)
{
	for(int i=0 ; i<posts.size() ; i++)
	{
		if(posts[i] == form)
		{
			delete form;
			posts.erase(posts.begin() + i);
			break;
		}
	}
}
