#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <fstream>


using namespace std;


class Clint {

protected:
    string name;
    string adress;
    string phone;

public:
    Clint(){}

    Clint(string userName, string useradress, string userNumber) {
        name = userName;
        adress = useradress;
        phone = userNumber;
    }
    string getName() {
        return name;
    }
    string getAdress() {
        return adress;
    }
    string getNumber() {
        return phone;

    }

};



class BankAccount {
protected:
    string accountID;
    long double balance;

public:

    BankAccount() {};

    BankAccount(string id, double balnce) {
    
        accountID = id;
        balance = balnce;

    }

    string getID() {
        return accountID;
    }
    double getBalance() {
        return balance;
    }
};


 class SavingsBankAccount {

 protected:
     string accountID;
     long double balance;
     double minimumBalance = 1000;


 public:
     SavingsBankAccount() {};

     SavingsBankAccount(string id, double balnce) {
         accountID = id;
         balance = balnce;
     }

     string getID() {
         return accountID;
     }
     double getBalance() {
         return balance;
     }
    
 };


class BankingApplication: public Clint, public BankAccount, public SavingsBankAccount {

    
public:
    int choice;
    void addClient();
    void save_data(string name, string adress, string phone, string id, double balance, string bankType);
    string generateID();
    void getAccountInfo();
    void withdrawMoney();
    void depositMoney();
    void changeBalance(string id, long double balance);
    void copyFile();



    BankingApplication() {


        cout << "\nWelcome to FCAI Banking Application" << endl;
        cout << "1. Create a New Account" << endl;
        cout << "2. List Clients and Accounts" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Deposit Money" << endl;
        cout << "\nPlease Enter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            addClient();
        }
        else if (choice == 2)
        {
            getAccountInfo();
        }
        else if (choice == 3)
        {
            withdrawMoney();
        }
        else if (choice == 4)
        {
            depositMoney();
        }
        else
        {
            cout << "Invalid Choice" << endl;
        }
    }



};


void BankingApplication:: addClient() {
    string name, adress, phone;
    int accountType;
    long double balance;

    cout << "Please Enter Client Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Please Enter Client Address: ";
    cin.ignore();
    getline(cin, adress);
    cout << "Please Enter Client Phone: ";
    cin >> phone;

    Clint userInformaiton(name, adress, phone);

    cout << "What Type of Account Do You Like? (1) Basic (2) Saving  Type 1 or 2: ";
    cin >> accountType;
    cout << "Please Enter the Starting Balance: ";
    cin >> balance;

    if (accountType == 1)
    {
        BankAccount accountInfo(generateID(), balance);
        save_data(userInformaiton.getName(), userInformaiton.getAdress(), userInformaiton.getNumber(), accountInfo.getID(), accountInfo.getBalance(), "Basic");

    }
    else if (accountType == 2)
    {
        if (balance < minimumBalance)
        {
            cout << "\nYou Must Have 1000 EGP to Open a Saving Account !!!\n" << endl;
            addClient();
        }
        else
        {
            SavingsBankAccount accountInfoS(generateID(), balance);
            save_data(userInformaiton.getName(), userInformaiton.getAdress(), userInformaiton.getNumber(), accountInfoS.getID(), accountInfoS.getBalance(), "Saving");
        }

    }

}


void BankingApplication:: save_data(string name, string adress, string phone, string id, double balance, string bankType) {

    ofstream dataWrite;
    dataWrite.open("dataBase.txt", ios::app);
    dataWrite << id << endl << name << endl << adress << endl << phone << endl << balance << endl << bankType << endl;

    dataWrite.close();

    cout << "\nAn account was created with ID " << id << " and Starting Balance " << balance << " L.E.\n" << endl;
}


string BankingApplication:: generateID() {
    ifstream dataRead("dataBase.txt");
    string line;
    int rowsNum = 0;
    while (getline(dataRead, line))
    {
        rowsNum++;
    }

    dataRead.close();

    return "USER-" + to_string(rowsNum / 6);
}

