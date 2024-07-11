#include <iostream>
#include <string>
#include <map>

#include "../server/server.hpp"
#include "handlers.hpp"
#include "SystemController.hpp"

const int VALID_POST_NUM = 10;


void mapServerPaths(Server& server,SystemController *ut_engine);
void ShowDynamicImages(Server &server,SystemController *ut_engine);


int main(int argc, char* argv[]) 
{
	SystemController *ut_engine =  new SystemController();
	ut_engine->Read_Majors(argv[2]);
	ut_engine->Read_Units(argv[3]);
	ut_engine->Read_Professor(argv[4]);
	ut_engine->Read_Student(argv[5]);

	ut_engine->Connect_to_All_User();

    try 
    {
	   	int port = argc > 1 ? std::stoi(argv[1]) : 8080;
	    Server server(port);
	    mapServerPaths(server,ut_engine);
	    std::cout << "Server running on port: " << port << std::endl;
	    server.run();
    }
    catch (const std::invalid_argument& e) 
    {
        std::cerr << e.what() << std::endl;
    }
    catch (const Server::Exception& e) 
    {
        std::cerr << e.getMessage() << std::endl;
    }
    return 0;
}

void mapServerPaths(Server &server,SystemController *ut_engine)
 {
    ShowDynamicImages(server,ut_engine);
    server.get("/student.png" , new ShowImage("pic/student.png"));
    server.get("/professor.png" , new ShowImage("pic/professor.png"));
    server.get("/admin.png" , new ShowImage("pic/admin.png"));
    server.setNotFoundErrPage("static/404.html");
    server.get("/", new UtMainPageHandler());
    server.get("/home.png", new ShowImage("pic/home.png"));
    server.get("/login", new ShowPage("static/login.html"));
    server.post("/login", new LoginHandler(ut_engine));
    server.get("/logout" , new ShowPage("static/logout.html"));
    server.post("/logout" , new LogoutHandler(ut_engine));
    server.get("/bad_request", new ShowPage("static/bad_request.html"));
    server.get("/permission_denied", new ShowPage("static/permission_denied.html"));
    server.get("/not_found", new ShowPage("static/not_found.html"));
    server.get("/empty", new ShowPage("static/empty.html"));
    server.get('/' + STUDENT_TYPE, new StudentHomePageHandler(ut_engine));
    server.get('/' + TEACHER_TYPE, new ProfessorHomePageHandler(ut_engine));
    server.get('/' + OPERATOR_TYPE, new OperatorHomePageHandler(ut_engine));
    server.get("/new_post" , new ShowPage("static/new_post.html"));
    server.post("/new_post" , new NewPostHandler(ut_engine));
    server.get("/course_offer" , new ShowPage("static/course_offer.html"));
    server.post("/course_offer" , new CourseOfferHandler(ut_engine));
    server.get("/show_courses", new ShowOfferedCoursesHandler(ut_engine));
    server.post("/course_detail" , new ShowCourseDetailHandler(ut_engine));
    server.get("/put_course" , new ShowPage("static/put_course.html"));
    server.post("/put_course" , new PutCourseHandler(ut_engine));
    server.get("/delete_course" , new ShowPage("static/delete_course.html"));
    server.post("/delete_course" , new DeleteCourseHandler(ut_engine));
    server.post("/my_courses" , new MyCoursesHandler(ut_engine));
    server.get("/change_profile_photo" , new ShowPage("static/upload_form.html"));
    server.post("/set_profile_photo" , new SetProfilePhotoHandler(ut_engine));
    server.post("/delete_profile_photo" , new DeleteProfilePhotoHandler(ut_engine));
    server.get("/find_user" , new ShowPage("static/find_user.html"));
    server.post("/user_personal_page" , new ShowUserPageHandler(ut_engine));
}

void ShowDynamicImages(Server &server,SystemController *ut_engine)
{
    std::vector<std::string> users_id = ut_engine->get_Users_Id();
    std::string profile_photo,post_photo;

    for(int i=0 ; i<users_id.size() ; i++)
    {
        profile_photo = users_id[i] + "_profile_photo.png";
        server.get('/' + profile_photo , new ShowImage("pic/" +profile_photo));
        for(int j=0 ; j<VALID_POST_NUM ; j++)
        {
            post_photo = users_id[i] +"_post_" + std::to_string(j) + ".png";
            server.get('/' + post_photo , new ShowImage("pic/" + post_photo));
        }
    }
}