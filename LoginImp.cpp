#include "Login.h"

Login::Login() {
	username = "placeholder";
	password = "";
}

Login::~Login() {

}

void Login::setUsername(string use) {
	username = use;
}

void Login::setPassword(string pas) {
	password = pas;
}

string Login::getUsername() {
	return username;
}

string Login::getPassword() {
	return password;
}