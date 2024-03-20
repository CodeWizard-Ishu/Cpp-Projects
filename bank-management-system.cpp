#include <iostream>
#include <fstream>
#include<string.h>
using namespace std;
struct bankStatement
{
    char name[30];
    char accNo[11];
    char accPassword[11];
    float currentBalance;
    float creditedAmount;
    float debitedAmount;
}statement;

class Bank
{
    char name[30];
    char accountNo[11];
    char password[11];
    float balance;

public:
    void openAccount();
    void checkBalance();
    void depositMoney();
    void withdrawMoney();
    void transferMoney();
    void showStatement();
};

void Bank::openAccount()
{
    Bank *user = new Bank;
    cout<<"\nPlease provide some information\n";
    cout<<"Enter Your Name:";
    cin.getline(user->name,29);
    cin.sync();
    cout<<"Choose Account No:";
    cin.getline(user->accountNo,10);
    cin.sync();
    cout<<"Create Password:";
    cin.getline(user->password,10);
    cout<<"Deposit Account opening balance:";
    cin>>user->balance;
    ofstream writeRecord;
    writeRecord.open("bankRecord.txt",ios::app|ios::binary);
    if (!writeRecord)
    {
        cout<<"\nFile is not found\n";
        return;
    }
    writeRecord.write((char *)user,sizeof(*user));
    writeRecord.close();
    cout<<"\nYour Account is Opened successfully\n\n";
}

void Bank::checkBalance()
{
    char userAccNo[11],userPassword[11];
    cout<<"Enter Your Account No: ";
    cin.getline(userAccNo,10);
    cin.sync();
    cout<<"Enter Your Password: ";
    cin.getline(userPassword,10);
    ifstream readRecord;
    readRecord.open("bankRecord.txt",ios::in|ios::binary);
    while (!readRecord.eof())
    {
        readRecord.read((char *)this,sizeof(*this));
        if (!strcmp(accountNo,userAccNo)&&!strcmp(password,userPassword))
        {
            cout<<"\nYour Balance is "<<balance<<" Rupees\n\n";
            readRecord.close();
            return;
        }
    }
    cout<<"\nBalance check Proccess is failed due to incorrect infomation Please try again\n\n";
    readRecord.close();
}

void Bank::depositMoney()
{
    struct bankStatement *record;
    record = &statement;
    char userAccNo[11],userPassword[11];
    float depositAmount;
    cout<<"Enter Your Account No: ";
    cin.getline(userAccNo,10);
    cin.sync();
    cout<<"Enter Your Password: ";
    cin.getline(userPassword,10);
    fstream updateRecord,tranStatement;
    updateRecord.open("bankRecord.txt",ios::in|ios::out|ios::binary);
    tranStatement.open("bankStatement.txt",ios::out|ios::app|ios::binary);
    while (!updateRecord.eof())
    {
        updateRecord.read((char *)this,sizeof(*this));
        if (!strcmp(accountNo,userAccNo)&&!strcmp(password,userPassword))
        {
            cout<<"Enter Deposit Amount: ";
            cin>>depositAmount;
            balance = balance+depositAmount;
            strcpy(record->name,name);
            strcpy(record->accNo,accountNo);
            strcpy(record->accPassword,password);
            record->currentBalance = balance;
            record->creditedAmount = depositAmount;
            record->debitedAmount = 0.00;
            int pos=updateRecord.tellg();
            updateRecord.seekg(pos-sizeof(*this));
            updateRecord.write((char *)this,sizeof(*this));
            tranStatement.write((char *)record,sizeof(*record));
            cout<<"\n"<<depositAmount<<" Rupees is deposited successfully\n\n";
            updateRecord.close();
            tranStatement.close();
            return;
        }
    }
    cout<<"\nDeposit Proccess is failed due to incorrect infomation please try again\n\n";
    updateRecord.close();
    tranStatement.close();
}

void Bank::withdrawMoney()
{    
    struct bankStatement *record;
    record = &statement;
    char userAccNo[11],userPassword[11];
    float withdrawAmount;
    cout<<"Enter Your Account No: ";
    cin.getline(userAccNo,10);
    cin.sync();
    cout<<"Enter Your Password: ";
    cin.getline(userPassword,10);
    fstream updateRecord,tranStatement;
    updateRecord.open("bankRecord.txt",ios::in|ios::out|ios::binary);
    tranStatement.open("bankStatement.txt",ios::out|ios::app|ios::binary);
    while (!updateRecord.eof())
    {
        updateRecord.read((char *)this,sizeof(*this));
        if (!strcmp(accountNo,userAccNo)&&!strcmp(password,userPassword))
        {
            cout<<"Enter Withdrawable Amount: ";
            cin>>withdrawAmount;
            if (balance<withdrawAmount)
            {
                cout<<"\nSorry! You don't have enough Money to withdraw\n\n";
                return;
            }
            balance = balance-withdrawAmount;
            strcpy(record->name,name);
            strcpy(record->accNo,accountNo);
            strcpy(record->accPassword,password);
            record->currentBalance = balance;
            record->creditedAmount = 0.00;
            record->debitedAmount = withdrawAmount;
            int pos=updateRecord.tellg();
            updateRecord.seekg(pos-sizeof(*this));
            updateRecord.write((char *)this,sizeof(*this));
            tranStatement.write((char *)record,sizeof(*record));
            cout<<"\n"<<withdrawAmount<<" Rupees is withdrawl successfully\n\n";
            updateRecord.close();
            tranStatement.close();
            return;
        }
    }
    cout<<"\nWithdraw Proccess is failed due to incorrect infomation please try again\n\n";
    tranStatement.close();
    updateRecord.close();
}

