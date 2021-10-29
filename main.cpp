#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <ctime>
#include "boost/lexical_cast.hpp"
#include "helper.h"
#include "transaction.h"
#include "account.h"
#include "employee.h"

using namespace std;

void rootFunction();

/* This function displays the options for the account holders to choose from */
void customerActions() {
  cout<<endl<<"Account login:\n";
  Account *account;
  if((account=searchAccount())==NULL) { // searcAccount() promts the account no from and checks if the account number is valid
      customerActions(); // if not available, the program once again prompts the account no
      return;
  }
  int choice;
  int amount;
  bool flag = true; // to break out of while loop
  while(flag) {
    cout<<endl<<endl<<"Options :\n1 - withdraw\n2 - deposit\n3 - check balance\n4 - calculate interest\n5 - Delete account\n6 - log out from account\n7 - exit\n";
    cin.ignore();
    cin>>choice;
    switch(choice) {
      case 1:
        cout<<"Enter the amount for withdrawal : ";
        cin>>amount;
        account->withdraw(amount); // This function does a lot. Refer it in account.h file
        break;
      case 2:
        cout<<"Enter the amount for deposit : ";
        cin>>amount;
        account->deposit(amount); // This function does a lot. Refer it in account.h file
        break;
      case 3:
        account->displayBalance();
        break;
      case 4:
        account->calculateInterest();
        break;
      case 5:
        account->deleteAccount();
        exit(0);
        break;
      case 6:
        customerActions();
        flag=false;
        break;
      case 7:
        flag=false;
        exit(0);
        break;
      default:
        cout<<"Please enter the valid option.";
    }
  }
  return;
}



void createAccount() {
  Account* newAccount = new Account();
  newAccount->setData(); // gets all the account data
  newAccount->addToRecords(); // saves the account object to the Customer records file
}

//customer section home screen
void customerSection() {
  int choice;
  cout<<endl<<"1 - Create a new account\n2 - Perform actions on the existing account\n3 - Back\n4 - exit\n";
  cin>>choice;
  switch(choice) {
    case 1:
      createAccount();
      rootFunction();
      break;
    case 2:
    {
      customerActions();
      break;
    }
    case 3:
      rootFunction();
      break;
    case 4:
      break;
    default:
      cout<<"Invalid option";
      customerSection();
  }
}

//employee section home screen
void employeeSection() {
  Employee emp;
  int choice;
  bool flag = true;
  while(flag) {
  cout<<endl<<endl<<"1 - Display list of all account holders\n2 - Display the last account number\n3 - Get all the transaction details from transaction file\n4 - Get the account information from customer file\n5.exit\n";
  cin>>choice;
    switch(choice) {
      case 1:
        emp.displayAccountHolders(); // displays all account holders names from customer records file
        break;
      case 2:
      {
        emp.displayLastAccountNumber(); // displays the last account number assigned to the account holder 
        break;
      }
      case 3:
        emp.transactionDetails(); // displays all the details from the transaction records file
        break;
      case 4:
        emp.accountInformation(); // displays the details of the specific account holders
        break;
      case 5:
        exit(0);
      default:
        cout<<"Invalid option";
        customerSection();
    }
  }
}



//root function from where the other functions are navigated to
void rootFunction() {
    
  int section;
  cout<<endl<<endl<<"Enter the section : \n1 - Customer\n2 - Employee\n3 - exit\n";
  cin>>section;
  switch(section) {
    case 1:
      customerSection();
      break;
    case 2:
      employeeSection();
      break;
    case 3:
      break;
    default:
      cout<<"Invalid option";
      rootFunction();
  }
}

int main() {
  rootFunction();
  return 0;
}