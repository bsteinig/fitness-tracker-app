#pragma once
#include "Activity.h"
#include "IntermediateActivity.h"

class ExpertActivity : public IntermediateActivity {
private:
	int avgCadence;
	string strideLength = "";
public:
	// Constructors
	ExpertActivity();
	ExpertActivity(string, int, int, int, int);

	// Getters and Setters
	int getCadence();
	void setCadence(int);

	// Member functions
	virtual void enterData(HANDLE) override;
	string printInfo();
	void calcStrideLength();
	virtual void displayActivity(Profile*) override;
	virtual void readData(vector<string>&) override;

	// File Handling
	virtual ostream& printFile(ostream&) override;
};
