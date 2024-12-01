
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

class User {

private:
  string name;
  string username;
  string password;
  double account_balance;

public:
  User() {
    name = "Guest";
    username = "Guest";
    password = "Guest";
    account_balance = 0.00;
  }

  User(string newName, string newUserName, string newPass, double newBalance) {
    name = newName;
    username = newUserName;
    password = newPass;
    account_balance = newBalance;
  }

  string getName() {
    return name;
  }
  string getUserName() {
    return username;
  }
  string getPass() {
    return password;
  }
  double getBalance() {
    return account_balance;
  }
  void setName(string newName) {
    name = newName;
  }
  void setUserName(string newUserName) {
    username = newUserName;
  }
  void setPass(string newPass) {
    password = newPass;
  }
  void setBalance(double newBalance) {
    account_balance = newBalance;
  }
  double deposit(double amount) {
    account_balance += amount;
    return account_balance;
  }
  double withdraw(double amount) {
    if (amount > account_balance) {
      cout << "You dont have sufficient funds.  Current balance: " << account_balance;
      return account_balance;
    }
    else {
      account_balance -= amount;
      cout << "You withdrew: " << amount << '\n';
      cout << "New balance: " << account_balance << '\n';
      return account_balance;
    }
  }

  bool checkPassword(string enteredPassword) {
    return password == enteredPassword;
  }

  void toString() {
    cout << "Name:" << name << "\n";
    cout << "User Name:" << username << "\n";
    cout << "Password:" << password << "\n";
    cout << "Account Balance:" << account_balance << "\n";
  }

};

class LoginSystem : protected User {
private:
  vector<User> users;
  User* currentUser;  // important 

public:
  LoginSystem() {
    // Initialize some sample users
    users.push_back(User("Youssef", "lebron", "pass123", 1000.00));
    users.push_back(User("guest", "guest", "guest", 1000.00));

    currentUser = nullptr;  // No user is logged in initially    if currentUser != bullptr => the user logged in
  }

  void createUser(string newName, string newUserName, string newPass, double newBalance) {
    users.push_back(User(newName, newUserName, newPass, newBalance));
  }

  // Login method
  void login(string username, string password) {
    for (User& user : users) { // loop all users  (vector)
      if (user.getUserName() == username && user.checkPassword(password)) {
        currentUser = &user; // very important
        cout << "\n";
        cout << "Login successful. Welcome, " << currentUser->getName() << "!\n";
        return;
      }
    }
    cout << "Login failed. Invalid username or password.\n";
  }

  // Logout method
  void logout() {
    if (currentUser != nullptr) {
      cout << "\n";
      cout << "Goodbye, " << currentUser->getName() << "!\n";
      currentUser = nullptr;
    }
    else {
      cout << "No user is currently logged in.\n";
    }
  }

  // Check if a user is currently logged in
  bool isLoggedIn() { // 
    return currentUser != nullptr;  // if logged in = true
  }

  // Access the current user (if logged in)

  User* getCurrentUser() { // bec currentUser pointer
    return currentUser;
  }
};

void printMenu(int* choice)
{
  int c = -1;
  int numOptions = 7;
  //	char str[255];

  printf("\n  MAIN MENU\n \n");
  printf("  (1) Create User\n");
  printf("  (2) Login\n");
  printf("  (3) Logout\n");
  printf("  (4) Withdraw/Deposit\n");
  printf("  (5) Start your Trip\n");
  printf("  (6) Offers section\n");
  cout << endl;
  printf("  -----------------------\n");
  printf("  (7) Management section\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  cin >> c;

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    cin >> c;
  }

  if (c == 0) {
    // not ness
    exit(0);
  }


  *choice = c;
}


class Trip {
public:
  int max_number_firstClass;
  int max_number_secondClass;
  int max_number_thirdClass;

  int current_num_firstClass;
  int current_num_secondClass;
  int current_num_thirdClass;

  string from;
  string to;

  string week; // this week , next week , after next week 
  string day;
  string discountCodes[3];
  int tripID;

  double ThirdClass_price;
  double ThirdClass_mealPrice;

  bool is_available = true; // if the trip available => to display it for the user or remove or edit it from management section
  bool offer = false;   // offers section
  double ThirdClass_price_afterOffer;
  void displayTrip();

  // for ticket
  int getCurrent_FirstClass();
  int getCurrent_SecondClass();
  int getCurrent_ThirdClass();
  void setCurrent_FirstClass(int newFirstClassCount);
  void setCurrent_SecondClass(int newSecondClassCount);
  void setCurrent_ThirdClass(int newThirdClassCount);
};



