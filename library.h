#ifndef LIBRARY_H
#define LIBRARY_H


//      Declarations for book_management.c file
//----------------------------------------------------
#define MAX_BOOKS 100
#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 50

typedef struct {
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    int copies; // 1<= if available, 0 if not
} Book;

extern Book books[MAX_BOOKS]; //
extern int numBooks;


// Function declarations for book management
int search_books(char *query, int searchType);
void make_a_loan();
void display_loans();
void return_books();
void donate_books();
//------------------------------------------------------




// Function declarations for login and user management
//--------------------------------------------------------------------
void readProfiles();
int validateLogin(const char *username, const char *password);
int login();
int new_user();
void logout();
//--------------------------------------------------------------------


// Utility function declaration
//--------------------------------------------------------------------
void removeNewline(char *str);

#endif // LIBRARY_H
