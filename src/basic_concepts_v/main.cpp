#include <algorithm>
#include <cstddef>
#include <print>

using namespace std;

#define PRINT_VAR(var) std::println("{} = {}", #var, var);

int main() {
    println("Basic Concepts V - functions and preprocessing\n");

    // ===================================================
    // ===================================================

    // Call-by-value - object is copied and assigned to input arguments
    //   - advantages:
    //       - changes made inside function don't effect argument
    //   - disadvantages:
    //       - performance penalty for large objects
    //   - use for:
    //       - built-in datatypes and small objects (<=8 bytes)
    //   - don't use:
    //       - fixed size arrays which decay into pointers
    //       - large objects

    // Call-by-pointer - address of variable is copied
    //   - advantages:
    //       - function can change value of argument
    //       - argument is not copied
    //   - disadvantages:
    //       - argument may be a null pointer
    //       - dereferencing a pointer is slower than directly accessing a value
    //   - use for:
    //       - for raw arrays (use `const T*` if read-only)
    //   - don't use:
    //       - anything else

    // Call-by-reference - reference of variable is copied
    //   - advantages:
    //       - function can change value of argument (with better readability)
    //       - argument is not copied
    //       - no nulls (references must be initialized)
    //       - avoid implicit conversion (without const T&)
    //   - use for:
    //       - all cases expect raw pointers
    //   - don't use:
    //       - pass by-value could have better performance and readability for
    //         built-in data types and small objects

    void f8(int *&a); // pass a pointer by-reference

    //

    // Overloading functions - same name, different signatures
    //
    // Searches for:
    //  - exact match
    //  - promotion (char to int)
    //  - standard type conversion (float to int)
    //  - constructor or user-defined type conversion

    // Can `=delete`
    // void f(int *);
    // void f(std::nullptr_t) = delete;
    // f(nullptr);

    // overloading functions get default parameters of overloaded function

    //

    // Function Objects (functors)
    //
    // A callable object that can be treated as a parameter
    // - argument type checking is always possible
    // - compiler injects `operator()` into destination function code
    //     - operator inlining is standard behavior

    struct Descending {                 // function object
        bool operator()(int a, int b) { // function call operator
            return a > b;
        }
    };
    // C-array
    int array1[]{7, 2, 5, 1};
    std::sort(array1, array1 + 4, Descending{});
    PRINT_VAR(array1);
    // std::array
    std::array array2{7, 2, 5, 1};
    std::sort(array2.begin(), array2.end(), Descending{});
    PRINT_VAR(array2);
    // using ranges
    std::array array3{7, 2, 5, 1};
    std::ranges::sort(array3, Descending{});
    PRINT_VAR(array3);

    // Lambdas (C++11)
    //
    // An inline local-scope function object
    //
    // auto x = [capture clause] (parameters) { body }
    //
    // Capture clause - marks declaration and how local scope arguments are
    //   captured
    // Lambda expression - expression to right of `=`
    // Closure - the runtime object `x` created by that expression

    std::array arr{8, 2, 1, 5};
    std::ranges::sort(arr, [](int a, int b) { return a > b; });
    PRINT_VAR(arr);

    // Capture list:
    //
    // [] - no capture
    // [=] - capture all variables by-value
    // [&] - capture all variables by-reference
    // [var1] - captures only var1 by-value
    // [&var2] - captures only var2 by-reference
    // [var1, &var2] - captures var1 by-value and var2 by-reference
    //
    // [=, &var1] - all variables by-value except var1, which is by-reference
    // [&, var1] - all by-reference except var1, which is by-value
    //
    // - Lambda can read a variable without capturing if the variable is
    //   `constexpr`
    // - Can be converted to a function (stateless) if capture list is empty
    //
    // C++14:
    // - parameters can be automatically deduced (declared with auto)
    // - parameters can be initialized
    //     - auto x = [](int i = 6) { return i + 4; }

    // Composed
    auto lambda1 = [](int value) { return value + 4; };
    auto lambda2 = [](int value) { return value * 2; };
    auto _ = [&](int value) { return lambda2(lambda1(value)); };

    // Functions can return lambdas

    // Lambdas can be called recursively
    auto factorial = [](int n, auto fac) -> int {
        return (n <= 1) ? 1 : n * fac(n - 1, fac);
    };
    PRINT_VAR(factorial(5, factorial))

    // C++23 - access `this` pointer of a lambda object with `this auto` or
    // `this auto&& self` as first parameter
    auto factorial2 = [](this auto self, int n) -> int {
        return (n <= 1) ? 1 : n * self(n - 1);
    };
    PRINT_VAR(factorial2(5))

    // C++17 - support constexpr
    // C++20 - support consteval
    auto fact = [](int value) constexpr {
        int ret = 1;
        // ...
        return ret;
    };
    auto mul = [](int v) consteval { return v * 2; };
    constexpr int _ = fact(4) + mul(5);

    // C++20 - supports `template` and `requires` clause
    auto l = []<typename T>(T value)
        requires std::is_arithmetic_v<T>
    { return value * 2; };
    l(3.4);

    // Without automatic deduction needs full syntax
    auto lam = []<typename T>(int value) {
        return value * sizeof(T); //
    };
    // lam(3);         // X - no matching function call
    // lam<double>(3); // X - isn't able to recognize template parameters
    lam.operator()<double>(3); // ok

    // Before C++20: `template` arguments emulated with `auto` + `decltype`
    auto la = [](auto value) {
        using T = decltype(value); // T: double
    };
    la(3.4);

    // Mutable lambda expressions
    // - can modify parameters captured by-value
    int var = 1;
    auto lamb = [=]() mutable { var = 3; };
    PRINT_VAR(var) // still 1

    // Capture List and Classes
    //
    // [this] - captures the current object (*this) by-reference (C++17)
    // [x = x] - captures current object member x by-value (C++14)
    // [&x = x] - current object member x by-reference (C++14)
    // [=] - default capture of `this` pointer by value has been deprecated
    //       (C++20)
    class A {
        int data = 1;
        void f() {
            int var = 2;

            auto l = [this]() { return data; };   // by-reference; return 1
            auto la = [*this]() { return data; }; // by-value (C++17); return 1
            auto lam = [data = data]() { return data; }; // return 1
            // auto lamb = [data]() { return data; }; // X - data is not visible
            auto lambd = [=]() { return data; }; // deprecation warning
        }
    };

    // ====================================================================
    // ====================================================================
    // ====================================================================
    // ====================================================================

    // Preprocessing

    // Preprocessor directive
    // - any line preceded by a #
    // - tells comiler how to interpret source code before compiling it
    //
    // Macro
    // - preprocessor directive that substitutes any ocrurrence of an identifier
    // in the rest of the code by replacement
    //   - can't be debugged
    //   - expansions can have unexpected side effects
    //   - no namespace or scope

    // TODO: return to slides 35-62(end) on macros
}
