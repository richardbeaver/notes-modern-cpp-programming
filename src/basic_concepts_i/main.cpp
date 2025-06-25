#include <cstring>
#include <iostream>
#include <utility>

#define PRINT_VAR(var) std::cout << #var << " = " << var << "\n";

auto main() -> int {
    std::cout << "Basic Concepts I - "
                 "type system, fundamental types, and operators\n\n";

    double d = 1.0;
    int i = 3;
    short h = 6;
    long l = 4'000'000;
    unsigned u = 65;

    // Implicit numeric type conversion rules
    double _ = i + d;   // floating point promotion
    int _ = h + h;      // integer promotion
    long _ = h + l;     // size promotion
    unsigned _ = u + i; // sign promotion

    std::cout << "implicit sign conversion - "
                 "negative number made unsigned wraps around:\n";
    int neg_i = -75;
    unsigned becomes_unsigned_negative = u + neg_i;
    std::cout << becomes_unsigned_negative << '\n';

    int int_division = i / 2;
    double float_division = i / 2.0;
    std::cout << "results of int and non-int division: " << int_division << ", "
              << float_division << "\n";

    char c = 'c';
    char c2 = 53;
    std::cout << "printing a char: " << c << '\n';
    std::cout << "printing a char defined as a number: " << c2 << '\n';
    std::cout << "binary op on char converts to an int: " << +c << '\n';
    std::cout << "binary op on number-defined char converts to an int (same "
                 "number value): "
              << +c2 << '\n';

    int test = 4;
    std::cout << '\n'
              << "inc/dec:\n"
              << --test << ' ' << test-- << ' ' << test << "\n";

    std::cout << "previously undefined behavior:\n";
    i = 0;
    i = ++i + 2;
    PRINT_VAR(i)
    i = 0;
    i = i++ + 2;
    std::cout << "slides say this shoud be 3 since C++17, but I'm getting 2:\n";
    PRINT_VAR(i)

    std::cout << "compound assignment:\n";
    int x = i = 12;
    PRINT_VAR(x)
    PRINT_VAR(i)
    std::cout << (x = 100) << '\n';
    PRINT_VAR(x)

    std::cout << "spaceship\n";
    std::cout << strcmp("first", "second") << '\n';
    std::string first = "first";
    std::string second = "second";
    auto result = (first <=> second) < 0;
    std::cout << result << '\n';
    PRINT_VAR(result)

    std::cout << "\nutil comparisons\n";
    unsigned u_pos = 4;
    int neg = -3;
    auto comp = u_pos > neg;
    PRINT_VAR(comp)
    auto util_comp = std::cmp_greater(u_pos, neg);
    PRINT_VAR(util_comp)

    return 0;
}
