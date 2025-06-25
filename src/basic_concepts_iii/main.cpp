#include <array>
#include <iostream>
#include <print>
#include <ranges>
#include <vector>

using namespace std;

#define PRINT_VAR(var) std::println("{} = {}", #var, var);

namespace MyNamespace {

void f() { println("MyNamespace::f()"); }

struct S {};

using T = int;

} // namespace MyNamespace

// incomplete type - declaration without definition
struct A;

struct B {
    int b;
    // A x; // => compile error - incomplete type A
    A *y; // ok -> pointer to incomplete type
};

// X: don't use - enums can be implicitly converted to ints
// - allows for unintended comparison results
enum color_t : std::uint8_t { BLACK, BLUE, GREEN };
// Use `enum class` (scoped enum) - type safe
// - not implicitly convertible to an int (can be explicitly converted)
// - compile error when trying to compare with other types
enum class Color : std::uint8_t { BLACK, BLUE, GREEN };

auto main() -> int {
    println("Basic Concepts III - entities and control flow\n");

    // C++20 allows introducing enumerator identifiers into local scope
    // - but this seems to work even when commenting out the `using` statement
    // - maybe default to using it anyway; or just using full form of enum value
    using enum Color;
    println("{}", BLUE == GREEN);       // false
    println("{}", Color::BLUE == BLUE); // true

    struct A {
        int x;
        enum : std::uint8_t { X, Y }; // enums can be declared without a name
    } a{}, b{};                       // declaring variables of this struct type

    println("{}", A::X == A::Y); // false

    // unnamed struct
    struct {
        int x;
        // struct {
        //     int y
        // }; //-Wgnu-anonymous-struct - anonymous structs are GNU extension
        //-Wpedantic - diagnose use of non-strict ISO C++ extensions
    } my_struct{};

    // bitfield
    struct S1 {
        int b1 : 10; // range [0, 1023]
        int b2 : 10; // range [0, 1023]
        int b3 : 8;  // range [0, 255]
    }; // sizeof(S1) = 4 bytes
    struct S2 {
        int b1 : 10;
        int : 0; // reset: force the next field to start at bit 32
        int b2 : 10;
    }; // sizeof(S2) = 8 bytes

    union U {
        int x;
        char y;
    }; // sizeof(A) = 4
    // from clang-tidy when accessing members: Do not access members of unions;
    // consider using (boost::)variant instead
    // Use std::variant for type-safe union

    // ternary operator
    std::string str = (sizeof(a) < sizeof(b)) ? "yes" : "no";
    PRINT_VAR(str)

    // multiple initializations and increments
    for (int i = 0, k = 0; i < 10; i++, k += 2) {
        //
    }
    for (;;) {
        println("infinite");
        break;
    }

    // C++11 - range-based for loop. Can be used in 3 cases:
    // 1. Initializer list
    for (int v : {3, 2, 1}) {
        PRINT_VAR(v)
    }
    // 2. Fixed-size array of values
    std::array<int, 3> values = {4, 5, 6};
    for (int v : values) {
        PRINT_VAR(v)
    }
    // 3. any object with `begin()` and `end()` methods
    for (auto c : "abcd") {
        PRINT_VAR(c)
    }
    std::vector vec{1, 2, 3, 4};
    for (auto c : vec) {
        PRINT_VAR(c)
    }

    // multidimensional:
    std::array<std::array<int, 4>, 2> matrix;
    // - equivalent to : int matrix[2][4];
    for (auto &row : matrix) {
        for (auto _ : row) {
            cout << '@';
        }
        cout << '\n';
    }

    // ======= Trying out other things =========
    //
    println("\nEnumerating");
    // enumerating
    // - std::views::enumerate not yet in C++ standard
    //     - Can use the `range-v3` library for it
    // - can use default standard for loop and [] accessing
    for (auto [it, i] = tuple{vec.begin(), 0}; it != vec.end(); it++, i++) {
        println("idx {}: {}", i, *it);
    }
    for (int i = 0; auto val : vec) {
        println("idx {}: {}", i, val);
        i++; // ***need to increment i on its own
    }
    for (auto [i, val] : std::views::zip(std::views::iota(0), vec)) {
        println("idx {}: {}", i, val);
    }

    println();

    // ===================================

    // C++17 - structure binding
    struct SB {
        int x;
        int y;
    };
    // warning about C-style arrays
    SB arr[] = {{.x = 1, .y = 2}, {.x = 3, .y = 4}, {.x = 5, .y = 6}};
    // But I keep getting errors on these. not sure how to do this here
    // array<SB, 3> arr = {{1, 2}, {3, 4}, {5, 6}};
    // array<SB, 3> arr = {{.x = 1, .y = 2}, {.x = 3, .y = 4}, {.x = 5, .y =
    // 6}};
    for (auto [x1, y1] : arr) {
        println("{}, {}", x1, y1);
    }

    // switch fall-through
    enum class E : std::uint8_t { A, B, C };
    for (auto i : std::views::iota(0, 3)) {
        PRINT_VAR(i)
        // switch (static_cast<E>(i)) {
        switch (i) {
        case (int)E::A:
            println("case A");
        case (int)E::B:
            println("case B");
        case (int)E::C:
            println("case C");
            break;
        default:
            break;
        }
    }

    // namespaces

    // `using`-declaration
    using MyNamespace::S;
    S _;
    // Generally not recommended:
    // `using namespace` directive
    using namespace MyNamespace;
    f();

    // annotations
    // [[nodiscard]]
    // [[maybe_unused]]
    // [[deprecated<(reason)>]]
}
