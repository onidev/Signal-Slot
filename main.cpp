#include "signal.h"
#include <cstdio>

void slot1()
{
    printf("Signal 1 emitted.\n");
}

void slot2(const std::string& param)
{
    printf("Signal 2 emitted. -> %s\n", param.c_str());
}

struct Foo
{
    void bar() {
        printf("Signal 3 emitted.\n");
    }
};

int main()
{
    // example 1 - function
    od::Signal<> signal1;
    signal1.connect(&slot1);
    
    // example 2 - parameters
    od::Signal<std::string> signal2;
    signal2.connect(&slot2);
    
    // example 3 - class method
    od::Signal<> signal3;
    Foo foo;
    signal3.connect(&Foo::bar, &foo);
    
    // example 4 - lambda
    od::Signal<int, float, std::string> signal4;
    signal4.connect([](int x, float y, const std::string& str)
        {
            printf("Signal 4 emitted. -> %d %f %s\n", x, y, str.c_str());
        });
    
    // emit signals
    signal1.emit();
    signal2.emit("Hello world!");
    signal3.emit();
    signal4.emit(123, 3.1415, "Pizza");
    
    return 0;
}
