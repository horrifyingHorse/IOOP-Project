#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>
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
        : model(model), fuelType(fuelType), transmission(transmission),
          category(category), price(price) {}

    string getModel() const { return model; }  // Mark as const
    double getPrice() const { return price; }  // Mark as const

    void displayCarDetails() const {  // Mark as const because it doesn't modify the object
        cout << "Model: " << model << ", Fuel Type: " << fuelType
             << ", Transmission: " << transmission
             << ", Category: " << category << ", Price: $" << price << endl;
    }
};

// List of Cars in the Dealership
vector<Car> carList = {
    Car("Model X", "Electric", "Automatic", "SUV", 75000),
    Car("Mustang", "Petrol", "Manual", "Sports", 55000),
    Car("Civic", "Petrol", "Automatic", "Sedan", 25000)
};

// Employee Class Definition
class Employee {
protected:
    string name;
    int id;
public:
    Employee() {}
    Employee(string empName, int empId) : name(empName), id(empId) {}
    
    string getName() const { return name; }  // Mark as const
    int getId() const { return id; }  // Mark as const

    void logSale(const string& carModel, int numCars, double totalAmount, const string& customerName) const {
        ofstream file("sales.txt", ios::app);  // Open file in append mode
        time_t now = time(0);
        tm* ltm = localtime(&now);
        if (file.is_open()) {
            file << id << " " << carModel << " " << numCars << " "
                 << totalAmount << " " << customerName << " "
                 << 1900 + ltm->tm_year << " "
                 << 1 + ltm->tm_mon << " " << ltm->tm_mday << endl;
            file.flush();  // Ensure data is written to disk
            cout << "Sale logged successfully.\n";
        } else {
            cout << "Error logging sale.\n";
        }
        file.close();
    }
};

// Manager Class Definition
class Manager {
private:
    string managerName = "Manager";
    string managerPassword = "admin123";
    vector<Employee> employeeList;  // List of employees managed by the manager

    // Helper function to load employees from file
    void loadEmployeesFromFile() {
        ifstream file("employees.txt");
        if (file.is_open()) {
            string name;
            int id;
            while (file >> id >> ws) {  // Reading employee ID and name from file
                getline(file, name);
                employeeList.push_back(Employee(name, id));  // Add employee to the list
            }
            file.close();
        } else {
            cout << "Error opening employees file.\n";
        }
    }

    // Helper function to save employees to file
    void saveEmployeesToFile() {
        ofstream file("employees.txt");
        if (file.is_open()) {
            for (const auto& emp : employeeList) {
                file << emp.getId() << " " << emp.getName() << endl;  // Save ID and Name to file
            }
            file.close();
        } else {
            cout << "Error saving employees to file.\n";
        }
    }

public:
    Manager() {
        loadEmployeesFromFile();  // Load existing employees when Manager is created
    }

    bool login() {
        string name, password;
        cout << "Enter Manager Name: ";
        cin >> name;
        cout << "Enter Manager Password: ";
        cin >> password;
        return (name == managerName && password == managerPassword);
    }

    void viewSalesStats() const {  // Mark as const since it doesn't modify the object
        ifstream file("sales.txt");
        string fileContent;
        if (file.is_open()) {
            while (getline(file, fileContent)) {
                cout << "File Content: " << fileContent << endl;

                int empId, numCars, year, month, day;
                string carModel, customerName;
                double totalAmount;
                if (file >> empId >> carModel >> numCars >> totalAmount >> customerName >> year >> month >> day) {
                    cout << "Employee ID: " << empId << ", Customer: " << customerName 
                         << ", Car Model: " << carModel << ", Date: " << day << "/" << month << "/" << year 
                         << ", Cars Sold: " << numCars << ", Total Amount: $" << totalAmount << endl;
                }
            }
            file.close();
        } else {
            cout << "Error opening sales file.\n";
        }
    }

    void addEmployee(const string& empName, int empId) {
        Employee newEmployee(empName, empId);
        employeeList.push_back(newEmployee);
        cout << "Employee " << empName << " added successfully.\n";
        saveEmployeesToFile();  // Save the updated employee list to file
    }

    void removeEmployee(int empId) {
        auto it = find_if(employeeList.begin(), employeeList.end(), [empId](const Employee& emp) {
            return emp.getId() == empId;
        });
        if (it != employeeList.end()) {
            employeeList.erase(it);
            cout << "Employee with ID " << empId << " removed successfully.\n";
            saveEmployeesToFile();  // Save the updated employee list to file
        } else {
            cout << "Employee with ID " << empId << " not found.\n";
        }
    }