void Bank::transferMoney()
{
    struct bankStatement *record;
    record = &statement;
    char userAccNo[11],userPassword[11];
    char transferAccNo[11],accHolderName[30];
    float transferAmount;
    bool isFound=false;
    cout<<"Enter Your Account No: ";
    cin.getline(userAccNo,10);
    cin.sync();
    cout<<"Enter Your Password: ";
    cin.getline(userPassword,10);
    cin.sync();
    fstream updateRecord,tranStatement;
    updateRecord.open("bankRecord.txt",ios::in|ios::out|ios::binary);
    while (!updateRecord.eof())
    {
        updateRecord.read((char *)this,sizeof(*this));
        if (!strcmp(accountNo,userAccNo)&&!strcmp(password,userPassword))
        {
            cout<<"Enter Account Holder Name: ";
            cin.getline(accHolderName,29);
            cin.sync();
            cout<<"Enter Account No: ";
            cin.getline(transferAccNo,10);
            cout<<"Enter Transfer Amount: ";
            cin>>transferAmount;
            if (balance<transferAmount)
            {
                cout<<"\nSorry! You don't have enough Money to Transfer\n\n";
                return;
            }
            balance = balance-transferAmount;
            int pos=updateRecord.tellg();
            updateRecord.seekg(pos-sizeof(*this));
            updateRecord.write((char *)this,sizeof(*this));
            updateRecord.close();            
            isFound=true;
            break;
        }
    }
    if (isFound==false)
    {
        updateRecord.close();        
        cout<<"\nTransfer Proccess is failed due to incorrect infomation please try again\n\n";
        return;
    }
    updateRecord.open("bankRecord.txt",ios::in|ios::out|ios::binary);
    tranStatement.open("bankStatement.txt",ios::out|ios::app|ios::binary);
    while (!updateRecord.eof())
    {
        updateRecord.read((char *)this,sizeof(*this));
        if (!strcmp(accountNo,transferAccNo)&&!strcmp(name,accHolderName))
        {
            balance = balance+transferAmount;
            strcpy(record->name,name);
            strcpy(record->accNo,accountNo);
            strcpy(record->accPassword,password);
            record->currentBalance = balance;
            record->creditedAmount = transferAmount;
            record->debitedAmount = 0.00;
            int pos=updateRecord.tellg();
            updateRecord.seekg(pos-sizeof(*this));
            updateRecord.write((char *)this,sizeof(*this));
            tranStatement.write((char *)record,sizeof(*record));
            cout<<"\n"<<transferAmount<<" Rupees is transfered successfully\n\n";
            updateRecord.close();
            tranStatement.close();
            return;
        }
    }
    updateRecord.close();
    tranStatement.close();

    updateRecord.open("bankRecord.txt",ios::in|ios::out|ios::binary);
    while (!updateRecord.eof())
    {
        updateRecord.read((char *)this,sizeof(*this));
        if (!strcmp(accountNo,userAccNo)&&!strcmp(password,userPassword))
        {
            balance = balance+transferAmount;
            int pos=updateRecord.tellg();
            updateRecord.seekg(pos-sizeof(*this));
            updateRecord.write((char *)this,sizeof(*this));
            updateRecord.close();
            break;
        }
    }
    cout<<"\nTransfer Proccess is failed due to incorrect infomation please try again\n\n";
}

void Bank::showStatement()
{
    struct bankStatement *record;
    record = &statement;
    char accountNo[11],Password[11];
    bool isFound=false;
    int check=0;
    cout<<"Enter Your Account No: ";
    cin.getline(accountNo,10);
    cin.sync();
    cout<<"Enter Your Password: ";
    cin.getline(Password,10);
    ifstream readRecord;
    readRecord.open("bankStatement.txt",ios::in|ios::binary);
    cout<<"\n  Name   \tAccount No \tBalance  \tCredit  \tDebited\n\n";

    readRecord.read((char *)record,sizeof(*record));
    while (!readRecord.eof())
    {
        if (!strcmp(accountNo,record->accNo)&&!strcmp(Password,record->accPassword))
        {
            cout<<" "<<record->name<<"  \t"<<record->accNo<<"    \t"<<record->currentBalance<<"     \t";
            cout<<record->creditedAmount<<"      \t"<<record->debitedAmount<<endl;
            isFound=true;
        }                
        readRecord.read((char *)record,sizeof(*record));
    }
    cout<<endl;
    readRecord.close();
    if (!isFound)
    {
        cout<<"\nBalance check Proccess is failed due to incorrect infomation Please try again\n\n";
    }    
}

int main()
{
    int choose;
    Bank account;
    cout<<"\nWELCOME TO BANK SYSTEM PROJECT\n\n";
    do
    {
        cout<<"Press 1 to Open Account\n";
        cout<<"Press 2 to Check Balance\n";
        cout<<"Press 3 to Deposit Money\n";
        cout<<"Press 4 to Withdraw Money\n";
        cout<<"Press 5 to Transfer Money\n";
        cout<<"Press 6 to Show Statement\n";
        cout<<"Press 7 to Exit\n";
        cout<<"Choose your choice: ";
        cin>>choose;
        cin.sync();
        switch (choose)
        {
        case 1:
            account.openAccount();
            break;
        case 2:
            account.checkBalance();
            break;
        case 3:
            account.depositMoney();
            break;
        case 4:
            account.withdrawMoney();
            break;
        case 5:
            account.transferMoney();
            break;
        case 6:
            account.showStatement();
            break;
        case 7:
            break;
        default:cout<<"Invalid choice try again\n";
            break;
        }
    } while (choose!=7);   
    return 0;
}