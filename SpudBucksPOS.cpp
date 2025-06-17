#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int totalCoffee = 0;
    int totalTea = 0;
    int totalCake = 0;
    int totalMuffin = 0;
    double totalPrice = 0.0;

    constexpr double COFFEE_COST = 2.00;
    constexpr double TEA_COST = 1.50;
    constexpr double CAKE_COST = 3.00;
    constexpr double MUFFIN_COST = 2.50;

    char moreFood = 'y';

    cout << "Welcome to SpudBucks" << endl;

    do {
        cout << fixed << setprecision(2);
        cout << "\nMenu:\n";
        cout << "1. Coffee     - $" << COFFEE_COST << endl;
        cout << "2. Tea        - $" << TEA_COST << endl;
        cout << "3. Cake       - $" << CAKE_COST << endl;
        cout << "4. Muffin     - $" << MUFFIN_COST << endl;

        int spudFoods;
        cout << "\nSelect an item (1-4): ";
        cin >> spudFoods;
        while (spudFoods < 1 || spudFoods > 4) {
            cout << "Invalid selection. Please select an item (1-4): ";
            cin >> spudFoods;
        }

        int foodQuantity;
        cout << "Enter quantity: ";
        cin >> foodQuantity;
        while (foodQuantity < 1) {
            cout << "Quantity must be at least 1. Enter quantity: ";
            cin >> foodQuantity;
        }

        switch (spudFoods) {
            case 1:
                totalCoffee += foodQuantity;
                totalPrice += foodQuantity * COFFEE_COST;
                break;
            case 2:
                totalTea += foodQuantity;
                totalPrice += foodQuantity * TEA_COST;
                break;
            case 3:
                totalCake += foodQuantity;
                totalPrice += foodQuantity * CAKE_COST;
                break;
            case 4:
                totalMuffin += foodQuantity;
                totalPrice += foodQuantity * MUFFIN_COST;
                break;
        }

        cout << "Do you want to add to the order? (y/n): ";
        cin >> moreFood;
        while (moreFood != 'y' && moreFood != 'n') {
            cout << "Please enter 'y' or 'n': ";
            cin >> moreFood;
        }

    } while (moreFood == 'y');

    cout << "\nSummary of your order\n";
    cout << left << setw(10) << "Item" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
    cout << "-----------------------------------" << endl;

    if (totalCoffee > 0)
        cout << left << setw(10) << "Coffee" << setw(10) << totalCoffee << "$" << fixed << setprecision(2) << totalCoffee * COFFEE_COST << endl;
    if (totalTea > 0)
        cout << left << setw(10) << "Tea" << setw(10) << totalTea << "$" << fixed << setprecision(2) << totalTea * TEA_COST << endl;
    if (totalCake > 0)
        cout << left << setw(10) << "Cake" << setw(10) << totalCake << "$" << fixed << setprecision(2) << totalCake * CAKE_COST << endl;
    if (totalMuffin > 0)
        cout << left << setw(10) << "Muffin" << setw(10) << totalMuffin << "$" << fixed << setprecision(2) << totalMuffin * MUFFIN_COST << endl;

    cout << "-----------------------------------" << endl;
    cout << left << setw(20) << "Total:" << "$" << fixed << setprecision(2) << totalPrice << endl;

    cout << "Thank you for ordering at SpudBucks!" << endl;

    return 0;
}
