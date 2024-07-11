#ifndef STUDENT
#define STUDENT

#include <string>
#include "user.hpp"



class Student : public User 
{
public:
	Student(std::string n,std::string i,std::string m,std::string m_i,std::string s,std::string p);
	~Student();
	void Delete_Course(std::string course_id);
	void Add_Collaborated_Course(Course *course);
	bool is_Allowed_to_Take(Course* new_course);
	std::string get_Info();
	std::string get_Page_Info();
	std::string get_Courses_Info();
	std::string get_Semester();
	
private:
	std::string semester;
	std::vector<Course*>  collaborated_courses;

};

#endif