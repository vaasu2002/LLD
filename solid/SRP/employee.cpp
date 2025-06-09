#include<bits/stdc++.h>
using namespace std;

enum class Position { JUNIOR, SENIOR, MANAGER };

map<Position, int> baseMap = {
    {Position::JUNIOR, 50000},
    {Position::SENIOR, 80000},
    {Position::MANAGER, 120000}
};

map<Position, int> esopsMap = {
    {Position::JUNIOR, 1000},
    {Position::SENIOR, 5000},
    {Position::MANAGER, 10000}
};

class Employee {
public:
    int id;
    string name;
    string address;
    Position position;

    Employee(int empId, string empName, string empAddress, Position empPosition)
        : id(empId), name(empName), address(empAddress), position(empPosition) {}
};

class SalaryService {
    int base;
    int esops;

public:
    SalaryService(const Employee& employee) {
        base = baseMap[employee.position];
        esops = esopsMap[employee.position];
    }

    int computeBonus(){
        // Dummy logic
        return 0.1 * base;
    }

    int computeTaxBenefits(){
        // Dummy logic
        return 0.05 * (base + esops);
    }

    int computeSalary() 
        int bonus = computeBonus();
        return base + esops + bonus;
    }
};

class EmployeeService {
    Employee employee;
    SalaryService salaryService;

public:
    EmployeeService(Employee emp)
        : employee(emp), salaryService(emp) {}

    int getSalary(){
        return salaryService.computeSalary();
    }

    void updateEmployeeData() {
        cout << "Updating employee data....." << endl;
    }

    void fetchEmployeeData() {
        cout << "Fetching data....." << endl;
    }
};
