#include "Profile.h"
#include "Login.h"


Profile::Profile() : loginInfo() {
	userId = 0;
	firstName = "";
	lastName = "";
	age = 0;
	weight = 0;
	dateAge = "";
	runType = "";
	gender = ' ';
}

Profile::~Profile() {

}

// Getters & Setters

int Profile::getUserID() {
	return userId;
}

string Profile::getFirstName() {
	return firstName;
}

string Profile::getLastName() {
	return lastName;
}

int Profile::getAge() {
	return age;
}

int Profile::getWeight() {
	return weight;
}

string Profile::getDOB() {
	return dateAge;
}

string Profile::getRunType() {
	return runType;
}

char Profile::getGender() {
	return gender;
}

string Profile::getUsername() {
	return loginInfo.getUsername();
}

string Profile::getPassword() {
	return loginInfo.getPassword();
}

//Setters
void Profile::setUserID(int iD) {
	userId = iD;
}

void Profile::setFirstName(string fName) {
	firstName = fName;
}

void Profile::setLastName(string lName) {
	lastName = lName;
}

void Profile::setAge(int pAge) {
	age = pAge;
}

void Profile::setWeight(int pWeight) {
	weight = pWeight;
}

void Profile::setDOB(string dob) {
	dateAge = dob;
}

void Profile::setRunType(string rType) {
	runType = rType;
}

void Profile::setGender(char gen) {
	gender = gen;
}

void Profile::setUsername(string user) {
	loginInfo.setUsername(user);
}

void Profile::setPassword(string pass) {
	loginInfo.setPassword(pass);
}

// Member Functions

void Profile::enterUserInfo(HANDLE screen)
{
	placeCursor(screen, 3, 25);
	cout << "-------Register New User-------" << endl;
	placeCursor(screen, 5, 36);
	cin >> firstName >> lastName;
	placeCursor(screen, 7, 30);
	cin >> age;
	placeCursor(screen, 7, 55);
	cin >> gender;
	placeCursor(screen, 7, 80);
	cin >> weight;
	setGender(toupper(getGender()));
	placeCursor(screen, 10, 26);
	cin >> dateAge;
	placeCursor(screen, 13, 26);
	cin >> runType;
}

void Profile::writeLoginInfo(ostream& out)
{
	out << userId << " " << loginInfo.getUsername() << " " << loginInfo.getPassword() << endl;
}

ostream& operator<<(ostream& out, const Profile& proF) {
	out << proF.userId << " " << proF.firstName << " " << proF.lastName << " " << proF.age << " " << proF.weight << " " << proF.gender << " " << proF.dateAge << " " << proF.runType << endl;
	return out;
}
