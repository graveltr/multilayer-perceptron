#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_SIZE 784
#define MAX_LINE_LENGTH 4096

// Function to trim newline characters from a string
void trim_newline(char *str) {
  size_t len = strlen(str);
  if (len > 0 && str[len - 1] == '\n') {
    str[len - 1] = '\0';
  }
}

void read_in_training_data(int **images, int *labels, int num_training_images) {
  const char *csv_file_path = "/usr/src/myapp/mnist_handwritten_train.csv";
  FILE *file = fopen(csv_file_path, "r");
  if (!file) {
    perror("File opening failed");
  }

  int image_idx = 0;
  char line[MAX_LINE_LENGTH];
  while (fgets(line, sizeof(line), file) && image_idx < num_training_images) {
    trim_newline(line);

    char *token = strtok(line, ",");
    int i = 0;

    for (; i < VECTOR_SIZE && token != NULL; i++) {
      images[image_idx][i] = atoi(token);
      token = strtok(NULL, ",");
    }

    if (token != NULL) {
      labels[image_idx] = atoi(token);
    } else {
      perror("Missing label");
    }

    image_idx++;
  }
}

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

  // First, we allocate the weight matrices.
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

  // Next, we need to read in the training data.
  int num_training_images = 3;
  int num_pixels_per_image = 784;
  int **images = (int **)malloc(num_training_images * sizeof(int *));
  int *labels = (int *)malloc(num_training_images * sizeof(int));
  for (int i = 0; i < num_training_images; i++) {
    images[i] = (int *)malloc(num_pixels_per_image * sizeof(int));
  }

  read_in_training_data(images, labels, num_training_images);

  for (int i = 0; i < num_training_images; i++) {
    printf("leading data: ");
    for (int j = 0; j < 10; j++) {
      printf("%d ", images[i][j]);
    }
    printf("\n");
    printf("label: %d \n", labels[i]);
  }

  // CLEAN UP
  for (int i = 0; i < num_layers - 1; i++) {
    free_matrix(weights[i], layer_sizes[i]);
  }
  free(weights);

  for (int i = 0; i < num_training_images; i++) {
    free(images[i]);
  }
  free(images);

  free(labels);

  return 0;
}
