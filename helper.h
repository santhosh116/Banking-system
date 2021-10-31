
using namespace std;

string findCurrentDate();
int findDifference(string lastDate);

//used to find the number of days between the given date and the current date
int findDifference(string lastDate) {
  char *ptr; // It is the char array to take the date, month and year
  char char_array[20]; //strtok() only works with native c type char array, so we copy the string to this char_array
  struct tm date = {0}; //tm is the in-built structure used to handle date
  int interval; 
  time_t current; // The current time
  time_t normal; // The time of the date mentioned in the function argument
  strcpy(char_array, lastDate.c_str()); //copy the string to c type char array  
  ptr = strtok(char_array, "-"); // string tokenize to find the date
  date.tm_mday = boost::lexical_cast<int>(ptr); //type conversion from char array to int // c type conversion don't work for char[] to int conversion so lexical_cast is used
  ptr = strtok (NULL, "-"); // find the month
  date.tm_mon  = boost::lexical_cast<int>(ptr)-1; //"-1" is used because the tm structure stores the month from 0 to 11
  ptr = strtok (NULL, "-"); // find the year
  date.tm_year = boost::lexical_cast<int>(ptr)-1900; // tm data structure takes year from 1900
  normal = mktime(&date); // create time from this date
  time(&current); // find the current time and store it in current
  interval = (difftime(current, normal)) / 86400L; // "/86400L" is used for converting seconds to days
  return interval;
}

//gives the current date in the string format
string findCurrentDate() {
  time_t now = time(0);
  struct tm tstruct;
  char buf[20];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%d-%m-%Y", &tstruct);
  string date(buf);
  return date;
}
