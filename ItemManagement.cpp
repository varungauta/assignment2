// ItemManagement.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>
using namespace std;
class ItemManagement
{
public:
    static bool itemExists(const string &filename, const string &itemName)
    {
        ifstream inFile(filename);

        if (!inFile.is_open())
        {
            cerr << "Error opening the file: " << filename << endl;
            return false;
        }

        string line;
        while (getline(inFile, line))
        {
            istringstream iss(line);
            string currentItemName, availability;
            getline(iss, currentItemName, ',');
            getline(iss, availability, ',');

            if (currentItemName == itemName && availability == "available")
            {
                inFile.close();
                return true; // Item found and available
            }
        }

        inFile.close();
        return false; // Item not found or not available
    }

    static void updateItemStatus(const string &filename, const string &itemName)
    {
        ifstream inFile(filename);
        ofstream tempFile("temp.csv", ios::out);

        if (!inFile.is_open() || !tempFile.is_open())
        {
            cerr << "Error opening the file: " << filename << endl;
            return;
        }

        string line;
        while (getline(inFile, line))
        {
            istringstream iss(line);
            string currentItemName, availability;
            getline(iss, currentItemName, ',');
            getline(iss, availability, ',');

            if (currentItemName == itemName)
            {
                tempFile << currentItemName << ",borrowed" << endl;
            }
            else
            {
                tempFile << line << endl;
            }
        }

        inFile.close();
        tempFile.close();

        // Rename temp file to the original filename
        rename("temp.csv", filename.c_str());
    }

