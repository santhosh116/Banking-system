
using namespace std;

long int initialAccountno = 6634000000; // starting account number
float rateOfInterest = 0.5; // rate of interest of the bank divided by 100 ( 5% )

class Account {

  char name[20]; // account holder name
  long int accountNo;
  char accountType[11];
  int balance;
  char date[11]; // account creation date
  char LanstWithdrawDate[11]; // date of last withdrawl of amount
  char address[50];
  
  public:
    void assingInitBalance();
    void setData();
    void deposit(int amount);
    void withdraw(int amount);
    void displayBalance();
    void allotAccountNo();
    void addToRecords();
    void setCurrentDate();
    string getName();
    long int getAccountNo();
    friend Account* searchAccount();
    void modifyRecord();
    void calculateInterest();
    void display();
    void deleteAccount();
    friend class Employee;
};

void Account::assingInitBalance() {
  cout<<"Enter the initial balance : ";
  cin>>balance;
}

void Account::setData() {
  cout<<"Enter your name : ";
  cin.ignore();
  cin.getline(name, 20);
  cout<<"Enter the account type : ";
  cin.getline(accountType, 10);
  cout<<"Enter your address : ";
  cin.getline(address, 50);
  allotAccountNo();
  assingInitBalance();
  setCurrentDate();
  cout<<endl<<"Your account no is "<<accountNo<<". Please note it down.";
}

void Account::deposit(int amount) {
  int oldBalance;
  char curDate[11]; // used to include in the transaction details
  strcpy(curDate, findCurrentDate().c_str()); // get the current date
  Transaction* newTransaction = new Transaction();
  oldBalance = balance;
  balance+=amount;
  newTransaction->createRecord(oldBalance, balance, amount, 0, curDate, accountNo); // create a new transaction record
  newTransaction->assignRecordNumber();
  newTransaction->addToRecords(); // store in the transaction records file
  modifyRecord(); 
}

void Account::withdraw(int amount) {
  if(balance < amount) {
    cout<<"Not enough balance.";
    return;
  }
  int oldBalance;
  char curDate[11];
  strcpy(curDate, findCurrentDate().c_str());
  Transaction* newTransaction = new Transaction();
  oldBalance = balance;
  balance -= amount;
  strcpy(LanstWithdrawDate, curDate);
  newTransaction->createRecord(oldBalance, balance, 0, amount, curDate, accountNo);
  newTransaction->assignRecordNumber();
  newTransaction->addToRecords(); // add the transaction to the transaction records file
  modifyRecord(); // change the balance of this account in the account records file
}

void Account::displayBalance() {
  cout<<endl<<"Hi "<<name<<", you have the balance amount of "<<balance<<" rupees";
}

//allot unique account number for the new account
void Account::allotAccountNo()
{
    ifstream fin;
    Account temp;
    long int accno=initialAccountno;
    fin.open("Records/Customer records",ios::in|ios::binary);
    if(!fin)
            this->accountNo = accno+1;
    else
    {
        fin.read((char*)&temp,sizeof(temp));
        while(!fin.eof())
        {
         accno=temp.accountNo;  // used to find the last account number
         fin.read((char*)&temp,sizeof(temp));
        }
        accno++; // last account number + 1 for the new account
        this->accountNo = accno;
    }
    fin.close();
}

//add the object to the customer records file
void Account::addToRecords() {
    ofstream fout;
    fout.open("Records/Customer records",ios::out|ios::app|ios::binary);
     if(!fout)
              cout<<"File can not open";
     else
              fout.write((char*)this,sizeof(*this));
     fout.close();
}

void Account::setCurrentDate() {
    strcpy(date,findCurrentDate().c_str());
    strcpy(LanstWithdrawDate, date);
}

string Account::getName(){
  string temp(name); // returning char* creates the array decay problem, so string is returned
  return temp; 
}

long int Account::getAccountNo() {
  return accountNo;
}

// search through the customer records file for the account with the specific name and account number
Account* searchAccount()
{
  Account *temp;
  bool flag = true;
  ifstream fin;
  char name[20];
  long int accountNo;
  fin.open("Records/Customer records",ios::in|ios::binary);
  cout<<endl<<"Enter your name : ";
  cin.ignore();
  cin.getline(name, 20);
  cout<<endl<<"Enter your account number : ";
  cin>>accountNo;
  if(!fin)
    cout<<"File not found";
  else
  {
    fin.read((char*)temp,sizeof(*temp));
    while(!fin.eof())
    {

    if((!strcmp(temp->name,name))&&(temp->accountNo == accountNo)) // check if the account is present
    {
      break;
    }
    fin.read((char*)temp,sizeof(*temp));
    }
    if(fin.eof()) {
    cout<<"\nNo account found. Enter valid account\n";
    flag = false;
    }
  }
  fin.close();
  if(flag) return temp;
  else return NULL;
}

//update the changes in the account to the customer records file
void Account:: modifyRecord()
{
  int r=0;
  fstream file;
  Account temp;
  file.open("Records/Customer records",ios::in|ios::out|ios::ate|ios::binary);
  file.seekg(0);
  if(!file)
    cout<<"File not found";
  else
  {
    file.read((char*)&temp,sizeof(temp));

    while(!file.eof())
    {
      r++; // r is used to find the position of the required object in the customer records file
      if(temp.accountNo==accountNo)
      {
        Account temp1(*this);
        file.seekp((r-1)*sizeof(Account),ios::beg);
        file.write((char*)&temp1,sizeof(temp1)); //overwrite the previous object with the current object
        break;
      }
      file.read((char*)&temp,sizeof(temp));
    }
    if(file.eof())
      cout<<"Record not found";
  }
  file.close();
}

void Account::calculateInterest() {
  string currDate = findCurrentDate();
  string lastDate(LanstWithdrawDate);
  int interval = findDifference(lastDate); //find the interval between the last withdrawl day and the current day
  float interest;
  if(interval < 30) { // check if it is atleast one month difference between the last withdrawl day and current day
    cout<<endl<<"You have withdrawn within last month or you created the account within the last month. So can't calculate.";
  }
  else {
    interest = (balance * interval * rateOfInterest) / 365; //calculate the interest
    cout<<"The interest is : "<<interest;
  }
}

//printing logic
void Account::display() {
  cout.setf(ios::left,ios::adjustfield);
  cout<<setw(20)<<name<<setw(20)<<accountNo<<setw(20)<<accountType<<setw(20)<<balance<<setw(20)<<date<<setw(20)<<LanstWithdrawDate<<setw(20)<<address<<endl;
}

/* To delete a specific object from the customers file, this function copies all the objects from the customer records file to the temporary records file except the object to be deleted. Then it deletes the customer records file and renames the temporary records file to customer records file*/
void Account::deleteAccount() {
  ifstream fin;
  ofstream fout;
  Account temp;
  fin.open("Records/Customer records",ios::in|ios::binary);
  fout.open("Records/Temp records",ios::out|ios::app|ios::binary);
  if(!fin)
    cout<<"File not found";
  else
  {
    fin.read((char*)&temp,sizeof(temp));
    while(!fin.eof())
    {
      if(temp.accountNo==accountNo) // if the account no matches don't write the object to the temp file
      {
        cout<<"\nAccount is deleted";
      }
      else {
        fout.write((char*)&temp,sizeof(temp));
      }
      fin.read((char*)&temp,sizeof(temp));
    }
    fin.close();
    fout.close();
    
    //execute system commands to manipulate the directories like deletion and renaming
    system("rm Records/\'Customer records\'");
    system("mv Records/\'Temp records\' Records/\'Customer records\'");
  }
}


