void printTermsAndConditions() {
  string path = "C:\\Users\\Samel Store\\Desktop\\programming project\\ConsoleApplication1\\ConsoleApplication1\\T&C.txt";
  ifstream file(path);

  if (file.is_open()) {
    string line;
    cout << "-----------------------------------------------------"
      << "-----------------------------------------------------"
      << endl;
    while (getline(file, line)) {
      cout << line << endl;
    }
    cout << endl
      << "-----------------------------------------------------"
      << "-----------------------------------------------------"
      << endl;
    cout << endl << endl;
    file.close();
  }
  else {
    cout << "Unable to open file";
  }
}




void addTrip(vector <Trip>& tripV, Trip trip) { //  4
  tripV.push_back(trip); // will add to the main vector  bec pass by ref
  int current_index;
  current_index = tripV.size() - 1;

  cout << "enter Trip ID =  ";
  int Tid;
  cin >> Tid;
  cout << "--" << endl;
  tripV.at(current_index).tripID = Tid;

  cout << "enter the name of trip day (Saturday or Friday or ....) =  ";
  string Tday;
  cin >> Tday;
  cout << "--" << endl;
  tripV.at(current_index).day = Tday;

  cout << "select weak of the Trip (1 or 2 or 3) " << endl;
  cout << "1. This week" << endl;
  cout << "2. Next week" << endl;
  cout << "3. After next week" << endl;
  int weekChoice;
  cout << "Enter your choice (1-3): ";
  cin >> weekChoice;
  cout << "--" << endl;
  switch (weekChoice) {
  case 1:
    tripV.at(current_index).week = "this week";
    break;
  case 2:
    tripV.at(current_index).week = "next week";
    break;
  case 3:
    tripV.at(current_index).week = "after next week";
    break;
  default:
    cout << "Invalid choice for week!" << endl;
    break;
  }

  cout << "enter Departure location =  ";
  string Tfrom;
  cin >> Tfrom;
  cout << "--" << endl;
  tripV.at(current_index).from = Tfrom;

  cout << "enter Destination location =  ";
  string Tto;
  cin >> Tto;
  cout << "--" << endl;
  tripV.at(current_index).to = Tto;

  cout << "enter capacity of first class =  ";
  int Tcapacity_Frist;
  cin >> Tcapacity_Frist;
  cout << "--" << endl;
  tripV.at(current_index).max_number_firstClass = Tcapacity_Frist;

  cout << "enter capacity of second class =  ";
  int Tcapacity_Second;
  cin >> Tcapacity_Second;
  cout << "--" << endl;
  tripV.at(current_index).max_number_secondClass = Tcapacity_Second;

  cout << "enter capacity of third class =  ";
  int Tcapacity_Third;
  cin >> Tcapacity_Third;
  cout << "--" << endl;
  tripV.at(current_index).max_number_thirdClass = Tcapacity_Third;

  cout << "enter ThirdClass Price =  ";
  double price_Third;
  cin >> price_Third;
  cout << "--" << endl;
  tripV.at(current_index).ThirdClass_price = price_Third;

  cout << "enter ThirdClass meal Price =  ";
  double Mprice_Third;
  cin >> Mprice_Third;
  cout << "--" << endl;
  tripV.at(current_index).ThirdClass_mealPrice = Mprice_Third;

  cout << "Is there an offer on the trip? " << endl;
  cout << "1- Yes " << endl;
  cout << "2- No " << endl;

  int Oselected;
  cout << "Enter 1 or 2 =  ";
  cin >> Oselected;
  cout << "--" << endl;

  if (Oselected != 1 && Oselected != 2) {

    cout << "invalid input" << endl;

  }
  else {
    if (Oselected == 1) {
      tripV.at(current_index).offer = true;
    }
    if (Oselected == 2) {
      tripV.at(current_index).offer = false;
    }
  }

  cout << "enter discount codes  " << endl;
  string disCodes[3];
  for (int i = 0; i < 3; i++) {
    cout << "enter code " << i + 1 << " =   ";
    cin >> disCodes[i];
    tripV.at(current_index).discountCodes[i] = disCodes[i];
  }
  cout << "--" << endl;
}

