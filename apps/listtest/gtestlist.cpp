//
// File:   gtestlist.cpp
// Author: Your Glorious Instructor
// Purpose:
// Test our list class using Google Test

#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include "List.hpp"

struct Employee {
    int empId;
    int hoursWorked;
    double rate;
    double pay;
};

// Test fixtures manage the state of the test. 
// Here we use it to create and delete a list of employees for testing
// purposes.   Test fixtures are subclass of the ::testing::Test class, with
// all contents set as protected.   As we are using member 
// variables not allocated on the heap, no need to do any
// special setup or teardown.  Do need to use the TEST_F() macro
// rather TEST()


class ListTest: public ::testing::Test {
protected:
    Employee emp1{001, 36, 15.25, 0.0};
    Employee emp2{002, 36, 15.25, 0.0};
    Employee emp3{003, 30, 12.24, 0.0};
    Employee emp4{004, 30, 18.25, 0.0};

    List<Employee> employeeList1;
    List<Employee> employeeList2;
    
    ListTest() {
        employeeList2.push_back(emp1);
        employeeList2.push_back(emp2);
    }
};

void printEmp(Employee emp) {
    std::cout << emp.empId << ",";
    std::cout << emp.hoursWorked << ",";
    std::cout << emp.rate << ",";
    std::cout << emp.pay << std::endl;
}

// Test: List starts empty
// Precondition: an empty list exists.
// Postcondition: The list remains empty
TEST_F(ListTest, StartsEmpty) {
    EXPECT_TRUE(employeeList1.empty());
}

// Test: Add new List
// Precondition: List is empty.
// Postconditon: List is full and contains 3 records
TEST_F(ListTest, PushBack) {
	EXPECT_TRUE(employeeList1.empty());
    employeeList1.push_back(emp1);
    EXPECT_FALSE(employeeList1.empty());
    std::cout << "After the first push:\n";
    employeeList1.traverse(printEmp);
    employeeList1.push_back(emp2);
    std::cout << "After the second push:\n";
    EXPECT_FALSE(employeeList1.empty());
    employeeList1.traverse(printEmp);
    employeeList1.push_back(emp3);
    EXPECT_FALSE(employeeList1.empty());
    std::cout << "After the third push:\n";
    employeeList1.traverse(printEmp);
    employeeList1.push_back(emp4);
    EXPECT_FALSE(employeeList1.empty());
    std::cout << "After the fourth push:\n";
    employeeList1.traverse(printEmp);
}
// Test: Add new List
// Precondition: List is empty.
// Postconditon: List is full and contains 3 records
TEST_F(ListTest, PushFront) {
    EXPECT_TRUE(employeeList1.empty());
    employeeList1.push_front(emp1);
    EXPECT_FALSE(employeeList1.empty());
    std::cout << "After the first push:\n";
    employeeList1.traverse(printEmp);
    employeeList1.push_front(emp2);
    std::cout << "After the second push:\n";
    EXPECT_FALSE(employeeList1.empty());
    employeeList1.traverse(printEmp);
    employeeList1.push_front(emp3);
    EXPECT_FALSE(employeeList1.empty());
    std::cout << "After the third push:\n";
    employeeList1.traverse(printEmp);
    employeeList1.push_front(emp4);
    EXPECT_FALSE(employeeList1.empty());
    std::cout << "After the fourth push:\n";
    employeeList1.traverse(printEmp);
}

// Test: Test iterator behavior
// Precondition: Have items in a list
// Postcondition: No changes are made to the list, output seen
TEST_F(ListTest, IteratorTestPushOnNotEmpty) {
    EXPECT_FALSE(employeeList2.empty());
    std::cout << "\nTest iterators: const -> ";
    for (auto iter = employeeList2.cbegin();
         iter != employeeList2.cend();
         ++iter) {
        printEmp(*iter);
    }
    
}

TEST_F(ListTest,TestTraverse){
    EXPECT_FALSE(employeeList2.empty());
    std::cout << std::endl;
    std::cout << "And if we traverse:\n";
    employeeList2.traverse(printEmp);
    EXPECT_FALSE(employeeList2.empty());
}

