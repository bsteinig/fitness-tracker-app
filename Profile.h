#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "ScreenControll.h"
#include "Login.h"

using namespace std;

static string classification[] = { "Beginner", "Intermediate", "Expert" };


class Profile
{
private:
	int userId;			//Unique user id for retrieval
	string firstName;	//User first name
	string lastName;	//User last name
	int age;
	int weight;
	string dateAge;		//Date of Birth
	string runType;		//bound between 0-2
	char gender;		//User gender
	Login loginInfo;	//user login
public:
	//Profile Constructor
	Profile();

	~Profile();
	// Getters & Setters
	int getUserID();
	string getFirstName();
	string getLastName();
	int getAge();
	int getWeight();
	string getDOB();
	string getRunType();
	char getGender();
	string getUsername();
	string getPassword();
	

	void setUserID(int);
	void setFirstName(string);
	void setLastName(string);
	void setAge(int);
	void setWeight(int);
	void setDOB(string);
	void setRunType(string);
	void setGender(char);
	void setUsername(string);
	void setPassword(string);

	// Member Functions
	void enterUserInfo(HANDLE);

	void writeLoginInfo(ostream&); // Prints only the login object to file

	friend ostream& operator<<(ostream&, const Profile&); // prints the profile object to file without the login object
};