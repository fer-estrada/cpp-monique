#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct Passenger {
    string fullName;
    int age;
    string size;
};

struct Party {
    string partyName;
    int partySize;
    int numberOfRooms;
    Passenger passengers[12];
};

void readIntialPassengerData(Party parties[], int& partyCount);
int menuHandler();
void addPassenger(Party parties[], int& partyCount);
void editPassenger(Party parties[], int partyCount);
void removePassenger(Party parties[], int& partyCount);
void printPassengerList(const Party parties[], int partyCount);
void printPartyList(const Party parties[], int partyCount);
void saveToFile(const string& fileName, const Party parties[], int partyCount);

bool isValidTshirtSize(const string& size) {
    return size == "xxs" || size == "xs" || size == "s" || size == "m" || 
           size == "l" || size == "xl" || size == "xxl" || size == "xxxl";
}

bool isValidAge(int age) {
    return age >= 1 && age <= 105;
}

int findPartyIndex(const Party parties[], int partyCount, const string& partyName) {
    for (int i = 0; i < partyCount; i++) {
        if (parties[i].partyName == partyName) {
            return i;
        }
    }
    return -1;
}

int findPassengerIndex(const Party& party, const string& fullName) {
    for (int i = 0; i < party.partySize; i++) {
        if (party.passengers[i].fullName == fullName) {
            return i;
        }
    }
    return -1;
}

void readInitialPassengerData(Party parties[], int& partyCount) {
    string fileName;
    ifstream file;
    
    while (true) {
        cout << "Enter filename: ";
        cin >> fileName;
        file.open(fileName);
        if (file.is_open()) {
            break;
        }
        cout << "Error Opening File, please enter valid file name:" << endl;
        file.clear();
    }
    
    string line;
    partyCount = 0;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        size_t lastSpace = line.find_last_of(' ');
        if (lastSpace == string::npos) continue;
        string partyName = line.substr(lastSpace + 1);
        
        size_t secondLastSpace = line.find_last_of(' ', lastSpace - 1);
        if (secondLastSpace == string::npos) continue;
        string size = line.substr(secondLastSpace + 1, lastSpace - secondLastSpace - 1);
        
        size_t thirdLastSpace = line.find_last_of(' ', secondLastSpace - 1);
        if (thirdLastSpace == string::npos) continue;
        string ageStr = line.substr(thirdLastSpace + 1, secondLastSpace - thirdLastSpace - 1);
        int age = stoi(ageStr);
        
        string name = line.substr(0, thirdLastSpace);
        
        int partyIndex = findPartyIndex(parties, partyCount, partyName);
        
        if (partyIndex == -1) {
            parties[partyCount].partyName = partyName;
            parties[partyCount].partySize = 0;
            partyIndex = partyCount;
            partyCount++;
        }
        
        int passengerIndex = parties[partyIndex].partySize;
        parties[partyIndex].passengers[passengerIndex].fullName = name;
        parties[partyIndex].passengers[passengerIndex].age = age;
        parties[partyIndex].passengers[passengerIndex].size = size;
        parties[partyIndex].partySize++;
        parties[partyIndex].numberOfRooms = (parties[partyIndex].partySize + 3) / 4;
    }
    
    file.close();
}

int menuHandler() {
    int choice;
    cout << "Please select one of the following Spudwegian choices:" << endl;
    cout << "1. Add a passenger" << endl;
    cout << "2. Edit a passenger" << endl;
    cout << "3. Remove a passenger" << endl;
    cout << "4. Print Passenger List" << endl;
    cout << "5. Print Party List" << endl;
    cout << "6. Save to file" << endl;
    cout << "7. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

void addPassenger(Party parties[], int& partyCount) {
    string partyName, fullName, size;
    int age;
    
    cout << "Enter party name: ";
    cin.ignore();
    getline(cin, partyName);
    
    cout << "Enter full name: ";
    getline(cin, fullName);
    
    cout << "Enter age: ";
    cin >> age;
    
    if (!isValidAge(age)) {
        cout << "Error: Age must be between 1 and 105" << endl;
        return;
    }
    
    cout << "Enter tshirt size: ";
    cin >> size;
    
    if (!isValidTshirtSize(size)) {
        cout << "Error: Invalid tshirt size" << endl;
        return;
    }
    
    int partyIndex = findPartyIndex(parties, partyCount, partyName);
    
    if (partyIndex == -1) {
        cout << "Party not found, creating party and adding passenger" << endl;
        parties[partyCount].partyName = partyName;
        parties[partyCount].partySize = 0;
        partyIndex = partyCount;
        partyCount++;
    }
    
    if (parties[partyIndex].partySize >= 12) {
        cout << "Error: Party is full" << endl;
        return;
    }
    
    int passengerIndex = parties[partyIndex].partySize;
    parties[partyIndex].passengers[passengerIndex].fullName = fullName;
    parties[partyIndex].passengers[passengerIndex].age = age;
    parties[partyIndex].passengers[passengerIndex].size = size;
    parties[partyIndex].partySize++;
    parties[partyIndex].numberOfRooms = (parties[partyIndex].partySize + 3) / 4;
    
    cout << "Passenger added successfully" << endl;
}

void editPassenger(Party parties[], int partyCount) {
    string partyName, fullName;
    
    cout << "Enter party name: ";
    cin.ignore();
    getline(cin, partyName);
    
    int partyIndex = findPartyIndex(parties, partyCount, partyName);
    if (partyIndex == -1) {
        cout << "Party not found" << endl;
        return;
    }
    
    cout << "Enter passenger name: ";
    getline(cin, fullName);
    
    int passengerIndex = findPassengerIndex(parties[partyIndex], fullName);
    if (passengerIndex == -1) {
        cout << "Passenger not found" << endl;
        return;
    }
    
    int choice;
    while (true) {
        cout << "1. Update name" << endl;
        cout << "2. Update age" << endl;
        cout << "3. Update tshirt size" << endl;
        cout << "4. exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        if (choice == 1) {
            string newName;
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, newName);
            parties[partyIndex].passengers[passengerIndex].fullName = newName;
            cout << "Success: Name updated" << endl;
        } else if (choice == 2) {
            int newAge;
            cout << "Enter new age: ";
            cin >> newAge;
            if (!isValidAge(newAge)) {
                cout << "Error: Age must be between 1 and 105" << endl;
            } else {
                parties[partyIndex].passengers[passengerIndex].age = newAge;
                cout << "Success: Age updated" << endl;
            }
        } else if (choice == 3) {
            string newSize;
            cout << "Enter new tshirt size: ";
            cin >> newSize;
            if (!isValidTshirtSize(newSize)) {
                cout << "Error: Invalid tshirt size" << endl;
            } else {
                parties[partyIndex].passengers[passengerIndex].size = newSize;
                cout << "Success: Tshirt size updated" << endl;
            }
        } else if (choice == 4) {
            break;
        } else {
            cout << "Invalid choice" << endl;
        }
    }
}

