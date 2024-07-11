#include "Post_method.hpp"

Post::Post(std::string t , std::vector <std::string> cmds)
:Method(t,cmds){}

Post::~Post() {}


void Post::Process_Cmd(std::string cmd_line,std::vector<Major*> &majors,std::vector<Unit*> &units,std::vector<User*> &users ,std::vector<Course*> &courses, User **current_user,std::vector<std::string> &response)
{
	std::stringstream S(cmd_line);

	std::string temp_str , command;

	S >> temp_str;
	S >> command;
	S >> temp_str;

	if(command == LOGIN_CMD)
	{
		HandleLoginCmd(S,users,current_user,response);
	}
	else if(command == LOGOUT_CMD)
	{
		HandleLogoutCmd(S,current_user,response);
	}
	else if(command == POST_CMD)
	{
		HandlePostCmd(cmd_line,S,current_user,response);
	}
	else if(command == CONNECT_CMD)
	{
		HandleConnectCmd(S,users,current_user,response);
	}
	else if(command == COURSE_OFFER_CMD)
	{
		HandleCourseOfferCmd(S,units,users,courses,current_user,response);
	}
	else if(command == PROFILE_PHOTO_CMD)
	{
		HandleProfilePhotoCmd(S,current_user,response);
	}	
	else if(command == COURSE_POST_CMD)
	{
		HandleCoursePostCmd(cmd_line,S,users,courses,current_user,response);
	}
	else if(command == TA_FORM_CMD)
	{
		HandleTaFormCmd(cmd_line,S,courses,current_user,response);
	}
	else if(command == TA_REQUEST_CMD)
	{
		HandleTaRequestCmd(S,users,courses,current_user,response);
	}
	else if(command == CLOSE_TA_FORM_CMD)
	{
		HandleCloseTaFormCmd(S,users,courses,current_user);
	}
}

void Post::HandleLoginCmd(std::stringstream &S,std::vector<User*> &users,User **current_user,std::vector<std::string> &response)
{
	std::string argument_1,argument_2,input_1,input_2,garbage_string;
		std::string id,password;
		S >> argument_1 >> input_1 >> argument_2 >> input_2 >> garbage_string;

		if(garbage_string != "")
			throw ArgumentException(BAD_REQUEST_ERROR);

		if((argument_1 == ID_ARGUMENT || argument_1 == PASSWORD_ARGUMENT) && (argument_2 == ID_ARGUMENT || argument_2 == PASSWORD_ARGUMENT))
		{
			if(argument_1 == ID_ARGUMENT)
			{
				id = input_1;
				password = input_2;
			}
			else
			{
				id = input_2;
				password = input_1;
			}
		}
		else
			throw ArgumentException(BAD_REQUEST_ERROR);

		if(!is_Number(id))
            throw ArgumentException(BAD_REQUEST_ERROR);

		*current_user = User_Login(users,id,password);
		
		std::ostringstream os;
        os << DONE_MESSAGE << std::endl;
        response.push_back(os.str());
}

void Post::HandleLogoutCmd(std::stringstream &S,User **current_user,std::vector<std::string> &response)
{
	std::string garbage_string;
	S >> garbage_string;
	if(garbage_string != "")
		throw ArgumentException(BAD_REQUEST_ERROR);
	(*current_user)->Logout();

	std::ostringstream os;
	os << DONE_MESSAGE << std::endl;
	response.push_back(os.str());
}

void Post::HandlePostCmd(std::string cmd_line,std::stringstream &S,User **current_user,std::vector<std::string> &response)
{
	std::string argument,garbage_str;
	std::string title,message,image;
	bool title_is_entered = false;
	bool message_is_entered = false;
	bool image_is_entered = false;

	for(int i=0 ; i<3 ; i++)
	{
		S >> argument;
		if(i==2 && title_is_entered && message_is_entered && argument == "")
		{
			image = "";
			break;
		}

		if(argument == TITLE_ARGUMENT && !title_is_entered)
		{
			title = Text_Reader(cmd_line);
			title_is_entered = true;
			S.str(cmd_line);
		}
		else if(argument == MESSAGE_ARGUMENT && !message_is_entered)
		{
			message = Text_Reader(cmd_line);
			message_is_entered = true;
			S.str(cmd_line);
		}
		else if(argument == IMAGE_ARGUMENT  && !image_is_entered)
		{
			S >> image;
			image_is_entered = true;
			int image_string_position = cmd_line.find(image);
			cmd_line.erase(0,image_string_position + image.length());
		}
		else 
			throw ArgumentException(BAD_REQUEST_ERROR);

		argument = "";
	}

	S >> garbage_str;
	if(garbage_str != "" || title == "" || message ==  ""  || (image == "" && image_is_entered))
		throw ArgumentException(BAD_REQUEST_ERROR);

	UT_Post *new_post = new UT_Post("",title,message,(*current_user)->get_Name(),image);
	(*current_user)->Add_Post(new_post);

	std::ostringstream os;
	os << DONE_MESSAGE << std::endl;
	response.push_back(os.str());
}

