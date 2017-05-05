# include <stdio.h>

/**
* Takes a string as input and determines its size by counting the elements until '\0'.
* The iteration is done via array index.
*
* @param input String
* @return The size of the input string
*/
int strLengthI (const char input[]){
  int count = 0;
  while (input[count] != '\0') {
    count++;
  }
  return count;
}

/**
* Takes a string as input and determines its size by counting the elements until '\0'.
* The iteration is done via pointer arithmetics.
*
* @param input String
* @return The size of the input string
*/
int strLengthP (const char input[]){
  int count = 0;
  char *currentChar = &(input[0]);
  while ( *currentChar != '\0') {
    currentChar += 1;
    count++;
  }
  return count;
}

int main(const int argc, const char *argv[]) {
  if (argc != 2) {
    printf("wrong input\n");
  } else {
    printf("%d\n", strLengthI(argv[1]));
    printf("%d\n", strLengthP(argv[1]));
  }
  return 0;
}