void removePassenger(Party parties[], int& partyCount) {
    string partyName, fullName;
    
    cout << "Enter party name: ";
    cin.ignore();
    getline(cin, partyName);
    
    int partyIndex = findPartyIndex(parties, partyCount, partyName);
    if (partyIndex == -1) {
        cout << "Party not found" << endl;
        return;
    }
    
    cout << "Enter passenger name: ";
    getline(cin, fullName);
    
    int passengerIndex = findPassengerIndex(parties[partyIndex], fullName);
    if (passengerIndex == -1) {
        cout << "Passenger not found" << endl;
        return;
    }
    
    if (parties[partyIndex].partySize == 1) {
        cout << "You must add a passenger before removing. Parties must have 1 passanger at all times" << endl;
        return;
    }
    
    for (int i = passengerIndex; i < parties[partyIndex].partySize - 1; i++) {
        parties[partyIndex].passengers[i] = parties[partyIndex].passengers[i + 1];
    }
    
    parties[partyIndex].partySize--;
    parties[partyIndex].numberOfRooms = (parties[partyIndex].partySize + 3) / 4;
    
    cout << fullName << " from party " << partyName << " successfully deleted" << endl;
}

void printPassengerList(const Party parties[], int partyCount) {
    cout << "Passenger List:" << endl;
    cout << left << setw(20) << "Name" << setw(5) << "Age" << setw(10) << "T-Shirt" << "Party Name" << endl;
    cout << string(50, '-') << endl;
    
    for (int i = 0; i < partyCount; i++) {
        for (int j = 0; j < parties[i].partySize; j++) {
            cout << left << setw(20) << parties[i].passengers[j].fullName
                 << setw(5) << parties[i].passengers[j].age
                 << setw(10) << parties[i].passengers[j].size
                 << parties[i].partyName << endl;
        }
    }
}

void printPartyList(const Party parties[], int partyCount) {
    cout << "Party List:" << endl;
    cout << left << setw(20) << "Party Name" << setw(15) << "Party Size" << "Number of Rooms" << endl;
    cout << string(50, '-') << endl;
    
    for (int i = 0; i < partyCount; i++) {
        cout << left << setw(20) << parties[i].partyName
             << setw(15) << parties[i].partySize
             << parties[i].numberOfRooms << endl;
    }
}

void saveToFile(const string& fileName, const Party parties[], int partyCount) {
    ofstream file(fileName);
    if (!file.is_open()) {
        cout << "Error opening file for writing" << endl;
        return;
    }
    
    file << "Party List:" << endl;
    file << left << setw(20) << "Party Name" << setw(15) << "Party Size" << "Number of Rooms" << endl;
    file << string(50, '-') << endl;
    
    for (int i = 0; i < partyCount; i++) {
        file << left << setw(20) << parties[i].partyName
             << setw(15) << parties[i].partySize
             << parties[i].numberOfRooms << endl;
    }
    
    file << endl << "Passenger List:" << endl;
    file << left << setw(20) << "Name" << setw(5) << "Age" << setw(10) << "T-Shirt" << "Party Name" << endl;
    file << string(50, '-') << endl;
    
    for (int i = 0; i < partyCount; i++) {
        for (int j = 0; j < parties[i].partySize; j++) {
            file << left << setw(20) << parties[i].passengers[j].fullName
                 << setw(5) << parties[i].passengers[j].age
                 << setw(10) << parties[i].passengers[j].size
                 << parties[i].partyName << endl;
        }
    }
    
    file.close();
    cout << "Data saved to file successfully" << endl;
}

int main() {
    Party parties[100];
    int partyCount = 0;
    
    readInitialPassengerData(parties, partyCount);
    
    int choice;
    while (true) {
        choice = menuHandler();
        
        switch (choice) {
            case 1:
                addPassenger(parties, partyCount);
                break;
            case 2:
                editPassenger(parties, partyCount);
                break;
            case 3:
                removePassenger(parties, partyCount);
                break;
            case 4:
                printPassengerList(parties, partyCount);
                break;
            case 5:
                printPartyList(parties, partyCount);
                break;
            case 6: {
                string fileName;
                cout << "Enter filename to save: ";
                cin >> fileName;
                saveToFile(fileName, parties, partyCount);
                break;
            }
            case 7:
                return 0;
            default:
                cout << "Invalid choice" << endl;
        }
        cout << endl;
    }
    
    return 0;
}
