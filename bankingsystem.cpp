#include <iostream>
#include <vector>
using namespace std;

class BankAccount {
protected:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(int accNum, string name, double bal)
        : accountNumber(accNum), accountHolderName(name), balance(bal) {}

    virtual void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: " << amount << " | New Balance: " << balance << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: " << amount << " | Remaining Balance: " << balance << endl;
        } else {
            cout << "Insufficient funds or invalid amount!" << endl;
        }
    }

    double getBalance() const {
        return balance;
    }

    virtual void displayAccountInfo() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Holder Name: " << accountHolderName << endl;
        cout << "Balance: " << balance << endl;
    }

    virtual void calculateInterest() {}  
    virtual ~BankAccount() {}
};


class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(int accNum, string name, double bal, double rate)
        : BankAccount(accNum, name, bal), interestRate(rate) {}

    void calculateInterest() override {
        double interest = balance * (interestRate / 100);
        balance += interest;
        cout << "Interest added: " << interest << " | New Balance: " << balance << endl;
    }

    void displayAccountInfo() const override {
        BankAccount::displayAccountInfo();
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }
};


class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CheckingAccount(int accNum, string name, double bal, double limit)
        : BankAccount(accNum, name, bal), overdraftLimit(limit) {}

    void withdraw(double amount) override {
        if (amount > 0 && (balance + overdraftLimit) >= amount) {
            balance -= amount;
            cout << "Withdrawn: " << amount << " | Remaining Balance: " << balance << endl;
        } else {
            cout << "Overdraft limit exceeded!" << endl;
        }
    }

    void displayAccountInfo() const override {
        BankAccount::displayAccountInfo();
        cout << "Overdraft Limit: " << overdraftLimit << endl;
    }
};


class FixedDepositAccount : public BankAccount {
private:
    int termMonths;
    double interestRate;

public:
    FixedDepositAccount(int accNum, string name, double bal, int term, double rate)
        : BankAccount(accNum, name, bal), termMonths(term), interestRate(rate) {}

    void calculateInterest() override {
        double interest = balance * (interestRate / 100) * (termMonths / 12.0);
        balance += interest;
        cout << "Fixed Deposit Interest Added: " << interest << " | New Balance: " << balance << endl;
    }

    void displayAccountInfo() const override {
        BankAccount::displayAccountInfo();
        cout << "Term: " << termMonths << " months" << endl;
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }
};


void displayMenu() {
    cout << "\n--- Banking System Menu ---\n";
    cout << "1. Create Savings Account\n";
    cout << "2. Create Checking Account\n";
    cout << "3. Create Fixed Deposit Account\n";
    cout << "4. Deposit Money\n";
    cout << "5. Withdraw Money\n";
    cout << "6. Display Account Info\n";
    cout << "7. Calculate Interest\n";
    cout << "8. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    vector<BankAccount*> accounts;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                int accNum;
                string name;
                double balance, interestRate;
                cout << "Enter Account Number ";
                cin >> accNum; 
                cout << "Name:";
                cin>>name;
                cout << "Initial Balance:";
                cin>>balance;
                cout << "Interest Rate:";
                cin>>interestRate;

                accounts.push_back(new SavingsAccount(accNum, name, balance, interestRate));
                cout << "Savings Account Created Successfully!\n";
                break;
            }
            case 2: {
               
                int accNum;
                string name;
                double balance, overdraftLimit;
                cout << "Enter Account Number ";
                cin >> accNum; 
                cout << "Name:";
                cin>>name;
                cout << "Initial Balance:";
                cin>>balance;
                cout << " Overdraft Limit:";
                cin>>overdraftLimit;






                accounts.push_back(new CheckingAccount(accNum, name, balance, overdraftLimit));
                cout << "Checking Account Created Successfully!\n";
                break;
            }
            case 3: {
                int accNum, term;
                string name;
                double balance, interestRate;
                cout << "Enter Account Number ";
                cin >> accNum; 
                cout << "Name:";
                cin>>name;
                cout << "Initial Balance:";
                cin>>balance;
                cout << " Term (months):";
                cin>>term ;
                cout << " Interest Rate:";
                cin>> interestRate;





                
                accounts.push_back(new FixedDepositAccount(accNum, name, balance, term, interestRate));
                cout << "Fixed Deposit Account Created Successfully!\n";
                break;
            }
            case 4: {
                int accNum;
                double amount;
                cout << "Enter Account Number and Deposit Amount: ";
                cin >> accNum >> amount;
                for (auto& acc : accounts) {
                    acc->deposit(amount);
                }
                break;
            }
            case 5: {
                int accNum;
                double amount;
                cout << "Enter Account Number and Withdrawal Amount: ";
                cin >> accNum >> amount;
                for (auto& acc : accounts) {
                    acc->withdraw(amount);
                }
                break;
            }
            case 6: {
                for (auto& acc : accounts) {
                    acc->displayAccountInfo();
                    cout << "---------------------\n";
                }
                break;
            }
            case 7: {
                for (auto& acc : accounts) {
                    acc->calculateInterest();
                }
                break;
            }
            case 8:
                cout << "Exiting Banking System...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 8);


    for (auto& acc : accounts) {
        delete acc;
    }

    return 0;
}
