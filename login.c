#include <stdio.h>
#include <string.h>
#include "library.h"

// string variables that hold a value
#define MAX_PROFILES 100
#define MAX_LENGTH 50

typedef struct {
    char name[MAX_LENGTH];
    char surname[MAX_LENGTH];
} Profile; //Profile = typedef(word used in creating variables of type Profile, which is a structure that holds two character arrays:
//one is called 'name' and the other is called surname)

Profile profiles[MAX_PROFILES]; // we use typedef Profile to create an array of variables of type Profile.

int numProfiles = 0;

void show_profiles() {
    for (int i = 0; i < numProfiles; i++)
        printf("\nProfile %d | Name:%s | Surname:%s\n",i,profiles[i].name,profiles[i].surname);
}

//reading and storing the values from the csv into the array of structures of type Profiles called profiles[].
void readProfiles() {
    FILE *file = fopen("profiles.csv", "r"); // Open the CSV file for read mode, under the FILE pointer type variable name 'file'. It will be called file.

    //Check for error when oppening the file. If there is an error, login will return nothin, and exit the function
    if (file == NULL) {
        perror("Error opening file.\n");
        return; // void return. It is used in void functions, where you can return nothing, and just exit the function.
    }

    char line[MAX_LENGTH * 2]; // line will be a string that will contain the rows in the csv file

    // file is a pointer to file. %s the string format specifier. line is the buffer where the red line from
    // the file will be stored. A buffer is a place in memory for temporary storage of data.
    // so fscanf takes a pointer to a file, reads from it under the format specifier, and stores the red value in a variable
    // By default, fscanf reads data sequentially from the file until it encounters whitespace (like a space, tab, or newline),
    // unless otherwise specified by the format string.
    // Also, fscanf keeps track from where it left off last time it red from the file through the file position indicator.
    //There is a function called fseek that changes the file position indicator.
    fscanf(file, "%s", line);
    fgetc(file);// consume the new line character after reading the first row of the file, because the file position indicator has stopped
    // right before the newline character, and the next time it reads data from the file, it takes it with the newline character also, until it
    // encounters the next whitespace character...



    //So while it is reading data from file, it will execute the code bellow.
    //The format is made in such a way that it stores the string before the ',' in the name, and the string after
    //the ',' in the surname variable, which are members of the array of Profile structures called 'profiles'
    // It stores in the profiles array starting from profiles[0]. Then it increments numProfiles everytime so that it will
    // store the data red from the file in the next profiles[] variable from the array.
    // It also removes the newline from the end of each line of the file, so it won't also store the newline character within the surname member
    // fgetc(file) (f - file get c - character) is used to read and skip a single character from the file pointed to by file, since the file
    // position indicator stops rights after encountering a whitespace a newline and so on, so we want to get rid of that newline character,
    // to continue reading.
    while (fscanf(file, "%[^,],%s", profiles[numProfiles].name, profiles[numProfiles].surname) != EOF) {
        removeNewline(profiles[numProfiles].surname);
        fgetc(file); // Skip newline character
        numProfiles++;
    }

    // After done reading and storing the values from the csv into the array of structures of type Profiles, we exit the file.
    fclose(file);
}

// This function takes the passed name and surname from the user and checks to see if it corresponds to on of the rows within the csv file.
int validateLogin(const char *name, const char *surname) {// takes a pointer to a name and a surname as parameters.
    for (int i = 0; i < numProfiles; i++) {// an iterator 'i' that will represent the profiles.
        //if the passed name and surname arguments are identitcal to one of the rows within the csv file, validateLogin will return 1.
        if (strcmp(name, profiles[i].name) == 0 && strcmp(surname, profiles[i].surname) == 0) {
            return 1; // Return 1 indicating login successful
        }
    }

    // if it gets to this point, it means that the function did not find a match between the passed name and surname of the user
    // and one of the profiles from the csv file
    // Therfore, it will print an error message and return 0
    printf("Invalid name or surname!\n");
    return 0; // Return 0 indicating login failed
}

// This function will return 1 if the user input matches one of the account profile details, or 0 if it does not, and in that case it will
// loop back to the login or new user menu.
int login() {
    // when called, login() will first call the readProfiles() function, which will store the values within the csv file into an array of
    // structures of type Profile, called profiles[]. In profiles[] there are the member for name and the member for surname.
    readProfiles();
    // So after this call, we now have access to the data within the csv files stored in profiles[]

    //SHOW THE EXISTING PROFILES BEFORE LOGGING IN:
    //show_profiles();


    char name[MAX_LENGTH];
    char surname[MAX_LENGTH];

    // GET THE name FROM THE USER
    printf("Enter name:");
    scanf("%s", name); // Read entire line for name
    getchar(); // Consume the newline character left by scanf

    // GET THE surname FROM THE USER
    printf("Enter surname:");
    scanf("%s", surname); // Read entire line for surname
    getchar(); // Consume the newline character left by scanf

    // we pass the name and surname from the user to validateLogin() function, which will check if the input from the user corresponds to
    // one of the profiles in the csv file. If it does, it will return 1, and execute the if statement, which will print a message for succesful login,
    // and then return 1 to main.c so it will continue the program within the state of a logged in user.
    // If it does not find a corelation with the given input and the stored profiles in the csv, then it will print a message for login failure,
    // and it will return 0 to main.c, which will make the program loop back to the choose a option for login or new user manu.
    if (validateLogin(name, surname)) {
        printf("Login successful!\n");
        return 1; // Return 1 indicating successful login
    } else {
        printf("Login failed! Please try again.\n");
        return 0; // Return 0 for failed
    }
}

// This function
int new_user() {
    // opens the profile.csv file, stores the adress of the file within the file pointer of type FILE, for 'a' = 'appending' mode
    FILE *file = fopen("profiles.csv", "a");

    // if file pointer is null, it means that the file did not open, will print an error and will return 0.
    if (file == NULL) {
        perror("Error opening file.\n");
        return 0; // Return 0 indicating failure
    }

    char name[MAX_LENGTH];
    char surname[MAX_LENGTH];

    // GET name
    // in scanf %s: Reads a string of characters until it encounters whitespace (space, tab, newline), that leftover will remain in the input buffer.
    printf("Enter your name:");
    scanf("%s", name); // Read entire line for name
    getchar(); // Consume the newline character left by scanf

    // Check if the name already exists
    for (int i = 0; i < numProfiles; i++) {
        if (strcmp(name, profiles[i].name) == 0) {// if inputted name is identical to one name from the csv file,
            // it will close the file, print message, and return 0 to main.c which will cause the program to loop back to MENU 1
            printf("Name already exists! Please choose a different name for your profile.\n");
            fclose(file);
            return 0; // Return 0 indicating failure
        }
    }

    // GET surname, same story as GET name
    printf("Enter your surname:");
    scanf("%s", surname); // Read entire line for surname
    getchar(); // Consume the newline character left by scanf

    // fprintf will write to 'file', under the specified format (string,string\n), the passed name and surname by the user
    fprintf(file, "%s,%s\n", name, surname);

    // after passing a name and surname, the file closes
    fclose(file);

    // if you get to this point, it means that no errors and no return 0's, you get a succesful message and return 1 to main.c, which
    // will make the program print a succes message again in the main,
    printf("Registered successfully!\n");
    return 1; // Return 1 indicating success
}

// This function will simply print a message for logging out, and then the program will exit within the main.c file.
void logout() {
    // Reset any session-specific data or flags here
    // For example, you could reset a login status flag or clear any user-specific data in memory
    printf("Logged out successfully!\n");
}
