#include <exception>
#include <string>

using namespace std; 

class Exception : public exception
{
public:
    Exception(string err){
        _err = err; 
    }
    string getError() const{
        return _err;
    }
private:
    string _err; 
};