#include <stdio.h>
#include "route-records.h"

int main() {
  char* filepath = "data.csv";

  FILE* fp = fopen(filepath, "r");

  RouteRecord* routes = createRecords(fp);

  int count = fillRecords(routes, fp);

  printf("total count:  %d\n", count);

  return 0;
}