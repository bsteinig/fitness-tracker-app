#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include <deque>
#include "ScreenControll.h"
#include <algorithm>
#include <memory>
#include <sstream>

#include "Profile.h"
#include "Login.h"
#include "Activity.h"
#include "IntermediateActivity.h"
#include "ExpertActivity.h"

using namespace std;

// Login/Register Menu
int loginMenu();
// User Registration												//Line: 126
void registerUser(Profile*, const string, const string, HANDLE);
void validateInfo(Profile*, HANDLE);
int createAccount(Profile*, const string);
int validateAccount(Profile*, istream&, int);
int writeUserInfo(Profile*, const string);

// Login Validation													//Line: 432
int loginUser(Profile*, const string, const string, HANDLE);
int validateLogin(Profile*, istream&, int);

// User Main Menu													//Line: 406
int retrieveProfile(Profile*, const string, int);
int actionMenu(Profile*);
void createActivity(Profile*, const string, int);
void printActivities(Profile*, const string, int);

// Screen Control Function											//Line: 513
void drawRegistration(int);
void profileDataForm(HANDLE);
void displayDataForm(Profile*, HANDLE);
void drawActivityForm(int);

HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);

int main() {
	int quit = 0;
	int valid;
	int choice = 0;
	const string LOGIN_FILE = "LoginDatabase.txt";
	const string PROFILE_FILE = "ProfileDatabase.txt";
	const string USER_FILE = "ActivityDatabase.txt";

	// Initial login/register menu
	while (quit != 99) {
		quit = loginMenu();
		if (quit == 1) {
			system("CLS");
			Profile* checkUser = new Profile();
			valid = loginUser(checkUser, LOGIN_FILE, PROFILE_FILE, screen);
			delete checkUser;
			if (valid >= 0) {  // A valid user id has been returned and the application menu is launched
				Profile* retrieved = new Profile();
				retrieveProfile(retrieved, PROFILE_FILE, valid);
				// user action menu contained within login option
				while (choice != 99) {
					system("CLS");
					choice = actionMenu(retrieved);
					if (choice == 1) {
						system("CLS");
						displayDataForm(retrieved, screen);
						placeCursor(screen, 16, 50);
						system("pause");
					}
					else if (choice == 2) {
						system("CLS");
						printActivities(retrieved, USER_FILE, valid);
					}
					else if (choice == 3) {
						system("CLS");
						createActivity(retrieved, USER_FILE, valid);
					}
					else if (choice == 4) {
						break;					// if a user chooses to "logout" they are returned to the login/register menu
					}
				}
				delete retrieved;
			}
		}
		else if (quit == 2) {
			system("CLS");
			Profile *newUser = new Profile();
			registerUser(newUser, LOGIN_FILE, PROFILE_FILE,screen);
			delete newUser;
		}
		else {
			quit = 99; // any input either than 1,2 is converted to quit
		}
	}
	if (quit == 99) {
		return 0;
	}
}

// Login Menu

int loginMenu()
{
	system("CLS");
	int choice;
	placeCursor(screen, 3, 28);
	cout << "Welcome to the Run Tracking App" << endl;
	placeCursor(screen, 4, 25);
	cout << "Please login or register as a new user" << endl;
	placeCursor(screen, 5, 25);
	cout << "---------------------------------------" << endl;
	placeCursor(screen, 6, 31);
	cout << "1. Login       \t2. Register" << endl;
	placeCursor(screen, 7, 40);
	cout << "3. quit" << endl;
	placeCursor(screen, 9, 43);
	cin >> choice;
	return choice;
}

// User Registration

/**
  * void registerUser(Profile* user, const string loginFile, const string profileFile, HANDLE screen)
  *
  * Summary of the registerUser function:
  *
  *    The registerUser functon calls a two functions which fill a Profile object, then it calls a validation
  *		function to ensure the inputs are of the correct type, finally it writes the object to file
  *
  * Parameters   : Profile*: pointing to initially empty object, strings: containing filenames to write to, HANDLE: allows for windows console control
  *
  * Return Value : Nothing -- Note: Modifies the Profile object
  *
  * Description:
  *
  *    This function calls a variety of functions
  */
