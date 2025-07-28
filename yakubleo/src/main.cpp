#include <iostream>
#include "UserInterface.h"

int main()
{
    try
    {
        UserInterface interface;
        while (true)
        {
            interface.print();
            if(!interface.processInput())
                break;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
