#ifndef USER
#define USER

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "exception.hpp"
#include "commands.hpp"
#include "messages.hpp"
#include "UT_media.hpp"
#include "notification.hpp"
#include "unit.hpp"
#include "course.hpp"


const std::string USER_TYPE_1 = "Professor";
const std::string USER_TYPE_2 = "Student";
const std::string USER_TYPE_3 = "Operator";

const std::string DEFAULT_PROFESSOR_PROFILE_PHOTO = "professor.png";
const std::string DEFAULT_STUDENT_PROFILE_PHOTO = "student.png";
const std::string DEFAULT_ADMIN_PROFILE_PHOTO = "admin.png";



class User
{
public:
	User(std::string n,std::string i,std::string p);
	User(std::string n,std::string i,std::string m,std::string m_i,std::string p);
	virtual ~User();
	virtual std::string get_Info() = 0;
	virtual std::string get_Page_Info() = 0;
	bool is_Valid_Id (std::string i);
	bool is_Valid_Password(std::string p);
	bool Comamnd_Permision_Check(std::string cmd);
	bool is_LoggedIn();
	void Login();
	void Logout();
	void Add_Post(UT_Media *new_post);
	void Connect(User *target);
	void Sort_Posts();
	void Send_Notification(std::string notice_text);
	void Recieve_Notification(Notification* notif);
	void Delete_Post(std::string post_id);
	void Set_Profile_Photo(std::string photo_path);
	void Free_Allocated_Memory();
	void Delete_Profile_Photo();
	UT_Media* Find_Post(std::string post_id);
	std::string get_Id();
	std::string get_Major();
	std::string get_Major_Id();
	std::string get_Name();
	std::string get_Profile_Photo();
	std::string get_Notifications();
	std::string get_Post(std::string post_id);
	int get_Num_of_Post();

protected:	
	bool logged_in;
	std::string user_type;
	std::string name;
	std::string id;
	std::string major_id;
	std::string major;
	std::string password;
	std::string profile_photo_path;
	std::vector<std::string> valid_cmds;
	std::vector<UT_Media*> posts;
	std::vector<User*> connection_list;
	std::vector<Course*> courses;
	std::vector<Notification*> notifications;
	int num_of_posts_history;

};

#endif