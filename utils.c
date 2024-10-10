#include "utils.h"

#include <string.h>

const char *serveripAddress = "127.0.0.1";

const char *clientMenu = "Enter log-in type: \n 1. Customer \n 2. Bank Employee \n 3. Manager \n 4. Administrator \n 5. Exit \n Enter your choice : ";
const char *loginIdLabel = "\nEnter login Id : ";
const char *passwordLabel = "\nEnter Password : ";

int clientMenuLength;
int loginIdLabelLength;
int passwordLabelLength;

void init() {
	clientMenuLength = strlen(clientMenu);
	loginIdLabelLength = strlen(loginIdLabel);
	passwordLabelLength = strlen(passwordLabel);
}