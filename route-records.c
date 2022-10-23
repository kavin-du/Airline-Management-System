
#include <stdlib.h>
#include "route-records.h"

RouteRecord* createRecords(FILE* fileIn) {

  if(!fileIn) {
    printf("Cannot open file");
    return NULL;
  }

  int rows = -1; // skipping the first line

  char buffer[50]; // temporary buffer for reading lines

  // count the total rows
  while(fgets(buffer, 50, fileIn)) {
    rows++;
  }

  // dynamically allocating array of RouteRecords
  RouteRecord* routesList = (RouteRecord*)malloc(sizeof(RouteRecord) * rows);

  printf("Total records: %d\n", rows);

  // initialize only the passenger count
  for(int i=0; i < rows; i++) {
    routesList[i] = (RouteRecord){ .passenger_count = {0,0,0,0,0,0}};
  }

  return routesList;
};


int fillRecords(RouteRecord* r, FILE* fileIn);

int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx);

void searchRecords(RouteRecord* r, int length, const char*key1, const char* key2, SearchType st);

void printMenu();