void registerUser(Profile* user, const string loginFile, const string profileFile, HANDLE screen)
{
	createAccount(user, loginFile);
	system("CLS");
	profileDataForm(screen);
	user->enterUserInfo(screen);
	validateInfo(user, screen);
	writeUserInfo(user, profileFile);
}

/*
* void validateInfo(Profile* user, HANDLE screen)
*
* Summary of the validateInfo function:
*
*    The validateInfo function takes a filled Profile object and uses relational operators to determine if the inputs
*		are in the correct format for future manipulations, if an error is detected the user will be prompted to reenter data
*		until it is correct
*
* Parameters   : Profile*: pointing to object, HANDLE: allows for windows console control
*
* Return Value : Nothing -- Note: Modifies the Profile object if errors detected
*
* Description:
*
*    The first attribute tested is char gender, to remove inconsistencys the toupper() function is called during comparisons, if any error is found it
*		changes the respective bool value is false. To ensure a proper date of birth format has been used the program tests both the string length and 
*		substrings where each value should be found MM/DD/YYYY. again to remove inconsistencys the runType is set to lowercase and then compared to strings.
*		If a bool is switched to false its respective attribute is cleared and a message is printed, then a new input is taken. The function calls itself until 
*		no errors are detected.
*/
void validateInfo(Profile* user, HANDLE screen)
{
	bool genderValid = true;
	bool dateValid = true;
	bool runTypeValid = true;
	int lines = 2;
	vector<string> dates;
	string date;

	system("CLS");

	if (toupper(user->getGender()) != 'F' && toupper(user->getGender()) != 'M') {
		genderValid = false;
	}
	stringstream dob(user->getDOB());
	while (getline(dob, date, '/')) {
		dates.push_back(date);
	}
	string month = user->getDOB().substr(0, 2);
	string day = user->getDOB().substr(3, 5);
	if (user->getDOB().size() > 10 || user->getDOB().size() < 10) {
		dateValid = false;
	}
	if (stoi(dates[0]) > 12 || stoi(dates[0]) < 1) {
		dateValid = false;
	}
	if (stoi(dates[1]) > 31 || stoi(dates[1]) < 1) {
		dateValid = false;
	}
	if (stoi(dates[2]) > 2020 || stoi(dates[2]) < 1850) {
		dateValid = false;
	}
	string rTypeConversion = user->getRunType();
	std::for_each(rTypeConversion.begin(), rTypeConversion.end(), [](char& ch) {
		ch = ::tolower(ch);
		});
	rTypeConversion[0] = toupper(rTypeConversion[0]);
	user->setRunType(rTypeConversion);
	if (user->getRunType() != "Beginner" && user->getRunType() != "Intermediate" && user->getRunType() != "Expert") {
		runTypeValid = false;
	}

	if (genderValid == false) {
		placeCursor(screen, lines, 25);
		cout << "Gender entry invalid, please reenter" << endl;
		user->setGender(' ');
		lines++;
	}
	if (dateValid == false) {
		placeCursor(screen, lines, 25);
		cout << "Date entry invalid, please reenter, check formatting" << endl;
		user->setDOB("");
		lines++;
	}
	if (runTypeValid == false) {
		placeCursor(screen, lines, 25);
		cout << "Runner Type entry invalid, please reenter" << endl;
		user->setRunType("");
		lines++;
	}
	if (!genderValid || !dateValid || !runTypeValid) {
		placeCursor(screen, lines, 25);
		cout << "------------------------------------------" << endl;
		displayDataForm(user, screen);
		char gen;
		string dob, rType;
		if (!genderValid) {
			placeCursor(screen, 7, 55);
			cin >> gen;
			user->setGender(gen);
		}
		if (!dateValid) {
			placeCursor(screen, 10, 26);
			cin >> dob;
			user->setDOB(dob);
		}
		if (!runTypeValid) {
			placeCursor(screen, 13, 26);
			cin >> rType;
			user->setRunType(rType);
		}

	}
	if (genderValid && dateValid && runTypeValid) {
		cout << "all clear" << endl;
	}
	else {
		validateInfo(user, screen);
	}

}

