#include "student.hpp"

Student::Student(std::string n,std::string i,std::string m,std::string m_i,std::string s,std::string p)
:User(n,i,m,m_i,p)
{
	semester = s;
	user_type = USER_TYPE_2;
	profile_photo_path = DEFAULT_STUDENT_PROFILE_PHOTO;
	valid_cmds.push_back(LOGIN_CMD);
	valid_cmds.push_back(LOGOUT_CMD);
	valid_cmds.push_back(COURSES_CMD);
	valid_cmds.push_back(POST_CMD);
	valid_cmds.push_back(PERSONAL_PAGE_CMD);
	valid_cmds.push_back(CONNECT_CMD);
	valid_cmds.push_back(NOTIFICATION_CMD);
	valid_cmds.push_back(MY_COURSES_CMD);
	valid_cmds.push_back(PROFILE_PHOTO_CMD);
	valid_cmds.push_back(COURSE_CHANNEL_CMD);
	valid_cmds.push_back(COURSE_POST_CMD);
	valid_cmds.push_back(TA_REQUEST_CMD);

}

Student::~Student() {}


std::string Student::get_Info()
{
	std::ostringstream S;
	S << name << SPACE_CHAR << major << SPACE_CHAR << semester << SPACE_CHAR;
	for(int i=0 ; i<courses.size() ; i++)
	{
		S << courses[i]->get_Name();
		if(i != courses.size() - 1)
			S << WORD_SEPRATOR;
	}
	S << std::endl;
	return S.str();
}

std::string Student::get_Page_Info()
{
	std::ostringstream S;

	S << get_Info();
	
	Sort_Posts();
	
	for(int i=0 ; i<posts.size() ; i++)
	{
		S <<  posts[i]->get_Info();
	}	
	return S.str();
}

std::string Student::get_Semester()
{
	return semester;
}


bool Student::is_Allowed_to_Take(Course* new_course)
{
	if(!new_course->is_Valid_Semester(semester))
		return false;
	if(!new_course->is_Valid_Major(major_id))
		return false;
	
	for(int i=0 ; i<courses.size() ; i++)
	{
		if(courses[i]->is_Interrupted(new_course))
			return false;
	}

	Send_Notification(GET_COURSE_NOTIF);
	courses.push_back(new_course);

	return true;
}

void Student::Delete_Course(std::string course_id)
{
	bool id_validation = false;
	for(int i=0 ; i<courses.size() ; i++)
	{
		if(courses[i]->is_Valid_Id(course_id))
		{
			id_validation = true;
			courses.erase(courses.begin() + i);
			Send_Notification(DELETE_COURSE_NOTIF);
			break;
		}
	}
	if(!id_validation)
		throw AvailabilityException(NOT_FOUND_ERROR);
}


std::string Student::get_Courses_Info()
{
	std::ostringstream S;

	if(courses.size() == 0)
		throw AvailabilityException(EMPTY_ERROR);

	for(int i=0 ; i<courses.size() ; i++)
	{
		S << courses[i]->get_All_Info();
	}
	return S.str();
}


void Student::Add_Collaborated_Course(Course *course)
{
	collaborated_courses.push_back(course);
}
