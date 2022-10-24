#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "route-records.h"

int main(int argc, char *argv[])
{
  /* 1. Declare variables here */
  char *filepath;

  /* 2. Check command line arguments here. If a command line argument (for the file name) is missing, print out the following: ERROR: Missing file name and end the program */
  if(argc < 2) {
    printf("ERROR: Missing file name\n");
    exit(0);
  } else if (argc > 2) {
    printf("Too many arguments supplied, only need the file name\n");
    exit(0);
  }

  filepath = argv[1]; // get the filepath from command line arguments


  /* 3. Attempt to open the file. Print out Opening <filename>... before you call fopen(). */
  printf("Opening %s...\n", filepath);
  FILE *fp = fopen(filepath, "r");

  /* 4. Check to see if the file opens. If it does not open, print out ERROR: Could not open file and end the program. */
  if (!fp){
    printf("ERROR: Could not open file.\n");
    exit(0);
  }


  /* 5. Do the following to load the records into an array of RouteRecords
    5.1 Call createRecords(), which will read through the file once to find the total number of lines/records in the file. Use this count, to dynamically allocate memory for an array of RouteRecords. It returns a pointer to that array. Don't forget to rewind the file pointer.
    5.2 Call fillRecords() to go through the CSV file again to fill in the values. It will then return the actual number of items the array has. Recall that not all records in the original CSV file will be entered into the array. Print the number of unique routes operated by different airlines: Unique routes operated by airlines: ???
    5.3 Close the the file.
  */
  RouteRecord *routes = createRecords(fp);
  int count = fillRecords(routes, fp);
  printf("Unique routes operated by airlines:  %d\n", count);
  fclose(fp);

  /* 6. Create an infinite loop that will do the following:
    6.1 Call printMenu()
    6.2 Ask the user to input a value for the menu
    6.3 Handle the case in which a non-integer value is entered
    6.4 Create a switch/case statement to handle all the menu options
      6.4.1 Each option requires the user to enter a search key
      6.4.2 Quit needs to free the array
  */

  char input[50] = "", key1[50] = "", key2[50] = "";
  int i, parsedInput;

  while(1) {
    printMenu();
    scanf("%s", input); // getting user input
    // check if valid integer
    for(i=0; i< strlen(input); i++) {
      if(!isdigit(input[i])) {
        printf("Please enter a number!\n");
        break;
      }
    }
    parsedInput = atoi(input); // convert to int

    switch (parsedInput){
      case ROUTE:
        printf("Enter origin: ");
        scanf("%s", key1);
        printf("Enter destination: ");
        scanf("%s", key2);
        searchRecords(routes, count, key1, key2, ROUTE);
        break;

      case ORIGIN:
        printf("Enter origin: ");
        scanf("%s", key1);
        searchRecords(routes, count, key1, key2, ORIGIN);
        break;
      
      case DESTINATION:
        printf("Enter destination: ");
        scanf("%s", key1);
        searchRecords(routes, count, key1, key2, DESTINATION);
        break;
      
      case AIRLINE:
        printf("Enter airline: ");
        scanf("%s", key1);
        searchRecords(routes, count, key1, key2, AIRLINE);
        break;
      
      case 5:
        printf("Good-bye!\n");
        exit(0);
        break;
      
      default:
        printf("Invalid choice.\n");
        break;
    }
  }

  return 0;
}
