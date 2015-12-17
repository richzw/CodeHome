
-----------------------------------------------------------------------------------------

#include <iostream>

struct Window{
    void show() {
        std::cout << "Window\n";
    }
    //stuff
}w1, w2, w3;

struct Widget{
    void show() {
        std::cout << "Widget\n";
    }
    //stuff
}w4, w5, w6;

struct Toolbar{
    void show()
    {
        std::cout << "Toolbar\n";
    }
    //stuff
}t1, t2, t3;


template<class...Objects>
void call_show(Objects&&...objects)
{
    using expand = int[];
    (void) expand { 0, ((void)objects.show(), 0)... };
}

auto main() -> int
{
    call_show(w3, w4, w5, t1);
    return 0;
}

//-------------------------------------------------------------------------------

auto Printer = [](auto&&... args) {
    (args.show(), ...);
};

Printer(w1, w2, w3, w4, w5, w6, t1, t2, t3);