void BankingApplication:: getAccountInfo() {
    ifstream dataRead("dataBase.txt");
    string line;
    int rowsNum = 0;
    while (getline(dataRead, line))
    {
        rowsNum++;
        if (rowsNum % 6 == 1)
        {
            cout << "Account ID: " << line << endl;
        }
        else if (rowsNum % 6 == 2)
        {
            cout << "Client Name: " << line << endl;
        }
        else if (rowsNum % 6 == 3)
        {
            cout << "Client Adress: " << line << endl;
        }
        else if (rowsNum % 6 == 4)
        {
            cout << "Client Phone number: " << line << endl;
        }
        else if (rowsNum % 6 == 5)
        {
            cout << "Account Balance: " << line << endl;
        }
        else if (rowsNum % 6 == 0)
        {
            cout << "Account Type: " << line << endl;
            cout << "-----------------------------------" << endl;
        }
    }

    dataRead.close();
}



void BankingApplication:: withdrawMoney() {
    string id;
    long double amount;
    long double balance;
    ifstream dataRead("dataBase.txt");
    string  line;

    cout << "Please Enter Your Account ID: ";
    cin >> id;

    while (getline(dataRead, line)) {

        if (line == id)
        {
            dataRead >> line;
            dataRead >> line;
            dataRead >> line;
            dataRead >> line;
            cout << "Your Current Balance is: " << line << endl;
            balance = stod(line);
            cout << "Please Enter the Amount You Want to Withdraw: ";
            cin >> amount;
            dataRead >> line;
            if (balance < amount)
            {
                cout << "You Don't Have Enough Balance !!!" << endl;
                exit(0);
            }
            else if (balance - amount < minimumBalance && line == "Saving")
            {
                cout << "You Can't Withdraw Money Because Your Balance Will Be Less Than the minimum balance of Saving accounts which is " << minimumBalance << " EGP !!!" << endl;
                exit(0);
            }
            else
            {
                changeBalance(id, balance - amount);
                balance -= amount;
                cout << "\nYour New Balance is: " << balance << endl;
                cout << "Thank You For Using Our Service :)" << endl;
                cout << "-----------------------------------" << endl;
            }
        }
    }
    dataRead.close();
}


void BankingApplication:: depositMoney() {
    string id;
    long double amount;
    long double balance;
    ifstream dataRead("dataBase.txt");
    string  line;

    cout << "Please Enter Your Account ID: ";
    cin >> id;

    while (getline(dataRead, line)) {

        if (line == id)
        {
            dataRead >> line;
            dataRead >> line;
            dataRead >> line;
            dataRead >> line;
            cout << "Your Current Balance is: " << line << endl;
            balance = stod(line);
            cout << "Please Enter the Amount You Want to Deposit: ";
            cin >> amount;
            dataRead >> line;

            if (line == "Saving" && amount < 100)
            {
                cout << "You Can't Deposit Money Because the Deposit of Saving accounts Must Be More Than 100 EGP !!!" << endl;
                exit(0);
            }

            changeBalance(id, balance + amount);
            balance += amount;
            cout << "\nYour New Balance is: " << balance << endl;
            cout << "Thank You For Using Our Service :)" << endl;
            cout << "-----------------------------------" << endl;
        }
    }
    dataRead.close();
}


void BankingApplication:: changeBalance(string id, long double balance) {
    ifstream dataRead("dataBase.txt");
    ofstream dataWrite("temp.txt");
    string line;
    while (getline(dataRead, line))
    {
        if (line == id)
        {
            for (int i = 0; i < 4; i++)
            {
                dataWrite << line << endl;
                dataRead >> line;
            }
            line = to_string(balance);
            dataWrite << line;
        }
        else
        {
            dataWrite << line << endl;
        }
    }
    dataRead.close();
    dataWrite.close();
    remove("dataBase.txt");
    rename("temp.txt", "dataBase.txt");
    copyFile();
}


void BankingApplication:: copyFile() {
    ifstream dataRead("temp.txt");
    ofstream dataWrite("dataBase.txt");
    string line;
    while (getline(dataRead, line))
    {
        dataWrite << line << endl;
    }
    dataRead.close();
    dataWrite.close();
}





int main()
{
    BankingApplication start;
    
    return 0;
}

