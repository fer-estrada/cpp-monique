#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void displayReceipt(string names[], int quantities[], double prices[], int itemCount);

int main() {
    string itemNames[10];
    int quantities[10];
    double prices[10];
    int itemCount = 0;

    cout << "Welcome to SpudMart!\n" << endl;

    while (itemCount < 10) {
        string name;
        cout << "Enter item name (or 'exit' to finish): ";
        getline(cin, name);

        if (name == "exit") {
            break;
        }

        itemNames[itemCount] = name;

        cout << "Enter quantity: ";
        cin >> quantities[itemCount];

        cout << "Enter price per items: ";
        cin >> prices[itemCount];
        cin.ignore();

        itemCount++;
        cout << endl;
    }

    displayReceipt(itemNames, quantities, prices, itemCount);

    return 0;
}

void displayReceipt(string names[], int quantities[], double prices[], int itemCount) {
    cout << "\nYour SpudMart Receipt:\n" << endl; 
    cout << "Item                 Qty  Total Price\n";
    cout << "----------------------------------------" << endl;

    double grandTotal = 0.0;

    for (int i = 0; i < itemCount; i++) {
        double totalPrice = quantities[i] * prices[i];
        cout << left << setw(21) << names[i]
             << right << setw(4) << quantities[i]
             << "  $" << fixed << setprecision(2) << totalPrice << endl;

        grandTotal += totalPrice;
    }

    cout << "\nGrand Total: $" << fixed << setprecision(2) << grandTotal << endl;
}
