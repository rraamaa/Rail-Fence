#include <iostream>
#include <regex>

using namespace std;

void cipherEncryption();
void cipherDecryption();


int main() {
	cout << "\n\n** Rail Fence Cipher Programming **\n";
	int choice;

	do {
		cout << "1. Encryption. \n2. Decryption. \n3. Exit.\n Choose(1,2,3): ";
		

		cin >> choice;
		cin.ignore();

		if (choice == 1) {
			cout << "\n*** Encryption ***";
			cipherEncryption();
		}
		else if (choice == 2) {
			cout << "\n*** Decryption ***";
			cipherDecryption();
		}
		else if (choice == 3) {
			cout << "\nExiting program...\n";
		}
		else {
			cout << "\nInvalid choice! Please enter 1, 2, or 3.\n";
		}

	} while (choice != 3); // Repeat until user enters 3

	return 0;

}


// Encryption Function
void cipherEncryption() {
	string message;
	cout << "\n Enter message : ";
	getline(cin, message);

	//remove white space from message :
	message = regex_replace(message, regex("\\s+"), "");

	cout << "\nEntwr key (number of rails or levels): ";
	int key;
	cin >> key;
	cin.ignore();

	//Creating Dynamic empty matrix : 
	char** railMatrix = new char* [key];

	for (int i = 0; i < key; i++) {
		railMatrix[i] = new char[message.length()]; // Allocate memory for columns
		for (int j = 0; j < message.length(); j++) {
			railMatrix[i][j] = '.';
		}
	}


	// testing newly created matrix : 
	/*
	cout << "\nRail Matrix:\n";
	for (int i = 0; i < key; i++) {
		for (int j = 0; j < message.length(); j++) {
			cout << railMatrix[i][j] << "\t";
		}
		cout << endl;
	}
	*/

	// puting message letters one by one in rail matrix in zig-zag
	int row = 0;
	int check = 0;

	for (int i = 0; i < message.length(); i++) {
		if (check == 0){
			railMatrix[row][i] = message[i];
			row++;
			if (row == key) {
				check = 1;
				row--;
			} // inner if

		} // if
		else if (check == 1) {
			row--;
			railMatrix[row][i] = message[i];
			if (row == 0) {
				check = 0;
				row = 1;
			}
		} // else if
        
	}// end for enternal

	// test : 
    /*
	
	for (int i = 0; i < key; i++) {		
		for (int j = 0; j < message.length(); j++) {			
			cout << railMatrix[i][j] << "\t";
		}
		cout << endl;
	}
	*/

	// creating encrypted text ;

	string encryptText = "";
	for (int i = 0; i < key; i++) {
		for (int j = 0; j < message.length(); j++) {
			encryptText += railMatrix[i][j];
		}
		cout << endl;
	}

	//removing '.' from encrypted text
	encryptText = regex_replace(encryptText, regex("\\."), "");
	cout << "Encrypted text : " << encryptText << "\n\n";

	// freeing allocated memory 
	for (int i = 0; i < key; i++) {
		delete[] railMatrix[i];
	}
	delete[] railMatrix;


}


//Decryption Function
void cipherDecryption() {

	string message;
	cout << "\n Enter message : ";
	getline(cin, message);

	//remove white space from message :
	message = regex_replace(message, regex("\\s+"), "");

	cout << "\nEntwr key (number of rails or levels): ";
	int key;
	cin >> key;
	cin.ignore();

	//Creating Dynamic empty matrix : 
	char** railMatrix = new char* [key];

	for (int i = 0; i < key; i++) {
		railMatrix[i] = new char[message.length()]; // Allocate memory for columns
		for (int j = 0; j < message.length(); j++) {
			railMatrix[i][j] = '.';
		}
	}


	// testing newly created matrix : 
	/*
	cout << "\nRail Matrix:\n";
	for (int i = 0; i < key; i++) {
		for (int j = 0; j < message.length(); j++) {
			cout << railMatrix[i][j] << "\t";
		}
		cout << endl;
	}
	*/

	// puting message letters one by one in rail matrix in zig-zag
	int row = 0;
	int check = 0;

	for (int i = 0; i < message.length(); i++) {
		if (check == 0) {
			railMatrix[row][i] = message[i];
			row++;
			if (row == key) {
				check = 1;
				row--;
			} // inner if

		} // if
		else if (check == 1) {
			row--;
			railMatrix[row][i] = message[i];
			if (row == 0) {
				check = 0;
				row = 1;
			}
		} // else if

	}// end for enternal

	// test : 
	/*

	for (int i = 0; i < key; i++) {
		for (int j = 0; j < message.length(); j++) {
			cout << railMatrix[i][j] << "\t";
		}
		cout << endl;
	}
	*/

	// re-ordering rails: 
	int order = 0;
	for (int i = 0; i < key; i++) {
		for (int j = 0; j < message.length(); j++) {
			string temp = "";
			temp += railMatrix[i][j];
			if (regex_match(temp, regex("\\."))) {
				continue; //skipping
			}
			else {
				// adding cipher letters one by one diagonally:
				railMatrix[i][j] = message[order];
				order++;
			}

		} // inner for
	}//for

	//testing re-ordering : 
	/*
	for (int i = 0; i < key; i++) {
		for (int j = 0; j < message.length(); j++) {
			cout << railMatrix[i][j] << "\t";
		}
		cout << endl;
	}
	*/

	// Converting rows back into a message of single line
	string decryptText = "";
	check = 0;
	row = 0;
	for (int i = 0; i < message.length(); i++) {
		if (check == 0) {
			decryptText += railMatrix[row][i];
			row++;

			if (row == key) {
				check = 1;
				row--;
			}//inner if
		}// if 
		else if (check == 1) {
			row--;
			decryptText += railMatrix[row][i];
			if (row == 0) {
				check = 0;
				row = 1;
			}
		}// else if

	}// for



	//removing '.' from decrypted text
	decryptText = regex_replace(decryptText, regex("\\.+"), "");
	cout << "\ndecrypt Text : " << decryptText << "\n\n";

	// freeing allocated memory 
	for (int i = 0; i < key; i++) {
		delete[] railMatrix[i];
	}
	delete[] railMatrix;
	
}