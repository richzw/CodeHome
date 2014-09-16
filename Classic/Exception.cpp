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
