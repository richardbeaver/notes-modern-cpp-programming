#include <cstddef>
#include <print>

using namespace std;

#define PRINT_VAR(var) std::println("{} = {}", #var, var);

int main() {
    println("Object-Oriented Programming I - Class Concepts");

    // C++ Classes

    // use struct and class to distinguish semantically:
    //   - struct - passive objects; the physical state (set of data)
    //   - class - active objects; the logical state (data abstraction)
    //
    // data within class - 'data member', 'field'
    // function - 'function member', 'method'

    // RAII
    //
    // Holding a resource is a class invariant, and is tied to object lifetime
    //
    // 3 steps:
    // - encapsulate a resource into a class (constructor)
    // - use the resource via a local instance of the class
    // - resource is automatically released when object gets out of scope
    //   (destructor)

    // Class Heirarchy
    //
    // class DerivedClass : [<inheritance attribute>] BaseClass { ... }

    // Access Specifiers
    //
    // public - no restriction
    // protected - function members and derived classes can accesss
    // private - function members only (internal)
    //
    // Use protected/private data members when:
    //   - not part of interface (logical state of the object)
    //   - must preserve `const` correctness (ex. for pointers), see `Advanced
    //     Concepts I`
    // Use public data members:
    //   - can potentially change anytime
    //   - `const` correctness is preserved for values and references (data
    //     members preferred to member fuctions in this case)
    //
    // Access by specifiers on the inheritance:
    // - public - as they were
    // - protected - public things now protected
    // - private - everything private
    //
    // Struct members and inheritance are public by default
    // Class members and inheritance private by default

    struct A {
        int var1; // public
      protected:
        int var2; // protected
    };
    struct B : protected A {
        int var3; // public
    };
    B b{};
    // b.var1; // X - because B inherits with protected access, var1 is now
    //                protected through B
    A a{};
    a.var1; // still accessible through A

    // ============================================================
    // ============================================================
    // ============================================================
    // ============================================================

    // Constructors

    // - special member function executed when new instance is created
    // - supposed to initialize all data members
    // - any constructor can be `constexpr`

    // =============================================================

    // Default Constructor

    // T()
    //
    // - with no argument
    // - every class has implicit, explicit, or deleted default constructor
    //   - (an implicit one is constexpr)

    struct S {
        S() {
            static int num_constructed = 0;
            num_constructed++;
            println("S#{}", num_constructed);
        };
    };
    S s;
    // S s(); // X - interpreted as a function declaration
    S s3{};
    S array[2];        // constructs 2 new S objects
    S *ptr = new S[3]; // constructs 3 new S objects

    // Implicit default constructor marked deleted if any:
    // - class has any user-defined constructors
    // - has a non-static member/base class of reference/const type
    // - has a non-static member/base class with deleted or inaccessible:
    //     - default constructor
    //     - destructor

    // Can initialize data members with defaults where they are declared
    //
    // Initializer list
    //   - direct initialization - x(x1)
    //   - direct-list initialization - x{x1}
    // Initialization follows order of declarations, not the list orders
    //
    // const and reference data members must be initialized in initialization
    // list or (from C++11) in-class brace-or-equal-initializer syntax

    // Uniform Initialization {}
    //
    // - or list-initialization
    // - fully initialize any object independently of its data type
    /*
    struct Point {
        int x, y;
        Point(int x1, int y1) : x(x1), y(y1) {}
    };
    Point add(Point a, Point b) {
        return {a.1 + b.1, a.y + b.y}; // construct Point with the list
    }
    auto c = add({1, 2}, {3, 4}); // construct Points with lists
    */

    // Inheritance
    //
    // - constructors are never inherited
    // - derived class must call base constructor implicitly or explicitly
    //   before the current class constructor
    //     - class constructors called in order from the top Base class to the
    //       most Derived class
    //
    // - "delegate constructor"
    //     - calling another constructor in same class with arguments to
    //       initialize data members
    //     - can do this as part of the initializer list by using the class name
    //       where the data member would be

    // `explicit` keyword
    //
    // - specify a constructor or conversion operator does not allow implicit
    //   conversions or copy-initialization from single arguments or braced
    //   initializers

    // =============================================================

    // Copy Constructor

    // T(const T&)
    //
    // - creates a new object as a deep copy of an existing object
    // - every class has implicit or explicit one, potentially deleted
    // - implicitly calls base class constructor
    // - considered user-defined
    // - not same as assignment operator `operator=`

    // Used to:
    // - initialize one object from another having the same type
    //     - A a2(a1);    // direct copy initialization
    //     - A a3{a1};    // direct copy initialization
    //     - A a4 = a1;   // copy initialization
    //     - A a5 = {a1}; // copy list initialization
    // - copy an object passed by-value as input parameter of a function
    //     - `void f(A a);`
    // - copy an object returned as a result from a function (without RVO
    //   optimization (see "Advanced Concepts I"))
    //     - `A f() { return A(3); }`

    // Implicit copy constructor marked deleted if:
    // - class has the move constructor (see next lectures)
    // - has a deleted copy assignment operator
    // - has non-static member/base class with deleted or inaccessible:
    //     - copy constructor
    //     - destructor

    // =============================================================

    // Destructor

    // ~T()
    //
    // - executed whenever an object is out-of-scope or the delete/delete[]
    //   expression is applied to a pointer of that class
    //     - to release resources
    // - any object has one destructor, either implicitly or explicitly declared
    // - C++20: can be constexpr

    // Inheritance
    //
    // - destructors never inherited
    // - base class destructor invoked after the current class destructor
    //     - class destructors called in reverse order from the most Derived to
    //       the top Base class
    //     - (opposite of constructor order)
    //     - ? - member destructors called between current class and base class

    // =============================================================

    // Defaulted Constructors, Destructor, and Operators (=default)

    // C++11 - compiler can automatically generate:
    // - default / copy / move constructors:
    //     - A() = default
    //     - A(const A&) = default
    //     - A(A&&) = default
    // - destructor
    //     - ~A() = default
    // - copy/move assignment operators
    //     - A& operator=(const A&) = default
    //     - A& operator=(A&&) = default
    // - spaceship operator
    //     - auto operator<=>(const A&) const = default
    //
    // `= default` implies `constexpr`, but not `noexcept` or `explicit`

    // Used to:
    //   - change the access of non-user provided implementations (public,
    //     protected, private)
    //   - make the declarations visible
    //
    // The defaulted default constructor is similar to user-defined constructor
    //   with empty body and empty initializer list
    // Why use compiler-generated constructor:
    //   - forces the default values for the class data members
    //   - any user-provided constructor disables implicitly-generated default
    //     constructor

    struct X {
        // Deletes implicitly-defined default constructor b/c a user-provided
        // constructor is defined:
        X(int v) { println("1 arg"); }

        // X now has the default constructor again
        X() = default;
    };

    // ============================================================
    // ============================================================
    // ============================================================
    // ============================================================

    // Class Keywords

    // this
    // - object has access to own address through the `this` pointer
    // - explicit usage not suggested
    // - necessary when:
    //     - name of a local variable is equal to some member name
    //     - returning a reference to the calling object

    // static
    // - declares members (fields or methods) that are not bound to class
    //   instances
    // - shared by all objects of the class
    // - static member function can only access static class members
    //     - non-static member function can access static class members
    //
    // Constant members
    /*
    struct H {
        static const int a = 4;          // C++03
        static constexpr float b = 4.2F; // better, C++11

        static constexpr int f() { return 1; } // C++11
        // static const int g() { return 1; }  // `const` refers to return type
    };
     */
    // Mutable members
    // - non-const static members cannot be inlined before C++17
    /*
    struct I {
        // static int a = 1;        // X - must be initialized out of line
        static inline int b = 2; // ok from C++17
    };
    */

    // const
    // - const member functions (inspectors/observers) cannot change the
    //   object's logical state
    //     - all data members and `this` marked const inside observer method
    //     - physical state can still be changed
    //         - see `mutable` below
    // - member functions without const are called non-const member functions
    //   (mutators/modifiers)
    // - part of the function signature
    //     - signatures differing only by const are still different functions
    //     - which one is called depends on whether the calling object is const

    // mutable
    // - mutable data members of const instances are modifiable
    // - should not change anything that can be retrieved from the interface
    // - allow const member functions to modify their state while retaining an
    //   external const guarantee

    // using
    // - to declare a type alias tied to a specific class
    struct I {
        using type = int;
    };
    typename I::type i = 3;
    // - change the inheritance attribute of members
    //     - ex. if A had a protected x, it would now be public through B
    /*
    struct B : A {
      public:
        using A::x;
    };
    */

    // friend
    // - a class that can access the private and protected members of the class
    //   in which it is declared a friend
    // - not symmetric, transitive, or inherited
    class F;
    class G {
        friend class F;
        int x;
    };
    class F {
        int f(G g) { return g.x; } // can access private var in G from F
    };
    // - a non-member function could also access variables in a similar way
    /*
    class W {
        int x = 3;
        friend int f(G g);
    };
    int f(G g) { return gx; } // accessing private var in G from function
    */

    // delete
    // - explicitly marks a member function as deleted
    // - when used on copy/move constructor or assignment, prevents compiler
    //   from implicitly generating these functions
    //     - default copy/move functions can produce unexpected results;
    //       `delete` prevents these errors
    /*
    struct E {
        E() = default;
        E(const E &) = delete; // deleted because unsafe or expensive
    };
    void f(E e) {} // makes implicit call to copy constructor

    E e;
    // f(e); // X - call to deleted constructor
    */
}
