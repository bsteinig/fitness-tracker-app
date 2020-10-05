#pragma once
#include <string>
#include <Windows.h>

using namespace std;

class Login {
private:
	string username;
	string password;
public:
	Login();
	~Login();

	void setUsername(string);
	void setPassword(string);

	string getUsername();
	string getPassword();

};