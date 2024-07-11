#include "handlers.hpp"

#include <cstdlib>
#include <iostream>


UtMainPageHandler::UtMainPageHandler()
{
    std::srand(time(0));    
    session_id = std::to_string(rand() % 10000);
    
}

Response* UtMainPageHandler::callback(Request* req)
{
    Response* res = new Response();
    res->setHeader("Content-Type", "text/html");

    std::ostringstream bodystream;
    bodystream 
      << "<!DOCTYPE html>"
         "<html lang=\"en\">"
         "<head>"
         "<meta charset=\"UTF-8\">"
         "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
         "<title>main_page</title>"
         "<style>"
           "body {"
            "font-family: Arial, sans-serif;"
            "background-color: rgb(30, 84, 102);"
            "margin: 0;"
            "padding: 20px;}"
         ".button {"
         "display: inline-block;"
         "background-color: rgb(30, 84, 102);"
         "color: white;"
         "padding: 10px 20px;"
         "text-decoration: none;"
         "border-radius: 5px;"
         "font-size: 16px;"
         "border: none;"
         "margin-bottom: 10px; }"
         ".button:hover {"
         "background-color: rgb(190, 185, 185);}"
         "img {"
         "border-radius: 50%; }"
         "</style>"
         "</head>"
         "<body style=\"text-align: center;\">"
         "<section style=\"background-color: white; padding: 1%; max-width: 500px; border-radius: 3px; margin: auto;\">"
         "<font size=5px><h1 style=\"color:rgb(30, 84, 102);\">UT MS</h1>"
         "<h2>"
        "<img src=\"/home.png\" alt=\"Home Logo\" style=\"width:50%;\"><br>"
         "<a href=\"/login\" class=\"button\" style=\"width:30%;   margin-top: 30px\">Login</a><br>"
         "</form>"
         "</section>"
         "</body>"
         "</html>";

    res->setBody(bodystream.str());
    res->setSessionId(session_id);

    return res;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
LoginHandler::LoginHandler(SystemController *ut_engine_)
{
    ut_engine = ut_engine_;
    
}

Response* LoginHandler::callback(Request* req)
{
    Response* res;

    std::string id = req->getBodyParam("id");
    std::string password = req->getBodyParam("password");
    std::ostringstream cmd_stream;
    cmd_stream << POST_MTHD << SPACE_CHAR << LOGIN_CMD
                    << SPACE_CHAR << OPERATOR_ARGUMANT << SPACE_CHAR << ID_ARGUMENT << SPACE_CHAR << id
                    << SPACE_CHAR << PASSWORD_ARGUMENT << SPACE_CHAR << password;
    std::string command_line = cmd_stream.str();
    std::vector<std::string> engine_response;
    
    try
    {      
       
        ut_engine->Handle_Cmd(command_line,engine_response,req->getSessionId());
        std::string  user_page_dir = '/' + ut_engine->get_Current_User_Type(req->getSessionId());
        res = Response::redirect(user_page_dir);
        res->setSessionId(req->getSessionId());   
    }
    catch(std::runtime_error &ex)
    {
        if(ex.what() == BAD_REQUEST_ERROR)
            res = Response::redirect("/bad_request");
        else if(ex.what() == PERMISSION_DENIED_ERROR)
            res = Response::redirect("/permission_denied");
        else if(ex.what() == NOT_FOUND_ERROR)
            res = Response::redirect("/not_found");
    }

    return res;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

LogoutHandler::LogoutHandler(SystemController *ut_engine_)
{
    ut_engine = ut_engine_;
}

Response* LogoutHandler::callback(Request* req)
{
   
    std::ostringstream cmd_stream;
    cmd_stream << POST_MTHD << SPACE_CHAR << LOGOUT_CMD
                    << SPACE_CHAR << OPERATOR_ARGUMANT ;
    std::string command_line = cmd_stream.str();
    std::vector<std::string> engine_response;
    Response* res;

    try
    {  
        ut_engine->Handle_Cmd(command_line,engine_response,req->getSessionId());
        res = Response::redirect("/logout");
    }
    catch(std::runtime_error &ex)
    {
        if(ex.what() == BAD_REQUEST_ERROR)
            res = Response::redirect("/bad_request");
        else if(ex.what() == PERMISSION_DENIED_ERROR)
            res = Response::redirect("/permission_denied");
        else if(ex.what() == NOT_FOUND_ERROR)
            res = Response::redirect("/not_found");
    }

    return res;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
HomePageHandler::HomePageHandler(SystemController *ut_engine_)
{
    ut_engine = ut_engine_;
}

OperatorHomePageHandler::OperatorHomePageHandler(SystemController *ut_engine_)
:HomePageHandler(ut_engine_) {}


Response* OperatorHomePageHandler::callback(Request* req) {
    Response* res = new Response();
    res->setHeader("Content-Type", "text/html");

    std::string body;
    body = Generate_HomePage_HTML(req->getSessionId());
    res->setBody(body);
    return res;
}

std::string OperatorHomePageHandler::Generate_HomePage_HTML(std::string sessionId)
{
    std::ostringstream body_stream;

    body_stream 
        << "<!DOCTYPE html>"
        << "<html lang=\"en\">"
        << "<head>"
        << "<meta charset=\"UTF-8\">"
        << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
        << "<title>main_page</title>"
        << "<style>"
                   "body {"
            "font-family: Arial, sans-serif;"
            "background-color: rgb(30, 84, 102);"
            "margin: 0;"
            "padding: 20px;}"
        << ".button {"
        << "display: inline-block;"
        << "background-color: rgb(30, 84, 102);"
        << "color: white;"
        << "padding: 10px 20px;"
        << "text-decoration: none;"
        << "border-radius: 5px;"
        << "font-size: 16px;"
        << "border: none;"
        << "margin-bottom: 10px; }"
        << ".button:hover {"
        << "background-color: rgb(190, 185, 185);}"
        << "img {"
        << "border-radius: 50%; }"
        << "</style>"
        << "</head>"
        << "<body style=\"text-align: center;\">"
        << "<section style=\"background-color: white; padding: 1%; max-width: 300px; border-radius: 3px; margin: auto;\">"
        << "<h1>Admin</h1>"
        << "<h2>"
        << "  <img src=\"admin.png\" alt=\"Student Logo\" style=\"width:50%;\"><br>"
        << "</h2>"
        << "<a href=\"/course_offer\" class=\"button\">Course Offer</a><br>"
        << "<a href=\"/new_post\" class=\"button\">New Post</a><br>"
        << "<form action=\"/logout\" method=\"post\">"
        << "<button type=\"submit\" name=\"logout button\" value=\"Logout\"  class = \"button\">Logout"
        << "</button>"
        << "</form>"
        << "</section>"
        << "</body>"
        << "</html>";

    return body_stream.str();
}


StudentHomePageHandler::StudentHomePageHandler(SystemController *ut_engine_)
:HomePageHandler(ut_engine_) {}


Response* StudentHomePageHandler::callback(Request* req) {
    Response* res = new Response();
    res->setHeader("Content-Type", "text/html");

    std::string body;
    body = Generate_HomePage_HTML(req->getSessionId());
    res->setBody(body);
    return res;
}

std::string StudentHomePageHandler::Generate_HomePage_HTML(std::string sessionId)
{
    std::ostringstream body_stream;

    std::vector <std::string> user_page_info = ut_engine->get_Current_User_Page_Info(sessionId);

    body_stream 
        << "<!DOCTYPE html>"
        << "<html lang=\"en\">"
        << "<head>"
        << "<meta charset=\"UTF-8\">"
        << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
        << "<title>main_page</title>"
        << "<style>"
           "body {"
            "font-family: Arial, sans-serif;"
            "background-color: rgb(30, 84, 102);"
            "margin: 0;"
            "padding: 20px;}"
        << ".button {"
        << "display: inline-block;"
        << "background-color: rgb(30, 84, 102);"
        << "color: white;"
        << "padding: 10px 20px;"
        << "text-decoration: none;"
        << "border-radius: 5px;"
        << "font-size: 16px;"
        << "border: none;"
        << "margin-bottom: 10px; }"
        << ".button:hover {"
        << "background-color: rgb(190, 185, 185);}"
        << "img {"
        << "border-radius: 50%; }"
        << "</style>"
        << "</head>"
        << "<body style=\"text-align: center;\">"
        << "<section style=\"background-color: white; padding: 1%; max-width: 300px; border-radius: 3px; margin: auto;\">"
        << "<h1>Student</h1>"
        << "<h2>";

        body_stream  
        << "<img src=" <<  "\"" << user_page_info[3] << "\"" << " alt=\"Student Logo\" style=\"width:50%;\"><br>"
        << "<font size = \"5px\">" << user_page_info[0]  << "<br>"
        << user_page_info[1] << "<br>"
        << user_page_info[2] << "<br>"
        << "</h2>"
        << "<a href=\"/find_user\" class=\"button\">Users Page</a><br>"
        << "<a href=\"/new_post\" class=\"button\">Add Post</a><br>"
        << "<form action=\"/my_courses\" method=\"post\">"
        << "<button type=\"submit\" name=\"my_course button\" value=\"My courses\"  class = \"button\">My courses"
        << "</button>"
        << "</form>"
        << "<a href=\"/put_course\" class=\"button\">Add course</a><br>"
        << "<a href=\"/delete_course\" class=\"button\">Delete course</a><br>"
        << "<a href=\"/show_courses\" class=\"button\">Offered Courses</a><br>"
        << "<a href=\"/change_profile_photo\" class=\"button\">Change Profile Photo</a><br>"
        << "<form action=\"/logout\" method=\"post\">"
        << "<button type=\"submit\" name=\"logout button\" value=\"Logout\"  class = \"button\">Logout"
        << "</button>"
        << "</form>"
        << "</section>"
        << "</body>"
        << "</html>";

    return body_stream.str();
}

ProfessorHomePageHandler::ProfessorHomePageHandler(SystemController *ut_engine_)
:HomePageHandler(ut_engine_) {}

Response* ProfessorHomePageHandler::callback(Request* req) {
    Response* res = new Response();
    res->setHeader("Content-Type", "text/html");

    std::string body;
    body = Generate_HomePage_HTML(req->getSessionId());
    res->setBody(body);
    return res;
}

std::string ProfessorHomePageHandler::Generate_HomePage_HTML(std::string sessionId)
{
    std::ostringstream body_stream;

    std::vector <std::string> user_page_info = ut_engine->get_Current_User_Page_Info(sessionId);

    body_stream 
        << "<!DOCTYPE html>"
        << "<html lang=\"en\">"
        << "<head>"
        << "<meta charset=\"UTF-8\">"
        << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
        << "<title>main_page</title>"
        << "<style>"
        "body {"
         "font-family: Arial, sans-serif;"
         "background-color: rgb(30, 84, 102);"
         "margin: 0;"
         "padding: 20px;}"
        << ".button {"
        << "display: inline-block;"
        << "background-color: rgb(30, 84, 102);"
        << "color: white;"
        << "padding: 10px 20px;"
        << "text-decoration: none;"
        << "border-radius: 5px;"
        << "font-size: 16px;"
        << "border: none;"
        << "margin-bottom: 10px; }"
        << ".button:hover {"
        << "background-color: rgb(190, 185, 185);}"
        << "img {"
        << "border-radius: 50%; }"
        << "</style>"
        << "</head>"
        << "<body style=\"text-align: center;\">"
        << "<section style=\"background-color: white; padding: 1%; max-width: 300px; border-radius: 3px; margin: auto;\">"
        << "<h1>Porfessor</h1>"
        << "<h2>";

        body_stream 
        << "<img src=" <<  "\"" << user_page_info[3] << "\"" << " " << "alt=\"Student Logo\" style=\"width:50%;\"><br>"
        << "<font size = \"5px\">" << user_page_info[0]  << "<br>"
        << user_page_info[1] << "<br>"
        << user_page_info[2] << "<br>"
        << "</h2>"
        << "<a href=\"/find_user\" class=\"button\">Users Page</a><br>"
        << "<a href=\"/show_courses\" class=\"button\">Offered Courses</a><br>"
        << "<a href=\"/new_post\" class=\"button\">New Post</a><br>"
        << "<form action=\"/logout\" method=\"post\">"
        << "<a href=\"/change_profile_photo\" class=\"button\">Change Profile Photo</a><br>"
        << "<button type=\"submit\" name=\"logout button\" value=\"Logout\"  class = \"button\">Logout"
        << "</button>"
        << "</form>"
        << "</section>"
        << "</body>"
        << "</html>";

    return body_stream.str();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


NewPostHandler::NewPostHandler(SystemController *ut_engine_)
{
    ut_engine = ut_engine_;
}

Response* NewPostHandler::callback(Request* req)
{
     Response* res;
    std::string title = req->getBodyParam("post_title");
    std::string message = req->getBodyParam("post_message");
    std::string image = req->getBodyParam("post_image");

    std::ostringstream cmd_stream;
    std::string image_name;
    if(image != "")
    {
        std::vector current_user_info = ut_engine->get_Current_User_Page_Info(req->getSessionId());
        int post_id = std::stoi(current_user_info[4]) + 1;
        image_name = current_user_info[0] + "_post_" + std::to_string(post_id) + ".png";
        cmd_stream << POST_MTHD << SPACE_CHAR << POST_CMD
                << SPACE_CHAR << OPERATOR_ARGUMANT  << SPACE_CHAR
                << TITLE_ARGUMENT << SPACE_CHAR  << TEXT_CHAR << title << TEXT_CHAR <<  SPACE_CHAR
                << MESSAGE_ARGUMENT<< SPACE_CHAR << TEXT_CHAR << message << TEXT_CHAR << SPACE_CHAR 
                << IMAGE_ARGUMENT << SPACE_CHAR << image_name;
    }
    else
    {
        
        cmd_stream << POST_MTHD << SPACE_CHAR << POST_CMD
                << SPACE_CHAR << OPERATOR_ARGUMANT  << SPACE_CHAR
                << TITLE_ARGUMENT << SPACE_CHAR  << TEXT_CHAR << title << TEXT_CHAR <<  SPACE_CHAR
                << MESSAGE_ARGUMENT<< SPACE_CHAR << TEXT_CHAR << message << TEXT_CHAR;
    }
   
                    
    std::string command_line = cmd_stream.str();
    std::vector<std::string> engine_response;
   
    try
    {
        ut_engine->Handle_Cmd(command_line,engine_response,req->getSessionId());
        if(image != "")
            utils::writeToFile(image,"pic/"+image_name);
        res = Response::redirect('/' + ut_engine->get_Current_User_Type(req->getSessionId()));
    }
    catch(std::runtime_error &ex)
    {
        if(ex.what() == BAD_REQUEST_ERROR)
            res = Response::redirect("/bad_request");
        else if(ex.what() == PERMISSION_DENIED_ERROR)
            res = Response::redirect("/permission_denied");
        else if(ex.what() == NOT_FOUND_ERROR)
            res = Response::redirect("/not_found");
    }

    return res;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

CourseOfferHandler::CourseOfferHandler(SystemController *ut_engine_)
{
    ut_engine = ut_engine_;
}

Response* CourseOfferHandler::callback(Request* req)
{
    std::string course_id = req->getBodyParam("course_id");
    std::string professor_id = req->getBodyParam("professor_id");
    std::string capacity = req->getBodyParam("capacity");
    std::string class_time = req->getBodyParam("day_of_week") + DAY_TIME_SEPRATOR + req->getBodyParam("start_time") + START_END_SEPRATOR + req->getBodyParam("end_time");
    std::string exam_date = req->getBodyParam("exam_date");
    std::string class_num = req->getBodyParam("class_num");


    std::ostringstream cmd_stream;
    cmd_stream << POST_MTHD << SPACE_CHAR << COURSE_OFFER_CMD
                    << SPACE_CHAR << OPERATOR_ARGUMANT  << SPACE_CHAR
                    << COURSE_ID_ARGUMENT << SPACE_CHAR  <<  course_id <<  SPACE_CHAR
                    << PROFESSOR_ID_ARGUMENT << SPACE_CHAR << professor_id << SPACE_CHAR
                    << CAPACITY_ARGUMENT << SPACE_CHAR << capacity << SPACE_CHAR
                    << TIME_ARGUMENT << SPACE_CHAR << class_time << SPACE_CHAR
                    << EXAM_DATE_ARGUMENT << SPACE_CHAR << exam_date << SPACE_CHAR
                    << CLASS_NUMBER_ARGUMENT << SPACE_CHAR << class_num << SPACE_CHAR;

    std::string command_line = cmd_stream.str();
    std::vector<std::string> engine_response;
    Response* res;

    try
    {  
        ut_engine->Handle_Cmd(command_line,engine_response,req->getSessionId());
        res = Response::redirect('/' + ut_engine->get_Current_User_Type(req->getSessionId()));
    }
    catch(std::runtime_error &ex)
    {
        if(ex.what() == BAD_REQUEST_ERROR)
            res = Response::redirect("/bad_request");
        else if(ex.what() == PERMISSION_DENIED_ERROR)
            res = Response::redirect("/permission_denied");
        else if(ex.what() == NOT_FOUND_ERROR)
            res = Response::redirect("/not_found");
    }

    return res;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

ShowOfferedCoursesHandler::ShowOfferedCoursesHandler(SystemController *ut_engine_)
{
    ut_engine = ut_engine_;
}

Response* ShowOfferedCoursesHandler::callback(Request* req)
{
    std::ostringstream cmd_stream;
    cmd_stream << GET_MTHD << SPACE_CHAR << COURSES_CMD << SPACE_CHAR << OPERATOR_ARGUMANT;

    std::string command_line = cmd_stream.str();
    std::vector<std::string> engine_response;
    Response* res = new Response();
    try
    { 
        ut_engine->Handle_Cmd(command_line,engine_response,req->getSessionId());
        std::string body = Generate_Offered_Courses_HTML(engine_response);
        res->setHeader("Content-Type", "text/html");
        res->setBody(body);
    }
    catch(std::runtime_error &ex)
    {
        if(ex.what() == BAD_REQUEST_ERROR)
            res = Response::redirect("/bad_request");
        else if(ex.what() == PERMISSION_DENIED_ERROR)
            res = Response::redirect("/permission_denied");
        else if(ex.what() == NOT_FOUND_ERROR)
            res = Response::redirect("/not_found");
        else if(ex.what() == EMPTY_ERROR)
            res = Response::redirect("/empty");

    }

    return res;
}

std::string ShowOfferedCoursesHandler::Generate_Offered_Courses_HTML(std::vector<std::string> engine_response)
{
    std::ostringstream body_stream;

   body_stream << "<!DOCTYPE html>"
        "<html>"
        "<head>"
        "<style>"
            "body {"
                "font-family: Arial, sans-serif;"
                "background-color: rgb(30, 84, 102);"
                "margin: 0;"
                "padding: 20px;}"

            "h2 {"
                "color: #333;}"

            ".container {"
               " max-width: 400px;"
                "margin: 0 auto;"
                "background-color: #fff;"
                "padding: 20px;"
                "border-radius: 5px;"
                "box-shadow: 0 2px 5px rgba(0, 0, 0, 0.2);}"

            "ul {"
                "list-style-type: none;"
                "margin: 0;"
                "padding: 0;}"
            "li {"
                "padding: 15px;"
                "border-bottom: 1px solid #ccc;"
                "background-color: #e6e6e6;"
                "color: #333;"
                "position: relative; }"

            "li:before {"
                "content: '';"
                "position: absolute;"
                "top: 50%;"
                "left: 0;"
                "width: 10px;"
                "height: 10px;"
                "background-color: #333;"
                "transform: translateY(-50%);"
                "border-radius: 50%; }"

            "li:last-child {"
                "border-bottom: none;}"

                ".input-container {"
                "display: flex;"
                "align-items: center;"
               "margin-top: 20px;}"
            
            ".input-container input[type=\"text\"] {"
                "padding: 10px;"
                "border-radius: 5px;"
                "border: 1px solid #ccc;"
                "flex-grow: 1; }"

        "</style>"
        "</head>"
        "<body>"
             "<div class=\"container\">"
        "<h2>Course Detail</h2>"
        "<ul id=\"myList\">";

    for(int i=0 ; i<engine_response.size() ; i++)
    {
        body_stream << "<li>" <<  engine_response[i] << "</li>";
    }

    body_stream  << "</ul>"
         
         "<form action=\"/course_detail\" method=\"post\">"
	         "<div class=\"input-container\">"
           " <input  name=\"course_id\" type=\"text\"  placeholder=\"Enter course id\";>"
                  "<input type=\"submit\" style=\"display: block; width:20%; padding: 7px;\" value=\"Submit\" class = \"container\">"
                   "</div>"
        "</form>"
        "</div>"
    "</body>"
    "</html>";


  return body_stream.str();
}

ShowCourseDetailHandler::ShowCourseDetailHandler(SystemController *ut_engine_)
{
    ut_engine = ut_engine_;
}

Response* ShowCourseDetailHandler::callback(Request* req)
{
    std::string course_id = req->getBodyParam("course_id");

    std::ostringstream cmd_stream;
    cmd_stream << GET_MTHD <<SPACE_CHAR << COURSES_CMD << SPACE_CHAR << OPERATOR_ARGUMANT << SPACE_CHAR << ID_ARGUMENT << SPACE_CHAR << course_id;

    std::string command_line = cmd_stream.str();
    std::vector<std::string> engine_response;
    Response* res = new Response();
    try
    { 
        ut_engine->Handle_Cmd(command_line,engine_response,req->getSessionId());
        std::string body = Generate_Offered_Course_Detail_HTML(engine_response);
        res->setHeader("Content-Type", "text/html");
        res->setBody(body);
    }
    catch(std::runtime_error &ex)
    {
        if(ex.what() == BAD_REQUEST_ERROR)
            res = Response::redirect("/bad_request");
        else if(ex.what() == PERMISSION_DENIED_ERROR)
            res = Response::redirect("/permission_denied");
        else if(ex.what() == NOT_FOUND_ERROR)
            res = Response::redirect("/not_found");
    }

    return res;
}

std::string ShowCourseDetailHandler::Generate_Offered_Course_Detail_HTML(std::vector<std::string> engine_response)
{
    std::ostringstream body_stream;

   body_stream <<  "<!DOCTYPE html>"
         "<html>"
        "<head>"
        "<style>"
         "body {"
         "font-family: Arial, sans-serif;"
         "background-color: rgb(30, 84, 102);"
         "margin: 0;"
         "padding: 20px;}"
         "h2 {"
         "color: #333;}"
         ".container {"
         "max-width: 400px;"
         "margin: 0 auto;"
         "background-color: #fff;"
         "padding: 20px;"
          "border-radius: 5px;"
          "box-shadow: 0 2px 5px rgba(0, 0, 0, 0.2);}"
          "ul {"
          "list-style-type: none;"
          "margin: 0;"
          "padding: 0;}"
            "li {"
                "padding: 15px;"
                "border-bottom: 1px solid #ccc;"
                "ackground-color: #e6e6e6;"
                "color: #333;"
                "position: relative;}"

                "li:before {"
                "content: '';"
               " position: absolute;"
                "top: 50%;"
                "left: 0;"
                "width: 10px;"
                "height: 10px;"
                "background-color: #333;"
                "transform: translateY(-50%);"
                "border-radius: 50%;}"
            "li:last-child {"
                "border-bottom: none;}"

            ".reference-button {"
            "display: flex;"
            "justify-content: center;"
           " margin-top: 20px;}"

       " .reference-button a {"
            "text-decoration: none;"
            "padding: 10px 20px;"
            "background-color: #333;"
            "color: #fff;"
            "border-radius: 5px;}"
        "</style>"
    "</head>"
    "<body>"
        "<div class=\"container\">"
            "<h2>Course Detail</h2>"
            "<ul id=\"Course List\">";

     body_stream << "<li>" ;

     for(int i=0 ; i<engine_response.size() ; i++)
     {
        body_stream << engine_response[i];
     }
     body_stream << "</li>" ;

    body_stream <<"</ul>"

        "</div>"
        "</body>"
    " </html>";

  return body_stream.str();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

PutCourseHandler::PutCourseHandler(SystemController *ut_engine_)
{
    ut_engine = ut_engine_;
}


Response* PutCourseHandler::callback(Request* req)
{
    std::string course_id = req->getBodyParam("course_id");

    std::ostringstream cmd_stream;
    cmd_stream << PUT_MTHD << SPACE_CHAR << MY_COURSES_CMD << SPACE_CHAR << OPERATOR_ARGUMANT << SPACE_CHAR << "id" << SPACE_CHAR << course_id;

    std::string command_line = cmd_stream.str();
    std::vector<std::string> engine_response;
    Response* res = new Response();
    try
    { 
        ut_engine->Handle_Cmd(command_line,engine_response,req->getSessionId());
        res = Response::redirect('/' + ut_engine->get_Current_User_Type(req->getSessionId()));
    }
    catch(std::runtime_error &ex)
    {
        if(ex.what() == BAD_REQUEST_ERROR)
            res = Response::redirect("/bad_request");
        else if(ex.what() == PERMISSION_DENIED_ERROR)
            res = Response::redirect("/permission_denied");
        else if(ex.what() == NOT_FOUND_ERROR)
            res = Response::redirect("/not_found");
    }

    return res;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

MyCoursesHandler::MyCoursesHandler(SystemController *ut_engine_)
{
    ut_engine = ut_engine_;
}


Response* MyCoursesHandler::callback(Request* req)
{
    Response* res = new Response();
    std::ostringstream cmd_stream;
    cmd_stream << GET_MTHD << SPACE_CHAR << MY_COURSES_CMD << SPACE_CHAR << OPERATOR_ARGUMANT;

    std::string command_line = cmd_stream.str();
    std::vector<std::string> engine_response;
    
    try
    { 
        ut_engine->Handle_Cmd(command_line,engine_response,req->getSessionId());
        std::string body = Generate_My_Courses_HTML(engine_response);
        res->setHeader("Content-Type", "text/html");
        res->setBody(body);
    }
    catch(std::runtime_error &ex)
    {
        if(ex.what() == BAD_REQUEST_ERROR)
            res = Response::redirect("/bad_request");
        else if(ex.what() == PERMISSION_DENIED_ERROR)
            res = Response::redirect("/permission_denied");
        else if(ex.what() == NOT_FOUND_ERROR)
            res = Response::redirect("/not_found");
        else if(ex.what() == EMPTY_ERROR)
            res = Response::redirect("/empty");
    }

    return res;
}

std::string MyCoursesHandler::Generate_My_Courses_HTML(std::vector<std::string> engine_response)
{
    std::ostringstream body_stream;

   body_stream << "<!DOCTYPE html>"
        "<html>"
        "<head>"
        "<title>my courses</title>"
        "<style>"
            "body {"
                "font-family: Arial, sans-serif;"
                "background-color: rgb(30, 84, 102);"
                "margin: 0;"
                "padding: 20px;}"

            "h2 {"
                "color: #333;}"

            ".container {"
               " max-width: 400px;"
                "margin: 0 auto;"
                "background-color: #fff;"
                "padding: 20px;"
                "border-radius: 5px;"
                "box-shadow: 0 2px 5px rgba(0, 0, 0, 0.2);}"

            "ul {"
                "list-style-type: none;"
                "margin: 0;"
                "padding: 0;}"
            "li {"
                "padding: 15px;"
                "border-bottom: 1px solid #ccc;"
                "background-color: #e6e6e6;"
                "color: #333;"
                "position: relative; }"

            "li:before {"
                "content: '';"
                "position: absolute;"
                "top: 50%;"
                "left: 0;"
                "width: 10px;"
                "height: 10px;"
                "background-color: #333;"
                "transform: translateY(-50%);"
                "border-radius: 50%; }"

            "li:last-child {"
                "border-bottom: none;}"

                ".input-container {"
                "display: flex;"
                "align-items: center;"
               "margin-top: 20px;}"
            
            ".input-container input[type=\"text\"] {"
                "padding: 10px;"
                "border-radius: 5px;"
                "border: 1px solid #ccc;"
                "flex-grow: 1; }"

        "</style>"
        "</head>"
        "<body>"
             "<div class=\"container\">"
        "<h2>My Courses</h2>"
        "<ul id=\"myList\">";

    for(int i=0 ; i<engine_response.size() ; i++)
    {
        body_stream << "<li>" <<  engine_response[i] << "</li>";
    }

    body_stream  << "</ul>"
        "</div>"
    "</body>"
    "</html>";


  return body_stream.str();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

DeleteCourseHandler::DeleteCourseHandler(SystemController *ut_engine_)
{
    ut_engine = ut_engine_;
}


Response* DeleteCourseHandler::callback(Request* req)
{
    Response* res;
    std::string course_id = req->getBodyParam("course_id");

    std::ostringstream cmd_stream;
    cmd_stream << DELETE_MTHD << SPACE_CHAR << MY_COURSES_CMD << SPACE_CHAR << OPERATOR_ARGUMANT << SPACE_CHAR << ID_ARGUMENT << SPACE_CHAR<< course_id;

    std::string command_line = cmd_stream.str();
    std::vector<std::string> engine_response;
    try
    { 
        ut_engine->Handle_Cmd(command_line,engine_response,req->getSessionId());
        res = Response::redirect('/' + ut_engine->get_Current_User_Type(req->getSessionId()));
    }
    catch(std::runtime_error &ex)
    {
        if(ex.what() == BAD_REQUEST_ERROR)
            res = Response::redirect("/bad_request");
        else if(ex.what() == PERMISSION_DENIED_ERROR)
            res = Response::redirect("/permission_denied");
        else if(ex.what() == NOT_FOUND_ERROR)
            res = Response::redirect("/not_found");
    }

    return res;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

SetProfilePhotoHandler::SetProfilePhotoHandler(SystemController *ut_engine_)
{
    ut_engine = ut_engine_;
}


Response* SetProfilePhotoHandler::callback(Request* req)
{
    Response* res;

    std::string file = req->getBodyParam("file");

    std::vector current_user_info = ut_engine->get_Current_User_Page_Info(req->getSessionId());
    std::string file_name =  current_user_info[0] + "_profile_photo.png";

    std::ostringstream cmd_stream;
    cmd_stream << POST_MTHD << SPACE_CHAR << PROFILE_PHOTO_CMD << SPACE_CHAR << OPERATOR_ARGUMANT << SPACE_CHAR << PHOTO_ARGUMENT << SPACE_CHAR << file_name;

    std::string command_line = cmd_stream.str();
    std::vector<std::string> engine_response;
    try
    { 
        ut_engine->Handle_Cmd(command_line,engine_response,req->getSessionId());
        utils::writeToFile(file,"pic/" + file_name);
        res = Response::redirect('/' + ut_engine->get_Current_User_Type(req->getSessionId()));
    }   
    catch(std::runtime_error &ex)
    {
        if(ex.what() == BAD_REQUEST_ERROR)
            res = Response::redirect("/bad_request");
        else if(ex.what() == PERMISSION_DENIED_ERROR)
            res = Response::redirect("/permission_denied");
        else if(ex.what() == NOT_FOUND_ERROR)
            res = Response::redirect("/not_found");
    }

    return res;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////


DeleteProfilePhotoHandler::DeleteProfilePhotoHandler(SystemController *ut_engine_)
{
    ut_engine = ut_engine_;
}


Response* DeleteProfilePhotoHandler::callback(Request* req)
{
    Response* res;

    ut_engine->Delete_Current_User_Profile_photo(req->getSessionId());

    res = Response::redirect('/' + ut_engine->get_Current_User_Type(req->getSessionId()));

    return res;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

ShowUserPageHandler::ShowUserPageHandler(SystemController *ut_engine_)
{
    ut_engine = ut_engine_;
}


Response* ShowUserPageHandler::callback(Request* req)
{
    Response* res = new Response();

    std::string user_id = req->getBodyParam("user_id");


    std::ostringstream cmd_stream;
    cmd_stream << GET_MTHD << SPACE_CHAR << PERSONAL_PAGE_CMD << SPACE_CHAR<< OPERATOR_ARGUMANT << SPACE_CHAR << ID_ARGUMENT << SPACE_CHAR << user_id;

    std::string command_line = cmd_stream.str();
    std::vector<std::string> engine_response;
    try
    { 
        
        ut_engine->Handle_Cmd(command_line,engine_response,req->getSessionId());

        std::string user_info = Extract_User_Info(engine_response[0]);

        std::vector<std::string> posts_id = Extract_Post_Id(engine_response[0]);

        std::vector<std::string> user_posts = ExtreactUserPostsFromEngine(ut_engine,req->getSessionId(),user_id,posts_id);

        std::string body = Generate_User_Page_HTML(user_info,user_posts,engine_response[1]);

        res->setHeader("Content-Type", "text/html");
        res->setBody(body);

    }   
    catch(std::runtime_error &ex)
    {
        if(ex.what() == BAD_REQUEST_ERROR)
            res = Response::redirect("/bad_request");
        else if(ex.what() == PERMISSION_DENIED_ERROR)
            res = Response::redirect("/permission_denied");
        else if(ex.what() == NOT_FOUND_ERROR)
            res = Response::redirect("/not_found");
    }

    return res;
}

std::string ShowUserPageHandler::Extract_User_Info(std::string &response_str)
{
    std::string info = response_str.substr(0,response_str.find('\n'));
    response_str.erase(0,response_str.find('\n') + 1);

    return info;

}

std::vector<std::string> ShowUserPageHandler::Extract_Post_Id(std::string &posts_str)
{
    std::vector<std::string> extracted_posts_id;
    std::string id;
    while(posts_str.length() != 0)
    {
        std::stringstream S(posts_str);
        S >> id;
        extracted_posts_id.push_back(id);
        posts_str.erase(0,posts_str.find('\n') + 1);
    }
    return extracted_posts_id;
}



std::vector<std::string> ShowUserPageHandler::ExtreactUserPostsFromEngine(SystemController *ut_engine,std::string session_id,std::string user_id,std::vector<std::string> posts_id)
{
    std::vector<std::string> user_posts;
    for(int i=0 ; i<posts_id.size() ; i++)
    {
        std::ostringstream cmd_stream;
        cmd_stream << GET_MTHD << SPACE_CHAR << POST_CMD << SPACE_CHAR << OPERATOR_ARGUMANT << SPACE_CHAR <<  ID_ARGUMENT << SPACE_CHAR << user_id << SPACE_CHAR << POST_ID_ARGUMENT << SPACE_CHAR << posts_id[i];

        std::string command_line = cmd_stream.str();
        std::vector <std::string> engine_response;
        try
        { 
            ut_engine->Handle_Cmd(command_line,engine_response,session_id);
            engine_response[0].erase(0,engine_response[0].find('\n') + 1);
            user_posts.push_back(engine_response[0]);
        }   
        catch(std::runtime_error &ex)
        {
            if(ex.what() == BAD_REQUEST_ERROR)
                user_posts.push_back(BAD_REQUEST_ERROR);
            else if(ex.what() == PERMISSION_DENIED_ERROR)
                user_posts.push_back(PERMISSION_DENIED_ERROR);
            else if(ex.what() == NOT_FOUND_ERROR)
                user_posts.push_back(NOT_FOUND_ERROR);
        }
    }
    return user_posts;
}


std::string ShowUserPageHandler::Generate_User_Page_HTML(std::string user_info ,std::vector<std::string> user_posts,std::string user_profile_photo)
{

    std::ostringstream body_stream;

    body_stream << "<!DOCTYPE html>"
        "<html>"
        "<head>"
        "<style>"
        "body {"
        "font-family: Arial, sans-serif;"
        "background-color: rgb(30, 84, 102);}"

        ".container {"
        "max-width: 600px;"
        "margin: 0 auto;"
        "padding: 20px;}"

        ".user-info {"
        "background-color: #fff;"
        "border-radius: 5px;"
        "box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);"
        "padding: 20px;"
        "margin-bottom: 20px; }"

        ".user-info h2 {"
        "margin: 0 0 10px;}"

        ".user-info p {"
        "margin: 0;}"

        ".info-label {"
        "color: #999;"
        "font-weight: bold; }"

        ".info-value {"
        "margin-bottom: 10px;}"

        ".post {"
        "display: flex;"
        "flex-direction: column;"
        "background-color: #fff;"
        "border-radius: 5px;"
        "box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);"
        "margin-bottom: 20px;"
        "overflow: hidden;}"


        ".post img {"
        "width: 100%;"
        "height: auto;"
        "display: block;"
        "object-fit: cover;"
        "border-top-left-radius: 5px;"
        "border-top-right-radius: 5px;}"

        ".post .content {"
        "padding: 20px;}"

        ".post h3 {"
        "margin: 0 0 10px;}"

        ".post p {"
        "margin: 0;}"

        "</style>"
        "</head>"
        "<body>"

        "<div class=\"container\">"


        "<div class=\"user-info\">";
        

            body_stream << "<img src=\""  << user_profile_photo << "\" alt=\"User Image\" style=\"width:25%; border-radius: 50%;\" > <br>"
            "<h2>User Information</h2>"
            "<div class=\"info-label\">Name , Major , semester/degree</div>";

            body_stream << "<div class=\"info-value\">" << user_info
                << "</div>"
                "</div>";

        for(int i=0 ; i<user_posts.size() ; i++)
        {
            std::vector<std::string> post_info = ExtractUserPostInformation(user_posts[i]);
            body_stream <<
                "<div class=\"post\">";

            if(post_info[2] != "")    
                body_stream << "<img src=\""  << post_info[2]  << "\" alt=\"Image description\">";
                    
            body_stream << "<div class=\"content\">"
                    "<h3>"
                    << post_info[0]
                    << "</h3>"  
                    "<p>"
                    << post_info[1]
                    << "</p>"
                    "</div>"
                "</div>";
        }

    body_stream << " </div>"
            "</body>"
            "</html>";
    return body_stream.str();
}

std::vector<std::string> ShowUserPageHandler::ExtractUserPostInformation(std::string post)
{
    std::vector<std::string> post_info;
    std::string title,message,image;
    post.erase(0,post.find('"') + 1);
    title = post.substr(0,post.find('"'));
    post.erase(0,post.find('"') + 1);
    post.erase(0,post.find('"') + 1);
    message = post.substr(0,post.find('"'));
    post.erase(0,post.find('"') + 1);
    image = post.substr(1,post.length() - 2);

    post_info.push_back(title);
    post_info.push_back(message);
    post_info.push_back(image);

    return post_info;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