    void viewEmployees() const {  // Mark as const since it doesn't modify the object
        if (employeeList.empty()) {
            cout << "No employees available.\n";
        } else {
            for (const auto& emp : employeeList) {
                cout << "Employee Name: " << emp.getName() << ", ID: " << emp.getId() << endl;
            }
        }
    }
};

// Customer Class Definition
class Customer {
public:
    void viewCars() const {  // Mark as const since it doesn't modify the object
        cout << "\nAvailable Cars:\n";
        for (auto& car : carList) {
            car.displayCarDetails();
        }
    }

    void purchaseCar() {
        string customerName, carModel;
        int numCars;
        double totalAmount = 0;
        cout << "\nEnter Your Name: ";
        cin.ignore();
        getline(cin, customerName);
        cout << "Enter Car Model to Purchase: ";
        getline(cin, carModel);
        cout << "Enter Number of Cars: ";
        cin >> numCars;

        bool carFound = false;
        for (auto& car : carList) {
            if (car.getModel() == carModel) {
                totalAmount = car.getPrice() * numCars;
                carFound = true;
                break;
            }
        }

        if (carFound) {
            Employee emp("AutoLog", 0);  // Using a temporary employee object to log the sale
            emp.logSale(carModel, numCars, totalAmount, customerName);
            cout << "Purchase Successful! Total Amount: $" << totalAmount << endl;
        } else {
            cout << "Car model not found.\n";
        }
    }
};

// Employee Login Menu
void employeeLogin() {
    int empId;
    cout << "Enter Employee ID: ";
    cin >> empId;
    Employee emp("AutoLog", empId);  // Initializing Employee object with a sample name and provided ID
    int choice;
    do {
        cout << "\nEmployee Menu:\n";
        cout << "1. Log Sale\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                string carModel, customerName;
                int numCars;
                double totalAmount;
                cout << "Enter Customer Name: ";
                cin.ignore();
                getline(cin, customerName);
                cout << "Enter Car Model: ";
                getline(cin, carModel);
                cout << "Enter Number of Cars Sold: ";
                cin >> numCars;
                cout << "Enter Total Sale Amount: ";
                cin >> totalAmount;
                emp.logSale(carModel, numCars, totalAmount, customerName);
                break;
            }
            case 2:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 2);
}

// Manager Login Menu
void managerMenu() {
    Manager manager;
    if (manager.login()) {
        int choice;
        do {
            cout << "\nManager Menu:\n";
            cout << "1. View Sales Stats\n";
            cout << "2. Add Employee\n";
            cout << "3. Remove Employee\n";
            cout << "4. View Employees\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    manager.viewSalesStats();
                    break;
                case 2: {
                    string empName;
                    int empId;
                    cout << "Enter Employee Name: ";
                    cin.ignore();
                    getline(cin, empName);
                    cout << "Enter Employee ID: ";
                    cin >> empId;
                    manager.addEmployee(empName, empId);
                    break;
                }
                case 3: {
                    int empId;
                    cout << "Enter Employee ID to remove: ";
                    cin >> empId;
                    manager.removeEmployee(empId);
                    break;
                }
                case 4:
                    manager.viewEmployees();
                    break;
                case 5:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        } while (choice != 5);
    } else {
        cout << "Invalid login credentials.\n";
    }
}

// Main function
int main() {
    int choice;
    do {
        cout << "\nCar Dealership Menu:\n";
        cout << "1. Employee Login\n";
        cout << "2. Customer Menu\n";
        cout << "3. Manager Login\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                employeeLogin();
                break;
            case 2: {
                Customer customer;
                int customerChoice;
                do {
                    cout << "\nCustomer Menu:\n";
                    cout << "1. View Cars\n";
                    cout << "2. Purchase Car\n";
                    cout << "3. Exit\n";
                    cout << "Enter your choice: ";
                    cin >> customerChoice;
                    switch (customerChoice) {
                        case 1:
                            customer.viewCars();
                            break;
                        case 2:
                            customer.purchaseCar();
                            break;
                        case 3:
                            cout << "Exiting...\n";
                            break;
                        default:
                            cout << "Invalid choice.\n";
                    }
                } while (customerChoice != 3);
                break;
            }
            case 3:
                managerMenu();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
