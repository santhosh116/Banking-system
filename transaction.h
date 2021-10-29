using namespace std;

//Holds the transaction details
class Transaction {

  int oldBalance;
  int newBalance;
  int withdrawAmount;
  int depositAmount;
  char date[11];
  long int accountNo;
  int recordNumber;
  
  public:
    void createRecord(int oldBalance, int newBalance, int withdrawAmount, int depositAmount, char* date, long int accountNo);
    void assignRecordNumber();
    void addToRecords();
    void display();
};

//create a new transation
void Transaction::createRecord(int oldBalance, int newBalance, int withdrawAmount, int depositAmount, char* date, long int accountNo) {
  this->oldBalance = oldBalance;
  this->newBalance = newBalance;
  this->withdrawAmount = withdrawAmount;
  this->depositAmount = depositAmount;
  strcpy(this->date,date);
  this->accountNo = accountNo;
}

//adds the transaction object to the transaction records file
void Transaction::addToRecords() {
  ofstream fout;
  fout.open("Records/Transaction records",ios::out|ios::app|ios::binary);
  if(!fout)
    cout<<"File can not open";
  else
    fout.write((char*)this,sizeof(*this));
  fout.close();
}

//assigns a unique record number for the transaction which can be used as an index
void Transaction::assignRecordNumber() {
  ifstream fin;
  Transaction temp;
  long int recordNo = 0;
  fin.open("Records/Transaction records",ios::in|ios::binary);
  if(!fin)
    this->recordNumber = recordNo+1;
  else
  {
    fin.read((char*)&temp,sizeof(temp));
    while(!fin.eof())
    {
      recordNo=temp.recordNumber;
      fin.read((char*)&temp,sizeof(temp));
    }
    recordNo++;
    this->recordNumber = recordNo;
  }
}

void Transaction::display() {
  cout.setf(ios::left,ios::adjustfield);
  cout<<setw(20)<<recordNumber<<setw(20)<<accountNo<<setw(20)<<oldBalance<<setw(20)<<newBalance<<setw(20)<<withdrawAmount<<setw(20)<<depositAmount<<date<<endl;
}