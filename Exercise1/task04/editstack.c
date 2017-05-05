#include <stdio.h>
/**
* Skips the line of code following the call of modify by creating a char variable
* and adding to a not allocated position which is the return addres of modify.
*/
void modify(void) {
    char *firstOnStack;
    (&firstOnStack)[2] += 1;
}

int main(void) {
 int i = 42;
 modify();
 i = 0;
 printf("The answer is %d!\n", i);
}
