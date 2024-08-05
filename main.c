#include <stdio.h>


// The layer sizes from left to right.
// 784 corresponds to the number of pixels
// in the images from the database. 10 
// corresponds to the number of possible outputs,
// namely the digits 0-9. The two internal layers
// are arbitrarily set to size 16 each. 
#define INPUT_LAYER_SIZE 784
#define OUTPUT_LAYER_SIZE 10
#define INTERNAL_LAYER_ONE_SIZE 16
#define INTERNAL_LAYER_TWO_SIZE 16

#define MAX_LAYER_SIZE 784

#define NUM_CONNECTION_FABRICS 3

void print_weights(float arr[NUM_CONNECTION_FABRICS][MAX_LAYER_SIZE][MAX_LAYER_SIZE]) {
  for(int i = 0; i < NUM_CONNECTION_FABRICS; i++) {
    printf("Printing connections for layer %d \n", i);
    for(int j = 0; j < MAX_LAYER_SIZE; j++) {
      for(int k = 0; k < MAX_LAYER_SIZE; k++) {
        printf("%f ", arr[i][j][k]);
      }
      printf("\n");
    }
  }
}

int main() {
  // We preallocate a 3D array to keep track of the weights.
  float weights[NUM_CONNECTION_FABRICS][MAX_LAYER_SIZE][MAX_LAYER_SIZE] = {0};
  print_weights(weights);
  return 0;
}