    // Convert a string to lowercase
    static string toLowercase(const string &str)
    {
        string result = str;
        transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

    static set<int> getRandomIndex(int ub, int lb, int size){
        set<int> idx_set;
        for (int j=0; j<size; j++){
            idx_set.insert((rand() % (ub - lb + 1)) + lb);
        }
        return idx_set;
        
            
    }

    static vector<string> searchBooksByTitle(const string &filename, const string &userRole, const string &userName)
    {

        vector<string> result; // Vector to store selected book information

        string searchTitle;

        // Get user input for the item name
        cout << "Enter the name of the " << filename << ": ";
        getline(cin, searchTitle);

        // Open the CSV file
        ifstream file(filename + ".csv");

        // Check if the file is opened successfully
        if (!file.is_open())
        {
            cerr << "Error opening the file." << endl;
            return result;
        }

        vector<vector<string>> data; // Vector to store CSV data

        // Read the CSV file line by line
        string line;

        // Read the header row to get the column indices
        if (getline(file, line))
        {
            istringstream iss(line);
            vector<string> header;

            // Parse the CSV header
            while (iss)
            {
                string field;
                if (!getline(iss, field, ','))
                {
                    break;
                }
                header.push_back(field);
            }

            
            // Find the index of the "title" column
            auto titleColumnIt = find(header.begin(), header.end(), "title");
            if (titleColumnIt == header.end())
            {
                cerr << "Error: 'title' column not found in the header." << endl;
                return result;
            }
            size_t titleColumnIndex = distance(header.begin(), titleColumnIt);

            // Find the index of the "authors" column
            auto authorsColumnIt = find(header.begin(), header.end(), "authors");
            if (authorsColumnIt == header.end())
            {
                cerr << "Error: 'authors' column not found in the header." << endl;
                return result;
            }
            size_t authorsColumnIndex = distance(header.begin(), authorsColumnIt);

            // Read the remaining rows
            while (getline(file, line))
            {
                istringstream iss(line);
                vector<string> record;

                // Parse the CSV line
                while (iss)
                {
                    string field;
                    if (!getline(iss, field, ','))
                    {
                        break;
                    }
                    record.push_back(field);
                }

                // Add the record to the data vector
                data.push_back(record);
            }

            // Close the file
            file.close();

            // Convert the search title to lowercase
            string lowercaseSearchTitle = toLowercase(searchTitle);

            // Search for books with the specified title
            cout << "Searching for books with title containing: " << searchTitle << endl;

            vector<size_t> matchingIndexes;
            for (size_t i = 0; i < data.size(); ++i)
            {
                // Convert the current title field to lowercase
                string lowercaseTitle = toLowercase(data[i][titleColumnIndex]);

                // Check if the lowercase search title is present in the lowercase title
                if (lowercaseTitle.find(lowercaseSearchTitle) != string::npos)
                {
                    // Print the matching title and author
                    cout << "Index " << matchingIndexes.size() + 1 << ": ";
                    cout << "Title: " << data[i][titleColumnIndex] << ", ";
                    cout << "Author(s): " << data[i][authorsColumnIndex] << endl;

                    // Save the index for later selection
                    matchingIndexes.push_back(i);
                }
            }

            if (matchingIndexes.empty())
            {
                cout << "No matching books found in the current library." << endl;
                cout<<"Do you want to search the book to other libraries? y(for yes), n(for no)"<<endl;
                map<int, string> library_dict;
                library_dict[0] = "DTU Library";
                library_dict[1] = "NSUT Library";
                library_dict[2] = "IITD Library";
                library_dict[3] = "IITR Library";
                library_dict[4] = "NITD Library";

                
                string option;
                getline(cin, option);
                if (option=="y"){
                    cout<< "below are the libraries that has the book: "<<endl;
                    int ub = 4;
                    int lb = 0;
                    int size = rand() % 4;
                    set<int> rnd_idx_list;
                    for (int j=0; j<size; j++){
                        rnd_idx_list.insert((rand() % (ub - lb + 1)) + lb);
                    }
                    std::set<int>::iterator it = rnd_idx_list.begin();
                    for (int k=0;k<rnd_idx_list.size();k++){
                        std::advance(it, k);
                        int rnd_num = *it;
                        cout<<"Index "<<rnd_num<<" "<<library_dict[rnd_num]<<endl;
                    }

                    cout<<"input the index you prefer: "<<endl;
                    int idx;
                    cin>>idx;
                    cout<<"We have registered your request!"<<endl;

                    string author = "Unknown";
                    size_t selectedBookIndex = (rand() % (100 - 0 + 1)) + 0;
                    // cout<<"check"<<endl;
                    result.push_back(to_string(selectedBookIndex + 1)); // Index is 1-based
                    result.push_back(searchTitle);
                    result.push_back(author);

                    // cout<<library_dict[idx]<<endl;
                    result.push_back(library_dict[idx]);
                    
                }
                else{
                    cout<<"See you next time!"<<endl;
                }

            }
            else
            {
                // Ask the user to select an index
                cout << "Enter the index of the book you want to select: ";
                size_t selectedIndex;
                cin >> selectedIndex;

                // Validate the selected index
                if (selectedIndex >= 1 && selectedIndex <= matchingIndexes.size())
                {
                    // Get the selected index from the list of matching indexes
                    size_t selectedBookIndex = matchingIndexes[selectedIndex - 1];

                    result.push_back(to_string(selectedBookIndex + 1)); // Index is 1-based
                    result.push_back(data[selectedBookIndex][titleColumnIndex]);
                    result.push_back(data[selectedBookIndex][authorsColumnIndex]);
                    result.push_back("IIITD Library");
                }
                else
                {
                    cout << "Invalid index." << endl;
                }
            }
        }
        return result;
    }

    static vector<string> searchJournals(const string &filename, const string &userRole, const string &userName)
    {

        vector<string> result;

        string searchTerm;

        // Get user input for the item name
        cout << "Enter the name of the " << filename << ": ";
        getline(cin, searchTerm);

        // Open the CSV file
        ifstream file(filename + ".csv");

        // Check if the file is opened successfully
        if (!file.is_open())
        {
            cerr << "Error opening the file." << endl;
            return result;
        }

        vector<vector<string>> data; // Vector to store CSV data

        // Read the CSV file line by line
        string line;

        // Skip the first row (header)
        if (getline(file, line))
        {
            while (getline(file, line))
            {
                istringstream iss(line);
                vector<string> record;

                // Parse the CSV line
                while (iss)
                {
                    string field;
                    if (!getline(iss, field, ','))
                    {
                        break;
                    }
                    record.push_back(field);
                }

                // Add the record to the data vector
                data.push_back(record);
            }
        }

        // Close the file
        file.close();

        // Convert the search term to lowercase
        string lowercaseSearchTerm = toLowercase(searchTerm);

        // Search for the specified journal
        cout << "Searching for journal: " << searchTerm << endl;

        bool found = false;
        for (size_t i = 0; i < data.size(); ++i)
        {
            // Convert the current field (journal name) to lowercase
            string lowercaseJournalName = toLowercase(data[i][0]);

            // Check if the lowercase search term is present in the lowercase journal name
            if (lowercaseJournalName.find(lowercaseSearchTerm) != string::npos)
            {
                found = true;

                // Print all fields in the matching record (journal)
                cout << "Index " << i + 1 << ": ";
                for (const auto &field : data[i])
                {
                    cout << field << ", ";
                }
                cout << endl;
            }
        }

        if (!found)
        {
            cout << "Journal not found." << endl;
        }
        else
        {
            // Ask the user to select an index
            cout << "Enter the index of the journal you want to select: ";
            int selectedIndex;
            cin >> selectedIndex;

            // Validate the selected index
            if (selectedIndex >= 1 && static_cast<size_t>(selectedIndex) <= data.size())
            {
                // Print the selected journal
                cout << "Selected Journal (Index " << selectedIndex << "): ";
                result.push_back(to_string(selectedIndex));
                for (const auto &field : data[selectedIndex - 1])
                {
                    // cout << field << ", ";
                    result.push_back(field);
                }
                cout << endl;
            }
            else
            {
                cout << "Invalid index." << endl;
            }
        }

        return result;
    }
};
