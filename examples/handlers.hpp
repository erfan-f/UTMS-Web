#ifndef HANDLERS_HPP_INCLUDE
#define HANDLERS_HPP_INCLUDE

#include <map>
#include <string>
#include <sstream>

#include "../server/server.hpp"
#include "SystemController.hpp"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class UtMainPageHandler : public RequestHandler
{
    public:

    UtMainPageHandler();
    Response* callback(Request*) override;

private:
    std::string session_id;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LoginHandler : public RequestHandler 
{
public:

    LoginHandler(SystemController *ut_engine_);
    Response* callback(Request*) override;

private:
    SystemController *ut_engine;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LogoutHandler : public RequestHandler 
{
public:

    LogoutHandler(SystemController *ut_engine_);
    Response* callback(Request*) override;

private:
    SystemController *ut_engine;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
class NewPostHandler : public RequestHandler
{
public:

    NewPostHandler(SystemController *ut_engine_);
    Response* callback(Request*) override;

private:
    SystemController *ut_engine;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class HomePageHandler : public RequestHandler
{
public:
    HomePageHandler(SystemController *ut_engine_);
    virtual std::string Generate_HomePage_HTML(std::string sessionId) = 0;
protected:
    SystemController *ut_engine;
};

class OperatorHomePageHandler : public HomePageHandler
{
public:
    OperatorHomePageHandler(SystemController *ut_engine_);
    Response* callback(Request*) override;
    std::string Generate_HomePage_HTML(std::string sessionId);

};


class StudentHomePageHandler : public HomePageHandler
{
public:
    StudentHomePageHandler(SystemController *ut_engine_);
    Response* callback(Request*) override;
    std::string Generate_HomePage_HTML(std::string sessionId);

};

class ProfessorHomePageHandler : public HomePageHandler
{
public:
    ProfessorHomePageHandler(SystemController *ut_engine_);
    Response* callback(Request*) override;
    std::string Generate_HomePage_HTML(std::string sessionId);

};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CourseOfferHandler : public RequestHandler
{
public:

    CourseOfferHandler(SystemController *ut_engine_);
    Response* callback(Request*) override;

private:
    SystemController *ut_engine;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ShowOfferedCoursesHandler : public RequestHandler
{
public:
    ShowOfferedCoursesHandler(SystemController *ut_engine_);
    Response* callback(Request*) override;

private:
    SystemController *ut_engine;
    std::string Generate_Offered_Courses_HTML(std::vector<std::string> engine_response);
};


class ShowCourseDetailHandler : public RequestHandler
{
public:
    ShowCourseDetailHandler(SystemController *ut_engine_);
    Response* callback(Request*) override;

private:
    SystemController *ut_engine;
    std::string Generate_Offered_Course_Detail_HTML(std::vector<std::string> engine_response);
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PutCourseHandler : public RequestHandler
{
public:
    PutCourseHandler(SystemController *ut_engine_);
    Response* callback(Request*) override;

private:
    SystemController *ut_engine;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MyCoursesHandler : public RequestHandler
{
public:
    MyCoursesHandler(SystemController *ut_engine_);
    Response* callback(Request*) override;

private:
    SystemController *ut_engine;
    std::string Generate_My_Courses_HTML(std::vector<std::string> engine_response);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DeleteCourseHandler : public RequestHandler
{
public:
    DeleteCourseHandler(SystemController *ut_engine_);
    Response* callback(Request*) override;

private:
    SystemController *ut_engine;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SetProfilePhotoHandler : public RequestHandler
{
public:
    SetProfilePhotoHandler(SystemController *ut_engine_);
    Response* callback(Request*) override;

private:
    SystemController *ut_engine;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DeleteProfilePhotoHandler : public RequestHandler
{
public:
    DeleteProfilePhotoHandler(SystemController *ut_engine_);
    Response* callback(Request*) override;

private:
    SystemController *ut_engine;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ShowUserPageHandler : public RequestHandler
{
public:
    ShowUserPageHandler(SystemController *ut_engine_);
    Response* callback(Request*) override;

private:
    SystemController *ut_engine;
    std::string Generate_User_Page_HTML(std::string user_info,std::vector<std::string> user_posts,std::string user_profile_photo);
    std::string Extract_User_Info(std::string &response_str);
    std::vector<std::string> Extract_Post_Id(std::string &posts_str);
    std::vector<std::string> ExtreactUserPostsFromEngine(SystemController *ut_engine,std::string session_id,std::string user_id,std::vector<std::string> posts_id);
    std::vector<std::string> ExtractUserPostInformation(std::string post);

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif 