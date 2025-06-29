#include <algorithm>
#include <array>
#include <cstddef>
#include <print>

using namespace std;

#define PRINT_VAR(var) std::println("{} = {}", #var, var);

auto main() -> int {
    println("Basic Concepts IV - memory concepts\n");

    // Pointers

    // pointer - a value referring to a location in memory
    // pointer dereferencing - accessing the value stored at the location
    // referred to by a pointer
    // [] - subscript operator; allows accessing a memory location at an offset
    // from the pointer value

    // pointer operators: +, -, ++, --,
    // comparisons: ==, !=, <, <=, >, >=
    // subscript: []
    // dereferencing: *

    // can be explicitly converted to an integer type
    void *x = nullptr;

    auto _ = (size_t)x; // clang-tidy warning on using C-style cast

    // could replace with C++ reinterpret cast
    // - also a clang-tidy warning to not use that
    auto f = reinterpret_cast<size_t>(x);
    PRINT_VAR(f)

    // size_t _ = x; // compile error (implicit conversion)

    // address-of operator - `&` -> returns address of a variable
    int a = 3;
    int *b = &a;
    a++;
    PRINT_VAR(*b) // prints 4
    // As opposed to reference syntax: T& var = ...

    // struct member access
    struct MyStruct {
        int x;
    };
    MyStruct s{123};
    // dot operator - local objects and references
    int _ = s.x;
    // arrow operator - pointer to an object
    MyStruct *ptr = &s;
    int _ = ptr->x;
    PRINT_VAR(ptr->x) // 123

    // void pointer

    // std::array<int, 3> arr = {1, 2, 3};
    int arr[] = {1, 2, 3};
    void *v_ptr = nullptr;
    PRINT_VAR(sizeof(void *) == sizeof(int *)) // true
    PRINT_VAR(arr == v_ptr)                    // false

    // pointer arithmetic rule:
    // ptr[i] == *(ptr + i)
    // address(ptr + i) = address(ptr) + (sizeof(T) * i)

    int *i_ptr =
        arr + 2; // clang-tidy : not implicitly decay an array into a pointer
    PRINT_VAR(*i_ptr)    // ==> 3
    PRINT_VAR(i_ptr[-1]) // ==> 2
                         // clang-tidy : do not use pointer arithmetic

    // ==========

    // Heap and Stack

    // stored on stack:
    //   - local variables
    //   - function arguments
    //   - return addresses
    //   - compiler temporaries
    //   - interrupt contexts

    // stack objects not valid outside their scope - no longer valid stack
    // memory
    // Undefined Behavior
    /*
    int* f() {
        int array[3] = {1,2,3};
        return array;
    }
    int* ptr = f();
    println(ptr[0]); // ! - illegal memory access
    */

    // heap
    // new/new[] and delete/delete[]
    // - C++ keywords
    // - perform dynamic memory allocation/deallocation and object
    // construction/destruction at runtime
    //   - throw exceptions
    // malloc/free
    // - C functions
    // - only allocate and free memory blocks (in bytes)
    int *ints = new int[3]();
    std::fill_n(ints, 3, 23);
    for (int i = 0; i < 3; i++) {
        PRINT_VAR(ints[i])
    }

    // returns a null pointer instead of throwing `std::bad_alloc` if memory
    // allocation fails
    //   - allocated objects can still throw
    // int *_ = new (std::nothrow) int[SIZE_T_MAX];

    // memory leak
    int *ml = new int{10};
    ml = nullptr; // the memory can no longer be deallocated

    // pages
    // program asks OS for chunk of memory; OS provides memory in pages
    // out-of-bound access is not always seg fault (worst case is execution with
    // undefined behavior)
    int *ip = new int;
    int num_iters = 4096 / sizeof(int);
    for (int i = 0; i < num_iters; i++) {
        ip[i] = 1; // potential seg fault (-fsanitize=address reports a heap
                   // buffer overflow)
    }

    // Initialization

    // C++03
    int a1;    // default (undefined value)
    int a2(2); // direct / value
    int a3(0); // direct / value (zero-initialization)
    // int a4();        // X -> interpreted as a function
    int a5 = 2;      // copy
    int a6 = 2u;     // copy (+ implicit conversion)
    int a7 = int(2); // copy
    int a8 = int();  // copy (zero-initialization)
    int a9 = {2};    // copy list initialization,
                     // brace-initialization/braced-init-list syntax

    // C++11 - Uniform Initialization
    int b1{2}; // direct list / value
    int b2{}; // direct list / value (default constructor / zero-initialization)
    int b3 = int{};  // copy (default constructor / zero-initialization)
    int b4 = int{4}; // copy
    int b5 = {};     // copy list (default constructor / zero-initialization)

    // uniform also good for safe explicit arithemetic type conversion

    // Arrays
    // - brace-initialization syntax
    // - also called braced-init list, or aggregate initialization
    int array[3] = {1, 2, 3};
    int arr2[3] = {}; // all values initialized to 0 (C++11)
    int arr3[3]{};    // all values initialized to 0 (C++11)

    int a2d[][2] = {{1, 2}, {3, 4}, {5, 6}};
    int b2d[][2] = {1, 2, 3, 4}; // automatically fills 2d array with values

    // structs
    struct S {
        unsigned x;
        unsigned y;
    };

    // C++03
    S s1;          // default; x,y undefined
    S s2 = {};     // copy list; x,y default constr./zero-init
    S s3 = {1, 2}; // copy list; x=1, y=2
    S s4 = {1};    // copy list; x=1, y default constr./zero-init
    // S s5(3, 5);    // compile error - constructor not found

    // C++11
    S s6{}; // direct list / value
    S s7{1, 2};
    // S s8{1, -2}; // compile errror - narrowing converion

    // C++20 designated initializer list
    S s8{.x = 3, .y = 4};

    struct B {
        bool a, b, c, d, e;
    };
    B s9{.a = true, .c = true}; // rest of fields zero-initialized to false
    println("{}, {}, {}", s9.a, s9.b, s9.c);

    // C++17 structure binding applies for structs, arrays, and tuples
    int q[2] = {1, 2};
    auto [q1, q2] = q;
    println("{}, {}", q1, q2);
    auto [u1, u2] = std::array<int, 2>{1, 2};
    println("{}, {}", u1, u2);

    // ==========

    // References

    // an alias; both 'variable' and 'variable reference' can be applied to
    // refer to the value of the variable

    // pointer - own memory address and size on the stack
    // reference - shares the same memory address with the original variable

    // cannot be null, cannot be changed, must be initialized when created

    int c = 2;
    int &d = c;
    int &e = d; // reference of a reference
    ++d;
    ++e;
    PRINT_VAR(c) // prints 4

    // As a function argument:

    // void f(int &val) {}
    // - `val` in never a nullpointer

    // void f(int (&arr)[3]) {}
    // - accepts only arrays of size 3

    // ==========

    // `const` and Constant Expressions

    // constant expression - can be evaluated at compile time
    // literal - fixed value that can be assigned to a constant
    // - concrete values of scalar types, string literals of type const char[],
    // nullptr, user-defined literals (ex. 2s)

    // `const` - object that never changes; must be initialized when declared

    // Pointers
    // read types from right to left

    int *_; // pointer to int

    const int *_; // pointer to const int ("pointer to an int that's const")
    //   - value of pointer can be modified; elements referred to by the ptr
    //     cannot
    int const *_; // equivalent

    int *const _ = new int{3}; // const pointer to an int
    //   - value of pointer can't be modified - elements referred to by the ptr
    //     can

    const int *const _ = new int{}; // const pointer to const int
    //    - neither pointer nor elements can be modified

    // adding const to a pointer not the same as adding const to type alias
    using ptr_t = int *;
    const ptr_t p = new int{3}; // this is now `int *const`, not `const int *`
                                //   - clang-tidy warning for doing this
    *p = 5;                     // can modify element pointed to
    // p = new int{};              // X - can't reassign variable

    // `constexpr` (C++11)

    // as a specifier, declares an expression that can be evaluated at compile
    // time

    // constexpr variables are always evaluated at compile time
    // can't assign to dynamic variables

    // constexpr functions guarantee compile-time evaluation if all arguments
    // are compile-time evaluated
    //   - these functions have some limitations in different C++ standards

    // consteval (C++20)
    // guarantees compile-time evaluation
    // runtime value produces compile error

    // constinit (C++20)
    // guarantees compile-time initialization of a variable
    // runtime initialization value produces compile error

    // if constexpr (C++17)
    // evaluate branch at compile time

    // std::is_constant_evaluated() (C++20)
    // evaluate whether current function is evaluated at compile time
    // <type_traits> header
    //   - has two problems that `if consteval` (C++23) solves
    //   1. consteval function can't be used within a constexpr function if
    //   called with a runtime parameter
    //   2. `if constexpr (std::is_constant_evaluated())` is a bug - always true

    // ==========

    // `volatile`

    // hint to compiler to avoid aggressive memory optimizations involving a
    // pointer or object
    // C++20 deprecates volatile outside single load and store operations

    // ==========

    // Explicit Type Conversion

    // static_cast - compile time run check; equivalent to old style cast for
    // value semantic
    //   - prevents accidental or unsafe conversions between pointer types and
    //     const/non-const, and unrelated classes

    // const_cast - can add or remove constness or volatility

    // reinterpret_cast - allows a subset of unsafe conversion
    //  - between pointers/references of different type with same constness
    //  - between pointer and integer types
    // type punning - using reinterpret cast to point 2 pointers of different
    //     types to the same location
    //      - UB; compiler follows 'strict aliasing' rule, where it assumes
    //        different-typed pointers will not alias
    //        - can use memcpy
    //        - std::bit_cast (C++20) is a safe alternative to reinterpret_cast
    //          and memcpy

    // Brace initialization disallows narrowing conversions

    // ==========

    // `sizeof` Operator

    // compile-time operator to determine size in bytes
    // returns a size_t
    // calling on incomplete type or bitfield member produces compile error
    // includes internal padding of structs

    // struct MyStruct {
    //     int x;
    // };
    PRINT_VAR(sizeof(MyStruct)) // 4
    PRINT_VAR(sizeof(s))        // 4
    PRINT_VAR(sizeof(&s))       // 8 - reference (clang-tidy warning for this)

    // [[no_unique_address]] (C++20)
    // allows structure member to be overlapped with other data members of
    // different type

    struct Empty {}; // sizeof(Empty) == 1

    struct Y { // sizeof(Y) == 8 (4 + 1 + 3 for padding)
        int i;
        Empty e;
    };

    struct Z { // sizeof(Z) == 4 ('e' overlaps with 'i')
        int i;
        [[no_unique_address]] Empty e;
    };

    PRINT_VAR(sizeof(Y));
    PRINT_VAR(sizeof(Z));
}
