#ifndef HUMANS
#define HUMANS

#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Employee {
 protected:
  string name;
  int id;

  static int count;

 public:
  Employee();
  Employee(string empName, int empId);

  string getName();
  int getId();
  void viewSales();
};

class Manager {
 private:
  string managerName;      // "bt23cse021";
  string managerPassword;  // "Arpi1703";

  bool isLoggedIn;

 public:
  Manager();

  bool login(string name, string password);
  bool addEmployee(string empName, string empId);
  void removeEmployee(string empID);
  vector<pair<string, string>> getAllEmployees();

  static void viewSalesStats(Manager& m);
};

class Customer {
 protected:
  string name;
  string address;
  string phoneNumber;
  string email;
  string carModel;
  string color;
  string carVariant;
  double price;

  bool isPreOwned;
  string prevOwner;

  string date;
  int billNum;
  static int billNo;

 public:
  friend void managerSalesView(Manager &m);
  friend void managerSalesViewExpand(Customer& c);

  Customer();
  Customer(string n, string addr, string phone, string email, string model,
           string color, string brand);

  static int generateBillNo();
  static void initializeBillNo();
  void setPreOwned(string prevOwner);
  void updateDetails(const string& n, const string& addr, const string& phone,
                     const string& email, const string& model,
                     const string& color, const string& brand, const double& price);
  static bool isValid(const Customer& c);
  static void storeReceipt(const Customer& c);
};

#endif  // !HUMANS
