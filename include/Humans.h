#ifndef HUMANS
#define HUMANS

#include <fstream>
#include <ios>
#include <iostream>
#include <vector>

using namespace std;

class Employee {
 protected:
  string name;
  int id;

  static inline int count = 0;

 public:
  Employee() {}
  Employee(string empName, int empId) : name(empName), id(empId) {}

  string getName() { return name; }
  int getId() { return id; }

  // View sales for the employee
  void viewSales() {
    ifstream file("./db/sales.txt");
    int empId, numCars, year, month, day;
    string carModel;
    double totalAmount;
    bool hasSales = false;

    if (file.is_open()) {
      cout << "Sales for Employee ID: " << id << "\n";
      while (file >> empId >> carModel >> numCars >> totalAmount >> year >>
             month >> day) {
        if (empId == id) {
          cout << "Car Model: " << carModel << ", Date: " << day << "/" << month
               << "/" << year << ", Cars Sold: " << numCars
               << ", Total Amount: $" << totalAmount << endl;
          hasSales = true;
        }
      }
      if (!hasSales) {
        cout << "No sales records found.\n";
      }
      file.close();
    } else {
      cout << "Error opening sales file.\n";
    }
  }
};

class Manager {
 private:
  string managerName;      // "bt23cse021";
  string managerPassword;  // "Arpi1703";

  bool isLoggedIn;

 public:
  Manager() : managerName(""), managerPassword(""), isLoggedIn(false) {}

  bool login(string name, string password) {
    isLoggedIn = (name == managerName && password == managerPassword);
    return isLoggedIn;
  }

  bool addEmployee(string empName, string empId) {
    if (!isLoggedIn) return false;

    bool success = false;

    ofstream file("./db/employees.txt", ios::app);
    if (file.is_open()) {
      file << empId << " " << empName << endl;
      success = true;
    }
    file.close();

    return success;
  }

  void removeEmployee(string empID) {
    if (!isLoggedIn) return;

    ifstream file("./db/employees.txt");
    ofstream tempFile("./db/temp.txt");
    bool found = false;
    string empName, id;

    if (file.is_open() && tempFile.is_open()) {
      while (file >> id >> empName) {
        if (id != empID) {
          tempFile << id << " " << empName << endl;
        } else {
          found = true;
        }
      }
      file.close();
      tempFile.close();
      remove("./db/employees.txt");
      rename("./db/temp.txt", "./db/employees.txt");

      if (found) {
        cout << "Employee removed successfully.\n";
      } else {
        cout << "Employee ID not found.\n";
      }
    } else {
      cout << "Error opening file.\n";
    }
  }

  // View sales stats including number of cars sold
  void viewSalesStats() {
    if (!isLoggedIn) return;

    ifstream file("./db/sales.txt");
    int empId, numCars, year, month, day;
    string carModel;
    double totalAmount;
    int totalCars = 0;
    double totalSales = 0;
    bool hasRecords = false;

    if (file.is_open()) {
      while (file >> empId >> carModel >> numCars >> totalAmount >> year >>
             month >> day) {
        totalCars += numCars;
        totalSales += totalAmount;
        hasRecords = true;
      }
      file.close();
      if (hasRecords) {
        cout << "\nTotal Cars Sold: " << totalCars << endl;
        cout << "Total Sales Amount: $" << totalSales << endl;
      } else {
        cout << "No sales records found.\n";
      }
    } else {
      cout << "Error opening sales file.\n";
    }
  }

  vector<pair<string, string>> getAllEmployees() {
    vector<pair<string, string>> employees = {};

    ifstream file("./db/employees.txt");
    string empId, empName;

    if (file.is_open()) {
      while (file >> empId >> empName) {
        employees.push_back(make_pair(empId, empName));
      }
      file.close();
    } else {
      cout << "Error opening employees file.\n";
    }

    return employees;
  }
};

#endif  // !HUMANS
