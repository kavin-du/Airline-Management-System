#include <stdio.h>

#ifndef ROUTE_RECORDS_H
#define ROUTE_RECORDS_H


typedef struct RouteRecord {
  char origin[3];
  char dest[3];
  char air_code[2];
  int passenger_count[6];
} RouteRecord;

typedef enum SearchType { 
  ROUTE, 
  ORIGIN, 
  DESTINATION,
  AIRLINE 
} SearchType;

// function definitions

RouteRecord* createRecords(FILE*);

int fillRecords(RouteRecord*, FILE*);

int findAirlineRoute(RouteRecord*, int, const char*, const char*, const char*, int);

void searchRecords(RouteRecord* r, int, const char*, const char*, SearchType);

void printMenu(void);

#endif