void edit_trip(vector <Trip>& tripV) { // 3
  bool is_there_trip = false;
  for (int i = 0; i < tripV.size(); i++) {
    if (tripV.at(i).is_available == true) {
      is_there_trip = true;
    }
  }

  if (is_there_trip) {


    for (int i = 0; i < tripV.size(); i++) {
      if (tripV.at(i).is_available) {
        cout << "------------------------------------------------------------------------------------------" << endl;
        cout << "# " << i << "  " << endl << endl;
        cout << "ID -> " << tripV.at(i).tripID << endl;
        cout << "day -> " << tripV.at(i).day << "   &  " << "weak -> " << tripV.at(i).week << endl;
        cout << "from -> " << tripV.at(i).from << "   &   " << "to -> " << tripV.at(i).to << endl << endl;
      }
    }
    cout << "------------------------------------------------------------------------------------------" << endl << endl;
    cout << "enter the number of the trip to edit =  ";
    int selectedTrip;
    cin >> selectedTrip;
    cout << endl;

    cout << "what you want to edit " << endl;
    cout << "---------------------" << endl;
    cout << "1- day" << endl;
    cout << "2- week " << endl;
    cout << "3- Departure " << endl;
    cout << "4- Destination " << endl;
    cout << "5- remove " << endl;
    cout << "6- offer " << endl;
    cout << "7- capacity of first class " << endl;
    cout << "8- capacity of second class " << endl;
    cout << "9- capacity of third class " << endl;
    cout << "10- ThirdClass Price " << endl;
    cout << "11- ThirdClass meal Price " << endl << endl;

    int Selected_task;
    cout << "enter the number of the task to perform: ";
    cin >> Selected_task;
    string newDay, newDeparture, newDestination;
    int offerStatus;
    switch (Selected_task) {
    case 1:
      cout << "please enter the new day: ";
      cin >> newDay;
      tripV.at(selectedTrip).day = newDay;
      cout << "Successfully modified !" << endl;
      break;
    case 2:
      cout << "Please select the new week:" << endl;
      cout << "1. This week" << endl;
      cout << "2. Next week" << endl;
      cout << "3. After next week" << endl;
      int weekChoice;
      cout << "Enter your choice (1-3): ";
      cin >> weekChoice;
      switch (weekChoice) {
      case 1:
        tripV.at(selectedTrip).week = "this week";
        break;
      case 2:
        tripV.at(selectedTrip).week = "next week";
        break;
      case 3:
        tripV.at(selectedTrip).week = "after next week";
        break;
      default:
        cout << "Invalid choice for week!" << endl;
        break;
      }
      cout << "Successfully modified !" << endl;
      break;
    case 3:
      cout << "please enter the new departure location: ";
      cin >> newDeparture;
      tripV.at(selectedTrip).from = newDeparture;
      cout << "Successfully modified !" << endl;
      break;
    case 4:
      cout << "please enter the new destination location: ";
      cin >> newDestination;
      tripV.at(selectedTrip).to = newDestination;
      cout << "Successfully modified !" << endl;
      break;
    case 5:
      tripV.at(selectedTrip).is_available = false;
      cout << "Successfully modified !" << endl;
      break;
    case 6:
      cout << "change offer status (1 for Yes, 2 for No): ";
      cin >> offerStatus;
      if (offerStatus == 1) {
        tripV.at(selectedTrip).offer = true;
        cout << "Successfully modified !" << endl;
      }
      else if (offerStatus == 2) {
        tripV.at(selectedTrip).offer = false;
        cout << "Successfully modified !" << endl;
      }
      else {
        cout << "Invalid input for offer status!" << endl;
      }
      break;
    case 7:
      cout << "please enter the new capacity of first class: ";
      int newCapacityFirst;
      cin >> newCapacityFirst;
      tripV.at(selectedTrip).max_number_firstClass = newCapacityFirst;
      cout << "Successfully modified !" << endl;
      break;
    case 8:
      cout << "please enter the new capacity of second class: ";
      int newCapacitySecond;
      cin >> newCapacitySecond;
      tripV.at(selectedTrip).max_number_secondClass = newCapacitySecond;
      cout << "Successfully modified !" << endl;
      break;
    case 9:
      cout << "please enter the new capacity of third class: ";
      int newCapacityThird;
      cin >> newCapacityThird;
      tripV.at(selectedTrip).max_number_thirdClass = newCapacityThird;
      cout << "Successfully modified !" << endl;
      break;
    case 10:
      cout << "please enter the new ThirdClass Price: ";
      double newPriceThird;
      cin >> newPriceThird;
      tripV.at(selectedTrip).ThirdClass_price = newPriceThird;
      cout << "Successfully modified !" << endl;
      break;
    case 11:
      cout << "please enter the new ThirdClass meal Price: ";
      double newMealPriceThird;
      cin >> newMealPriceThird;
      tripV.at(selectedTrip).ThirdClass_mealPrice = newMealPriceThird;
      cout << "Successfully modified !" << endl;
      break;
    default:
      cout << "Invalid task number" << endl;
      break;
    }

  }
  else {
    cout << "No Trips available !" << endl;
  }

}   // add trip

