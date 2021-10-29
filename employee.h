using namespace std;

//Stores the details of the employees
class Employee {
  public:
    void displayAccountHolders();
    void displayLastAccountNumber();
    void transactionDetails();
    void accountInformation();
};

//displays the list of all account holders
void Employee::displayAccountHolders() {
  cout<<"The list of account holder : \n";
  ifstream fin;
  Account temp;
  fin.open("Records/Customer records",ios::in|ios::binary);
  if(!fin)
    cout<<"File not found";
  else
  {
    fin.read((char*)&temp,sizeof(temp));
    while(!fin.eof())
    {
      cout<<endl<<temp.getName();
      fin.read((char*)&temp,sizeof(temp));
    }
  }
  fin.close();
}

//displays the last assigned account number
void Employee::displayLastAccountNumber() {
  cout<<"The last account number : ";
  ifstream fin;
  Account temp;
  long int accountNo;
  fin.open("Records/Customer records",ios::in|ios::binary);
  if(!fin)
    cout<<"File not found";
  else
  {
    fin.read((char*)&temp,sizeof(temp));
    while(!fin.eof())
    {
      accountNo = temp.getAccountNo();
      fin.read((char*)&temp,sizeof(temp));
    }
    cout<<accountNo;
  }
  fin.close();
}

//displays all the transaction details from the transaction records file
void Employee::transactionDetails() {
  cout<<endl<<"The transaction details : \n";
  int recordNumber;
  cout.setf(ios::left,ios::adjustfield);
  cout<<setw(20)<<"record number"<<setw(20)<<"account number"<<setw(20)<<"oldBalance"<<setw(20)<<"newBalance"<<setw(20)<<"withdrawAmount"<<setw(20)<<"depositAmount"<<setw(20)<<"date"<<endl;
  ifstream fin;
  Transaction temp;
  fin.open("Records/Transaction records",ios::in|ios::binary);
  if(!fin)
    cout<<"File not found";
  else
  {
    fin.read((char*)&temp,sizeof(temp));
    while(!fin.eof())
    {
      temp.display();
      fin.read((char*)&temp,sizeof(temp));
    }
  }
  fin.close();
}

//displays the account holder details from their account no
void Employee::accountInformation() {
  long int accountNo;
  cout<<endl<<"Enter the account number : ";
  cin>>accountNo;
  cout.setf(ios::left,ios::adjustfield);
  cout<<setw(20)<<"name"<<setw(20)<<"accountNo"<<setw(20)<<"accountType"<<setw(20)<<"Balance"<<setw(20)<<"create date"<<setw(20)<<"last withdraw date"<<setw(20)<<"Address"<<endl;
  ifstream fin;
  Account temp;
  fin.open("Records/Customer records",ios::in|ios::binary);
  if(!fin)
    cout<<"File not found";
  else
  {
    fin.read((char*)&temp,sizeof(temp));
    while(!fin.eof())
    {
      if(temp.accountNo == accountNo)
        temp.display();
      fin.read((char*)&temp,sizeof(temp));
    }
  }
  fin.close();
}