void Post::HandleConnectCmd(std::stringstream &S,std::vector<User*> &users,User **current_user,std::vector<std::string> &response)
{
	std::string target_id_argument,target_id,garbage_string;
	S >> target_id_argument >> target_id >> garbage_string; 
	if(target_id_argument != ID_ARGUMENT || target_id == "")
		throw ArgumentException(BAD_REQUEST_ERROR);

	if(!is_Number(target_id))
		throw ArgumentException(BAD_REQUEST_ERROR);

	if(stoll(target_id) <= 0)
		throw ArgumentException(BAD_REQUEST_ERROR);
	if(garbage_string != "")
		throw ArgumentException(BAD_REQUEST_ERROR);

	if((*current_user)->get_Id() == target_id)
		throw AcessibilityException(PERMISSION_DENIED_ERROR);

	Connect_Two_User(users,target_id,current_user);
	
	std::ostringstream os;
	os << DONE_MESSAGE << std::endl;
	response.push_back(os.str());
}

void Post::HandleCourseOfferCmd(std::stringstream &S,std::vector<Unit*> &units,std::vector<User*> &users,std::vector<Course*> &courses,User **current_user,std::vector<std::string> &response)
{
	std::string course_id,professor_id,capacity_str,time,exam_date,class_number,garbage_string;
	std::string operator_1,operator_2,operator_3,operator_4,operator_5,operator_6;
	std::string input_1,input_2,input_3,input_4,input_5,input_6;
	bool course_id_entered = false;
	bool professor_id_entered = false;
	bool capacity_str_entered = false;
	bool time_entered = false;
	bool exam_date_entered = false;
	bool class_number_entered = false;
	std::string opr ,inp;
	for(int i=0 ; i<6 ; i++)
	{
		S >> opr >> inp ;
		if(inp == "")
			throw ArgumentException(BAD_REQUEST_ERROR);
		if(opr == COURSE_ID_ARGUMENT && !course_id_entered)
		{
			course_id = inp;
			course_id_entered = true;
		}
		else if(opr == PROFESSOR_ID_ARGUMENT && !professor_id_entered)
		{
			professor_id = inp;
			professor_id_entered = true;
		}
		else if(opr == CAPACITY_ARGUMENT && !capacity_str_entered)
		{
			capacity_str = inp;
			capacity_str_entered = true;
		}
		else if(opr == TIME_ARGUMENT && !time_entered)
		{
			time = inp;
			time_entered = true;				
		}	
		else if(opr == EXAM_DATE_ARGUMENT && !exam_date_entered)
		{
			exam_date = inp;
			exam_date_entered = true;				
		}
		else if(opr == CLASS_NUMBER_ARGUMENT && !class_number_entered)
		{
			class_number = inp;
			class_number_entered = true;				
		}	
		else
			throw ArgumentException(BAD_REQUEST_ERROR);
		inp = "";
	}
	S >> garbage_string;
	if(garbage_string != "")
		throw ArgumentException(BAD_REQUEST_ERROR);

	if(!is_Number(capacity_str)  || !is_Number(class_number) || !is_Number(course_id) || !is_Number(professor_id))
		throw ArgumentException(BAD_REQUEST_ERROR);

	int capacity = std::stoll(capacity_str);

	if(capacity <=0 || std::stoll(class_number) <=0 || std::stoll(course_id) <=0 || std::stoll(professor_id) <=0)
		throw ArgumentException(BAD_REQUEST_ERROR);

	Unit *unit = Find_Unit(units,course_id);
	User *user = Find_User(users,professor_id);

	Professor *professor = dynamic_cast<Professor*>(user);
	if(professor == NULL)
		throw AcessibilityException(PERMISSION_DENIED_ERROR);


	if(!unit->is_Valid_Major(professor->get_Major_Id()))
		throw AvailabilityException(PERMISSION_DENIED_ERROR);		

	if(!professor->is_Free(time))
		throw AvailabilityException(PERMISSION_DENIED_ERROR);

	int id = courses.size() + 1;
	Course *new_course = new Course(std::to_string(id),unit->get_Name(),professor->get_Name(),professor_id,capacity,unit->get_Majors_Id(),unit->get_Prerequisite(),exam_date,time,class_number);
	courses.push_back(new_course);
	professor->Add_New_Course(new_course);

	Send_Public_Notification(users,professor_id,professor->get_Name(),NEW_COURSE_OFFERING_NOTIF);

	std::ostringstream os;
	os << DONE_MESSAGE << std::endl;
	response.push_back(os.str());
}

