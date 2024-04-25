#include <stdio.h>
#include <string.h>
#include "library.h"

Book books[MAX_BOOKS];
int numBooks = 0;


//-------------------------------------------------------------------------------------------------------------------------------
// Add a new book to the library
void add_book() {
    if (numBooks >= MAX_BOOKS) {
        printf("Cannot add more books. Library is full.\n");
        return;
    }

    printf("Enter the title of the book: ");
    scanf("%s", books[numBooks].title);
    getchar(); // Consume newline

    printf("Enter the author of the book: ");
    scanf("%s", books[numBooks].author);
    getchar(); // Consume newline

    books[numBooks].copies = 1; // Set book as available
    numBooks++;

    printf("Book added successfully!\n");
}
//-------------------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------------------
// it retrieves the number of books in stock.csv, and also stores the books in their own structure variables called books[]
void store_books_and_get_number_of_books() {
    //open file
    FILE *books_file = fopen("stock.csv","r");
    // check for errors upon opening
    if (books_file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    //Skip first row from csv
    char line[150 * 2];
    fscanf(books_file, "%s", line);
    fgetc(books_file);

    int copies;
    while (fscanf(books_file, "%[^,],%[^,],%d", books[numBooks].title, books[numBooks].author, &copies) == 3) {
        fgetc(books_file); // consume newline character
        books[numBooks].copies = copies;
        numBooks++;
    }

    fclose(books_file);
}
//-------------------------------------------------------------------------------------------------------------------------------




//-------------------------------------------------------------------------------------------------------------------------------
//Print the stock library, the books
void show_books() {
    for (int i = 0; i < numBooks; i++)
        printf("\nProfile %d | Name:%s | Surname:%s\n",i,books[i].title,books[i].author);
}
//-------------------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------------------
// Search for a book by title, author, or both
int search_books(char *query, int searchType) {
    printf("You are searching for '%s' ...\n", query);

    int found = 0;
    for (int i = 0; i < numBooks; i++) {
        if ((searchType == 1 || searchType == 3) && strstr(books[i].title, query) != NULL) {
            if (!found) {
                printf("Book found!\n");
            }
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Availability: %s\n", books[i].copies ? "Available" : "Not Available");
            found = 1;
        }
        if ((searchType == 2 || searchType == 3) && strstr(books[i].author, query) != NULL) {
            if (!found) {
                printf("Book found!\n");
            }
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Availability: %s\n", books[i].copies ? "Available" : "Not Available");
            found = 1;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }

    return found; // Return 1 if book found, 0 otherwise
}
//-------------------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------------------
// Implement the logic to make a loan
void make_a_loan() {
    // RETRIEVE THE DATA FROM CSV
    store_books_and_get_number_of_books();

    char query[MAX_TITLE_LENGTH + MAX_AUTHOR_LENGTH + 2]; // +2 for space and null terminator
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];

    printf("Enter the title of the book you want to loan: ");

    // Read the entire line, including spaces
    fgets(query, MAX_TITLE_LENGTH + MAX_AUTHOR_LENGTH + 2, stdin);

    // Remove the newline character at the end
    removeNewline(query);

    // Split the query into title and author
    sscanf(query, "%s %[^\n]", title, author);

    // Search for the book based on both title and author using the search_books() function
    if (search_books(title, 3)) {  // Search based on both title and author
        char response;
        printf("Do you want to proceed with making the loan? (y/n): ");
        scanf(" %c", &response);

        if (response == 'y' || response == 'Y') {
            // Logic to make the loan can be added here
            printf("Loan made successfully!\n");
        } else {
            printf("Loan not made.\n");
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------------------
// Display all loans
void display_loans() {
    printf("Loans:\n");
    for (int i = 0; i < numBooks; i++) {
        if (!books[i].copies) {
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("--------------\n");
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------------------
// Implement the logic to return a book
void return_books() {
    char title[MAX_TITLE_LENGTH];
    printf("Enter the title of the book you want to return: ");
    scanf("%s", title);
    getchar(); // Consume newline

    int found = 0;
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(title, books[i].title) == 0 && !books[i].copies) {
            books[i].copies = 1; // Set book as available
            printf("Book returned successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found or already returned.\n");
    }
}
//-------------------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------------------
// Implement the logic to donate a book
void donate_books() {
    if (numBooks >= MAX_BOOKS) {
        printf("Cannot add more books. Library is full.\n");
        return;
    }

    printf("Enter the title of the book you want to donate: ");
    scanf("%s", books[numBooks].title);
    getchar(); // Consume newline

    printf("Enter the author of the book you want to donate: ");
    scanf("%s", books[numBooks].author);
    getchar(); // Consume newline

    books[numBooks].copies = 1; // Set book as available
    numBooks++;

    printf("Book donated successfully!\n");
}
//-------------------------------------------------------------------------------------------------------------------------------