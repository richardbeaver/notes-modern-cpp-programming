#include <concepts>
#include <list>
#include <print>
#include <type_traits>
#include <vector>

using namespace std;

#define PRINT_VAR(var) std::println("{} = {}", #var, var);

int main() {
    println("Templates and Metaprogramming II - "
            "Class Templates, SFINAE, and Concepts");

    // Class Templates

    // - family of classes
}

// - Every class specialization is a new class, and does not share anything with
//   the generic class
template <typename T, typename R> //
struct A {                        // generic class template
    T x;
};
template <typename T> //
struct A<T, int> {    // partial specialization
    T y;
};
template <>            //
struct A<float, int> { // full specialization
};
// A<float, float> a1;
// a1.x; // ok, generic template
//
// A<float, int> a2;
// a2.y; // ok, partial specialization

//

// - class template arguments don't need to be repeated if they are the default
// ones
template <typename T> //
struct B {
    B(const B &x); // B(const B<T>& x);
    B f();         // B<T> f();
};

//

// Constructor Template Automatic Deduction (CTAD) (C++17)

// - auto deduce types in constructor calls to generic types
//     - don't need <> on the created type
// - mechanism for compiler to map constructor parameter types into class
//   template parameters
template <typename T, typename R> //
struct Z {
    Z(T x, R y) {}
};
Z<int, float> z1(3, 4.0F); // before C++17
Z z2(3, 4.0F);             // since C++17
// Z<int> z{3, 5}; // X - too few argument (partial specialization)

template <typename T> //
struct MyString {
    MyString(T) {}
};
MyString(char const *) -> MyString<std::string>; // deduction guide
// ^constructor           ^class instantiation
MyString s{"abc"}; // construct 'MyString<std::string>'

// With aggregates:
//
template <typename T> //
struct C {
    T x, y;
};
template <typename T> // deduction guide (not required for aggregates in C++20)
C(T, T) -> C<T>;

C c{1, 3}; // constructs 'C<int, int>'

// Template deduction does not work within the class scope
//
template <typename T> //
struct SomeString {
    SomeString(T) {}
    SomeString f() { return MyString("abc"); }
};
SomeString(const char *) -> SomeString<std::string>; // deduction guide

MyString<const char *> str{"abc"}; // still constructs a 'MyString<const char*>'
// (this seems to construct a MyString<std::string> though:)
auto some = MyString{"abc"};
//
// Can be avoided with a factory:
template <typename T> //
auto make_my_string(const T &x) {
    return MyString(x);
}
auto str2 = make_my_string("abc");
auto str3 = MyString("abc");

// =================================================================

// Class Templates - Advanced Concepts

// Class and Function specialization
//
// - given a class template and a member function, there are two ways to
//   specialize the class/function:
//     1. generic class + generic function
//     2. full class specialization + generic/full specialization function
template <typename T, typename R> //
struct D {
    template <typename X, typename Y> //
    void f();
};
// - a partially specialized class is an independent class, and so must be
//   defined before
// - function members cannot be partially specialized
// - function members of a non-specialized class cannot be specialized
//     - requires a binding to a specific template instantiation at compile-time

//

// `typename` - accessing a dependent type
//

// `template` - what follows is a template name
// - as opposed to interpreting < operator
// - ex. if `g` is a template function in class of `a`:
//     - a.template g<int>();

// can use class template members inside derived classes with `using`
//
// template <typename T> //
// struct B : A<T> {
//     using A<T>::x;
//     using A<T>::f;
// };

// Virtual functions
// - virtual functions cannot have template arguments
//     - virtual functions are a run-time feature
//     - templates are a compile-time feature

// friend
// - can declare generic/full specialized structs and functions as friend
// - partial specializations cannot be declared as friend

// template template parameters
// - match templates instead of concrete types
template <template <typename> class R> //
struct E {
    R<int> x;
    R<float> y;
};
// - C++17 - `class` and `typename` are interchangeable

// ===========================================================================
// ===========================================================================
// ===========================================================================
// ===========================================================================

// Template Metaprogramming

// - Metaprogramming - programs with the ability to treat other programs as data
//     - read, generate, analyze, transform onter programs
//     - modify itself while running
// - C++ Metaprogramming - using C++ template system to perform computation at
//   compile-time within the code
//
// Template Metaprogramming
// - fast, turing complete
// - but is complex, and compilation is slower and requires more memory

// Ex. Factorial

// Recursive step - generic template
template <int N> struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};
// Base case - full specialization
template <> struct Factorial<0> {
    static constexpr int value = 1;
};
// execute at compile time
constexpr int x = Factorial<5>::value; // 120
// int y = Factorial<-1>::value;          // infinite recursion

// Can be rewritten as a constexpr (C++14)
template <typename T> constexpr int factorial(T value) {
    T tmp = 1;
    for (int i = 2; i <= value; i++) {
        tmp *= i;
    }
    return tmp;
}
// Advantages:
// - easy to read, write, and debug
// - faster compile time (no recursion)
// - works with different types (typename T)
// - works at run-time and compile-time

