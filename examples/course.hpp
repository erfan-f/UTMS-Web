#ifndef COURSE
#define COURSE

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "time.hpp"
#include "date.hpp"
#include "exception.hpp"
#include "messages.hpp"
#include "UT_media.hpp"


class Course
{
public:
    Course(std::string i,std::string n , std::string p_n,std::string p_i, int cap ,std::vector <std::string> m_i,std::string pre,std::string d, std::string t,std::string c_n);
    ~Course();
    bool is_Valid_Id(std::string course_id);
    bool is_Allowed_to_Post_in_Channel(std::string user_id);
    bool is_Allowed_to_View_Channel(std::string user_id);
    bool is_Interrupted(Course *course);
    bool is_Interrupted(std::string time);
    bool is_Valid_Semester(std::string semester);
    bool is_Valid_for_TA(std::string semester);
    bool is_Valid_Major(std::string id);
    void Add_Student(std::string student_id);
    void Add_TA(std::string volunteer_id);
    void Add_Post_to_Channel(UT_Post *new_post);
    void Free_Allocated_Memory();
    std::string get_Info();
    std::string get_All_Info();
    std::string get_Channel_Info();
    std::string get_Channel_Post(std::string post_id);
    std::string get_Name();
    std::string get_Id();
    std::vector<std::string> get_Participants_Id();

private:
    int capacity;
    int num_of_posts_history;
    Date *exam_date;
    Time *class_time;
    std::string id;
    std::string name;
    std::string professor_name;
    std::string professor_id;
    std::string class_number;
    std::string prerequisite;
    std::vector<std::string> participants_id;
    std::vector<std::string>  teaching_assistants_id;
    std::vector<std::string> majors_id;
    std::vector<UT_Post*> channel;
    Week Specify_Day_Of_Week(std::string day_of_week_str);
    void Sort_Channel_Posts(); 

};

#endif