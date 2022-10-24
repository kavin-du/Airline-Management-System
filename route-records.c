
#include <stdlib.h>
#include <string.h>
#include "route-records.h"

// helper function to get the record count
int getRecordCount(FILE* file) {
  int rows = -1; // skipping the first line
  char buff[50]; // temporary for reading lines

  // count the total rows
  while(fgets(buff, 50, file)) {
    rows++;
  }
  rewind(file); // rewind the file pointer
  return rows;
}

RouteRecord* createRecords(FILE* fileIn) {
  int rows = getRecordCount(fileIn); // get the total record count

  // dynamically allocating array of RouteRecords
  RouteRecord* routesList = (RouteRecord*)malloc(sizeof(RouteRecord) * rows);

  // initialize only the passenger count
  for(int i=0; i < rows; i++) {
    routesList[i] = (RouteRecord){ .passenger_count = {0,0,0,0,0,0}};
  }

  return routesList;
};


int fillRecords(RouteRecord* r, FILE* fileIn) {
  int rows = -1; 
  char buffer[50]; 
  int actualRecords = 0;

  char line[6][20]; // to save the line values
  int i;
  while(fgets(buffer, 50, fileIn)) {
    rows++;

    if(rows == 0) continue; // skip the first line
    
    i = 0;

    char* value = strtok(buffer, ","); // tokenize the line

    while(value) {
      strcpy(line[i++], value); // save values into array for later reference
      value = strtok(NULL, ",");
    }

    int month = atoi(line[0]);
    const char* origin = line[1];
    const char* dest = line[2];
    const char* airline = line[3];
    int passengerCount = atoi(line[5]);

    // find if already exists
    int index = findAirlineRoute(r, actualRecords, origin, dest, airline, 0);

    if(index >= 0) {
      // update passenger count
      r[index].passenger_count[month-1] += passengerCount;
    } else {
      // create a new record
      strcpy(r[actualRecords].origin, origin);
      strcpy(r[actualRecords].dest, dest);
      strcpy(r[actualRecords].air_code, airline);

      r[actualRecords].passenger_count[month-1] = passengerCount;

      actualRecords++; // new record count increased
    }
  }
  return actualRecords;

};

int findAirlineRoute(
  RouteRecord* r, 
  int length, 
  const char* origin, 
  const char* destination, 
  const char* airline, 
  int curIdx) {
    if(curIdx >= length) return -1; // no record found

    if(strcmp(r[curIdx].origin, origin) == 0 && 
        strcmp(r[curIdx].dest, destination) == 0 && 
        strcmp(r[curIdx].air_code, airline) == 0) {
        return curIdx; // record found
    }

    // recursively find the next record
    return findAirlineRoute(r, length, origin, destination, airline, ++curIdx);
};

// helper function for printing statistics
void printStatistics(int matches, int total, int m1, int m2, int m3, int m4, int m5, int m6) {
  printf("\n%d matches were found.\n\n", matches);

  printf("Statistics\n");
  printf("Total Passengers: \t%d\n", total);

  printf("Total Passengers in Month 1: \t%d\n", m1);
  printf("Total Passengers in Month 2: \t%d\n", m2);
  printf("Total Passengers in Month 3: \t%d\n", m3);
  printf("Total Passengers in Month 4: \t%d\n", m4);
  printf("Total Passengers in Month 5: \t%d\n", m5);
  printf("Total Passengers in Month 6: \t%d\n\n", m6);

  printf("Average Passengers per Month: \t%d\n", (int)(total/6));
}

void searchRecords(RouteRecord* r, int length, const char*key1, const char* key2, SearchType st) {
  int total = 0, matches = 0, m1 = 0, m2 = 0, m3 = 0, m4 = 0, m5 = 0, m6 = 0;

  if(st == ORIGIN) {
    printf("Searching by origin...\n");
    for(int i=0; i < length; i++) {
      if(strcmp(r[i].origin, key1) == 0) {
        matches++;

        // count in each month
        m1 += r[i].passenger_count[0];
        m2 += r[i].passenger_count[1];
        m3 += r[i].passenger_count[2];
        m4 += r[i].passenger_count[3];
        m5 += r[i].passenger_count[4];
        m6 += r[i].passenger_count[5];

        printf("%s (%s-%s) ", r[i].air_code, r[i].origin, r[i].dest);
      }
    }

  } else if(st == DESTINATION) {
    printf("Searching by destination...\n");
    for(int i=0; i < length; i++) {
      if(strcmp(r[i].dest, key1) == 0) {
        matches++;

        // count in each month
        m1 += r[i].passenger_count[0];
        m2 += r[i].passenger_count[1];
        m3 += r[i].passenger_count[2];
        m4 += r[i].passenger_count[3];
        m5 += r[i].passenger_count[4];
        m6 += r[i].passenger_count[5];

        printf("%s (%s-%s) ", r[i].air_code, r[i].origin, r[i].dest);
      }
    }

  } else if(st == AIRLINE) {
    printf("Searching by airline...\n");
    for(int i=0; i < length; i++) {
      if(strcmp(r[i].air_code, key1) == 0) {
        matches++;

        // count in each month
        m1 += r[i].passenger_count[0];
        m2 += r[i].passenger_count[1];
        m3 += r[i].passenger_count[2];
        m4 += r[i].passenger_count[3];
        m5 += r[i].passenger_count[4];
        m6 += r[i].passenger_count[5];

        printf("%s (%s-%s) ", r[i].air_code, r[i].origin, r[i].dest);
      }
    }
    
  } else if(st == ROUTE) {
    printf("Searching by route...\n");
    for(int i=0; i < length; i++) {
      if(strcmp(r[i].origin, key1) == 0 && strcmp(r[i].dest, key2) == 0) {
        matches++;

        // count in each month
        m1 += r[i].passenger_count[0];
        m2 += r[i].passenger_count[1];
        m3 += r[i].passenger_count[2];
        m4 += r[i].passenger_count[3];
        m5 += r[i].passenger_count[4];
        m6 += r[i].passenger_count[5];

        printf("%s (%s-%s) ", r[i].air_code, r[i].origin, r[i].dest);
      }
    }
  }

  total = m1 + m2 + m3 + m4 + m5 + m6;
  // print statistics
  if(matches == 0) 
      printf("No matches found!\n"); 
    else
      printStatistics(matches, total, m1, m2, m3, m4, m5, m6);
};

void printMenu() {
  printf( "\n\n######### Airline Route Records Database MENU #########\n" );
  printf( "1. Search by Route\n" );
  printf( "2. Search by Origin Airport\n" );
  printf( "3. Search by Destination Airport\n" );
  printf( "4. Search by Airline\n" );
  printf( "5. Quit\n" );
  printf( "Enter your selection: " );
};