#ifndef LIBRARY_H
#define LIBRARY_H

// Function declarations for login and user management
void readProfiles();
int validateLogin(const char *username, const char *password);
int login();
int new_user();
void logout();

// Function declarations for book management
void addBook();
void removeBook();
void displayBooks();

// Utility function declaration
void removeNewline(char *str);

#endif // LIBRARY_H
