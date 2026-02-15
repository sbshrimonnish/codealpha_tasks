#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

/* ---------------- Transaction Class ---------------- */
class Transaction {
public:
    int accountNumber;
    string type;
    double amount;

    Transaction(int acc, string t, double a) {
        accountNumber = acc;
        type = t;
        amount = a;
    }

    void save() {
        ofstream file("transactions.txt", ios::app);
        file << accountNumber << " " << type << " " << amount << endl;
        file.close();
    }
};

/* ---------------- Account Class ---------------- */
class Account {
public:
    int accountNumber;
    int customerId;
    double balance;

    Account(int acc, int cust, double bal = 0) {
        accountNumber = acc;
        customerId = cust;
        balance = bal;
    }

    void saveAccount() {
        ofstream file("accounts.txt", ios::app);
        file << accountNumber << " " << customerId
             << " " << balance << endl;
        file.close();
    }

    static bool findAccount(int accNo, Account &acc) {
        ifstream file("accounts.txt");
        while (file >> acc.accountNumber
               >> acc.customerId >> acc.balance) {
            if (acc.accountNumber == accNo) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    static void updateAccount(Account updated) {
        ifstream in("accounts.txt");
        ofstream out("temp.txt");

        Account acc(0,0);
        while (in >> acc.accountNumber
               >> acc.customerId >> acc.balance) {
            if (acc.accountNumber == updated.accountNumber)
                out << updated.accountNumber << " "
                    << updated.customerId << " "
                    << updated.balance << endl;
            else
                out << acc.accountNumber << " "
                    << acc.customerId << " "
                    << acc.balance << endl;
        }
        in.close();
        out.close();

        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
    }
};

/* ---------------- Banking System ---------------- */
class BankSystem {
public:
    void createAccount() {
        int accNo, custId;
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Customer ID: ";
        cin >> custId;

        Account acc(accNo, custId);
        acc.saveAccount();

        cout << "Account created successfully.\n";
    }

    void deposit() {
        int accNo;
        double amt;
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Amount: ";
        cin >> amt;

        Account acc(0,0);
        if (!Account::findAccount(accNo, acc)) {
            cout << "Account not found.\n";
            return;
        }

        acc.balance += amt;
        Account::updateAccount(acc);
        Transaction(accNo, "Deposit", amt).save();

        cout << "Deposit successful.\n";
    }

    void withdraw() {
        int accNo;
        double amt;
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Amount: ";
        cin >> amt;

        Account acc(0,0);
        if (!Account::findAccount(accNo, acc)) {
            cout << "Account not found.\n";
            return;
        }

        if (amt > acc.balance) {
            cout << "Insufficient balance.\n";
            return;
        }

        acc.balance -= amt;
        Account::updateAccount(acc);
        Transaction(accNo, "Withdraw", amt).save();

        cout << "Withdrawal successful.\n";
    }

    void showTransactions() {
        int accNo;
        cout << "Enter Account Number: ";
        cin >> accNo;

        ifstream file("transactions.txt");
        int a;
        string type;
        double amt;

        cout << "\nTransaction History:\n";
        while (file >> a >> type >> amt) {
            if (a == accNo)
                cout << type << " - " << amt << endl;
        }
        file.close();
    }

    void showAccount() {
        int accNo;
        cout << "Enter Account Number: ";
        cin >> accNo;

        Account acc(0,0);
        if (Account::findAccount(accNo, acc)) {
            cout << "\nAccount Number: " << acc.accountNumber;
            cout << "\nCustomer ID: " << acc.customerId;
            cout << "\nBalance: " << acc.balance << endl;
        } else {
            cout << "Account not found.\n";
        }
    }
};

/* ---------------- Main ---------------- */
int main() {
    BankSystem bank;
    int choice;

    do {
        cout << "\n==== Banking Management System ====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. View Account\n";
        cout << "5. View Transactions\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bank.createAccount(); break;
            case 2: bank.deposit(); break;
            case 3: bank.withdraw(); break;
            case 4: bank.showAccount(); break;
            case 5: bank.showTransactions(); break;
            case 6: cout << "Exiting system.\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}

