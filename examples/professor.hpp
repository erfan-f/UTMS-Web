#ifndef PROFESSOR
#define PROFESSOR
#include <string>
#include "user.hpp"



class Professor : public User 
{
public:
	Professor(std::string n,std::string i,std::string m,std::string m_i,std::string po,std::string p);
	~Professor();
	void Add_New_Course(Course *new_course);
	void Delete_Form(TA_Form *form);
	bool is_Free(std::string time);
	bool Do_You_Offer(Course *course);
	std::string get_Info();
	std::string get_Page_Info();
	
private:
	std::string position;
};


#endif