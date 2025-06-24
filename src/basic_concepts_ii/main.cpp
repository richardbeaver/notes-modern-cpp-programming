#include <climits>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <print>

using namespace std;

#define PRINT_VAR(var) std::println("{} = {}", #var, var);

auto main() -> int {
    println("Basic Concepts II - integral and floating-point types\n\n");

    // int and unsigned are widely accepted by C++ data models
    // but otherwise, prefer C++11 fixed width integer types
    // same size on any architecture
    int16_t h = 3;
    uint64_t ll = 56L;

    // not "real" types; they're typedefs

    // 5 fundamental types:
    //      char, short, int, long, long long
    // 4 `int*_t` overloads:
    //      int8_t, int16_t, int32_t, int64_t

    // I/O stream interprets uint8_t and int8_t as `char`, not integer values
    int8_t num = 2;
    int8_t c = '2';
    PRINT_VAR(num)
    PRINT_VAR(c)
    println("{}, {}", num * 2, c * 2);

    // size_t, ptrdiff_t, uintptr_t
    size_t big = 45UZ;
    ptrdiff_t signed_big = 56Z;
    uintptr_t void_convertible = 78;

    println("signed overflow may be undefined behavior");
    int biggest = INT_MAX;
    PRINT_VAR(INT_MAX)
    println("{}", INT_MAX + 1);
    println("{}", INT_MIN * -1);

    println("unsigned max wraps around to 0:");
    println("{}", UINT_MAX + 1);

    println("don't mix signed and unsigned arithmetic");
    unsigned x = 32;
    x += 2U - 4; // this doesn't give a warning unless the mixed integers are
                 // declared as their own variables and then used together
    print("30, as expected: ");
    PRINT_VAR(x)
    uint64_t y = 32;
    y += 2U - 4;
    print("not as expected: ");
    PRINT_VAR(y)

    println();
    println("\nFloating point arithmetic\n\n");

    println("infinity\n");
    println("Division by 0 is generally undefined behavior");
    println("integer division is has been showing both 0 and 1; "
            "float division has been 'inf'");
    println("{}", 5 / 0);
    println("{}", 5.0 / 0);
    println("{}", 5 / 0.0);

    println("{}", std::numeric_limits<float>::infinity());
    println("{}", std::numeric_limits<double>::infinity());
    println("numeric limits<int> is 0 here:");
    println("{}", std::numeric_limits<int>::infinity());

    auto inf = std::numeric_limits<float>::infinity();
    println("not sure what int division by infinity can do, but here it's 0:");
    println("{}", 5 / inf);
    println("float division by infinity is 0");
    println("{}", -5.0 / inf);

    println("-0 == 0 = {}", -0 == 0);
    println("-0.0 == 0 = {}", -0.0 == 0);

    println("0 / 0 => undefined behavior");
    println("{}", 0 / 0);
    println("0.0 / 0 => prints nan or -nan");
    println("{}", 0.0 / 0);
    println("0.0 / 0.0 => {}", 0.0 / 0.0);

    println("numeric_limits nan == numeric_limits nan = {}",
            std::numeric_limits<float>::quiet_NaN() ==
                std::numeric_limits<float>::quiet_NaN());
    println("std::nan == std::nan = {}", std::nan == std::nan);
    println("std::nanf == std::nanf = {}", std::nanf == std::nanf);

    println();
    println("Many operations with floats causes inaccuracy");
    float f = 0.0F;
    for (int i = 0; i < 20'000'000; i++) {
        f += 1.0F;
    }
    println("would expect f to be 20'000'000:");
    PRINT_VAR(f)

    double d = 0.0F;
    for (int i = 0; i < 20'000'000; i++) {
        d += 1.0F;
    }
    println("would expect d to be 20'000'000: "
            "yes, even while adding float values to it");
    PRINT_VAR(d)

    println("solving quadratic equation with floats vs doubles:");
    auto res_float =
        (-5000 + std::sqrt((5000.0F * 5000.0F) - (4.0F * 1.0F * 0.25F))) / 2;
    PRINT_VAR(res_float)
    auto res_double =
        (-5000 + std::sqrt((5000.0 * 5000.0) - (4.0 * 1.0 * 0.25))) / 2;
    PRINT_VAR(res_double)
}