void Post::HandleProfilePhotoCmd(std::stringstream &S,User **current_user,std::vector<std::string> &response)
{
	std::string phtoto_argument,photo_address,garbage_str;
	S >> phtoto_argument >> photo_address >> garbage_str;

	if((phtoto_argument != PHOTO_ARGUMENT) || photo_address == "" || garbage_str != "")
		throw ArgumentException(BAD_REQUEST_ERROR);

	(*current_user)->Set_Profile_Photo(photo_address);
	std::ostringstream os;
	os << DONE_MESSAGE << std::endl;
	response.push_back(os.str());
}

void Post::HandleCoursePostCmd(std::string cmd_line,std::stringstream &S,std::vector<User*> &users,std::vector<Course*> &courses,User **current_user,std::vector<std::string> &response)
{
	std::string argument,garbage_str;
	std::string course_id,title,message,image;
	bool course_id_is_entered = false;
	bool title_is_entered = false;
	bool message_is_entered = false;
	bool image_is_entered = false;

	for(int i=0 ; i<4 ; i++)
	{
		S >> argument;
		if(i==3 && title_is_entered && message_is_entered && course_id_is_entered && argument == "")
		{
			image = "";
			break;
		}

		if(argument == ID_ARGUMENT && !course_id_is_entered)
		{
			S >> course_id;
			course_id_is_entered = true;
			int id_string_position = cmd_line.find(course_id);
			cmd_line.erase(0,id_string_position + course_id.length());
		}
		else if(argument == TITLE_ARGUMENT && !title_is_entered)
		{
			title = Text_Reader(cmd_line);
			title_is_entered = true;
			S.str(cmd_line);
		}
		else if(argument == MESSAGE_ARGUMENT && !message_is_entered)
		{
			message = Text_Reader(cmd_line);
			message_is_entered = true;
			S.str(cmd_line);
		}
		else if(argument == IMAGE_ARGUMENT  && !image_is_entered)
		{
			S >> image;
			image_is_entered = true;
			int image_string_position = cmd_line.find(image);
			cmd_line.erase(0,image_string_position + image.length());
		}
		else 
			throw ArgumentException(BAD_REQUEST_ERROR);

		argument = "";
	}

	S >> garbage_str;
	if(garbage_str != ""  || !is_Number(course_id) || title == "" || message ==  ""  || (image == "" && image_is_entered))
		throw ArgumentException(BAD_REQUEST_ERROR);

	Course *course = Find_Course(courses,course_id);
	std::vector<std::string> participants = course->get_Participants_Id();

	Professor *professor = dynamic_cast<Professor*>(*current_user);
	Student *student = dynamic_cast<Student*>(*current_user);

	if(student != NULL)
	{
		if(!course->is_Allowed_to_Post_in_Channel(student->get_Id()))
			throw AcessibilityException(PERMISSION_DENIED_ERROR);
		
		UT_Post *new_post = new UT_Post("",title,message,student->get_Name(),image);
		course->Add_Post_to_Channel(new_post);
		Send_Channel_Notification(users,participants,course_id,course->get_Name());
	}
	else if(professor != NULL)
	{
		if(!course->is_Allowed_to_Post_in_Channel(professor->get_Id()))
			throw AcessibilityException(PERMISSION_DENIED_ERROR);

		UT_Post *new_post = new UT_Post("",title,message,professor->get_Name(),image);
		course->Add_Post_to_Channel(new_post);
		Send_Channel_Notification(users,participants,course_id,course->get_Name());
	}
	else 
		throw AcessibilityException(PERMISSION_DENIED_ERROR);

	std::ostringstream os;
	os << DONE_MESSAGE << std::endl;
	response.push_back(os.str());
}

