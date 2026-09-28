#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 32

struct Student {
  int id;
  char name[MAX_LENGTH];
  int age;
  float gpa;
};

struct Student *createStudent(int id, const char *name, int age, float gpa) {
  struct Student *student = malloc(sizeof(*student));
  if (student == NULL) {
    return NULL;
  }

  student->id = id;
  snprintf(student->name, sizeof(student->name), "%s", name);
  student->age = age;
  student->gpa = gpa;
  return student;
}

void printStudent(const struct Student *student) {
  printf("Student: %d %s %d %.2f\n", student->id, student->name, student->age,
         student->gpa);
}

struct StudentDynamic {
  int id;
  size_t nameLength;
  char *name;
  int age;
  float gpa;
};

struct StudentDynamic *createStudentDynamic(int id, const char *name, int age,
                                            float gpa) {
  struct StudentDynamic *student = malloc(sizeof(*student));
  if (student == NULL) {
    return NULL;
  }

  student->nameLength = strlen(name);
  student->name = malloc(student->nameLength + 1);
  if (student->name == NULL) {
    free(student);
    return NULL;
  }

  memcpy(student->name, name, student->nameLength + 1);
  student->id = id;
  student->age = age;
  student->gpa = gpa;
  return student;
}

void printStudentDynamic(const struct StudentDynamic *student) {
  printf("Student: %d %s %d %.2f\n", student->id, student->name, student->age,
         student->gpa);
}

void destroyStudentDynamic(struct StudentDynamic *student) {
  if (student == NULL) {
    return;
  }
  free(student->name);
  free(student);
}

int main(void) {
  struct Student *student = createStudent(1, "John loves me", 20, 3.5f);
  if (student == NULL) {
    return EXIT_FAILURE;
  }
  printStudent(student);
  free(student);

  struct StudentDynamic *studentDynamic =
      createStudentDynamic(1, "John loves me", 20, 3.5f);
  if (studentDynamic == NULL) {
    return EXIT_FAILURE;
  }
  printStudentDynamic(studentDynamic);
  destroyStudentDynamic(studentDynamic);

  return EXIT_SUCCESS;
}
