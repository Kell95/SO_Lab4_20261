#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
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

  for (int i = 0; i < n; i++) {
    printf("%lld ", arr[i]);
  }
  printf("\n");

  free(arr);

  return 0;
}
