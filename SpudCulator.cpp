#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void displayMessage(int count) {
    string message;

    if (count < 100) {
        message = "This year is not a good harvest";
    } else if (count >= 100 && count < 500) {
        message = "This year had an average harvest";
    } else {
        message = "This year had a great harvest";
    }

    cout << "Harvest Message: " << message << endl;
}

double calculateTotalValue(double totalWeight, double pricePerPound) {
    return totalWeight * pricePerPound;
}

int main() {
    int numberOfSpuds;
    double avgWeight;
    double pricePerPound;

    cout << "Welcome to the SpudCulator" << endl << endl;

    cout << "Enter the total number of spuds: ";
    cin >> numberOfSpuds;

    cout << "Enter the average weight of a spud (lbs): ";
    cin >> avgWeight;

    cout << "Enter the price per pound of spuds ($): ";
    cin >> pricePerPound;

    double totalWeight = numberOfSpuds * avgWeight;
    double totalValue = calculateTotalValue(totalWeight, pricePerPound);

    cout << fixed << setprecision(3);
    cout << endl << "Total weight of the harvest: " << totalWeight << "lbs";

    cout << fixed << setprecision(2);
    cout << endl << "Total value of the harvest: $" << totalValue << endl << endl;

    displayMessage(numberOfSpuds);

    return 0;
}
