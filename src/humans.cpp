#include "../include/Humans.h"

#include <regex>
#include <string>
#include <vector>

#include "../include/utils.h"
int Employee::count = 0;
int Customer::billNo = 0;

Employee::Employee() {}
Employee::Employee(string empName, int empId) : name(empName), id(empId) {}

string Employee::getName() { return name; }

int Employee::getId() { return id; }

Manager::Manager() : managerName("bt23cse021"), managerPassword("1703"), isLoggedIn(false) {}

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

  } else {
    cout << "Error opening file.\n";
  }
}

// void Manager::viewSalesStats() {
//   auto screen = ScreenInteractive::Fullscreen();
//
//   Component main_renderer = Renderer([&] {
//     return vbox({
//
//            }) |
//            flex;
//   });
// }

void Manager::viewSalesStats(Manager& m) {
  if (!m.isLoggedIn) return;
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
                             const string& brand, const double& price) {
  name = n;
  address = addr;
  phoneNumber = phone;
  this->email = email;
  carModel = model;
  this->color = color;
  carVariant = brand;
  this->price = price;
}

bool Customer::isValid(const Customer& c) {
  // Phone number should be exactly 10 digits
  if (c.phoneNumber.length() != 10 ||
      !all_of(c.phoneNumber.begin(), c.phoneNumber.end(), ::isdigit)) {
    // cout << "Invalid phone number. It must be exactly 10 digits.\n";
    return false;
  }

  // Email validation using regex
  const regex emailPattern(R"((\w+)(\.|\w)*@(\w+)(\.\w+)+)");
  if (!regex_match(c.email, emailPattern)) {
    // cout << "Invalid email address format.\n";
    return false;
  }

  // Check if any required field is empty
  bool isValid = !c.name.empty() && !c.address.empty() &&
                 !c.phoneNumber.empty() && !c.email.empty() &&
                 !c.carModel.empty() && !c.color.empty() &&
                 !c.carVariant.empty() && (c.price > 0);

  return isValid;
}

void Customer::storeReceipt(const Customer& c) {
  initializeBillNo();
  string filename = "./db/reciept/" + to_string(billNo) + ".txt";

  if (c.isPreOwned) {
    filename = "./db/reciept/preowned/" + to_string(billNo) + ".txt";
  }

  ofstream file(filename);
  if (file.is_open()) {
    if (c.prevOwner != "x0428") file << c.prevOwner << endl;
    file << billNo << endl;
    file << utils::currentDate() << endl;
    file << c.name << endl;
    file << c.address << endl;
    file << c.phoneNumber << endl;
    file << c.email << endl;
    file << c.carModel << endl;
    file << c.color << endl;
    file << c.carVariant << endl;
    file << c.price << endl;
    file.close();
    // cout << filename << endl;
  }
}