void manageTrips(vector<Trip>& tripV, Trip& trip) { // 2
  cout << endl;

  bool running = true;

  while (running) {
    cout << "Welcome to the Trip Management Section!" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Select an option:" << endl;
    cout << "1. Add Trip" << endl;
    cout << "2. Edit Trip" << endl;
    cout << "--------------------------------------" << endl;

    int choice;
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    switch (choice) {
    case 1:
      cout << "Adding a New Trip..." << endl;

      addTrip(tripV, trip);
      break;
    case 2:
      cout << "Editing a Trip..." << endl;
      edit_trip(tripV);
      break;
    default:
      cout << "Invalid choice. Please select 1 or 2." << endl;
      break;
    }

    char cont;
    cout << "Do you want to continue managing trips? (y/n): ";
    cin >> cont;

    if (cont != 'y' && cont != 'Y')
      running = false;
  }
}


void management_section(vector <Trip>& tripV, Trip trip) { // 1
  string secret_key;
  string keyPassword = "key";
  bool zz = true;
  while (zz) {
    cout << "for testing secret key is key" << endl;
    cout << "Enter the secret key = ";
    cin >> secret_key;

    if (secret_key == keyPassword) {

      manageTrips(tripV, trip);
      zz = false;
    }
    else {
      cout << " invalid secretkey " << endl;// repeat the mission;
    };
  }
}
/////////////////////////////////////////////

void displayAvailableOffers(const vector<Trip>& tripV) {
  for (const Trip& trip : tripV) {
    if (trip.is_available && trip.offer) {
      cout << "----------------------------------------------------------------" << endl;
      double discountedPrice = trip.ThirdClass_price_afterOffer > 0 ? trip.ThirdClass_price_afterOffer : trip.ThirdClass_price;
      double discountPercentage = (trip.ThirdClass_price - discountedPrice) / trip.ThirdClass_price * 100;
      cout << "Discount: " << fixed << setprecision(2) << discountPercentage << "%" << endl << "-----------------" << endl << endl;

      cout << "Day: " << trip.day << endl;
      cout << "Week: " << trip.week << endl;
      cout << "From: " << trip.from << endl;
      cout << "To: " << trip.to << endl;
      cout << "Original Price: " << trip.ThirdClass_price << endl;

      cout << "Price After Offers: " << discountedPrice << endl;

    }
  }
  cout << "----------------------------------------------------------------" << endl;
}


void BigIntro() {

  cout << endl << endl;
  cout << "                        WW      WW  EEEEEEE  LL       CCCCCC  OOOOOO    MM     MM    EEEEEEE" << endl;
  cout << "                        WW      WW  EE       LL      CC      OO    OO  MMMM   MMMM   EE      " << endl;
  cout << "                        WW  WW  WW  EEEEE    LL      CC     OO      OO MM  M M  MM   EEEEE   " << endl;
  cout << "                        WW WWWW WW  EE       LL      CC     OO      OO MM  M M  MM   EE      " << endl;
  cout << "                        WW  WW  WW  EEEEEEE  LLLLLLL  CCCCCC  OOOOOO   MM       MM   EEEEEEE" << endl;
  cout << "                        --------------------------------------------------------------------" << endl;
  cout << "                        <                     EXPLORE      &       CREATE                  >  " << endl << endl << endl;


  bool running = true;
  while (running) {
    cout << "------------------- Choose an Option --------------------\n";
    cout << "1. I agree to the Terms and Conditions" << endl;
    cout << "2. I do not agree to the Terms and Conditions" << endl;
    cout << "3. View Terms & Conditions" << endl;
    cout << "----------------------------------------------------------\n";
    cout << "Enter your choice: ";

    int select;
    cin >> select;

    if (select == 1) {
      running = false;
      cout << endl;
    }

    if (select == 2) {
      exit(0);
    }
    if (select == 3) {
      printTermsAndConditions();
    }
  }
}

