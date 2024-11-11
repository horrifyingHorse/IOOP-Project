#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
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

    string getModel() { return model; }
    double getPrice() { return price; }

    void displayCarDetails() {
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
    string getName() { return name; }
    int getId() { return id; }

    void logSale(const string& carModel, int numCars, double totalAmount, const string& customerName) {
        ofstream file("sales.txt", ios::app);  // Open file in append mode
        time_t now = time(0);
        tm* ltm = localtime(&now);
        if (file.is_open()) {
            // Debugging: Print the sale data before writing to the file
            cout << "Logging Sale: "
                 << "Employee ID: " << id << ", Car: " << carModel << ", Cars: " << numCars
                 << ", Amount: $" << totalAmount << ", Customer: " << customerName << endl;

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
public:
    bool login() {
        string name, password;
        cout << "Enter Manager Name: ";
        cin >> name;
        cout << "Enter Manager Password: ";
        cin >> password;
        return (name == managerName && password == managerPassword);
    }

    void viewSalesStats() {
        ifstream file("sales.txt");
        string fileContent;
        if (file.is_open()) {
            while (getline(file, fileContent)) {
                cout << "File Content: " << fileContent << endl;  // Debugging output to check the file content

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
};

// Customer Class Definition
class Customer {
public:
    void viewCars() {
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
            Employee emp("AutoLog", 0);
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
    Employee emp("", empId);
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

// Manager Menu
void managerMenu() {
    Manager manager;
    if (manager.login()) {
        int choice;
        do {
            cout << "\nManager Menu:\n";
            cout << "1. View Sales Stats\n";
            cout << "2. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    manager.viewSalesStats();
                    break;
                case 2:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 2);
    } else {
        cout << "Login failed.\n";
    }
}

// Main Function
int main() {
    int mainChoice;
    do {
        cout << "\nCar Dealership System:\n";
        cout << "1. Customer Portal\n";
        cout << "2. Employee Login\n";
        cout << "3. Manager Login\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;
        switch (mainChoice) {
            case 1: {
                Customer customer;
                customer.viewCars();
                customer.purchaseCar();
                break;
            }
            case 2:
                employeeLogin();
                break;
            case 3:
                managerMenu();
                break;
            case 4:
                cout << "Exiting the system...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (mainChoice != 4);
    return 0;
}
