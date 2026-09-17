
// #include <iostream>
// #include "shared_pointer.hpp"

// using namespace std;
// using namespace ilrd178;


// class A 
// {
    
// public:
//     A(const int a = 1 , const int b = 2):m_a(a), m_b(b){}
//     virtual ~A(){}
//     int m_a;
//     int m_b;
// };

// class B : public A
// {
    
// public:
//     B(const int c = 5):m_c(c){}
//     ~B(){}
//     int m_c;
// };

// int main()
// {
//     SharedPtr<B> ptrB(new B(42));
//     SharedPtr<A> ptrA = ptrB; 

//     cout << "ptrB->m_c: " << ptrB->m_c << endl; // 42
//     cout << "ptrA->m_a: " << ptrA->m_a << endl; // 1
//     cout << "(*ptrA).m_b: " << (*ptrA).m_b << endl; // 2

//     {
//         SharedPtr<A> ptrA2(ptrB);
//         ptrA2 = ptrB; 
//     }

//     cout << "(*ptrB).m_c: " << (*ptrB).m_c << endl; 
//     return 0;
// } 


/////////////////////////////////////////////////////////////////////////////////



#include <iostream> /* cout */
#include <pthread.h> /* pthread_mutex_t, pthread_mutex_init, pthread_mutex_lock... */

#include "shared_pointer.hpp" /* SharedPtr */

using namespace ilrd178;

class Animal
{
public:
    virtual ~Animal();

    virtual void Speak() const;

    int m_legs;
};

class Named
{
public:
    /* virtual: a SharedPtr<Named> may be the last owner of a Dog,
       and its destructor deletes through this type */
    virtual ~Named();

    int m_id;
};

class Dog : public Named, public Animal
{
public:
    void Speak() const;

    int m_tricks;
};

Animal::~Animal()
{
}

void Animal::Speak() const
{
    std::cout << "Animal\n";
}

Named::~Named()
{
}

void Dog::Speak() const
{
    std::cout << "Dog\n";
}

static void* ThreadTest(void* data)
{
    SharedPtr<int> sp1(reinterpret_cast<int*>(data));
    SharedPtr<int> sp2=sp1;
}

int main()
{
    SharedPtr<int> sp_int1(new int(22));
    SharedPtr<int> sp_int2(new int(33));
    std::cout << "\n=== sp_int1=sp_int2; ===" << std::endl;
    sp_int1 = sp_int2;
    std::cout << "\n=== sp_int1= ===\n" << *sp_int1 << std::endl;

    (*sp_int1) = 4;
    std::cout << "\n=== after (*sp_int1) = 4; ===\n" << *sp_int2 << std::endl;

    std::cout << "\n=== count should be 1: ===" << std::endl;
    SharedPtr<Dog> dog_holder(new Dog);

    std::cout << "\n=== count should be 2: ===" << std::endl;
    SharedPtr<Dog> dog_holder2(dog_holder);

    std::cout << "\n=== count should be 3: ===" << std::endl;
    SharedPtr<Animal> animal_holder(dog_holder);

    std::cout << "\n=== SharedPtr<Named> name_holder = dog_holder; ==="
              << std::endl;
    SharedPtr<Named> name_holder = dog_holder;

    std::cout << "\n=== SharedPtr<Dog> dog_holder3(dog_ptr); ==="
              << std::endl;
    SharedPtr<Dog> dog_holder3(new Dog);

    std::cout << "\n=== dog_holder3=dog_holder2; ===" << std::endl;
    dog_holder3 = dog_holder2;

    std::cout << "\n=== name_holder=dog_holder2; ===" << std::endl;
    name_holder = dog_holder2;

    std::cout << "\n=== dog_holder->Speak() ===" << std::endl;
    dog_holder->Speak();
    (*dog_holder).Speak();

    animal_holder->Speak();
    (*animal_holder).Speak();

    // std::cout << "\n=== threads test ===" << std::endl;
    // pthread_t threads[3];
    // SharedPtr<int> thread_arg1(new int(22));

//     pthread_create(&threads[0], NULL, ThreadTest, &thread_arg1);
//     pthread_create(&threads[1], NULL, ThreadTest, &thread_arg1);
//     pthread_create(&threads[2], NULL, ThreadTest, &thread_arg1);

// #ifdef SHOW_DOWNCAST
//     /* base to derived is never implicit: this must not compile */
//     SharedPtr<Dog> back(animal_holder);
// #endif
// #ifdef SHOW_NO_TEMPLATE
//     /* a pointer to a pointer does not upcast either */
//     Dog* dog_ptr = new Dog;
//     Animal** pp = &dog_ptr;
// #endif
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////


// #include <string>
// #include <iostream>

// #include "shared_pointer.hpp"

// using namespace ilrd178;

// struct test_p
// {
// public:
//     test_p() : num1(0), num2(0) {}
//     test_p(int num1, double num2 = 0) : num1(num1), num2(num2){}

//     int num1;
//     double num2;
// private:
// };

// struct test_c : public test_p
// {
// public:
//     test_c() : test_p(), str("") {}
//     test_c(const std::string str) : test_p(), str(str) {}
//     test_c(int num1, double num2 = 0,const std::string str = "") : test_p(num1, num2), str(str) {}
//     std::string str;
// private:
// };

// int main()
// {
//     test_p* test_p1 = new test_p();
//     test_p* test_p2 = new test_p(1, 1);
    

//     SharedPtr<test_p> sptr1(test_p1);
//     SharedPtr<test_p> sptr2(test_p2);

//     std::cout << "sptr1 = " << sptr1->num1 << std::endl;
//     std::cout << "sptr1 = " << (*sptr1).num1 << std::endl;

//     std::cout << "sptr2 = " << sptr2->num1 << std::endl;
//     std::cout << "sptr2 = " << (*sptr2).num1 << std::endl;

//     SharedPtr<test_p> sptr1_copy(sptr1);
    
//     return 0;
// }