int Selected_trip(vector <Trip>& tripV, Trip trip, string& day, string& week) {
  bool running = true;

  while (running) {
    cout << "------------------- Choose an Option --------------------\n";
    cout << "1. Available this week" << endl;
    cout << "2. Search for your Trip" << endl;
    cout << "----------------------------------------------------------\n";
    cout << "Enter your choice: ";

    int select;
    cin >> select;

    if (select == 1) {

      for (int i = 0; i < tripV.size(); i++) {
        if (tripV.at(i).is_available && tripV.at(i).week == "this week") {
          cout << "------------------------------------------------------------------------------------------" << endl;
          cout << "# " << i << "  " << endl << endl;
          cout << "ID -> " << tripV.at(i).tripID << endl;
          cout << "day -> " << tripV.at(i).day << "   &  " << "weak -> " << tripV.at(i).week << endl;
          cout << "from -> " << tripV.at(i).from << "   &   " << "to -> " << tripV.at(i).to << endl << endl;
        }
      }
      cout << "------------------------------------------------------------------------------------------" << endl << endl;
      cout << "enter number of the trip to select =  ";
      int selectedTrip;
      cin >> selectedTrip;
      cout << endl;
      return selectedTrip;
      break;
    }

    if (select == 2) {

      cout << "please select the week of the Trip" << endl;
      cout << "------------------- Choose an week --------------------\n";
      cout << "1. this week" << endl;
      cout << "2. next week" << endl;
      cout << "3. after next week" << endl;
      cout << "----------------------------------------------------------\n";
      cout << "Enter your choice: ";
      int selected;
      cin >> selected;
      switch (selected)
      {
      case 1:
        week = "this week";
        break;
      case 2:
        week = "next week";
        break;
      case 3:
        week = "after next week";
        break;
      default:
        cout << "invalid choice" << endl;
        break;
      }
      ////////////////

      cout << "please select the day of the Trip" << endl;
      cout << "------------------- Choose an day --------------------\n";
      cout << "1. saturday" << endl;
      cout << "2. sunday" << endl;
      cout << "3. monday" << endl;
      cout << "4. tuesday" << endl;
      cout << "5. wednesday" << endl;
      cout << "6. thursday" << endl;
      cout << "7. friday" << endl;
      cout << "----------------------------------------------------------\n";
      cout << "Enter your choice: ";
      cin >> selected;
      switch (selected)
      {
      case 1:
        day = "saturday";
        break;
      case 2:
        day = "sunday";
        break;
      case 3:
        day = "monday";
        break;
      case 4:
        day = "tuesday";
        break;
      case 5:
        day = "wednesday";
        break;
      case 6:
        day = "thursday";
        break;
      case 7:
        day = "friday";
        break;

      default:
        cout << "invalid choice" << endl;
        break;
      }
      bool atleast_one = false;
      for (int i = 0; i < tripV.size(); i++) {
        if (tripV.at(i).is_available) {
          if (tripV.at(i).week == week && tripV.at(i).day == day) {
            atleast_one = true;
            cout << "------------------------------------------------------------------------------------------" << endl;
            cout << "# " << i << "  " << endl << endl;
            cout << "ID -> " << tripV.at(i).tripID << endl;
            cout << "day -> " << tripV.at(i).day << "   &  " << "weak -> " << tripV.at(i).week << endl;
            cout << "from -> " << tripV.at(i).from << "   &   " << "to -> " << tripV.at(i).to << endl << endl;
          }
        }


      }
      if (atleast_one) {
        cout << "------------------------------------------------------------------------------------------" << endl << endl;
        cout << "enter number of the trip to select =  ";
        int selectedTrip;
        cin >> selectedTrip;
        cout << endl;
        running = false; // any running => while loop
        return selectedTrip;
      }
      else {
        cout << "No Trips available" << endl;
        cout << "press (0) to exit or (1) keep searching =  ";
        int press;
        cin >> press;
        if (press == 0) {
          exit(0);
        }

      }


    }

  }
  return -1;
}








