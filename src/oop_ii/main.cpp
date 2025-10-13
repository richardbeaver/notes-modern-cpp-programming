#include <cstddef>
#include <print>

using namespace std;

#define PRINT_VAR(var) std::println("{} = {}", #var, var);

int main() {
    println("Object-Oriented Programming II - "
            "Polymorphism and Operator Overloading");
    //

    // Polymorphism

    // - an entity mutating its behavior in accordance with the specific usage
    //   context
    // Polymorphism dispatch can be at:
    // - compile time (static polymorphism)
    // - runtime (dynamic)
    //
    // Binding - connecting the function call to the function body
    // - early binding - compiler identifies type of the object at compile time
    //   (static)
    //     - program can jump directly to function address
    // - late binding - identifies type of the object at execution time, then
    //   matches function call with the correct function definition
    //     - achieved with `virtual` functions
    //
    // Forms
    // - ad-hoc - on a set of individually specified types (ex. overloading)
    // - parametric - involves generic types (ex. templates)
    // - subtyping - on elements of subtypes (ex. virtual functions)
    //
    // Mechanisms for polymorphism (implementation, form):
    // - preprocessing (ex. macros)
    //     - static, parametric
    // - function/operator overloading
    //     - static, at-hoc
    // - templates
    //     - static, parametric
    // - virtual functions
    //     - dymanic, subtyping

    // Dynamic Polymorphism
    //
    // - at run-time, base class object behaves as objects of a derived class
    // - base class can define and implement polymorphic methods, and derived
    //   classes can override them

    // Virtual Table
    //
    // - a lookup table of functions used to resolve function calls and support
    //   dynamic dispatch (late binding)
    // - contains one entry for each `virtual` function that can be called by
    //   objects of the class
    //     - each entry is a function pointer to the most-derived function
    //       accessible by that class
    // - compiler adds a hidden pointer to the base class that points to the
    //   vtable for that class
    //     - `sizeof` accounts for this
    //
    // - calling `(<class>*) malloc(sizeof(<class>))` does not allocate enough
    // memory
    //     - calling a virtual method in this case will not succeed (vtable
    //       pointer location is outside allocated memory)
    //
    // - sizeof on a class with only a virtual method returns 8 bytes
    //     - storing the vtable pointer

    // `override` (C++11)
    // - ensures that a function is virtual and is overriding a virtual function
    //   from a base class
    //     - forces compiler to check the base class for a virtual function with
    //       this exact signature
    // - implies virtual; `virtual` should be omitted

    // `final` (C++11)
    // - prevents inheriting from classes or overriding methods in derived
    //   classes

    // Common errors
    // - all classes with at least 1 virtual method should declare a virtual
    //   destructor
    // - do not call virtual methods in constructor and destructor
    //     - ctor - derived class is not ready until ctor is completed
    //     - dtor - derived class is already destroyed
    // - do not use default parameters in virtual methods
    //     - default parameters are not inherited

    // Pure Virtual Methods
    //
    // - a function that must be implemented in derived classes
    // - can have or not have a body
    //     - virtual void f() = 0;
    //     - ...
    //     - void A::f() {} // - pure virtual body for f()
    //
    // - a class with one pure virtual function cannot be instantiated
    // - deriving classes that do not have an implementation of a pure
    //   virtual method implicitly have it declared
    //     - and so also cannot be instantiated
    //
    // Interface
    // - class with only pure virtual functions
    // - optionally, (suggested) has a virtual destructor
    // - does not have implementation or data
    //
    // Abstract Class
    // - class with at least one pure virtual function

    // Inheritance Casting and Runtime Type Identification
    //
    // - class-casting - allows implicit or explicit conversion of a cast into
    //   another one across its heirarchy
    //
    // Upcasting
    // - from derived class reference or pointer to a base class
    // - implicit or explicit
    // - safe
    // - `static_cast` or `dynamic_cast`
    //
    // Downcasting
    // - bass class to derived class
    // - only explicit
    // - can be dangerous
    // - `static_cast` or `dynamic_cast`
    //
    // Sidecasting (cross-cast)
    // - between classes of same heirarchy level
    // - only explicit
    // - can be dangerous
    // - `dynamic_cast`

    // Run Time Type Identification (RTTI)
    //
    // - allows type of an object to be determined at run time
    // - only for polymorphic classes (those with at least one virtual method)
    //
    // - dynamic_cast - conversion of polymorphic types
    // - typeid - identifying exact type of an object
    // - type_info class - type information returned by typeid operator
    //     - name() method to return name of the type
    //
    // dynamic_cast<New>(Obj) uses RTTI to deduce correctness of output type
    // - expensive

    // ===================================================================
    // ===================================================================
    // ===================================================================
    // ===================================================================

    // Operator Overloading

    // - special case of polymorphism where some operators are treated as
    //   polymorphic functions and have different behaviors depending on the
    //   type of its arguments
    //
    // arithmetic - + - * / % ++
    // comparison - == != < <= > >= <=>
    // bitwise - | & ^ ~ << >>
    // logical - ! && ||
    // compound assignment arithm - += -= *= /= %=
    // compound assignment bitwise - >>= <<= |= &= ^=
    // subscript - []
    // function call - ()
    // address-of, ref, deref - & -> ->* *
    // memory - new new[] delete delete[]
    // comma - ,
    //
    // operators that cannot be overloaded - ? . .* :: sizeof typeid

    // comparison
    // operator< used for ordering objects (eg. sort)
    //
    // Overloading the spaceship operator (C++20)
    // - three-way comparison
    // - replaces all comparison operators
    // - can also default it
    //     - will use default comparison semantic of its members
    // - a non-defaulted operator<=> doesn't generate == and != operators
    //
    // auto operator<=>(const Obj&) const { ... }
    // auto operator<=>(const Obj&) const = default;
    //
    // - returns one of the ordering classes:
    //     - std::strong_ordering
    //     - std::weak_ordering
    //     - std::partial_ordering

    // array suscript operator[]
    // - accepts everything as parameter, not just integers
    //
    // char& operator[](char c) { ... } // read/write
    // char operator[](char c) { ... }  // read only

    // multidimensional subscript operator[] (C++23)
    // - replaces standard behavior of comma operator
    //
    // int operator[](int x, int y) { ... }
    //   - a[3, 4];

    // function call operator()
    // - generally to create objects that behave like functions, or for classes
    //   that have a primary operation
    //
    // int operator()(int a, int b) const { ... }
    //
    // static operator() and static operator[] (C++23)
    // - for stateless objects
    // - don't receive an implicit `this` pointer
    //     - can't access non-static members
    //     - performance benefit

    // conversion operator T()
    // - implicitly or explicitly (casting) converting to another type
    //
    // operator bool() const { ... }
    //
    // C++11 - can mark explicit to prevent implicit conversions
    //   - good practice

    // increment/decrement - operator++, operator--
    //
    class A {
        int *ptr;
        int pos;

        // prefix (++var) - return a new copy of the object by-reference
        A &operator++() {
            ++ptr;
            ++pos;
            return *this;
        }

        // postfix (var++) - return old copy of the object by-value
        A operator++(int) {
            A tmp = *this;
            ++ptr;
            ++pos;
            return tmp;
        }
    };

    // assignment operator=
    // - copy values from one object to another already existing object
    //
    // A& operator=(const A& x) {
    //     // create new data member values from x
    // }
    //
    // A& operator=(Array x) { // pass by-value
    //     // std::swap values
    //     // x is destroyed at end of scope
    // }

    // stream operator<<
    // - input and output
    // - operator<< is a member of std::ostream - need friend
    //
    // friend std::ostream& operator<<(std::ostream& stream, const Point& p) {
    //     stream << "(" << p.x << "," << p.y << ")";
    //     return stream;
    // }

    // Binary operators - should be implemented as friend methods

    // ===================================================================
    // ===================================================================
    // ===================================================================
    // ===================================================================

    // C++ Object Layout

    // - how objects are arranged in memory
    // - important to how C++ objects interact with pure C API for optimizations
    //     - e.g. pass in registers, memcpy, serialization
    //
    // 1. Aggregate
    // - supports aggregate initialization (form of list-initialization) through
    //   curly brace syntax
    //
    // 2. Trivial Class
    // - class that is trivially copyable (supports memcpy)
    //
    // 3. Standard-Layout
    // - class with same memory layout of the equivalent C struct or union
    // - useful for communicating with other languages
    //
    // 4. Plain Old Data (POD)
    // - trivially copyable + standard layout

    // C++11 utilities to check object layout:
    // - std::is_pod
    // - std::is_trivially_copyable
    // - std::is_standard_layout
}
