//http://stackoverflow.com/questions/315948/c-catching-all-exceptions
//http://stackoverflow.com/questions/541235/how-to-build-a-c-dll-wrapper-that-catches-all-exceptions
//http://blogs.msdn.com/b/jaredpar/archive/2008/01/11/mixing-seh-and-c-exceptions.aspx

try{
     //…
}catch(std::bad_alloc& e)
{
	cout << “Catch bad alloc exception ” << e.what() << endl;
}
catch(std::bad_cast& e)
{
	cout << “Catch bad alloc exception ” << e.what() << endl;
}
catch(std::bad_exception& e)
{
	cout << “Catch bad alloc exception ” << e.what() << endl;
}
// catch more exception types here
// … 
catch(...)
{
	// how to get the content of unkown exception?
}


#include <iostream>

#include <exception>
#include <typeinfo>
#include <stdexcept>

int main()
{
    try {
        throw ...; // throw something
    }
    catch(...)
    {
        std::exception_ptr p = std::current_exception();
        std::clog <<(p ? p.__cxa_exception_type()->name() : "null") << std::endl;
    }
    return 1;
}