void Post::HandleTaFormCmd(std::string cmd_line,std::stringstream &S,std::vector<Course*> &courses,User **current_user,std::vector<std::string> &response)
{
	std::string argument,garbage_str;
	std::string course_id,message;
	bool course_id_is_entered = false;
	bool message_is_entered = false;

	for(int i=0 ; i<2 ; i++)
	{
		S >> argument;
		if(argument == COURSE_ID_ARGUMENT && !course_id_is_entered)
		{
			S >> course_id;
			course_id_is_entered = true;
			int course_id_string_position = cmd_line.find(course_id);
			cmd_line.erase(0,course_id_string_position + course_id.length());
			
		}
		else if(argument == MESSAGE_ARGUMENT && !message_is_entered)
		{
			message = Text_Reader(cmd_line);
			message_is_entered = true;
			S.str(cmd_line);
		}
		else 
			throw ArgumentException(BAD_REQUEST_ERROR);
	}
	S >> garbage_str;
	if(garbage_str != "" || course_id ==  ""  || message == "")
		throw ArgumentException(BAD_REQUEST_ERROR);
	
	Course *course = Find_Course(courses,course_id);

	Professor *professor = dynamic_cast<Professor*>(*current_user);
	if(professor == NULL)
		throw AcessibilityException(PERMISSION_DENIED_ERROR);

	if(!professor->Do_You_Offer(course))
		throw AvailabilityException(PERMISSION_DENIED_ERROR);

	std::string title;
	title = TA_FORM_TITLE + SPACE_CHAR + course->get_Name() + SPACE_CHAR + COURSE_TEXT;

	TA_Form *new_form = new TA_Form("",title,message,professor->get_Name(),course_id,course->get_All_Info());
	professor->Add_Post(new_form);

	std::ostringstream os;
	os << DONE_MESSAGE << std::endl;
	response.push_back(os.str());
}

void Post::HandleTaRequestCmd(std::stringstream &S,std::vector<User*> &users,std::vector<Course*> &courses,User **current_user,std::vector<std::string> &response)
{
	std::string argument_1,argument_2,input_1,input_2,garbage_string;
	std::string professor_id,form_id;
	S >> argument_1 >> input_1 >> argument_2 >> input_2 >> garbage_string;

	if(garbage_string != "")
		throw ArgumentException(BAD_REQUEST_ERROR);

	if((argument_1 == PROFESSOR_ID_ARGUMENT || argument_1 == FORM_ID_ARGUMENT) && (argument_2 == PROFESSOR_ID_ARGUMENT || argument_2 == FORM_ID_ARGUMENT))
	{
		if(argument_1 == PROFESSOR_ID_ARGUMENT)
		{
			professor_id = input_1;
			form_id = input_2;
		}
		else
		{
			professor_id = input_2;
			form_id = input_1;
		}
	}
	else
		throw ArgumentException(BAD_REQUEST_ERROR);


	if(!is_Number(professor_id) || !is_Number(form_id))
		throw ArgumentException(BAD_REQUEST_ERROR);

	Student *student = dynamic_cast<Student*>(*current_user);
	if(student == NULL)
		throw AcessibilityException(PERMISSION_DENIED_ERROR);

	User *user = Find_User(users,professor_id);
	Professor *professor = dynamic_cast<Professor*>(user);
	if(professor == NULL)
		throw AvailabilityException(NOT_FOUND_ERROR);

	TA_Form *form = dynamic_cast<TA_Form*>(professor->Find_Post(form_id));
	if(form == NULL)
		throw AvailabilityException(NOT_FOUND_ERROR);
	
	Course *course = Find_Course(courses,form->get_Course_Id());

	if(!course->is_Valid_for_TA(student->get_Semester()))
		throw AcessibilityException(PERMISSION_DENIED_ERROR);

	form->Add_TA_Request(student->get_Id());

	std::ostringstream os;
	os << DONE_MESSAGE << std::endl;
	response.push_back(os.str());
}

