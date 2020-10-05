// This is the base class for ExpertActivity
#pragma once
#include "Activity.h"

class IntermediateActivity : public Activity {
private:
	int avgHeartRate;
	string effortReport = "";
public:
	// Constructors
	IntermediateActivity();
	IntermediateActivity(string, int, int, int);

	// Getters and Setters
	int getHR();
	string getEffortReport();
	void setHR(int);

	// Member Functions
	virtual void enterData(HANDLE) override;
	string printInfo();
	// pace, calories burned
	void calcHRZone(int);
	virtual void displayActivity(Profile*) override;
	virtual void readData(vector<string>&) override;

	// File Handling
	virtual ostream& printFile(ostream& out) override;
};