/**
  * int createAccount(Profile* user, const string fileName)
  *
  * Summary of the createAccount function:
  *
  *   This function opens the LoginDatabase file and validates that the username and password combination is valid,
  *		Then it writes the login information to the file where it is stored permanently
  *
  * Parameters   : Profile*: pointing to object, string: containing filenames to read/write
  *
  * Return Value : 0 -- Note: writes to login file
  *
  * Description:
  *
  *    This function opens an ifstream of loginDatabase and then calls validateAccount, then it opens a ofstream of loginDatabase
  *		and writes the username and password to file using class function writeLoginInfo(ofstream&);
  */
int createAccount(Profile* user, const string fileName)
{
	ifstream inFile(fileName, fstream::in);
	validateAccount(user, inFile, 0);
	inFile.close();
	ofstream outFile(fileName, ios::out | ios::app);
	user->writeLoginInfo(outFile);
	outFile.close();

	return 0;
}

/**
  * int validateAccount(Profile* user, istream& inFile, int switcher)
  *
  * Summary of the validateAccount function:
  *
  *   This function called by createAccount, takes the user entered login info and 
  *		compares it to existing login info to ensure that there are no duplicate users
  *
  * Parameters   : Profile*: pointing to object, istream&: containing file read object
  *
  * Return Value : 1 -- Note: modifies Profile object
  *
  * Description:
  *
  *   The function first reads the LoginDatabase and fills parallel vectors of usernames and passwords,
  *	  then the function takes user input username and password, these are first checked to see if they contain spaces
  *	  Spaces are avoided to simplify file reading. Next the username is compared to all usernames in the file to ensure
  *		there are no duplicate users
  *
  */
int validateAccount(Profile* user, istream& inFile, int switcher) {
	bool containsSpace = false;
	bool duplicateUser = false;
	bool passSpace = false;
	string userName = "", pass = "";
	string userTemp, passTemp, idTemp;
	vector <string> users, passes, ids;
	if (!inFile.fail()) { //Runs if File read successful
		// reads LoginDatabase.txt and stores all info
		while (inFile >> idTemp >> userTemp >> passTemp) {
			users.push_back(userTemp); //contains list of all usernames to check for duplicates
			passes.push_back(passTemp);
			ids.push_back(idTemp); // allows the program to set the next id number, ensures no duplicate ids
		}
		user->setUserID(stoi(ids.back()) + 1);
		cin.clear();
		cin.ignore();
		do {	// validates username input
			system("CLS");
			if (containsSpace == true) {
				placeCursor(screen, 8, 25);
				if (switcher == 0) {
					cout << "username contains spaces please try again" << endl;
				}
				else {
					cout << "username doesn't match any records please try again" << endl;
				}
			}
			if (duplicateUser == true) {
				placeCursor(screen, 9, 25);
				if (switcher == 0) {
					cout << "username has been taken, please try again" << endl;
				}
				else {
					cout << "username doesn't match any records please try again" << endl;
				}
			}
			containsSpace = false;
			duplicateUser = false;
			drawRegistration(switcher);
			placeCursor(screen, 6, 40);
			getline(cin, userName);
			for (int i = 0; i < userName.size(); i++) {
				if (userName[i] == ' ') {
					containsSpace = true;
				}
			}
			for (int j = 0; j < users.size(); j++) {
				if (users[j] == userName) {
					duplicateUser = true;
				}
			}
		} while (containsSpace || duplicateUser);
		cin.clear();
		do {	//Validates password input
			placeCursor(screen, 7, 40);
			if (passSpace == true) {
				system("CLS");
				placeCursor(screen, 10, 25);
				if (switcher == 0) {
					cout << "password contains space, please try again" << endl;
				}
				else {
					cout << "password doesnt match any records, please try again" << endl;
				}
			}
			passSpace = false;
			drawRegistration(switcher);
			if (!duplicateUser && !containsSpace) {
				placeCursor(screen, 6, 40);
				cout << userName << endl;
			}
			placeCursor(screen, 7, 40);
			getline(cin, pass);
			for (int i = 0; i < pass.size(); i++) {
				if (pass[i] == ' ') {
					passSpace = true;
				}
			}
		} while (passSpace);

		// At this point both the username and pass word have been validated and can be entered;
		/*cout << "this is the username: " << userName << endl;
		cout << "this is the password: " << pass << endl;
		system("pause");*/
		user->setUsername(userName);
		user->setPassword(pass);

	}
	return 1;
}