void Post::HandleCloseTaFormCmd(std::stringstream &S,std::vector<User*> &users,std::vector<Course*> &courses,User **current_user)
{
	std::string argument,form_id,garbage_str;
	S >> argument >> form_id >> garbage_str;

	if(argument != ID_ARGUMENT || !is_Number(form_id) || garbage_str != "")
		throw ArgumentException(BAD_REQUEST_ERROR);

	Professor *professor = dynamic_cast<Professor*>(*current_user);
	if(professor == NULL)
		throw AvailabilityException(NOT_FOUND_ERROR);

	TA_Form *form = dynamic_cast<TA_Form*>(professor->Find_Post(form_id));
	if(form == NULL)
		throw AvailabilityException(NOT_FOUND_ERROR);

	Course *course = Find_Course(courses,form->get_Course_Id());

	TA_Admission(users,form->get_Volunteers(),course);

	professor->Delete_Form(form);
}


User* Post::User_Login(std::vector<User*> &users , std::string id , std::string password)
{
	for(int i=0 ; i<users.size() ; i++)
	{
		if(users[i]->is_Valid_Id(id))
		{
			if(users[i]->is_Valid_Password(password))
			{
				if(users[i]->is_LoggedIn())
					throw AcessibilityException(PERMISSION_DENIED_ERROR);
				users[i]->Login();
				return users[i];
			}
			throw AvailabilityException(PERMISSION_DENIED_ERROR);
		}	
	}
	throw AvailabilityException(NOT_FOUND_ERROR);
}

void Post::Connect_Two_User(std::vector<User*> &users , std::string target_id ,User **current_user)
{
	User *target_user = Find_User(users,target_id);

	target_user->Connect(*current_user);
	(*current_user)->Connect(target_user);
}


std::string Post::Text_Reader(std::string &cmd_line)
{
	int first_delimiter = cmd_line.find(TEXT_CHAR);
	std::string temp_str = cmd_line.erase(0,first_delimiter+1);
	int second_delimiter = cmd_line.find(TEXT_CHAR);
	if(second_delimiter == -1 || first_delimiter == -1)
		throw ArgumentException(BAD_REQUEST_ERROR);
	std::string text = cmd_line.substr(0,second_delimiter);
	cmd_line.erase(0,second_delimiter+1);

	return TEXT_CHAR + text + TEXT_CHAR;
}


void Post::Send_Public_Notification(std::vector<User*> users,std::string id,std::string name,std::string notice_text)
{
	for(int i=1 ; i<users.size() ; i++)
	{
		users[i]->Recieve_Notification(new Notification{id,name,notice_text});
	}

}


void Post::Send_Channel_Notification(std::vector<User*> users,std::vector<std::string> participants_id,std::string course_id,std::string course_name)
{
	User *user;
	for(int i=0 ; i<participants_id.size() ; i++)
	{
		user = Find_User(users,participants_id[i]);
		user->Recieve_Notification(new Notification{course_id,course_name,NEW_COURSE_POST_NOTIF});
	}
}

void Post::TA_Admission(std::vector<User*> users,std::vector<std::string> volunteers_id,Course *course)
{
	IOHandler template_io_handler;
	std::ostringstream os1;

	os1 << TA_ADMISSION_TEXT_PART_1 << SPACE_CHAR << volunteers_id.size() << SPACE_CHAR << TA_ADMISSION_TEXT_PART_2 << std::endl;
	template_io_handler.Print_Data(os1.str());

	for(int i=0 ; i<volunteers_id.size() ; i++)
	{
		std::string response;
		Student *student = dynamic_cast<Student*> (Find_User(users,volunteers_id[i])); 
		if(student == NULL)
			throw AcessibilityException(PERMISSION_DENIED_ERROR);

		std::ostringstream os2;
		os2 << student->get_Id() << SPACE_CHAR << student->get_Name() 
					<< SPACE_CHAR << student->get_Semester() << ":" << SPACE_CHAR;
					
		template_io_handler.Print_Data(os2.str());
		response = template_io_handler.get_Word();

		if(response == ACCEPTION_TEXT)
		{
			course->Add_TA(student->get_Id());
			student->Add_Collaborated_Course(course);
			student->Recieve_Notification(new Notification{course->get_Id(),course->get_Name(),ACCEPTION_NOTIF});
		}
		else if(response == REJECTION_TEXT)
			student->Recieve_Notification(new Notification{course->get_Id(),course->get_Name(),REJECTION_NOTIF});
		else
			i--;
	}
}
