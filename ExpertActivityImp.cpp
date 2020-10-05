#include "IntermediateActivity.h"
#include "ExpertActivity.h"
#include "Activity.h"

// Constructors
ExpertActivity::ExpertActivity() : IntermediateActivity(){
	avgCadence = 0;
}

ExpertActivity::ExpertActivity(string sName, int sTime, int sDistance, int sHeartRate, int sCadence) : IntermediateActivity(sName, sTime, sDistance, sHeartRate) {
	avgCadence = sCadence;
}

// Getters and Setters
int ExpertActivity::getCadence() {
	return avgCadence;
}

void ExpertActivity::setCadence(int sCadence) {
	avgCadence = sCadence;
}

// Member Functions
// Stride length = Distance (ft.) /  Total Steps Taken
void ExpertActivity::calcStrideLength() {
	stringstream sLength;
	int dist = (this->getDistance()) * 5280;
	int steps = avgCadence * (this->getTime()/60);
	double stride = dist / steps;
	sLength << stride << " ft.";
	strideLength = sLength.str();
}

void ExpertActivity::enterData(HANDLE screen)
{
	string name;
	double distance;
	int hours, mins, secs, time , hr;
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
	cin >> hr;
	placeCursor(screen, 10, 39);
	cin >> avgCadence;
	this->setName(name);
	this->setTime(time);
	this->setDistance(distance);
	this->setHR(hr);
}

string ExpertActivity::printInfo() {
	stringstream printer;
	printer << this->getName() << " | " << this->getTime() << " | " << this->getDistance() << " | " << calcPace() << " | " << this->getCalories() << endl << this->getEffortReport() << strideLength <<  endl;
	return printer.str();
}

void ExpertActivity::displayActivity(Profile* user) {
	int sec, hours, min;
	min = this->getTime() / 60;
	sec = this->getTime() % 60;
	hours = min / 60;
	min = min % 60;
	calcCalories(user->getWeight(), user->getGender(), user->getAge());
	calcHRZone(user->getAge());
	calcStrideLength();
	cout << (left) << this->getName() << endl;
	cout << setw(2) << setfill('0') << (right) << hours << ":" << min << ":" << sec << " Distance: " << setfill(' ') << fixed << setprecision(2) << setw(6) << this->getDistance() << " mi.  Pace: " << this->calcPace() << endl;
	cout << this->getCalories() << " Calories burned " << fixed << setprecision(2) << strideLength << " stride length" << endl;
	cout << this->getEffortReport() << endl;
}

void ExpertActivity::readData(vector<string>& data) {
	this->setName(data.at(1));
	this->setTime(stoi(data.at(2)));
	this->setDistance(stod(data.at(3)));
	this->setHR(stoi(data.at(4)));
	avgCadence = stoi(data.at(5));
}

// File Handling
ostream& ExpertActivity::printFile(ostream& out)
{
	out << getName() << "$" << getTime() << "$" << getDistance() << "$" << getHR() << "$" << avgCadence << endl;
	return out;
}