/**
  * int writeUserInfo(Profile* user, const string profileFile) 
  *
  * Summary of the writeUserInfo function:
  *
  *   This function writes a Profile object to file
  *
  * Parameters   : Profile*: pointing to object, string: contains file name
  *
  * Return Value : 0 -- Note: writes to profileDatabase file
  *
  * Description:
  *
  *   The function opens an ofstream object in append mode, then using a 
  *	  class overloaded << operator the object is written to file
  *
  */
int writeUserInfo(Profile* user, const string profileFile) {
	ofstream outFile(profileFile, ios::out | ios::app);
	outFile << *user;
	outFile.close();
	return 0;
}

// Login Validation
// These functions are used to login a user

/**
  * int loginUser(Profile* user, const string loginFile, const string profileFile, HANDLE screen)
  *
  * Summary of the loginUser function:
  *
  *   draws the login screen, then calls validateLogin to get the users id
  *
  * Parameters   : Profile*: pointing to object, strings: contains file names
  *
  * Return Value : index, users unique id
  *
  * Description:
  *
  *   The function opens an ifstream object of the loginDatabase.txt and passes it to validateLogin 
  *
  */
int loginUser(Profile* user, const string loginFile, const string profileFile, HANDLE screen) {
	drawRegistration(1);
	ifstream inFile(loginFile, ios::in);
	int index = validateLogin(user, inFile, 1);
	inFile.close();
	return index;
}

/**
  * int validateLogin(Profile* user, istream& inFile, int switcher)
  *
  * Summary of the validateLogin function:
  *
  *   checks the user inputted username and password against the file of user logins, if a match is found it returns the id
  *
  * Parameters   : Profile*: pointing to object, istream&: loginDatabase file
  *
  * Return Value : storage, users unique id
  *
  * Description:
  *
  *   The functions fills three parallel vectors with the login files ids, usernames, and passwords
  *		this information is then compared to the user input, when a match is found it returns the 
  *		cooresponding id from the vector
  *
  */
int validateLogin(Profile* user, istream& inFile, int switcher)
{
	int storage = 0;
	bool containsSpace = false;
	bool noMatch = false;
	bool passSpace = false;
	string userName = "", pass = "";
	string userTemp, passTemp, idTemp;
	vector <string> users, passes, ids;
	if (!inFile.fail()) { //Runs if File read successful
		// reads LoginDatabase.txt and stores all info
		while (inFile >> idTemp >> userTemp >> passTemp) {
			users.push_back(userTemp); //contains list of all usernames to check for duplicates
			passes.push_back(passTemp);
			ids.push_back(idTemp); // allows the program to set the next id number, ensures no duplicate ids
		}
		cin.clear();
		cin.ignore();
		do {	// validates username input
			system("CLS");
			if (containsSpace || noMatch || passSpace) {
				placeCursor(screen, 8, 25);
				cout << "username or password doesn't match any records, please try again" << endl;
			}
			containsSpace = false;
			noMatch = false;
			passSpace = false;
			drawRegistration(switcher);
			placeCursor(screen, 6, 40);
			getline(cin, userName);
			placeCursor(screen, 7, 40);
			getline(cin, pass);
			for (int i = 0; i < userName.size(); i++) {
				if (userName[i] == ' ') {
					containsSpace = true;
				}
			}
			for (int j = 0; j < users.size(); j++) {
				if (users[j] == userName) {
					if (passes[j] == pass) {
						storage = stoi(ids[j]);
						return storage;
					}
					else {
						noMatch = true;
					}
				}
			}
			noMatch = true;
		} while (containsSpace || passSpace || noMatch);
		return storage;
	}
	else {
		return -1;
	}
}

