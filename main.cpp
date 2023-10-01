// main.cpp
#include <iostream>
#include "UserRegistration.cpp"
#include "ItemManagement.cpp"
using namespace std;


void createBorrowersCSV(const string& filename) {
    // Open the CSV file for writing (create if it doesn't exist)
    ofstream file(filename);

    // Check if the file is opened successfully
    if (!file.is_open()) {
        cerr << "Error creating the file." << endl;
        return;
    }

    // Write the header row to the CSV file
    file << "userName,userRole,booksIssued,journalsIssued,publicationsIssued,timeDuration,dueTime,Location\n";

    // Close the file
    file.close();

    cout << "File 'borrowers.csv' created successfully with the specified details." << endl;
}

void addBorrowerData(const string& filename, const vector<string>& data) {
    ofstream file(filename, ios::app);  // Open the CSV file for appending

    // Check if the file is opened successfully
    if (!file.is_open()) {
        cerr << "Error opening the file for appending." << endl;
        return;
    }
    


    // Write the borrower data to the CSV file
    for (const auto& field : data) {
        file << field << ",";
    }
    file << "\n";  // End the line

    // Close the file
    file.close();

    cout << "Borrower data added successfully to 'borrowers.csv'." << endl;
}


string getDueDate(string date, string userRole, string location){
        std::vector<std::string> tokens;
        std::istringstream iss(date);
        std::string token;

        while (std::getline(iss, token, '-')) {
            tokens.push_back(token);
        }

        int day, month, year;
        day = stoi(tokens[0]);
        month = stoi(tokens[1]);
        year = stoi(tokens[2]);

        if (userRole=="s"){
            month += 1;
            if (month>12){
                month = month - 12;
                year += 1;
            }
            
        }
        else if (userRole=="f"){
            month += 6;
            if (month>12){
                month = month - 12;
                year += 1;
            }
            
        }   

        if(location!="IIITD Library"){
            day = day + 7;
            if (day>30){
                day = day - 30;
                month = month + 1;
                if (month>12){
                    month = month - 12;
                    year = year + 1;
                }

            }
        }

        string due_date = to_string(day) + "-" + to_string(month) + "-" + to_string(year);
        
        return due_date;
    }

int main() {
    string userRole;

    // Get user role (faculty or student)
    cout << "Are you a faculty or a student? (Type 'f' for faculty, 's' for student): ";
    getline(cin, userRole);

    if (userRole != "f" && userRole != "s") {
        cerr << "Invalid role. Please run the program again and provide a valid role." << endl;
        return 1;  // Exit with an error code
    }

    // Determine the filename based on the user role
    const string filename = (userRole == "f") ? "faculties.csv" : "students.csv";

    // Create or open the CSV file
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cerr << "Error opening the file: " << filename << endl;
        return 1;  // Exit with an error code
    }
    file.close();  // Close the file

    // Register a new user (faculty or student)
    // Get user input
    string name;
        cout << "Enter your name: ";
        getline(cin, name);

    UserRegistration::registerUser(filename, userRole, name);

    // Ask for registration data
    string date;
    cout << "Enter Today's Date (DD-MM-YYYY): ";
    getline(cin, date);
    
    // Ask the user to borrow an item
    string itemType;
    cout << "To borrow a book, type 1; to borrow a journal, type 2; to borrow a publication, type 3: ";
    getline(cin, itemType);

    // const string userType = (userRole == "f") ? "faculty" : "student";

    vector<string> selectedBook, selectedJournal, selectedPublication;

    switch (itemType[0]) {
        case '1':
            selectedBook = ItemManagement::searchBooksByTitle("books", userRole, name);
            break;
        case '2':
            selectedJournal = ItemManagement::searchJournals("journals", userRole, name);
            break;
        case '3':
            selectedPublication = ItemManagement::searchJournals("publications", userRole, name);
            break;
        default:
            cout << "Invalid choice. No item borrowed." << endl;
    }


    string book, journal, publication, location = "";

    // Print the selected book information
    if (!selectedBook.empty()) {
        cout << "Selected Book (Index " << selectedBook[0] <<"th row"<< "): ";
        cout << "Title: " << selectedBook[1] << ", ";
        cout << "Author(s): " << selectedBook[2] << endl;

        book = selectedBook[0] + " " + selectedBook[1] + " " + selectedBook[2];
        location = selectedBook[3];

    } 
    // else {
    //     cout << "No matching books found." << endl;
    // }

    // Print the selected journal information
    if (!selectedJournal.empty()) {
        cout << "Selected journal (Index " << selectedJournal[0] <<"th row"<< "): ";
        cout << "Title: " << selectedJournal[1] << ", ";

        journal = selectedJournal[0] + " " + selectedJournal[1];
        location = selectedBook[3];

    } 
    // else {
    //     cout << "No matching journal found." << endl;
    // }

    // Print the selected pulication information
    if (!selectedPublication.empty()) {
        cout << "Selected pulication (Index " << selectedPublication[0] <<"th row"<< "): ";
        cout << "Title: " << selectedPublication[1] << ", ";
        publication = selectedPublication[0] + " " + selectedPublication[1];
        location = selectedBook[3];
    } 
    // else {
    //     cout << "No matching pulication found." << endl;
    // }

    
    
    string dueDate = getDueDate(date, userRole, location);
    cout<<"book due date: "<<dueDate<<endl;
    cout<<"book registerd to: "<<location<<endl;
    

    vector<string> data;

    data.push_back(name);
    data.push_back(userRole);
    data.push_back(book);
    data.push_back(journal);
    data.push_back(publication);
    string duration = (userRole == "s") ? "1 month" : "6 month";
    data.push_back(duration);
    // data.push_back(date);
    data.push_back(dueDate);
    data.push_back(location);

    



    // Check if the file exists
    ifstream fileCheck("borrowers.csv");
    if (fileCheck.good()) {
        // File exists, add data to the existing file
        addBorrowerData("borrowers.csv", data);
    } else {
        // File doesn't exist, create it and add data
        createBorrowersCSV("borrowers.csv");
        addBorrowerData("borrowers.csv", data);
    }


    return 0;  // Exit successfully
}