// ===========================================================================
// ===========================================================================
// ===========================================================================
// ===========================================================================

// SFINAE: Substitution Failure Is Not An Error

// - during overload resolution of function templates, when substituting the
//   deduced type for the template parameter fails, the specialization is
//   discarded from the overload set instead of causing a compile error
//
// - `std::enable_if` allows a function template or a class template
//   specialization to include or exclude itself from a set of matching
//   functions/classes
//     - `std::enable_if<T>::type`
//     - `std::enable_if_t<T>`
//
// - enable_if<Cond, T> has a partial specialization where the first template
//   parameter is true
//
// - if the Cond is true, then std::enable_if<true, T> matches the partial
//   specialization, where `::type` will be defined as T
// - std::enable_if<false, T> does not match that specialization and `type`
//   will not be defined
// - attempting to access it results in a substitution failure, which results in
//   that template instantiation being discarded from the overload set
//
// std::enable_if_t<std::is_signed_v<T>>    -> if T is signed, evaluates to void
// std::enable_if_t<std::is_signed_v<T>, T> -> if T is signed: to T
// std::enable_if_t<std::is_signed_v<T>, int> -> if T is signed: to int
//
// - can be used as:
//     - return type (prevents using `auto` as the second parameter)
//     - parameter (prevents argument deduction)
//     - hidden parameter (as the last parameter with a default value)
//     - hidden template paramater
//
// - can also be used to check if a structure has a specific data member or type
//     - see slides 48-52 for examples

// ===========================================================================
// ===========================================================================
// ===========================================================================
// ===========================================================================

// Variadic Templates

// - captures a parameter pack of arguments holding an arbitrary number of
//   values
template <typename... TArgs> //
void f(TArgs... args) {}

// - parameter pack introduced by an identifier prefixed by an ellipsis
// - pack later used in a pattern expanded by an ellipsis
//
// - a pack expansion - equivalent to a comma-separated list of instances of the
//   pattern
// - pattern - set of tokens containing the identifiers of one or more parameter
//   packs
//     - all packs in a pattern must have same length

template <typename... TArgs>  //
void f1(TArgs... args) {      // typename expansion
    int values[] = {args...}; // arguments expansion
}
// f1(1, 2, 3);
//
// the pack TArgs expands in a template-argument-list
//   - list of template arguments
// the pack args expands in an initializer list
//   - list of values

// - number of args can be retrieved with sizeof

// - function unpack - calling function member on args and expanding expands to
//   calling it on all values in args
// ...
// return add(args.f()...); // expands to 'A{1}.f(), A{2}.f(), ...'

// - function application - similarly, passing args to a function and expanding
//   expands to a list of the resulting values from passing each arg to that
//   function
// ...
// return add(square(args)...);

// - use with a type_traits function by expanding typename and arguments
// ...
// g<std::make_unsigned_t<TArgs>...>(args...);

// Function Initializer List Types

template <typename... TArgs> //
void g(TArgs... args) {}     // pass by-value

template <typename... TArgs>  //
void h(const TArgs &...args); // pass by-const reference

template <typename... TArgs> //
void l(TArgs *...args) {}    // pass by-pointer

template <int... Sizes>            //
void m(int (&...arrays)[Sizes]) {} // pass a list of array references

//

// Variadic Template Parameters

template <int... IntSeq> // sequence of integers
void g() {}
// g<1, 2, 3>;

template <int... IntSeq> //
class G {};
// G<1, 2, 3> g{};

// Lambdas with generic parameters (C++14)
//
auto lambda = [](auto... args) {};
// lambda(1, 2u, 3.0F, 1ULL);

// Concepts (C++20)
//
void f(std::floating_point auto... args) {}
// f(1.0, 2.0F); // ok
// f(1U, 2.0F);  // X - compile error

//

// Advanced Usages
// - parameter pack can also be used in:
//     - capture list, constructor inializer-list, `using` declaration

// C++17 Folding expressions
// - perform a fold of a template parameter pack over any binary operator in C++
//
//
// Addition
//
// return (... + args);     // unfold: 1 + 2.0F + 3ULL
// return (1 + ... + args); // unfold: 1 + 1 + 2.0F + 3ULL
// - applying function to args adds results of calling function on each arg
//
//
// Extract last argument
//
// return (args, ...); // comma operator discards left values
//                     // same as (..., args)
// f(1, 2, 3);         // return 3
//
//
// Homogeneous Variadic Parameter Type
// - only enabled if all elements in the pack are ints
template <typename... TArgs>
std::enable_if_t<(std::is_same_v<TArgs, int> && ... && true)>
f(const TArgs... args) {}
// f(1, 2, 3);  // ok
// f(1U, 2, 3); // X - compile error - not all values are ints

