#include "course.hpp"

Course::Course(std::string i,std::string n , std::string p_n,std::string p_i , int cap ,std::vector <std::string> m_i,std::string pre,std::string d, std::string t,std::string c_n)
{
    id = i;
    name = n;
    professor_name = p_n;
    professor_id = p_i;
    capacity = cap;
    class_number = c_n;
    majors_id = m_i;
    prerequisite = pre;
    num_of_posts_history = 0;

    std::stringstream S(d);
    std::string day,month,year;

    getline(S,year,DATE_SEPRATOR);
    getline(S,month,DATE_SEPRATOR);
    getline(S,day,DATE_SEPRATOR);
    
    exam_date = new Date(std::stoll(day),std::stoll(month),std::stoll(year));

    std::stringstream S2(t);
    std::string day_of_week_str,start_time_str,end_time_str;

    getline(S2,day_of_week_str,DAY_TIME_SEPRATOR);
    getline(S2,start_time_str,START_END_SEPRATOR);
    getline(S2,end_time_str,START_END_SEPRATOR);

    Week day_of_week = Specify_Day_Of_Week(day_of_week_str);
    int start_time = stoll(start_time_str);
    int end_time = stoll(end_time_str);


    if((start_time < 1 && start_time > 24) || (end_time < 1 && end_time > 24))
        throw ArgumentException(BAD_REQUEST_ERROR);
    
    if(end_time <= start_time)
        throw ArgumentException(BAD_REQUEST_ERROR);

    class_time = new Time(day_of_week,start_time,end_time);

}

Course::~Course() {}

bool Course::is_Valid_Id(std::string course_id)
{
    if(id == course_id)
        return true;
    return false;
}

bool Course::is_Valid_Semester(std::string semester)
{
    if(std::stoll(semester) >= std::stoll(prerequisite))
        return true;
    return false;
}

bool Course::is_Valid_for_TA(std::string semester)
{
    if(std::stoll(semester) > std::stoll(prerequisite))
        return true;
    return false;
}



bool Course::is_Valid_Major(std::string id)
{
    for(int i=0 ; i<majors_id.size() ; i++)
    {
        if(id == majors_id[i])
            return true;
    }
    return false;
}

std::string Course::get_Info()
{
    std::ostringstream S;
    S << id << SPACE_CHAR << name << SPACE_CHAR << capacity << SPACE_CHAR << professor_name << std::endl;
    return S.str();
}

std::string Course::get_All_Info()
{
    std::ostringstream S;
    std::string class_time_str,date_str;
    class_time_str = class_time->get_Time();
    date_str = exam_date->get_Date();
    S << id << SPACE_CHAR << name << SPACE_CHAR << capacity << SPACE_CHAR << professor_name << SPACE_CHAR
        << class_time_str << SPACE_CHAR << date_str << SPACE_CHAR << class_number << std::endl;

    return S.str();
}

std::string Course::get_Name()
{
    return name;
}

std::string Course::get_Channel_Info()
{
    std::ostringstream S;
    S << get_All_Info();

    Sort_Channel_Posts();
    
    for(int i=0 ; i<channel.size() ; i++)
    {
        S  << channel[i]->get_Info_Include_Author();
    }
    return S.str();
}


std::string Course::get_Channel_Post(std::string post_id)
{
    bool post_id_validation = false;
    UT_Post *target_post;
    for(int i=0 ; i<channel.size() ; i++)
    {
        if(channel[i]->get_Id() == post_id)
        {
            post_id_validation =true;
            target_post = channel[i];
            break;
        }
    }
    if(!post_id_validation)
        throw AvailabilityException(NOT_FOUND_ERROR);
    
    return target_post->get_All_Info_Include_Author();
}


std::string Course::get_Id()
{
    return id;
}

std::vector<std::string> Course::get_Participants_Id()
{
    return participants_id;
}

bool Course::is_Interrupted(Course *course)
{
    if(exam_date->is_Equal_Date(course->exam_date))
    {
        return true;
    }

    Week day_of_week;
    int start_time,end_time;
    day_of_week = course->class_time->get_Day();
    start_time = course->class_time->get_Start();
    end_time = course->class_time->get_End();

    if(class_time->is_Interrupt_Time(day_of_week,start_time,end_time))
        return true;
    
    return false;
}

bool Course::is_Interrupted(std::string time)
{
    std::stringstream S(time);
    std::string day_of_week_str,start_time,end_time;

    getline(S,day_of_week_str,DAY_TIME_SEPRATOR);
    getline(S,start_time,START_END_SEPRATOR);
    getline(S,end_time,START_END_SEPRATOR);

    Week day_of_week = Specify_Day_Of_Week(day_of_week_str);

    if(class_time->is_Interrupt_Time(day_of_week,std::stoll(start_time),std::stoll(end_time)))
        return true;
    return false;
}

bool Course::is_Allowed_to_Post_in_Channel(std::string user_id)
{
    if(user_id == professor_id)
        return true;

    for(int i=0 ; i<teaching_assistants_id.size() ; i++)
    {
        if(teaching_assistants_id[i] == user_id)
            return true;
    }
    return false;
}


bool Course::is_Allowed_to_View_Channel(std::string user_id)
{
    if(user_id == professor_id)
        return true;

    for(int i=0 ; i<teaching_assistants_id.size() ; i++)
    {
        if(teaching_assistants_id[i] == user_id)
            return true;
    }
    for(int i=0 ; i<participants_id.size() ; i++)
    {
        if(participants_id[i] == user_id)
            return true;
    }

    return false;
}


Week Course::Specify_Day_Of_Week(std::string day_of_week_str)
{
    Week day_of_week;

    if(day_of_week_str == "Saturday")
        day_of_week = Saturday;
    else if(day_of_week_str == "Sunday")
        day_of_week = Sunday;
    else if(day_of_week_str == "Monday")
        day_of_week = Monday;
    else if(day_of_week_str == "Tuesday")
        day_of_week = Tuesday;
    else if(day_of_week_str == "Wednesday")
        day_of_week = Wednesday;
    else
        throw ArgumentException(BAD_REQUEST_ERROR);

    return day_of_week;
}

void Course::Free_Allocated_Memory()
{
    delete class_time;
    delete exam_date;
}

void Course::Add_Student(std::string student_id)
{
    participants_id.push_back(student_id);
}

void Course::Add_TA(std::string volunteer_id)
{
    teaching_assistants_id.push_back(volunteer_id);
}

void Course::Add_Post_to_Channel(UT_Post *new_post)
{
    new_post->set_Id(std::to_string(num_of_posts_history +1));
    channel.push_back(new_post);
	num_of_posts_history++;
}


void Course::Sort_Channel_Posts()
{
	UT_Post *temp;
	for(int i=0 ; i<channel.size() ; i++)
	{
		for(int j=0 ; j<channel.size() -1 ; j++)
		{
			if(channel[j]->Compare_Id(channel[j+1]))
			{
				temp = channel[j];
				channel[j] = channel[j+1];
				channel[j+1] = temp;
			}
		}
	}
}