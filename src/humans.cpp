#include "../include/Humans.h"

int Employee::count = 0;

Employee::Employee() {}
Employee::Employee(string empName, int empId) : name(empName), id(empId) {}

string Employee::getName() { return name; }
int Employee::getId() { return id; }

void Employee::viewSales() {
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
             << "/" << year << ", Cars Sold: " << numCars << ", Total Amount: $"
             << totalAmount << endl;
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

Manager::Manager() : managerName(""), managerPassword(""), isLoggedIn(false) {}

bool Manager::login(string name, string password) {
  isLoggedIn = (name == managerName && password == managerPassword);
  return isLoggedIn;
}

bool Manager::addEmployee(string empName, string empId) {
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

void Manager::removeEmployee(string empID) {
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

void Manager::viewSalesStats() {
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

vector<pair<string, string>> Manager::getAllEmployees() {
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

int Customer::billNo = 0;

Customer::Customer()
    : name(""),
      address(""),
      phoneNumber(""),
      email(""),
      carModel(""),
      color(""),
      carVariant(""),
      isPreOwned(false),
      prevOwner("x0428") {}

Customer::Customer(string n, string addr, string phone, string email,
                   string model, string color, string brand)
    : name(n),
      address(addr),
      phoneNumber(phone),
      email(email),
      carModel(model),
      color(color),
      carVariant(brand),
      isPreOwned(false),
      prevOwner("x0428") {}

int Customer::generateBillNo() {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(100000, 999999);  // 6-digit number
  return dis(gen);
}

void Customer::initializeBillNo() {
  if (billNo == 0) {
    billNo = generateBillNo();  // Initialize if not set yet
  }
}

void Customer::setPreOwned(string prevOwner) {
  this->isPreOwned = true;
  this->prevOwner = prevOwner;
}

void Customer::updateDetails(const string& n, const string& addr,
                             const string& phone, const string& email,
                             const string& model, const string& color,
                             const string& brand) {
  name = n;
  address = addr;
  phoneNumber = phone;
  this->email = email;
  carModel = model;
  this->color = color;
  carVariant = brand;
}

bool Customer::isValid(const Customer& c) {
  return !c.name.empty() && !c.address.empty() && !c.phoneNumber.empty() &&
         !c.email.empty() && !c.carModel.empty() && !c.color.empty() &&
         !c.carVariant.empty();
}

void Customer::storeReceipt(const Customer& c) {
  initializeBillNo();  // Ensure billNo is initialized
  string filename = "./db/reciept/" + to_string(billNo) + ".txt";

  if (c.isPreOwned) {
    filename = "./db/reciept/preowned/" + to_string(billNo) + ".txt";
  }

  ofstream file(filename);
  if (file.is_open()) {
    if (c.prevOwner != "x0428") file << c.prevOwner << endl;
    file << billNo << endl;
    file << c.name << endl;
    file << c.address << endl;
    file << c.phoneNumber << endl;
    file << c.email << endl;
    file << c.carModel << endl;
    file << c.color << endl;
    file << c.carVariant << endl;
    file.close();
    cout << filename << endl;
  }
}
