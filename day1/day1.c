#include <stdio.h>
#include <stdlib.h>

void printTable(int *number, int size);
int compareFunction(const void *first, const void *second);

int main() {
  // Open input.txt
  const char *fname = "input.txt";
  FILE *fp = fopen(fname, "r");

  if (!fp) {
    perror("File opening failed");
    return -1;
  }

  char line[256];
  int capacity = 1000;

  int *left = malloc(capacity * sizeof(int));
  int *right = malloc(capacity * sizeof(int));

  if (!left || !right) {
    perror("malloc");
    return 1;
  }

  int n = 0;
  while (fgets(line, sizeof(line), fp)) {
    if (n >= capacity) {
      capacity *= 2;
      left = realloc(left, capacity * sizeof(int));
      right = realloc(right, capacity * sizeof(int));
    }
    sscanf(line, "%d %d", &left[n], &right[n]);
    // printf("%d   %d\n", left[n], right[n]);
    n++;
  }
  fclose(fp);

  // Sort both array
  qsort(left, n, sizeof(int), compareFunction);
  qsort(right, n, sizeof(int), compareFunction);

  // printTable(left, n);
  // printTable(right, n);

  int maxDistance = 0;

  for (int i = 0; i < n; i++) {
    int distance = abs(left[i] - right[i]);
    maxDistance += distance;
  }

  printf("The result is %d\n", maxDistance);

  // Similarity score
  int similarityScore = 0;

  for (int i = 0; i < n; i++) {
    int count = 0;
    for (int j = 0; j < n; j++) {
      if (left[i] == right[j]) {
        count++;
      }
    }
    similarityScore = similarityScore + count * left[i];
  }

  printf("Similarity Score : %d\n", similarityScore);

  free(left);
  free(right);

  return 0;
}

void printTable(int *number, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d", number[i]);
  }
  printf("\n");
}

int compareFunction(const void *first, const void *second) {
  int firstInt = *(const int *)first;
  int secondInt = *(const int *)second;
  if (firstInt < secondInt)
    return -1;
  if (firstInt > secondInt)
    return 1;
  return 0;
}
