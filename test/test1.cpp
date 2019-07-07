#include <iostream>
#include <vunikEngine/init.hpp>

int main (void) {
    vunikEngine::Init::init();
    printf("Hello world!\n");
    vunikEngine::Init::deinit();
    return 0;
}
