#include <string>
#include <iostream>
#include <vector>
#include <cstddef>

class Employee
{
public:
    explicit Employee(const std::string& name);
    virtual ~Employee() = default;

    virtual double calculateSalary() const = 0;
    const std::string& GetName() const;

private:
    std::string m_name;
};

class FullTimeEmployee : public Employee
{
public:
    FullTimeEmployee(const std::string& name, double salary);

    double calculateSalary() const override;

private:
    double m_salary;
};

class HourlyEmployee : public Employee
{
public:
    HourlyEmployee(const std::string& name, double num_hours, double hours_pay);

    double calculateSalary() const override;

private:
    double m_num_hours;
    double m_hour_pay;
};

void printSalaries(const std::vector<Employee*>& employees);

FullTimeEmployee::
FullTimeEmployee(const std::string& name, double salary) : Employee(name), 
                                                           m_salary(salary) {}

double FullTimeEmployee::calculateSalary() const
{
    return m_salary;
}

HourlyEmployee::
HourlyEmployee(const std::string& name, double num_hours, double hours_pay) : Employee(name),
                                                                              m_num_hours(num_hours),
                                                                              m_hour_pay(hours_pay) {}

double HourlyEmployee::calculateSalary() const
{
    return m_hour_pay * m_num_hours;
}

void printSalaries(const std::vector<Employee*>& employees)
{
    for (const Employee* employee : employees)
    {
        std::cout << employee->GetName() << ": " << employee->calculateSalary() << "\n";
    }
}

Employee::Employee(const std::string& name) : m_name(name) {}

const std::string& Employee::GetName() const
{
    return m_name;
}
