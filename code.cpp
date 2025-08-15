#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

// Base class for financial things
class FinancialThing {
public:
    virtual void show() const = 0; // Pure virtual function
    virtual ~FinancialThing() = default; // Virtual destructor
};

// For expenses
struct Expense : public FinancialThing {
    string desc; // Description of the expense
    float amt;   // Amount of the expense

    Expense(string description, float amount) : desc(description), amt(amount) {}

    void show() const override {
        cout << "Expense: " << desc << ", Amount: " << amt << endl;
    }
};

// For income
struct Income : public FinancialThing {
    string source; // Where the income is from
    float amt;     // Amount of the income

    Income(string src, float amount) : source(src), amt(amount) {}

    void show() const override {
        cout << "Income: " << source << ", Amount: " << amt << endl;
    }
};

// Main class to manage finances
class FinanceManager {
private:
    float balance; // User's current balance
    vector<unique_ptr<FinancialThing>> transactions; // Store income and expenses

public:
    FinanceManager() : balance(0.0) {} // Constructor initializes balance

    void addIncome(string source, float amount) {
        transactions.push_back(make_unique<Income>(source, amount));
        balance += amount; // Add to balance
        cout << "Added income of " << amount << " from " << source << "\n New balance: " << balance << endl;
    }

    void addExpense(string description, float amount) {
        if (amount > balance) {
            cout << "Not enough balance for this expense!\n" << endl;
            return;
        }
        transactions.push_back(make_unique<Expense>(description, amount));
        balance -= amount; // Subtract from balance
        cout << "Added expense of \n" << amount << " for " << description << ". New balance: \n" << balance << endl;
    }

    void showBalance() const {
        cout << "Current balance:\n " << balance << endl;
    }

    void showTransactions() const {
        cout << "Your transactions:\n" << endl;
        for (const auto& transaction : transactions) {
            transaction->show(); // Call show() for each transaction
        }
    }
};

// User interface for interacting with the finance manager
class UserInterface {
public:
    void run() {
        FinanceManager manager; // Create finance manager
        int choice;
        do {
            cout << "Welcome to the Personal Finance Manager\n";
            cout << "1. Add Income\n";
            cout << "2. Add Expense\n";
            cout << "3. Show Balance\n";
            cout << "4. Show Transactions\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1) {
                string source;
                float amount;
                cout << "Enter income source: ";
                cin >> ws; // Clear input buffer
                getline(cin, source);
                cout << "Enter income amount: ";
                cin >> amount;
                manager.addIncome(source, amount);
            } else if (choice == 2) {
                string description;
                float amount;
                cout << "Enter expense description: ";
                cin >> ws; // Clear input buffer
                getline(cin, description);
                cout << "Enter expense amount: ";
                cin >> amount;
                manager.addExpense(description, amount);
            } else if (choice == 3) {
                manager.showBalance();
            } else if (choice == 4) {
                manager.showTransactions();
            }
        } while (choice != 0); // Loop until exit
    }
};

int main() {
    UserInterface ui; // Create user interface
    ui.run(); // Start the program
    return 0;
}