// User Main Menu
// These functions occur after a successful login

/**
  * int retrieveProfile(Profile* user, const string profileFile, int it)
  *
  * Summary of the retrieveProfile function:
  *
  *   reads the profileDatabase until it finds the profile data for the cooresponding user id
  *
  * Parameters   : Profile*: pointing to object, string: profile file name, int: unique id
  *
  * Return Value : 0 , fills Profile* object
  *
  * Description:
  *
  *   Reads the profileDatabase file, when it finds the cooresponding id, the profile object is filled 
  *
  */
int retrieveProfile(Profile* user, const string profileFile, int it) {
	ifstream inFile(profileFile, ios::in);
	int id, age, weight;
	char gen;
	string fName, lName, dob, rType;
	while (inFile >> id >> fName >> lName >> age >> weight >> gen >> dob >> rType) {
		if (id == it) {
			user->setUserID(id);
			user->setFirstName(fName);
			user->setLastName(lName);
			user->setAge(age);
			user->setWeight(weight);
			user->setGender(gen);
			user->setDOB(dob);
			user->setRunType(rType);
			break;
		}
	}
	inFile.close();
	return 0;
}

// User Menu
int actionMenu(Profile* user)
{
	int choice;
	placeCursor(screen, 3, 28);
	cout << "Welcome " << user->getFirstName() << " to your run tracking page" << endl;
	placeCursor(screen, 4, 25);
	cout << "Select any option to continue" << endl;
	placeCursor(screen, 5, 25);
	cout << "---------------------------------------" << endl;
	placeCursor(screen, 6, 31);
	cout << "1. View Profile          \t2. View Activities" << endl;
	placeCursor(screen, 7, 31);
	cout << "3. Add New Activity       \t4.Return to Login" << endl;
	placeCursor(screen, 9, 53);
	cin >> choice;
	return choice;
}

/**
  * void createActivity(Profile* user, const string fileName, int id)
  *
  * Summary of the createActivity function:
  *
  *   fills an activity object and writes it to file
  *
  * Parameters   : Profile*: pointing to object, string: activity file name, int: unique id
  *
  * Return Value : none
  *
  * Description:
  *
  *   get user runType and creates the cooresponding object, then calls overloaded fill activity data function
  *		before returning to menu it prints the newly entered activity with calculations
  *		Then the activity data is written to the activity database file
  *
  */
void createActivity(Profile* user, const string fileName, int id)
{
	Activity* newAct = NULL;
	int type = 0;
	if (user->getRunType() == "Beginner") {
		type = 1;
		newAct = new Activity;
	}
	else if (user->getRunType() == "Intermediate"){
		type = 2;
		newAct = new IntermediateActivity;
	}
	else {
		type = 3;
		newAct = new ExpertActivity;
	}	
	system("CLS");
	drawActivityForm(type);
	newAct->enterData(screen);
	system("CLS");
	newAct->displayActivity(user);
	system("pause");
	fstream outFile(fileName, ios::out | ios::app);
	outFile << id << "$" << (*newAct);
	outFile.close();
}

/**
  * void printActivities(Profile* user, const string fileName, int id)
  *
  * Summary of the printActivites function:
  *
  *   prints all activities that belong to a user
  *
  * Parameters   : Profile*: pointing to object, string: activity file name, int: unique id
  *
  * Return Value : none
  *
  * Description:
  *
  *   get user runType and creates the cooresponding object, then reads through the file and compares ids, 
  *		if a match is found an activity object is filled and the program prints the newly entered activity with calculations
  *		This is done for the entire file
  *
  */
