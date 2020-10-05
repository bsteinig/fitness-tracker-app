#include "IntermediateActivity.h"
#include "Activity.h"

// Constructors

IntermediateActivity::IntermediateActivity() : Activity() {
	avgHeartRate = 0;
}

IntermediateActivity::IntermediateActivity(string sName, int sTime, int sDistance, int sHeartRate) : Activity(sName, sTime, sDistance) {
	avgHeartRate = sHeartRate;
}

// Getters and Setters
int IntermediateActivity::getHR() {
	return avgHeartRate;
}

string IntermediateActivity::getEffortReport() {
	return effortReport;
}

void IntermediateActivity::setHR(int sHeartRate) {
	avgHeartRate = sHeartRate;
}

// Member Functions
void IntermediateActivity::calcHRZone(int age) {
	stringstream zone;
	int eF = 0;
	int maxHr = 220 - age; // Max Heart Rate is typically 220 - age
	int target = .7 * maxHr;
	eF = (avgHeartRate / 220.0) * 100.0; // Effort is based on percentage of Max HR
	int bottomRange, topRange;
	bottomRange = .55 * maxHr;	// A good heart rate range is between 55 and 85% of your max Heart Rate
	topRange = .85 * maxHr;
	if (avgHeartRate < topRange && avgHeartRate > bottomRange) {
		if (avgHeartRate > target) {
			zone << "Great job! This was run was within your target HR range: " << bottomRange << " bpm to " << topRange << " bpm\nThis run was more strenuous than usual, make sure to rest well before your next activity" << endl;
		}
		else {
			zone << "Great job! This was run was within your target HR range: " << bottomRange << " bpm to " << topRange << " bpm" << endl;
		}
	}
	else if (avgHeartRate < bottomRange) {
		zone << "Keep Going! This was run was below your target HR range : " << bottomRange << " bpm to " << topRange << " bpm" << endl;
	}
	else {
		zone << "Watch out! This was run was above your target HR range: " << bottomRange << " bpm to " << topRange << " bpm\nThis run was more strenuous than usual, make sure to rest well before your next activity" << endl;
	}
	zone << "You were at: " << eF << "% of your Max aerobic heart rate." << endl;
	effortReport = zone.str();
}

// Overloaded enterData
void IntermediateActivity::enterData(HANDLE screen)
{
	string name;
	double distance;
	int hours, mins, secs, time;
	cin.ignore();
	placeCursor(screen, 5, 46);
	getline(cin, name);
	placeCursor(screen, 7, 38);
	cin >> hours;
	placeCursor(screen, 7, 50);
	cin >> mins;
	placeCursor(screen, 7, 63);
	cin >> secs;
	time = secs + (mins * 60) + (hours * 3600);
	placeCursor(screen, 8, 40);
	cin >> distance;
	placeCursor(screen, 9, 50);
	cin >> avgHeartRate;
	this->setName(name);
	this->setTime(time);
	this->setDistance(distance);
}

// Overloaded data print
string IntermediateActivity::printInfo() {
	stringstream printer;
	printer << this->getName() << " | " << this->getTime() << " | " << this->getDistance() << " | " << calcPace() << " | " << this->getCalories() << endl << effortReport << endl;
	return printer.str();
}

// overrided display Activity
void IntermediateActivity::displayActivity(Profile* user) {
	int sec, hours, min;
	min = this->getTime() / 60;
	sec = this->getTime() % 60;
	hours = min / 60;
	min = min % 60;
	calcCalories(user->getWeight(), user->getGender(), user->getAge());
	calcHRZone(user->getAge());
	cout << (left) << this->getName() << endl;
	cout << setw(2) << setfill('0') << (right) << hours << ":" << min << ":" << sec << " Distance: " << setfill(' ') << fixed << setprecision(2) << setw(6) << this->getDistance() << " mi.  Pace: " << this->calcPace() << endl;
	cout << this->getCalories() << " Calories burned " << endl;
	cout << this->getEffortReport() << endl;
}

void IntermediateActivity::readData(vector<string>& data) {
	this->setName(data.at(1));
	this->setTime(stoi(data.at(2)));
	this->setDistance(stod(data.at(3)));
	avgHeartRate = stoi(data.at(4));
}

// File Handling
ostream& IntermediateActivity::printFile(ostream& out) 
{
	out << getName() << "$" << getTime() << "$" << getDistance() << "$" << avgHeartRate << endl;
	return out;
}