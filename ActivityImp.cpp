#include "Activity.h"


// Constructors
Activity::Activity()
{
	name = "";
	time = 0;
	distance = 0;
}

Activity::Activity(string sName, int sTime, int sDistance)
{
	name = sName;
	time = sTime;
	distance = sDistance;
}

// Getters and Setters
string Activity::getName()
{
	return name;
}

int Activity::getTime()
{
	return time;
}

double Activity::getDistance()
{
	return distance;
}

int Activity::getCalories()
{
	return calories;
}

string Activity::getPace()
{
	return pace;
}

void Activity::setName(string sName)
{
	name = sName;
}

void Activity::setTime(int sTime)
{
	time = sTime;
}

void Activity::setDistance(double sDistance)
{
	distance = sDistance;
}

// Member Functions

string Activity::calcPace() {
	string pace;
	stringstream ss;
	int paceS, sec, hours, min;

	paceS = time / distance;
	paceTime = paceS;

	min = paceS / 60;
	sec = paceS % 60;
	hours = min / 60;
	min = min % 60;

	ss << setw(2) << setfill('0') << hours << setw(1) << ":" << setw(2) << min << setw(1) << ":" << setw(2) << sec << setfill(' ') << " per mile";
	pace = ss.str();
	return pace;
}

void Activity::calcCalories(int weight, char gender, int age) {
	int cal= 0;
	int mTime = time / 60;
	double kgWeight = weight / 2.205;
	double min = paceTime / 60;
	double metVal = 4.5;
	for (int i = 0; i < 15; i++) {
		if (MET_Pace[i] >= min && MET_Pace[i + 1] <= min) {
			metVal = MET_Table[i];
		}
	}
	cal = (mTime * (metVal * 0.0175 * kgWeight)) + (31 - age); // This equation is an estimation, it is most accurate at ages close to 31
	if (gender == 'f' || gender == 'F') {
		cal = cal * .9;
	}
	calories = cal;
}

void Activity::enterData(HANDLE screen)
{
	int hours, mins, secs;
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
}

string Activity::printInfo() {
	stringstream printer;
	printer << name << " | " << time << " | " << distance << " | " << calcPace() << " | " << calories << endl;
	return printer.str();
}

void Activity::displayActivity(Profile* user) {
	int sec, hours, min;
	min = time / 60;
	sec = time % 60;
	hours = min / 60;
	min = min % 60;
	calcCalories(user->getWeight(), user->getGender(), user->getAge());
	cout << (left) << name << endl;
	cout << setw(2) << setfill('0') << (right) << hours << ":" << min << ":" << sec << " Distance: " << setfill(' ') << fixed << setprecision(2) << setw(6) << distance << " mi.  Pace: " << calcPace() << endl;
	cout << calories << " Calories burned " << endl;
}

void Activity::readData(vector<string>& data) {
	name = data.at(1);
	time = stoi(data.at(2));
	distance = stod(data.at(3));
}

// File Handling
ostream& operator<<(ostream& out, Activity& act)
{
	return act.printFile(out);
}

ostream& Activity::printFile(ostream& out) 
{
	out << name << "$" << time << "$" << distance << endl;
	return out;
}

