#include <stdio.h>

#ifndef ROUTE_RECORDS_H
#define ROUTE_RECORDS_H


typedef struct RouteRecord {
  char origin[4];
  char dest[4];
  char air_code[3];
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