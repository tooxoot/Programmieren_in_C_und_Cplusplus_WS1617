#include <stdio.h>

int globalvar = 1;

int main() {
  modtest();
  printf("globalvar = %d\n", globalvar);
}