void printActivities(Profile* user, const string fileName, int id) {
	deque<Activity> activities;
	vector<string> entries;
	string entry;
	stringstream ss;
	ifstream inFile(fileName, ios::in);
	Activity* newAct = NULL;
	int type = 0;
	if (user->getRunType() == "Beginner") {
		type = 1;
		newAct = new Activity;
	}
	else if (user->getRunType() == "Intermediate") {
		type = 2;
		newAct = new IntermediateActivity;
	}
	else {
		type = 3;
		newAct = new ExpertActivity;
	}
	while (getline(inFile,entry)) {
		stringstream ss(entry);
		//breaking up sentence into words delimited by a space
		while (getline(ss, entry, '$'))
		{
			entries.push_back(entry);
		}
		if (stoi(entries.at(0)) == id) {
			newAct->readData(entries);
			newAct->displayActivity(user);
			cout << endl;
		}
		entries.clear();
	}
	inFile.close();
	system("pause");
}

// Screen Control Functions
// These functions use the windows console setCursorPosition function
// to create custom entry forms, these functions are for purely aesthetic reasons
void profileDataForm(HANDLE screen)
{
	placeCursor(screen, 5, 25);
	cout << "Full Name: " << endl;
	placeCursor(screen, 7, 25);
	cout << "Age: \t\tGender (M/F): \t\tWeight(lbs): " << endl;
	placeCursor(screen, 9, 25);
	cout << "Please enter your Date of Birth (MM/DD/YYYY): " << endl;
	placeCursor(screen, 12, 25);
	cout << "Describe your runner type (Beginner, Intermediate, Expert): " << endl;
}

void displayDataForm(Profile* user, HANDLE screen) {
	placeCursor(screen, 5, 25);
	cout << "Full Name: " << user->getFirstName() << " " << user->getLastName() << endl;
	placeCursor(screen, 7, 25);
	cout << "Age: "<< user->getAge() << "    \tGender (M/F): " << user->getGender() << "    \tWeight(lbs): " << user->getWeight() << endl;
	placeCursor(screen, 9, 25);
	cout << "Date of Birth (MM DD YYYY): " << endl;
	placeCursor(screen, 10, 25);
	cout << user->getDOB() << endl;
	placeCursor(screen, 12, 25);
	cout << "runner type (Beginner, Intermediate, Expert): " << endl;
	placeCursor(screen, 13, 25);
	cout << user->getRunType() << endl;
}

void drawRegistration(int switcher) {
	if (switcher == 0) {
		placeCursor(screen, 3, 25); // draws registration
		cout << "Please enter a unique username and password" << endl;
	}
	else {
		placeCursor(screen, 3, 25); // draws login
		cout << "Please enter your username and password" << endl;
	}
	placeCursor(screen, 4, 25);
	cout << "Username and Password cannot contain spaces" << endl;
	placeCursor(screen, 5, 25);
	cout << "-------------------------------------------" << endl;
	placeCursor(screen, 6, 30);
	cout << "username: " << endl;
	placeCursor(screen, 7, 30);
	cout << "password: " << endl;
}

void drawActivityForm(int switcher) {
	placeCursor(screen, 3, 25); // draws activity form
	cout << "Please fill out the fields below for your new Activity" << endl;
	placeCursor(screen, 4, 25);
	cout << "------------------------------------------------------" << endl;
	placeCursor(screen, 5, 30);
	cout << "Activity Name: " << endl;
	placeCursor(screen, 6, 30);
	cout << "Total Run Time: " << endl;
	placeCursor(screen, 7, 30);
	cout << "Hours:     Minutes:     Seconds:    " << endl;
	placeCursor(screen, 8, 30);
	cout << "Distance:        miles" << endl;
	if (switcher > 1) {
		placeCursor(screen,9, 30);
		cout << "Average Heart Rate:     bpm" << endl;
	}
	if (switcher > 2) {
		placeCursor(screen, 10, 30);
		cout << "Cadence:     spm " << endl;
	}
}

