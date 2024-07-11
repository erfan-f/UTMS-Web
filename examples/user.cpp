#include "user.hpp"

User::User(std::string n,std::string i,std::string p)
{
	name = n;
	id = i;
	password = p;
	logged_in = false;
	num_of_posts_history = 0;
}


User::~User() {}

User::User(std::string n,std::string i,std::string m,std::string m_i,std::string p)
{
	name = n;
	id = i;
	major_id = m_i;
	major = m;
	password = p;
	logged_in = false;
	num_of_posts_history = 0;
}

bool User::is_LoggedIn()
{
	if(logged_in)
		return true;
	return false;
}

bool User::is_Valid_Id(std::string i)
{
	if(id == i)
		return true;
	return false;
}

bool User::is_Valid_Password(std::string p)
{
	if(password == p)
		return true;
	return false;
}

void User::Login()
{
	logged_in = true;
}

void User::Logout()
{
	logged_in =false;
}

void User::Add_Post(UT_Media *new_post)
{	
	new_post->set_Id(std::to_string(num_of_posts_history +1));
	posts.push_back(new_post);
	UT_Post *ut_post = dynamic_cast<UT_Post*>(new_post);
	if(ut_post != NULL)
		Send_Notification(NEW_POST_NOTIF);
	else
		Send_Notification(NEW_FORM_NOTIF);	

	num_of_posts_history++;
}

void User::Connect(User *target)
{
	for(int i=0 ; i<connection_list.size() ; i++)
	{
		if(connection_list[i] == target)
			throw AvailabilityException(BAD_REQUEST_ERROR);
	}
	connection_list.push_back(target);
}

bool User::Comamnd_Permision_Check(std::string cmd)
{
	for(int i=0 ; i<valid_cmds.size(); i++)
	{
		if(cmd == valid_cmds[i])
			return true;
	}
	return false;
}


std::string User::get_Id()
{
	return id;
}


std::string User::get_Major()
{
	return major;
}

std::string User::get_Major_Id()
{
	return major_id;
}

std::string User::get_Name()
{
	return name;
}

std::string User::get_Profile_Photo()
{
	return profile_photo_path;
}

int User::get_Num_of_Post()
{
	return num_of_posts_history;
}


void User::Sort_Posts()
{
	UT_Media *temp;
	for(int i=0 ; i<posts.size() ; i++)
	{
		for(int j=0 ; j<posts.size() -1 ; j++)
		{
			if(posts[j]->Compare_Id(posts[j+1]))
			{
				temp = posts[j];
				posts[j] = posts[j+1];
				posts[j+1] = temp;
			}
		}
	}
}

std::string User::get_Post(std::string post_id)
{
	std::ostringstream S;
	UT_Media *post;
	bool id_validation = false;

	for(int i=0 ; i<posts.size() ; i++)
	{
		if(posts[i]->is_Valid_Id(post_id))
		{
			id_validation = true;
			post = posts[i];
			break;
		}
	}
	if(!id_validation)
		throw AvailabilityException(NOT_FOUND_ERROR);
	S << this->get_Info();
	S << post->get_All_Info();
	return S.str();
}

void User::Send_Notification(std::string notice_text)
{
	for(int i=0 ; i<connection_list.size() ; i++)
	{	
		connection_list[i]->Recieve_Notification(new Notification{id,name,notice_text});
	}
}

void User::Recieve_Notification(Notification* notif)
{
	notifications.push_back(notif);
}

std::string User::get_Notifications()
{
	std::ostringstream S;

	if(notifications.size() == 0)
		throw AvailabilityException(EMPTY_ERROR);

	for(int i= notifications.size() - 1 ; i>=0 ; i--)
	{
		S << notifications[i]->id << SPACE_CHAR << notifications[i]->name << NAME_POST_SEPRATOR  << SPACE_CHAR << notifications[i]->notice << std::endl;
		delete notifications[i];
	}

	notifications.clear();
	
	return S.str();
}

void User::Delete_Post(std::string post_id)
{
	bool id_validation = false;
	for(int i=0 ; i<posts.size() ; i++)
	{
		if(posts[i]->is_Valid_Id(post_id))
		{
			id_validation = true;
			delete posts[i];
			posts.erase(posts.begin() + i);
			break;
		}
	}
	if(!id_validation)
		throw AvailabilityException(NOT_FOUND_ERROR);
}


void User::Free_Allocated_Memory()
{
	for(int i=0 ; i<posts.size() ; i++)
		delete posts[i];
	
	for(int i=0 ; i<notifications.size() ; i++)
		delete notifications[i];
}	


void User::Set_Profile_Photo(std::string photo_path)
{
	profile_photo_path = photo_path;
}


UT_Media* User::Find_Post(std::string post_id)
{
	UT_Media *target_post;
	bool id_validation = false;
	for(int i=0 ; i<posts.size() ; i++)
	{
		if(posts[i]->is_Valid_Id(post_id))
		{
			id_validation = true;
			target_post = posts[i];
			break;
		}
	}
	if(!id_validation)
		throw AvailabilityException(NOT_FOUND_ERROR);
	
	return target_post;
	
}


void User::Delete_Profile_Photo()
{
	if(user_type == USER_TYPE_1)
		profile_photo_path = DEFAULT_PROFESSOR_PROFILE_PHOTO;
	else if(user_type == USER_TYPE_2)
		profile_photo_path = DEFAULT_STUDENT_PROFILE_PHOTO;
	else if(user_type == USER_TYPE_3)
		profile_photo_path = DEFAULT_ADMIN_PROFILE_PHOTO;

}