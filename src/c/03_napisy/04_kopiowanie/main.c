#include <stdio.h>

void copyVersionA(const char *source, char *dest) {
  while ((*dest++ = *source++) != '\0') {
  }
}

void copyVersionB(const char *source, char *dest) {
  while (1) {
    *dest = *source;
    if (*dest == '\0') {
      break;
    }
    source++;
    dest++;
  }
}

int main(void) {
  const char source[] = "Hello World";
  char bufferA[50];
  char bufferB[50];

  copyVersionA(source, bufferA);
  copyVersionB(source, bufferB);

  printf("source = %s\n", source);
  printf("bufferA = %s\n", bufferA);
  printf("bufferB = %s\n", bufferB);

  return 0;
}
