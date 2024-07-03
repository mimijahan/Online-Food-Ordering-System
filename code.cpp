#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

unordered_map<string, string> readUserData(const string& filename) {
    unordered_map<string, string> um;
    fstream infile(filename, ios::in);
    string username, password;
    if (infile.is_open()) {
        while (infile >> username >> password) {
            um[username] = password;
        }
        infile.close();
    } else {
        cout << "Error opening file for reading!" << endl;
    }
    return um;
}

void writeUserData(const string& filename, const unordered_map<string, string>& um) {
    fstream outfile(filename, ios::out);
    if (outfile.is_open()) {
        for (const auto& pair : um) {
            outfile << pair.first << " " << pair.second << "\n";
        }
        outfile.close();
    } else {
        cout << "Error opening file for writing!" << endl;
    }
}

struct MenuItem {
    int id;
    string name;
    float price;
};

void displayMenu(const vector<MenuItem>& menu) {
    cout << "\n------ Menu ------\n";
    for (const auto& item : menu) {
        cout << item.id << ". " << item.name << " - $" << fixed << setprecision(2) << item.price << endl;
    }
    cout << "------------------\n";
}

void addToOrder(vector<MenuItem>& order, const MenuItem& item) {
    order.push_back(item);
    cout << item.name << " has been added to your order.\n";
}

void displayOrder(const vector<MenuItem>& order) {
    if (order.empty()) {
        cout << "Your order is empty.\n";
        return;
    }

    cout << "\n------ Your Order ------\n";
    float total = 0;
    for (const auto& item : order) {
        cout << item.name << " - $" << fixed << setprecision(2) << item.price << endl;
        total += item.price;
    }
    cout << "------------------------\n";
    cout << "Total: $" << fixed << setprecision(2) << total << endl;
}

void registerUser(unordered_map<string, string>& users, const string& filename) {
    string username, password;
    cout << "Enter new username: ";
    cin >> username;
    cout << "Enter new password: ";
    cin >> password;

    if (users.find(username) == users.end()) {
        users[username] = password;
        writeUserData(filename, users);
        cout << "Registration successful.\n";
    } else {
        cout << "Username already exists.\n";
    }
}

bool loginUser(const unordered_map<string, string>& users) {
    int attempt_count = 0;
    while (attempt_count < 5) {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (users.find(username) != users.end() && users.at(username) == password) {
            cout << "Login successful.\n";
            return true;
        } else {
            cout << "Invalid username or password. Please try again.\n";
            attempt_count++;
        }
    }

    cout << "You have tried 5 times and you cannot try anymore.\n";
    return false;
}

int main() {
    string filename = "userdata.txt";
    unordered_map<string, string> users = readUserData(filename);

    vector<MenuItem> breakfastMenu = {
        {1, "Pancakes", 5.99},
        {2, "Omelette", 6.99},
        {3, "French Toast", 7.49}
    };

    vector<MenuItem> lunchMenu = {
        {4, "Burger", 8.99},
        {5, "Sandwich", 7.99},
        {6, "Salad", 6.49}
    };

    vector<MenuItem> dinnerMenu = {
        {7, "Steak", 14.99},
        {8, "Pasta", 12.99},
        {9, "Pizza", 10.49}
    };

    vector<MenuItem> foreignCuisineMenu = {
        {10, "Sushi", 13.99},
        {11, "Tacos", 8.99},
        {12, "Curry", 9.99}
    };

    vector<MenuItem> order;

    while (true) {
        cout << "1. Register\n2. Login\n3. Exit\nEnter option: ";
        string option;
        cin >> option;

        if (option == "1") {
            registerUser(users, filename);
        } else if (option == "2") {
            if (loginUser(users)) {
                while (true) {
                    cout << "\n------ Main Menu ------\n";
                    cout << "1. Breakfast Menu\n2. Lunch Menu\n3. Dinner Menu\n4. Foreign Cuisine Menu\n5. Add Item to Order\n6. Logout\nEnter your choice: ";
                    int choice;
                    cin >> choice;

                    switch (choice) {
                        case 1:
                            displayMenu(breakfastMenu);
                            break;
                        case 2:
                            displayMenu(lunchMenu);
                            break;
                        case 3:
                            displayMenu(dinnerMenu);
                            break;
                        case 4:
                            displayMenu(foreignCuisineMenu);
                            break;
                        case 5: {
                            int menuChoice;
                            cout << "Select menu:\n1. Breakfast\n2. Lunch\n3. Dinner\n4. Foreign Cuisine\nEnter your choice: ";
                            cin >> menuChoice;

                            int itemId;
                            cout << "Enter item ID to add: ";
                            cin >> itemId;

                            switch (menuChoice) {
                                case 1:
                                    for (const auto& item : breakfastMenu) {
                                        if (item.id == itemId) {
                                            addToOrder(order, item);
                                            break;
                                        }
                                    }
                                    break;
                                case 2:
                                    for (const auto& item : lunchMenu) {
                                        if (item.id == itemId) {
                                            addToOrder(order, item);
                                            break;
                                        }
                                    }
                                    break;
                                case 3:
                                    for (const auto& item : dinnerMenu) {
                                        if (item.id == itemId) {
                                            addToOrder(order, item);
                                            break;
                                        }
                                    }
                                    break;
                                case 4:
                                    for (const auto& item : foreignCuisineMenu) {
                                        if (item.id == itemId) {
                                            addToOrder(order, item);
                                            break;
                                        }
                                    }
                                    break;
                                default:
                                    cout << "Invalid menu choice.\n";
                                    break;
                            }
                            break;
                        }
                        case 6:
                            cout << "Logging out...\n";
                            break;
                        default:
                            cout << "Invalid option. Please try again.\n";
                            break;
                    }

                    if (choice == 6) {
                        break;
                    }
                }
            }
        } else if (option == "3") {
            cout << "Exiting\n";
            break;
        } else {
            cout << "Invalid option, please try again\n";
        }
    }

    return 0;
}