void printTicketAndUpdateTrip(Trip* chosenTrip, double price, string classType, int numPassengers, User* currentUser) {

  // Print ticket details 
  cout << "----------------------------------------------------" << endl;
  cout << "                      TICKET                         " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "Trip ID:           " << chosenTrip->tripID << endl;
  cout << "Departure:         " << chosenTrip->from << endl;
  cout << "Destination:       " << chosenTrip->to << endl;
  cout << "Class:             " << classType << endl;
  cout << "Number of Passengers: " << numPassengers << endl;
  cout << "Total Price:       " << fixed << setprecision(2) << price << endl;
  cout << "----------------------------------------------------" << endl;



  // Adjust current_num based on class type
  if (classType == "FirstClass") {
    chosenTrip->setCurrent_FirstClass(chosenTrip->getCurrent_FirstClass() + numPassengers);
  }
  else if (classType == "SecondClass") {
    chosenTrip->setCurrent_SecondClass(chosenTrip->getCurrent_SecondClass() + numPassengers);
  }
  else if (classType == "ThirdClass") {
    chosenTrip->setCurrent_ThirdClass(chosenTrip->getCurrent_ThirdClass() + numPassengers);
  }
  else {
    cout << "Invalid class type provided." << endl;
    return;
  }

  // Withdraw price from user's balance
  currentUser->setBalance(currentUser->getBalance() - price);
}



void printTicketAndUpdateTrip(Trip* chosenTrip, double price, string classType, int numPassengers, User* currentUser, string bye_sentence) { //overloded fun 

  // Print ticket details 
  cout << "----------------------------------------------------" << endl;
  cout << "                      TICKET                         " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "Trip ID:           " << chosenTrip->tripID << endl;
  cout << "Departure:         " << chosenTrip->from << endl;
  cout << "Destination:       " << chosenTrip->to << endl;
  cout << "Class:             " << classType << endl;
  cout << "Number of Passengers: " << numPassengers << endl;
  cout << "Total Price:       " << fixed << setprecision(2) << price << endl;
  cout << "----------------------------------------------------" << endl;



  // Adjust current_num based on class type
  if (classType == "FirstClass") {
    chosenTrip->setCurrent_FirstClass(chosenTrip->getCurrent_FirstClass() + numPassengers);
  }
  else if (classType == "SecondClass") {
    chosenTrip->setCurrent_SecondClass(chosenTrip->getCurrent_SecondClass() + numPassengers);
  }
  else if (classType == "ThirdClass") {
    chosenTrip->setCurrent_ThirdClass(chosenTrip->getCurrent_ThirdClass() + numPassengers);
  }
  else {
    cout << "Invalid class type provided." << endl;
    return;
  }

  // Withdraw price from user's balance
  currentUser->setBalance(currentUser->getBalance() - price);
  cout << bye_sentence << endl;
}


int Trip::getCurrent_FirstClass() {
  return current_num_firstClass;
}

int Trip::getCurrent_SecondClass() {
  return current_num_secondClass;
}

int Trip::getCurrent_ThirdClass() {
  return current_num_thirdClass;
}

void Trip::setCurrent_FirstClass(int newFirstClassCount) {
  current_num_firstClass = newFirstClassCount;
}

void Trip::setCurrent_SecondClass(int newSecondClassCount) {
  current_num_secondClass = newSecondClassCount;
}

void Trip::setCurrent_ThirdClass(int newThirdClassCount) {
  current_num_thirdClass = newThirdClassCount;
}











