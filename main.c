#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float **allocate_matrix(int rows, int cols) {
  float **mat = (float **)malloc(rows * sizeof(float *));
  if (mat == NULL) {
    perror("malloc");
  }

  for (int i = 0; i < rows; i++) {
    mat[i] = (float *)malloc(cols * sizeof(float));
    if (mat[i] == NULL) {
      perror("malloc");
    }
  }

  return mat;
}

void free_matrix(float **mat, int rows) {
  for (int i = 0; i < rows; i++) {
    free(mat[i]);
  }
  free(mat);
}

int main() {
  int layer_sizes[] = {784, 16, 16, 10};
  int num_layers = sizeof(layer_sizes) / sizeof(layer_sizes[0]);

  float ***weights = (float ***)malloc((num_layers - 1) * sizeof(float **));
  if (weights == NULL) {
    perror("malloc");
    return 1;
  }

  for (int i = 0; i < num_layers - 1; i++) {
    weights[i] = allocate_matrix(layer_sizes[i], layer_sizes[i + 1]);
  }

  for (int i = 0; i < num_layers - 1; i++) {
    for (int j = 0; j < layer_sizes[i]; j++) {
      for (int k = 0; k < layer_sizes[i + 1]; k++) {
        weights[i][j][k] = (float)rand() / RAND_MAX;
      }
    }
  }

  for (int i = 1; i < 2; i++) {
    for (int j = 0; j < layer_sizes[i]; j++) {
      for (int k = 0; k < layer_sizes[i + 1]; k++) {
        printf("%f", weights[i][j][k]);
      }
      printf("\n");
    }
  }

  for (int i = 0; i < num_layers - 1; i++) {
    free_matrix(weights[i], layer_sizes[i]);
  }
  free(weights);

  return 0;
}
