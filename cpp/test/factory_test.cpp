

// #include <iostream>
// #include <string>

// #include "factory.hpp"

// using namespace ilrd_178;
// class IqLevel
// {
// public:
//     IqLevel() : iq_level(75) {}
//     IqLevel(int iq_level) : iq_level(iq_level) {}
//     void print_iq() {std::cout << "my iq is :" << iq_level << std::endl;}

// private:
//     int iq_level;
// };   


// class Stupid : public IqLevel
// {
// public:
//     Stupid() : IqLevel(50), str("I am stupid") { std::cout << str <<std::endl; }
//     Stupid(std::string str) : IqLevel(30), str(str) { std::cout << str <<std::endl; }
//     void create(int, std::string) {};
// private:
//     std::string str;
// };

// class Smart : public IqLevel
// {
// public:
//     Smart() :IqLevel(120), str("I am smart") { std::cout << str <<std::endl; }
//     Smart(int iq_level ,std::string str) : IqLevel(iq_level), str(str) { std::cout << str <<std::endl; }
// private:
//     std::string str;
// };

// class Avarage : public IqLevel
// {
// public:
//     Avarage() :IqLevel(120), str("I am just ok") { std::cout << str <<std::endl; }
//     Avarage(int iq_level ,std::string str) : IqLevel(iq_level), str(str) { std::cout << str <<std::endl; }
// private:
//     std::string str;
// };

// static std::shared_ptr<IqLevel> MakeStupid(std::string key, int iq, std::string str)
// {
//     (void)key;
//     (void)iq;
//     return std::make_shared<Stupid>(str);
// }

// static std::shared_ptr<IqLevel> MakeSmart(std::string key, int iq, std::string str)
// {
//     (void)key;
//     return std::make_shared<Smart>(iq, str);
// }

// int main()
// {
//     Factory<IqLevel, std::string, int, std::string> factory;

//     std::function<std::shared_ptr<IqLevel>(std::string, int, std::string)> stupid_creator = MakeStupid;
//     factory.Add("stupid", MakeStupid);
//     factory.Add("smart", MakeSmart);
    
//     std::shared_ptr<IqLevel> stupid = factory.Create("stupid", 0, "I am really stupid");
//     stupid->print_iq();

//     std::shared_ptr<IqLevel> smart = factory.Create("smart", 140, "I am really samrt");
//     smart->print_iq();
//     return 0;
// }

#include <iostream>
#include <functional>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <string>
#include <cassert>

#include <factory.hpp>

// ==========================================
// Test Hierarchy & Creators
// ==========================================

using namespace ilrd_178;

class BaseClass 
{
public:
    virtual ~BaseClass() = default;
    virtual std::string GetName() const = 0;
};

class DerivedA : public BaseClass 
{
public:
    DerivedA(int val, const std::string& name) : m_val(val), m_name(name) {}
    std::string GetName() const override { return "DerivedA: " + m_name; }
    int GetVal() const { return m_val; }

private:
    int m_val;
    std::string m_name;
};

class DerivedB : public BaseClass 
{
public:
    DerivedB(int val, const std::string& name) : m_val(val), m_name(name) {}
    std::string GetName() const override { return "DerivedB: " + m_name; }

private:
    int m_val;
    std::string m_name;
};

// Creator functions matching std::function signature
static std::shared_ptr<BaseClass> CreateDerivedA(int val, std::string name) 
{
    return std::make_shared<DerivedA>(val, name);
}

static std::shared_ptr<BaseClass> CreateDerivedB(int val, std::string name) 
{
    return std::make_shared<DerivedB>(val, name);
}

// ==========================================
// Test Cases
// ==========================================

void TestFactoryCreation() 
{
    Factory<BaseClass, std::string, int, std::string> factory;

    factory.Add("type_a", CreateDerivedA);
    factory.Add("type_b", CreateDerivedB);

    // Test successful instantiation
    auto objA = factory.Create("type_a", 42, "Alpha");
    assert(objA != nullptr);
    assert(objA->GetName() == "DerivedA: Alpha");

    auto objB = factory.Create("type_b", 100, "Beta");
    assert(objB != nullptr);
    assert(objB->GetName() == "DerivedB: Beta");

    std::cout << "[PASS] TestFactoryCreation\n";
}

void TestDowncasting() 
{
    Factory<BaseClass, std::string, int, std::string> factory;
    factory.Add("type_a", CreateDerivedA);

    auto baseObj = factory.Create("type_a", 99, "CastTest");
    
    // Explicit dynamic downcast
    auto derivedObj = std::dynamic_pointer_cast<DerivedA>(baseObj);
    assert(derivedObj != nullptr);
    assert(derivedObj->GetVal() == 99);

    std::cout << "[PASS] TestDowncasting\n";
}

void TestInvalidKeyHandling() 
{
    Factory<BaseClass, std::string, int, std::string> factory;
    factory.Add("type_a", CreateDerivedA);

    // Should catch out_of_range internally and return nullptr
    auto obj = factory.Create("non_existent_key", 0, "Test");
    assert(obj == nullptr);

    std::cout << "[PASS] TestInvalidKeyHandling\n";
}

void TestLambdaCreator() 
{
    Factory<BaseClass, std::string, int, std::string> factory;

    // Register creator using C++11 Lambda
    factory.Add("lambda_type", [](int val, std::string name) -> std::shared_ptr<BaseClass> {
        return std::make_shared<DerivedA>(val * 2, "Lambda_" + name);
    });

    auto obj = factory.Create("lambda_type", 10, "Custom");
    assert(obj != nullptr);
    assert(obj->GetName() == "DerivedA: Lambda_Custom");

    std::cout << "[PASS] TestLambdaCreator\n";
}

// ==========================================
// Main Runner
// ==========================================

int main() 
{
    std::cout << "--- Running Factory Tests ---\n";

    TestFactoryCreation();
    TestDowncasting();
    TestLambdaCreator();
    
    std::cout << "--- All Tests Passed Successfully! ---\n";
    
    TestInvalidKeyHandling();
    return 0;
}