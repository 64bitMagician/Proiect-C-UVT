#include <stdio.h>
#include "library.h"

int main() {
    int choice;

    do {
        // Let's call this MENU 1
        printf("\nMENU 1\n");
        printf("Library Management System\n");
        printf("1. Login\n");
        printf("2. Register to libary. We will ask you for your name and surname.\n");
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
                        printf("1. Search for a book and make a loan\n");
                        printf("2. View your loans\n");
                        printf("3. Return book\n");
                        printf("4. Donate book\n");
                        printf("5. Logout\n");
                        printf("Enter your choice: ");
                        scanf("%d", &loggedInChoice);

                        switch (loggedInChoice) {
                            case 1:
                                make_a_loan();
                                break; // exit switch statement
                            case 2:
                                display_loans();
                                break; // exit switch statement
                            case 3:
                                return_books();
                                break; // exit switch statement
                            case 4:
                                donate_books();
                                break;
                            case 5:
                                logout(); // logout message
                                break; // exit switch statement
                            default: // if no case, prints message and quits
                                printf("Invalid choice. Please try again.\n");
                                break; // exit switch statement
                        }
                    } while (loggedInChoice != 5);
                }
                break; // exit switch statement
            case 2: // new_user case
                if (new_user()) {
                    printf("You registered successfully!\n");
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

