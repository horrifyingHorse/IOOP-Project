#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// Car Class Definition
class Car {
 private:
  string model;
  string fuelType;
  string transmission;
  string category;
  double price;

 public:
  Car(string model = "Default", string fuelType = "Petrol",
      string transmission = "Manual", string category = "SEDAN",
      double price = 0.0)
      : model(model),
        fuelType(fuelType),
        transmission(transmission),
        category(category),
        price(price) {}

  void displayCarDetails() {
    cout << "Model: " << model << ", Fuel Type: " << fuelType
         << ", Transmission: " << transmission << ", Category: " << category
         << ", Price: $" << price << endl;
  }
};

// Employee Class Definition
class Employee {
 protected:
  string name;
  int id;

 public:
  Employee() {}
  Employee(string empName, int empId) : name(empName), id(empId) {}

  string getName() { return name; }
  int getId() { return id; }

  // Log sale with car model, number of cars sold, and total amount
  void logSale(const string &carModel, int numCars, double totalAmount) {
    ofstream file("sales.txt", ios::app);
    time_t now = time(0);
    tm *ltm = localtime(&now);
    if (file.is_open()) {
      file << id << " " << carModel << " " << numCars << " " << totalAmount
           << " " << 1900 + ltm->tm_year << " " << 1 + ltm->tm_mon << " "
           << ltm->tm_mday << endl;
      cout << "Sale logged successfully.\n";
    } else {
      cout << "Error logging sale.\n";
    }
    file.close();
  }

  // View sales for the employee
  void viewSales() {
    ifstream file("sales.txt");
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

// Manager Class Definition
class Manager {
 private:
  string managerName = "Manager";
  string managerPassword = "admin123";

 public:
  bool login() {
    string name, password;
    cout << "Enter Manager Name: ";
    cin >> name;
    cout << "Enter Manager Password: ";
    cin >> password;
    return (name == managerName && password == managerPassword);
  }

  void addEmployee() {
    string empName;
    int empId;
    cout << "Enter Employee Name: ";
    cin >> empName;
    cout << "Enter Employee ID: ";
    cin >> empId;

    ofstream file("employees.txt", ios::app);
    if (file.is_open()) {
      file << empId << " " << empName << endl;
      cout << "Employee added successfully.\n";
    } else {
      cout << "Error opening file.\n";
    }
    file.close();
  }

  void removeEmployee() {
    int empId;
    cout << "Enter Employee ID to remove: ";
    cin >> empId;

    ifstream file("employees.txt");
    ofstream tempFile("temp.txt");
    bool found = false;
    string empName;
    int id;

    if (file.is_open() && tempFile.is_open()) {
      while (file >> id >> empName) {
        if (id != empId) {
          tempFile << id << " " << empName << endl;
        } else {
          found = true;
        }
      }
      file.close();
      tempFile.close();
      remove("employees.txt");
      rename("temp.txt", "employees.txt");

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
    ifstream file("sales.txt");
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
};

// Employee Login Menu
void employeeLogin() {
  int empId;
  cout << "Enter Employee ID: ";
  cin >> empId;
  Employee emp("", empId);
  int choice;
  do {
    cout << "\nEmployee Menu:\n";
    cout << "1. Log Sale\n";
    cout << "2. View My Sales\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
      case 1: {
        string carModel;
        int numCars;
        double totalAmount;
        cout << "Enter car model: ";
        cin >> carModel;
        cout << "Enter number of cars sold: ";
        cin >> numCars;
        cout << "Enter total sale amount: ";
        cin >> totalAmount;
        emp.logSale(carModel, numCars, totalAmount);
        break;
      }
      case 2:
        emp.viewSales();
        break;
      case 3:
        cout << "Exiting...\n";
        break;
      default:
        cout << "Invalid choice. Try again.\n";
    }
  } while (choice != 3);
}

// Manager Menu
void managerMenu() {
  Manager manager;
  if (manager.login()) {
    int choice;
    do {
      cout << "\nManager Menu:\n";
      cout << "1. Add Employee\n";
      cout << "2. Remove Employee\n";
      cout << "3. View Sales Stats\n";
      cout << "4. Exit\n";
      cout << "Enter choice: ";
      cin >> choice;

      switch (choice) {
        case 1:
          manager.addEmployee();
          break;
        case 2:
          manager.removeEmployee();
          break;
        case 3:
          manager.viewSalesStats();
          break;
        case 4:
          cout << "Exiting...\n";
          break;
        default:
          cout << "Invalid choice. Try again.\n";
      }
    } while (choice != 4);
  } else {
    cout << "Login failed.\n";
  }
}
