#ifndef ADMINPAGE_H_INCLUDED
#define ADMINPAGE_H_INCLUDED

#include <iostream>
#include "adminUserPage.h"
#include "adminProviderPage.h"
// Include necessary headers

// Forward declaration of functions
void manageUsersMenu();
//void manageProvidersMenu(); // Uncomment if needed

void adminMenu() {
    int choice;
    do {
        std::cout << "\nAdmin Menu" << std::endl;
        std::cout << "1. Manage Users" << std::endl;
        std::cout << "2. Manage Providers" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Please select an option (1-3): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                manageUsersMenu();
                break;
            case 2:
                manageProvidersMenu(); // Implement this function if needed
                break;
            case 3:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 3);
}

#endif // ADMINPAGE_H_INCLUDED
