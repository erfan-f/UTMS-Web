#include "UT_media.hpp"

UT_Media::UT_Media(std::string i,std::string t,std::string m,std::string a)
{
    id = i;
    title = t;
    message = m;
    author = a;
}


UT_Media::~UT_Media() {}


bool UT_Media::is_Valid_Id(std::string target_id)
{
    if(id == target_id)
        return true;
    return false;
}

bool UT_Media::Compare_Id(UT_Media *target_post)
{
    if( id < target_post->id)
        return true;
    return false;
}

void UT_Media::set_Id(std::string i)
{
    id =i;
}

std::string UT_Media::get_Id()
{
    return id;
}


std::string UT_Media::get_Info()
{
    std::stringstream S;
	S << id << SPACE_CHAR << title << SPACE_CHAR << std::endl;
    return S.str();
}
 

UT_Post::UT_Post(std::string i,std::string t,std::string m,std::string a,std::string im_p)
:UT_Media(i,t,m,a) 
{
    image_path =im_p;
}

UT_Post::~UT_Post() {}


std::string UT_Post::get_All_Info()
{
    std::stringstream S;
	S << id << SPACE_CHAR << title <<SPACE_CHAR << message << SPACE_CHAR << image_path <<std::endl;
    return S.str();
}

std::string UT_Post::get_Info_Include_Author()
{
    std::stringstream S;
	S << id << SPACE_CHAR  << author << SPACE_CHAR << title  << std::endl;
    return S.str();
}

std::string UT_Post::get_All_Info_Include_Author()
{
    std::stringstream S;
	S << id << SPACE_CHAR << author << SPACE_CHAR << title <<SPACE_CHAR << message << std::endl;
    return S.str();
}


TA_Form::TA_Form(std::string i,std::string t,std::string m,std::string a,std::string c_i,std::string c_info)
:UT_Media(i,t,m,a) 
{
    course_id =c_i;
    course_information = c_info;
}

TA_Form::~TA_Form() {}


std::string TA_Form::get_All_Info()
{
    std::stringstream S;
	S << id << SPACE_CHAR << title  << std::endl;
    S << course_information;
    S << message << std::endl;
    return S.str();
}

std::string TA_Form::get_Course_Id()
{
    return course_id;
}

std::vector<std::string> TA_Form::get_Volunteers()
{
    return volunteers_id;
}

void TA_Form::Add_TA_Request(std::string student_id)
{
    volunteers_id.push_back(student_id);
}