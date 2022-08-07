#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_LENGTH = 10;

struct Student {
  int id;
  char name[MAX_LENGTH];
  int age;
  float gpa;
};

struct Student *createStudent(int id, char *name, int age, float gpa) {
  struct Student *student = malloc(sizeof(struct Student));
  student->id = id;
  strcpy(student->name, name);
  student->age = age;
  student->gpa = gpa;
  return student;
}

void printStudent(struct Student *student) {
  printf("Student: %d %s %d %f\n", student->id, student->name, student->age,
         student->gpa);
}

struct StudentDynamic {
  int id;
  unsigned int nameLength;
  char *name;
  int age;
  float gpa;
};

struct StudentDynamic *createStudentDynamic(int id, char *name, int age,
                                            float gpa) {
  struct StudentDynamic *student = malloc(sizeof(struct StudentDynamic));
  student->id = id;
  student->name = name;
  student->nameLength = strlen(name);
  student->age = age;
  student->gpa = gpa;
  return student;
}

void printStudentDynamic(struct StudentDynamic *student) {
  printf("Student: %d %s %d %f\n", student->id, student->name, student->age,
         student->gpa);
}

int main() {
  struct Student *student = createStudent(1, "John loves me", 20, 3.5);
  printStudent(student);
  free(student);

  struct StudentDynamic *studentDynamic =
      createStudentDynamic(1, "John loves me", 20, 3.5);
  printStudentDynamic(studentDynamic);
  free(studentDynamic);
  return 0;
}
