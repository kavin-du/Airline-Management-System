#include <stdio.h>
#include "route-records.h"

int main() {
  char* filepath = "data.csv";

  FILE* fp = fopen(filepath, "r");

  createRecords(fp);

  return 0;
}