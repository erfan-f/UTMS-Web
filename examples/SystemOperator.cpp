#include "SystemOperator.hpp"

SystemOperator::SystemOperator(std::string n , std::string i , std::string pass)
:User(n,i,pass) 
{
	user_type = USER_TYPE_3;
	profile_photo_path = DEFAULT_ADMIN_PROFILE_PHOTO;

    valid_cmds.push_back(LOGIN_CMD);
	valid_cmds.push_back(LOGOUT_CMD);
	valid_cmds.push_back(POST_CMD);
	valid_cmds.push_back(COURSE_OFFER_CMD);

}

SystemOperator::~SystemOperator() {}


std::string SystemOperator::get_Info()
{	
	std::ostringstream S;
	S << name << std::endl;
	return S.str();
}

std::string SystemOperator::get_Page_Info()
{
	std::ostringstream S;
	S << get_Info();
	
	Sort_Posts();
	for(int j=0 ; j<posts.size() ; j++)
	{
		S <<  posts[j]->get_Info();
	}
	return S.str();
}
