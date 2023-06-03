/*
        💥Practical No: 11 💥
 Company maintains employee information as employee ID, name, designation and salary. 
 Allow user to add, delete information of employee. Display information of particular 
 employee. If employee does not exist an appropriate message is displayed. 
 If it is, then the system displays the employee details. Use index sequential file to maintain the data.

*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_RECORDS = 100;

// Structure to hold employee information
struct Employee {
    int employeeID;
    string name;
    string designation;
    double salary;
};

// Function to add a new employee record
void addEmployee() {
    fstream file("employee.dat", ios::in | ios::out | ios::binary);

    Employee employee;
    cout << "Enter Employee ID: ";
    cin >> employee.employeeID;

    // Check if the record already exists
    Employee temp;
    bool recordExists = false;
    while (file.read(reinterpret_cast<char*>(&temp), sizeof(Employee))) {
        if (temp.employeeID == employee.employeeID) {
            recordExists = true;
            break;
        }
    }

    if (recordExists) {
        cout << "Employee record with the same ID already exists!" << endl;
        file.close();
        return;
    }

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, employee.name);

    cout << "Enter Designation: ";
    getline(cin, employee.designation);

    cout << "Enter Salary: ";
    cin >> employee.salary;

    // Append the record at the end of the file
    file.write(reinterpret_cast<char*>(&employee), sizeof(Employee));

    file.close();

    cout << "Employee record added successfully!" << endl;
}

// Function to delete an employee record
void deleteEmployee() {
    int employeeID;
    cout << "Enter Employee ID to delete: ";
    cin >> employeeID;

    fstream file("employee.dat", ios::in | ios::out | ios::binary);

    Employee employee;
    bool recordFound = false;

    while (file.read(reinterpret_cast<char*>(&employee), sizeof(Employee))) {
        if (employee.employeeID == employeeID) {
            recordFound = true;
            break;
        }
    }

    if (recordFound) {
        // Mark the record as deleted by setting the employee ID to -1
        employee.employeeID = -1;
        file.seekp(-static_cast<int>(sizeof(Employee)), ios::cur);
        file.write(reinterpret_cast<char*>(&employee), sizeof(Employee));
        cout << "Employee record deleted successfully!" << endl;
    } else {
        cout << "Employee record not found!" << endl;
    }

    file.close();
}

// Function to display information of a particular employee
void displayEmployee() {
    int employeeID;
    cout << "Enter Employee ID to display: ";
    cin >> employeeID;

    ifstream file("employee.dat", ios::binary);

    Employee employee;
    bool recordFound = false;

    while (file.read(reinterpret_cast<char*>(&employee), sizeof(Employee))) {
        if (employee.employeeID == employeeID) {
            recordFound = true;
            cout << "Employee Details:" << endl;
            cout << "Employee ID: " << employee.employeeID << endl;
            cout << "Name: " << employee.name << endl;
            cout << "Designation: " << employee.designation << endl;
            cout << "Salary: $" << fixed << setprecision(2) << employee.salary << endl;
            break;
        }
    }

    file.close();

    if (!recordFound) {
        cout << "Employee record not found!" << endl;
    }
}

int main() {
    int choice;

    do {
        cout << "---------- Employee Information Management System ----------" << endl;
        cout << "1. Add Employee" << endl;
        cout << "2. Delete Employee" << endl;
        cout << "3. Display Employee Information" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                deleteEmployee();
                break;
            case 3:
                displayEmployee();
                break;
            case 4:
                cout << "Exiting the program..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }

        cout << endl;
    } while (choice != 4);

    return 0;
}
