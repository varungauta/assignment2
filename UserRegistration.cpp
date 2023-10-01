// UserRegistration.cpp
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
class UserRegistration {
public:
    static bool nameExists(const string& filename, const string& name) {
        ifstream inFile(filename);

        if (!inFile.is_open()) {
            cerr << "Error opening the file: " << filename << endl;
            return false;
        }

        string line;
        while (getline(inFile, line)) {
            istringstream iss(line);
            string currentName;
            getline(iss, currentName, ',');

            if (currentName == name) {
                inFile.close();
                return true;  // Name found
            }
        }

        inFile.close();
        return false;  // Name not found
    }

    static void registerUser(const string& filename, const string& userRole, const string& name) {
        ofstream outFile;
        outFile.open(filename, ios::app);  // Open the file in append mode

        if (!outFile.is_open()) {
            cerr << "Error opening the file: " << filename << endl;
            return;
        }

        string  phoneNumber;


        // Check if the name already exists
        if (nameExists(filename, name)) {
            cout << "Congratulations! Your name (" << name << ") already exists in the system." << endl;

        } else {
            // Get phone number for registration
            cout << "Enter your phone number: ";
            getline(cin, phoneNumber);

            // Write user information to the file
            outFile << name << "," << phoneNumber << endl;

            cout << "Registration successful. User information has been stored in " << filename << endl;
        }

        // Close the file
        outFile.close();
    }
};
