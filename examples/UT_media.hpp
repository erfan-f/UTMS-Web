#ifndef UT_POST
#define UT_POST

#include <string>
#include <vector>
#include <sstream>
#include "messages.hpp"


class UT_Media
{
public:

	UT_Media(std::string i,std::string t,std::string m,std::string a);
	virtual ~UT_Media();
	virtual std::string get_All_Info() = 0;
	std::string get_Info();
	std::string get_Id();
	void set_Id(std::string i);
	bool is_Valid_Id(std::string target_id);
	bool Compare_Id(UT_Media *target_post);
	
protected:
	std::string id;
	std::string title;
	std::string message;
	std::string author;
	
};

class UT_Post : public UT_Media
{
public:
	UT_Post(std::string i,std::string t,std::string m,std::string a,std::string im_p);
	~UT_Post();
	std::string get_Info_Include_Author();
	std::string get_All_Info_Include_Author();
	std::string get_All_Info();

private:
	std::string image_path;

};

class TA_Form : public UT_Media
{
public:
	TA_Form(std::string i,std::string t,std::string m,std::string a,std::string c_i,std::string c_info);
	~TA_Form();
	void Add_TA_Request(std::string student_id);
	std::string get_All_Info();
	std::string get_Course_Id();
	std::vector<std::string> get_Volunteers();

private:
	std::string course_id;
	std::string course_information;
	std::vector<std::string> volunteers_id;
};

#endif