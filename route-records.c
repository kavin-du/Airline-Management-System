
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

    // printf("%s %s %s\n", line[0], line[1], line[2]);

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

    return findAirlineRoute(r, length, origin, destination, airline, ++curIdx);
};

void searchRecords(RouteRecord* r, int length, const char*key1, const char* key2, SearchType st);

void printMenu();