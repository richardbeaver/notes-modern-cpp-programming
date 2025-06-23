#include "greeting.h"
#include <iostream>

auto main() -> int {
    std::cout << "output from main()\n";
    std::cout << get_greeting() << "\n";

    return 0;
}
