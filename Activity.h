// This is the base class for IntermediateActivity
#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include "ScreenControll.h"
#include "Profile.h"

using namespace std;

class Activity {
private:
	string name;
	int time;
	double distance;
	int paceTime;
	string pace;
	int calories;
protected:
	// MET is the Metabolic Equivalent of Task, this is used to estimate calories burnt
	const double MET_Table[15] = { 4.5, 6, 8.3, 9, 9.8, 10.5, 11, 11.8, 12.3, 12.8, 14.5, 16, 19, 19.8, 23 };
	const double MET_Pace[16] =  {100, 15, 12, 11.5, 10, 9, 8.5, 7.5, 7, 6.5, 6, 5.5, 5, 4.6, 4.3, 0};
public:

	// Constructors
	Activity();
	Activity(string,int, int);

	// Getters and Setters
	string getName();
	int getTime();
	double getDistance();
	int getCalories();
	string getPace();

	void setName(string);
	void setTime(int);
	void setDistance(double);

	// Member Functions
	virtual void enterData(HANDLE);
	string printInfo();
	string calcPace();
	void calcCalories(int, char,int);
	virtual void displayActivity(Profile*);
	virtual void readData(vector<string>&);

	// Writing to file
	friend ostream& operator<<(ostream& out, Activity& act);
	virtual ostream& printFile(ostream& out);
};
