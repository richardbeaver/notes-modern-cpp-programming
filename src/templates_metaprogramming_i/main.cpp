#include <print>
#include <type_traits>

using namespace std;

#define PRINT_VAR(var) std::println("{} = {}", #var, var);

int main() {
    println("Templates and Metaprogramming I - "
            "Function Templates and Compile-Time Utilities");

    // Template
    // - mechanism for generic programming to provide a schema (or placeholders)
    //   to represent the structure of an entity
    // - in C++, templates are compile-time functionality to represent:
    //     - family of functions
    //     - family of classes
    //     - family of variables (C++14)
    //
    // Benefits
    // - less code, reusable, reduce redundancy, better maintainability and
    //   flexibility
    // - performance - computation done/optimized at compile-time
    // Drawbacks
    // - readability - hard to read and cryptic error messages
    // - compile time
    // - binary size - templates instantiated for every distinct parameter

    // Function Template
    //
    // - function schema with generic types (independent of any particular type)
    //   or concrete values
    /*
    template <typename T> // or template<class T>
    T add(T a, T b) {
        return a + b;
    }
    */

    // Template Instantiation
    //
    // - the substitution of template parameters with croncete values or types
    // - compiler automatically generates a function implementation for each
    //   template instantiation
    //
    // Implicit
    // - when compiler generates code based on deduced argument types of the
    //   explicit template argumensh and only when the definition is needed
    //
    // Explicit
    // - depending only on the explicit template arguments specified in the
    //   declaration
    //
    // template<typename T>
    // void f(T a) {}
    //
    // - implicit:
    //     - f(3)
    //     - f<short>(3.0);
    // - explicit:
    //     - template void f<int>(int);

    // Template Parameters
    //
    // - the names following `template`
    //     - `typename T`
    //     - f<int>(); // <- int is the template argument
    //
    // - can pass a concrete type for a 'non-type template parameter' (NTTP)
    //
    // template<int A, int B>
    // int add_int() { ... }
    //
    // add_int<3, 4>(); // <- sum is computed at compile time

    // - C++11 - template paramaters can have default values
    //
    // - Can have no name
    //     - g() generated if it is called
    // template<typename = void>
    // void g() {}

    // C++11 - can be initialized by previous values
    // template<int A, int B = A + 3>
    // template<typename T, int S = sizeof(T)>

    // Template Function Overloading
    // - concrete type overloading has higher precedence
    // - parameters are part of signature

    // Template Specialization
    // - a concrete implementation for a specific combination of template
    //   parameters
    // - function templates can be specialized if all template arguments are
    //   specialized
    //
    // template<>
    // bool compare<float>(float a, float b) {
    //     // ...
    // }

    // Template Variable
    //
    // - C++14 - allows variables with templates
    // - special case of a class template
    //
    // template<typename T>
    // constexpr T pi{ 3.1415926535897 };

    // Template Paramater Types
    //
    // template parameters can be:
    // - integral type
    // - enum, enum class
    // - generic type `typename`
    // - C++17 - `auto` placeholder
    // - C++20 - floating point type, class literals and concepts
    //
    // and rarely:
    // - function
    // - reference/pointer to global `static` function or object
    // - pointer to member type
    // - C++14 - `nullptr_t`

    // `auto` placeholder (C++17)
    //
    // - automatic deduction of non-type template parameters
    //
    // template<auto X, auto Y>
    // void g() { ... }

    // Function Type Template Paramater
    //
    // template<int (*F)(int, int)>
    // int apply1(int a, int b) {
    //     return F(a, b);
    // }
    //
    // - alternative syntax:
    //
    // template<decltype(f) F>
    //
    // - call as (assuming `int f(int, int)` is defined):
    //
    // apply1<f>(2, 3);

    // ============================================================
    // ============================================================
    // ============================================================
    // ============================================================

    // Compile-Time Utilities

    // static_assert (C++11)
    // - test an assertion at compile time
    //     - ex. sizeof, literals, templates, constexpr
    //
    // - C++17 - assertions without messages
    // - C++26 - assertions with text formatting

    // `using` keyword (C++11)
    //
    // - alias-declaration, or alias-template
    // - enhanced version of typedef with better syntax and that can be combined
    //   with templates
    // - simplify complex template expressions
    //
    // using distance_t = int;
    // using function = void (*)(int, float);
    //
    // - introduce new names for partial and full specializations
    //
    // template<int Size>
    // using Bitset = Vector<bool, Size>  // partial
    //
    // using IntV4 = Vector<int, 4>       // full

    // decltype (C++11)
    //
    // - returns the declared type of an entity
    // - returns the type of an expression
    //     - variable evaluated as an expression deduced as an lvalue
    //         - ex. decltype((var))
    //     - a general expression deduced as its final type
    //         - ex. decltype((a + b))

    // ============================================================
    // ============================================================
    // ============================================================
    // ============================================================

    // Type Traits (C++11)

    // - compile time interface to query or modify the properties of types
    //
    // - introspection - ability to inspect a type and query its properties
    // - reflection - ability of a program to examine, introspect, and modify
    //   its own structure and behavior

    // How can we specify only certain types allowed to be instantiated for
    // template parameters?
    //
    // Either
    // 1. specialize
    // 2. type traits + `static_assert`
    //
    // - specializing for all integral types requires rewriting the template for
    //   each type (int, long, char, short, etc.)
    // - instead we use type traits for compile time checks on the template
    //   instantiations to assert that they satisfy some condition

    // #include <type_traits>
    //
    // template<typename T>
    // T integral_div(T a, T b) {
    //     static_assert(std::is_integral<T>::value,
    //                   "integral_div accepts only integral types");
    //     return a / b;
    // }
    //
    // - std::is_integral<T> is a struct with a static constexpr boolean field
    //   `value`
    // - C++17 - utilities to improve readability
    //     - `std::is_integral_v<T>`

    // Fundamental and Scalar Types
    // - is_integral
    // - is_floating_point
    // - is_arithmetic
    // - is_signed
    // - is_unsigned
    // - is_enum
    // - is_void
    // - is_pointer
    // - is_null_pointer
    //
    // Entity type queries:
    // - is_reference
    // - is_array - ( T (&)[N] )
    // - is_function
    //
    // Class queries:
    // - is_class
    // - is_abstract
    // - is_polymorphic
    //
    // Type properties:
    // - is_const
    //
    // Type relation:
    // - is_same<T, R>
    // - is_base_of<T, R> - if T is base of R
    // - is_convertible<T, R> - if T can be converted to R

    PRINT_VAR(std::is_integral<int>::value) // true
    PRINT_VAR(std::is_integral_v<int>)      // true

    PRINT_VAR(std::is_unsigned_v<int>) // false

    PRINT_VAR((std::is_convertible_v<int, float>)) // true
    PRINT_VAR((std::is_convertible_v<float, int>)) // true

    PRINT_VAR((std::is_same_v<int, int *>)) // false

    //

    // Type Manipulation
    //
    // `type`
    using U = typename std::make_unsigned<int>::type;
    // - with C++14-style type templates
    using U = std::make_unsigned_t<int>;

    // Signed/Unsigned
    // - make_signed
    // - make_unsigned
    //
    // Pointers and References
    // - remove_pointer (T* -> T)
    // - remove_reference (T& -> T)
    // - add_pointer (T -> T*)
    // - add_lvalue_reference (T -> T&)
    //
    // `const` Specifiers
    // - remove_const
    // - add_const
    //
    // Other transformations:
    // - common_type<T, R>
    // - conditional<pred, T, R> - return T if pred is true, else R
    // - decay<T> - same conversion as for function arguments passed by-value

    using T = short; // assume T and R are template parameters
    using R = int;

    constexpr bool pred = sizeof(T) > sizeof(R); // whether T is larger than R

    using S = std::conditional<pred, T, R>::type; // S is the larger of T and R
    PRINT_VAR(sizeof(S) == sizeof(int))           // true (S is int type)

    using S = std::conditional_t<pred, T, R>; // using C++14 style
    PRINT_VAR(sizeof(S) == sizeof(int))       // true
}
