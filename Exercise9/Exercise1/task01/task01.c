# include <stdio.h>

/**
* Just prints out a bunch of typesizes.
*/
int main(void) {
  printf("char %d\n", sizeof(char));
  printf("short %d\n", sizeof(short));
  printf("int %d\n", sizeof(int));
  printf("long %d\n", sizeof(long));
  printf("long long %d\n", sizeof(long long));
  printf("float %d\n", sizeof(float));
  printf("double %d\n", sizeof(double));
  printf("long double %d\n", sizeof(long double));
  printf("pointer %d\n", sizeof(char*));
}