// ===========================================================================
// ===========================================================================
// ===========================================================================
// ===========================================================================

// Concepts (C++20)

// - an extension for templates to enforce constraints
//     - compile-time validation on template arguments
// - Advantages over SFINAE (`std::enable_if`):
//     - easier to read and write
//     - clear compile-time messages for debugging
//     - faster compile times
//
// `concept` - constraint
// `requires` - constraint/requirements list; clause and expression
//

// [template arguments]
// concept [name] = [compile-time boolean expression]

// defining a concept:
template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

// template argument constraint
template <Arithmetic T> //
T add(T value1, T value2) {
    return value1 + value2;
}

// auto deduction constrain (constrained auto)
auto add(Arithmetic auto value1, Arithmetic auto value2) {
    return value1 + value2;
}

// `requires` Clause
//
// requires [compile-time boolean expression or Concept]
// - acts like SFINAE

// after template parameter list
template <typename T>
    requires Arithmetic<T>
T add(T value1, T value2) {
    return value1 + value2;
}

// after function declaration:
template <typename T>
T add(T value1, T value2)
    requires(sizeof(T) == 4)
{
    return value1 + value2;
}

// concepts and requirements can have multiple statements
//   - primary expression (ex. constexpr value) or sequence of primary
//     expressions joined with && or ||
template <typename T>
concept Arithmetic2 = std::is_arithmetic_v<T> && sizeof(T) >= 4;

//

// `requires` Expression
// - compile time expression that defines the constraints on template arguments

// requires [(arguments)] {
//     [SFINAE constraint]; // or
//     requires [predicate];
// } -> bool

template <typename T>
concept MyConcept = requires(T a, T b) { // First case: SFINAE constraints
    a + b;                               // Req. 1 - support add operator
    a[0];                                // Req. 2 - support subscript operator
    a.x;                                 // Req. 3 - has "x" data member
    a.f();                               // Req. 4 - has "f" function member
    typename T::type;                    // Req. 5 - has "type" field
};

template <typename T>
concept MyConcept2 = requires(T a, T b) {
    // Req. 6 - can be dereferenced, and the sum plus an integer can be
    // converted to a float
    { *a + 1 } -> std::convertible_to<float>;

    // Req. 7 - "a * a" must be valid and the result type is "int"
    { a * a } -> std::same_as<int>;
};

//

// `requires` Expression + Clause

// - requires expression can be combined with requires clause to compute a
//   boolean value starting from SFINAE expressions

template <typename T>
concept Arithmetic3 = requires {      // expression -> bool (zero args)
    T::value;                         // clause -> direct FSINAE
    requires std::is_arithmetic_v<T>; // clause -> SFINAE from boolean
};

template <typename T>
concept MyConcept3 = requires(T value) {  // expression -> bool (one arg)
    requires sizeof(value) >= 4;          // clause -> SFINAE from boolean
    requires std::is_floating_point_v<T>; // clause -> SFINAE from boolean
};

// - requires clause can be combined with requires expression to apply SFINAE
//   (functions, structs) starting from compile-time boolean expressions

template <typename T>
void f(T a)
    requires requires { T::value; }
//  ^clause -> SFINAE followed by:
//           ^ expression -> bool (zero args)
{}

template <typename T>
T increment(T a)
    requires requires(T x) { x + 1; }
//  ^clause -> SFINAE followed by:
//           ^expression -> bool (one arg)
{
    return a + 1;
}

//

// `requires` and `constexpr`
//
// - Examples:
//
// constexpr bool has_member_x = requires(T v) { v.x; };
// if constexpr (MyConcept<T>)
// static_assert(requires(T v) { ++v; }, "no increment");
//
// template <typename Iter>
// constexpr bool is_iterator() {
//     return requires(Iter it) { *it++; };
// };

// Nested requires example
template <typename Iter>
concept IsIter = requires(Iter it) {
    // Iter it;

    // ⌄clause -> SFINAE followed by:
    requires requires(typename Iter::value_type v) {
        //   ^expression - bool (one arg)
        v = *it;
        *it = v;
    };
};

static_assert(IsIter<std::vector<int>::iterator>);
static_assert(IsIter<std::list<double>::iterator>);
static_assert(!IsIter<int>);

// ===========================================================================
// ===========================================================================
// ===========================================================================
// ===========================================================================

// Template Debugging

// -ftemplate-backtrace-limit=<N>
//   - max # of template instantiation notes for a single warning/error
//   - default 10
//   - N=1 useful when only looking at last instantiation
//   - N=100 (or higher) to look at all (rare)
//
// -ftemplate-depth=<N>
//   - max instantiation depth for template classes to N, default 900
//
// -Wfatal-errors
//   - abort compilation on the first error occurred instead of continuing and
//     printing further messages
//
// -fdiagnostics-show-template-tree
//   - display templates as an indented text tree
