#include <stdio.h>
#include "library.h"

int main() {
    int choice;

    do {
        // Let's call this MENU 1
        printf("\nMENU 1\n");
        printf("Library Management System\n");
        printf("1. Login\n");
        printf("2. Create New Account\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // login case
                if (login()) {
                    int loggedInChoice;
                    do {
                        printf("\nMENU 2\n");
                        printf("Library Management Menu\n");
                        printf("1. Add Book\n");
                        printf("2. Remove Book\n");
                        printf("3. Display Books\n");
                        printf("4. Logout\n");
                        printf("Enter your choice: ");
                        scanf("%d", &loggedInChoice);

                        switch (loggedInChoice) {
                            case 1:
                                addBook();
                                break; // exit switch statement
                            case 2:
                                removeBook();
                                break; // exit switch statement
                            case 3:
                                displayBooks();
                                break; // exit switch statement
                            case 4:
                                logout(); // logout message
                                break; // exit switch statement
                            default: // if no case, prints message and quits
                                printf("Invalid choice. Please try again.\n");
                                break; // exit switch statement
                        }
                    } while (loggedInChoice != 4);
                }
                break; // exit switch statement
            case 2: // new_user case
                if (new_user()) {
                    printf("New user created successfully!\n");
                }
                break; // exit switch statement
            case 3: // exit case
                printf("Exiting...\n");
                break;// exit switch statement
            default: // if no case, then print message and exit
                printf("Invalid choice. Please try again.\n");
                break;// exit switch statement
        }

    } while (choice != 3);

    return 0;
}