int main() {
  string day;
  string week;

  vector <User>userV;
  User user;

  vector <Trip>tripV;
  Trip trip, selected_trip;


  LoginSystem loginSystem;
  string name, userName, password;
  double accountBalance;
  User currentUser;


  // trip 1  

  tripV.push_back(trip);   // كل ما اعملو بووش يعمل واوبجيكت جديد التحكم بتاعنا بالانديكس بس
  tripV.at(0).day = "saturday";
  tripV.at(0).week = "this week";
  tripV.at(0).discountCodes[0] = "dis1";
  tripV.at(0).discountCodes[1] = "dis2";
  tripV.at(0).discountCodes[2] = "dis3";

  tripV.at(0).from = "dark";
  tripV.at(0).to = "light";

  tripV.at(0).is_available = true;
  tripV.at(0).offer = true;

  tripV.at(0).max_number_firstClass = 4;
  tripV.at(0).max_number_secondClass = 3;
  tripV.at(0).max_number_thirdClass = 2;

  tripV.at(0).tripID = 111;
  tripV.at(0).ThirdClass_mealPrice = 50;
  tripV.at(0).ThirdClass_price = 200;
  tripV.at(0).ThirdClass_price_afterOffer = 100;


  // trip 2

  tripV.push_back(trip);
  tripV.at(1).day = "sunday";
  tripV.at(1).week = "after next week";
  tripV.at(1).discountCodes[0] = "dis1";
  tripV.at(1).discountCodes[1] = "dis2";
  tripV.at(1).discountCodes[2] = "dis3";

  tripV.at(1).from = "giza";
  tripV.at(1).to = "cairo";

  tripV.at(1).is_available = true;
  tripV.at(1).offer = true;

  tripV.at(1).max_number_firstClass = 4;
  tripV.at(1).max_number_secondClass = 3;
  tripV.at(1).max_number_thirdClass = 2;

  tripV.at(1).tripID = 222;
  tripV.at(1).ThirdClass_mealPrice = 50;
  tripV.at(1).ThirdClass_price = 400;
  tripV.at(1).ThirdClass_price_afterOffer = 100;




  // trip 3

  tripV.push_back(trip);
  tripV.at(2).day = "friday";
  tripV.at(2).week = "this week";
  tripV.at(2).discountCodes[0] = "dis1";
  tripV.at(2).discountCodes[1] = "dis2";
  tripV.at(2).discountCodes[2] = "dis3";

  tripV.at(2).from = "alex";
  tripV.at(2).to = "cairo";

  tripV.at(2).is_available = true;
  tripV.at(2).max_number_firstClass = 4;
  tripV.at(2).max_number_secondClass = 3;
  tripV.at(2).max_number_thirdClass = 2;

  tripV.at(2).tripID = 333;
  tripV.at(2).ThirdClass_mealPrice = 50;
  tripV.at(2).ThirdClass_price = 200;


  // trip 4

  tripV.push_back(trip);
  tripV.at(3).day = "friday";
  tripV.at(3).week = "next week";
  tripV.at(3).discountCodes[0] = "dis1";
  tripV.at(3).discountCodes[1] = "dis2";
  tripV.at(3).discountCodes[2] = "dis3";

  tripV.at(3).from = "alexaaa";
  tripV.at(3).to = "cairoaaaa";

  tripV.at(3).is_available = true;
  tripV.at(3).max_number_firstClass = 4;
  tripV.at(3).max_number_secondClass = 3;
  tripV.at(3).max_number_thirdClass = 2;

  tripV.at(3).tripID = 333;
  tripV.at(3).ThirdClass_mealPrice = 50;
  tripV.at(3).ThirdClass_price = 200;

  string press;
  bool running = true;


  BigIntro();
  int trip_index;
  int choice = -1;
  while (choice != 0) {

    printMenu(&choice);



    switch (choice) {
    case 1:   // Create user and login
    {
      if (loginSystem.isLoggedIn()) {
        cout << "You're already logged in \n";
      }
      else {
        cout << "Please enter your Name: ";
        cin >> name;
        cout << "Please enter your Userame: ";
        cin >> userName;
        cout << "Please enter your Password: ";
        cin >> password;
        cout << "Please enter your Account Balance: ";
        cin >> accountBalance;
        loginSystem.createUser(name, userName, password, accountBalance);

        loginSystem.login(userName, password);
      }
    }break;

    case 2:   // Login
    {
      if (loginSystem.isLoggedIn()) {
        cout << "You're already logged in \n";
      }
      else {
        cout << "Please enter your Username: ";
        cin >> userName;
        cout << "Please enter your Password: ";
        cin >> password;
        loginSystem.login(userName, password);
      }
    }break;

    case 3:   // Logout
    {
      if (!loginSystem.isLoggedIn()) {
        cout << "You're not logged in \n";
      }
      else {
        loginSystem.logout();
      }
    }break;

    case 4:   // Withdraw/Deposit
    {
      double amount;
      if (!loginSystem.isLoggedIn()) {
        cout << "You're not logged in \n";
      }
      else {
        cout << "Current Balance: " << loginSystem.getCurrentUser()->getBalance() << "\n";
        cout << "Press 1 to withdraw or 2 to deposit: ";
        cin >> choice;
        if (choice == 1) {
          cout << "How much do you want to withdraw? ";
          cin >> amount;
          loginSystem.getCurrentUser()->withdraw(amount);

        }
        else if (choice == 2) {
          cout << "How much do you want to deposit? ";
          cin >> amount;
          loginSystem.getCurrentUser()->deposit(amount);
        }
        else {
          cout << "wrong choice ";
        }
      }
    }
    break;

    case 5: // select trip
      if (!loginSystem.isLoggedIn()) {
        cout << "You're not logged in \n";
      }
      else {
        trip_index = Selected_trip(tripV, trip, day, week);
        choice = 0; // to leave the loop
      }
      break;

    case 7:
      management_section(tripV, trip);
      break;

    case 6:
      displayAvailableOffers(tripV);
      while (running) {
        cout << "press any button to exit : ";
        cin >> press;
        running = false;
      }
      running = true;

      break;
    default:
      break;
    }
    // Display the total price to the user

  }
  string ClassType; // for ticket task
  double totalPrice = 0.0;
  // Option 1: Select class
  int classChoice;
  cout << "Select your class:\n";
  cout << "------------------- Choose an Option --------------------\n";
  cout << "1. First Class\n";
  cout << "2. Second Class\n";
  cout << "3. Third Class\n";
  cout << "----------------------------------------------------------\n";
  cout << "Enter your choice: ";

  cin >> classChoice;

  // Option 2: Meal or not
  int mealChoice;
  cout << "Do you want a meal?\n";
  cout << "------------------- Choose an Option --------------------\n";
  cout << "1. Yes\n";
  cout << "2. No\n";
  cout << "----------------------------------------------------------\n";
  cout << "Enter your choice: ";
  cin >> mealChoice;


  // Option 3: Number of people
  int numberOfPeople;
  bool run = true;
  while (run) {
    cout << "Enter the number of people in this ticket (max 5): ";
    cin >> numberOfPeople;
    if (numberOfPeople > 5) {
      cout << "max number or people is 5" << endl;
    }
    else { run = false; }
  }

  double selectedTrip_Third_price = tripV.at(trip_index).ThirdClass_price;
  double selectedTrip_Third_mealPrice = tripV.at(trip_index).ThirdClass_mealPrice;

  switch (classChoice) {
  case 1:
    ClassType = "FirstClass"; // for ticket task
    totalPrice = selectedTrip_Third_price * 3;
    if (mealChoice == 1) {
      totalPrice += selectedTrip_Third_mealPrice;
    }
    if (numberOfPeople > 1) {
      totalPrice *= numberOfPeople;
    }

    break;
  case 2:
    ClassType = "SecondClass";
    totalPrice = selectedTrip_Third_price * 2;
    if (mealChoice == 1) {
      totalPrice += selectedTrip_Third_mealPrice;
    }
    if (numberOfPeople > 1) {
      totalPrice *= numberOfPeople;
    }
    break;
  case 3:
    ClassType = "ThirdClass";
    totalPrice = selectedTrip_Third_price;
    if (mealChoice == 1) {
      totalPrice += selectedTrip_Third_mealPrice;
    }
    if (numberOfPeople > 1) {
      totalPrice *= numberOfPeople;
    }
    break;
  default:
    cout << "Invalid choice!" << endl;
    break;
  }
  cout << endl<<endl;
  cout << "           (^_^) Congratulations on choosing the trip (^_^)\n";
  cout << "-----------------------------------------------------------------------" << endl;
  cout << "                           pay for the trip                     " << endl;
  cout << "-----------------------------------------------------------------------" << endl << endl;
  int pay;
  cout << "Press (1) to complete the payment  ||  (any other button) to exit: ";
  cin >> pay;

  if (pay != 1) {
    exit(0);
  }
  cout << "---------------------------" << endl << endl;
  cout << "Trip price: $" << fixed << setprecision(2) << totalPrice << endl;
  cout << "Your account balance: $" << loginSystem.getCurrentUser()->getBalance() << endl;

  if (loginSystem.getCurrentUser()->getBalance() >= totalPrice) {
    loginSystem.getCurrentUser()->setBalance(loginSystem.getCurrentUser()->getBalance() - totalPrice);

    cout << "Payment successful! Your new account balance is $" << loginSystem.getCurrentUser()->getBalance() << endl << endl;
    User* User_ptr = loginSystem.getCurrentUser(); // pointer = pointer 
    Trip* ChosenTrip = &tripV.at(trip_index);
    string bye = "Thank you for booking your ticket!We look forward to serving you and seeing you onboard.\n";
    if (ClassType == "FirstClass") {
      printTicketAndUpdateTrip(ChosenTrip, totalPrice, ClassType, numberOfPeople, User_ptr, bye);
    }
    else {

      printTicketAndUpdateTrip(ChosenTrip, totalPrice, ClassType, numberOfPeople, User_ptr); // ticket
    }
  }
  else {
    // Inform user of insufficient funds
    cout << "Insufficient funds in your account. Please add more funds to proceed with payment." << endl;
  }

  return 0;
}