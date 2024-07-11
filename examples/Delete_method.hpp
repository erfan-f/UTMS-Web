#ifndef DELETE
#define DELETE

#include <string>
#include "method.hpp"

class Delete : public Method
{
public:
    Delete(std::string t , std::vector <std::string> cmds);
    ~Delete();
	void Process_Cmd(std::string cmd_line ,std::vector<Major*> &majors ,std::vector<Unit*> &units ,std::vector<User*> &users 
                        ,std::vector<Course*> &courses, User **current_user,std::vector<std::string> &response);

private:
    void HandlePostCmd(std::stringstream &S,User **current_user,std::vector<std::string> &response);
    void HandleMyCoursesCmd(std::stringstream &S,User **current_user,std::vector<std::string> &response);
};

#endif