#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>

void ResetIndexValues();
void CreateAllLoansFile();
void CreateAdminCredentialsFile();

void main() {
	ResetIndexValues();
	CreateAllLoansFile();
	CreateAdminCredentialsFile();
}

void ResetIndexValues() {
	int value;

	value = 1;

	int fd1 = open("/home/eshwar-chawda/Desktop/Online-Banking-System/data/customerindexes", O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	int fd2 = open("/home/eshwar-chawda/Desktop/Online-Banking-System/data/employeeindexes", O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

	write(fd1, &value, sizeof(value));
	write(fd2, &value, sizeof(value));

	close(fd1);
	close(fd2);
}

void CreateAllLoansFile() {
	int fd = creat("/home/eshwar-chawda/Desktop/Online-Banking-System/data/allloans", S_IRUSR | S_IWUSR);
	close(fd);
}

void CreateAdminCredentialsFile() {
	Credentials creds;

	strcpy(creds.loginId, "admin");
	strcpy(creds.password, "123");

	int fd = open("/home/eshwar-chawda/Desktop/Online-Banking-System/data/credentials", O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

	write(fd, &creds, sizeof(Credentials));

	close(fd);
}