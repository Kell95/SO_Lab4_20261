#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  clock_t start = clock();

  if (argc != 2) {
    fprintf(stderr, "Error: invalid params, usage fibonacci <n>\n");
    return 1;
  }

  int n = atoi(argv[1]);
  long long *arr = malloc(sizeof(long long) * n);
  arr[0] = 1;
  arr[1] = 2;

  for (int i = 2; i < n; i++) {
    arr[i] = arr[i - 2] + arr[i - 1];
  }

  clock_t end = clock();

  double time_spent = ((double)(end - start)) / CLOCKS_PER_SEC;

  if (n <= 100) { // ommit large outputs
    for (int i = 0; i < n; i++) {
      printf("%lld ", arr[i]);
    }
    printf("\n");
  }
  printf("time spent: %f seconds\n", time_spent);

  free(arr);

  return 0;
}
