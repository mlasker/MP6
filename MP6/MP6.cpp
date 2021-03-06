// String/name manipulator program 
//			by: Mark Lasker


#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

void print(string rawName, string formattedName);

enum Married {
	SINGLE, MARRIED, DIVORCED
};


Married isMarried(string s) {

	Married married;

	if (s == "M") {
		 married = MARRIED;
	}
	else if (s == "S") {
		married = SINGLE;
	}
	else if (s == "D") {
		married = DIVORCED;
	}

	return married;
}

string formatName(string gen, Married mar, string lN, string fN, string mI) {

	string formattedString;

	if (gen == "M") {
		formattedString += "Mr. ";
	}
	else if (gen == "F" && (mar == 0|| mar == 2)) {
		formattedString += "Ms. ";
	}
	else
		formattedString += "Mrs. ";

	formattedString += fN + " ";

	if (mI != " ") {
		formattedString += mI + " ";
	}

	formattedString += lN;

	return formattedString;
}

void process() {

	ifstream infile;
	infile.open("mp6names.txt");

	string gender;
	//string maritalStatus;
	string lastName;
	string firstName;
	string middleInit;
	Married maritalStatus;
	string strFull;

	while (getline(infile, strFull)) {
		gender = strFull.substr(0, 1);
		maritalStatus = isMarried(strFull.substr(1, 1));
		string str = strFull.substr(2);
		string::size_type pos1 = str.find_first_not_of(" ");
		string::size_type pos2 = str.find(",");

		//Retrieve last name from line by using pos1 & pos2 variables to create substring from the first non-blank char to one space before
		//the comma for the last name
		lastName = str.substr(pos1, (pos2 - pos1));

		//to trim off last name from original string and then locate the first non-empty space in newString
		string newStr = str.substr(pos2 + 1);
		pos1 = newStr.find_first_not_of(" ");

		//Locate first name
		firstName = newStr.substr(pos1, newStr.substr(pos1).find(" "));

		//Routine to find last instance of white space, then read in anything after that into string - if string is NOT blank print out as middle name
		string findMidInit = str.substr((str.find_last_of(" ")) + 1);
		if (findMidInit != " ") {
			middleInit = findMidInit;
		}

		string formattedName = formatName(gender, maritalStatus, lastName, firstName, middleInit);

		print(str, formattedName);
	}
}

void print(string rawName, string formattedName) {

	cout << "**************************************************" << endl;
	cout << "Unformatted name: " << rawName << endl;
	cout << "Formatted name: " << formattedName << endl;
}

int main()
{
	process();

	return 0;
}