int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

const int array2[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

static int array3[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

unsigned int uninitialized_array[1000];

char string[4] = {'A','B','C','0'};

float *ptr;

int main() {
  int element = array[4];
  int element2 = array3[4];
  
  return 0;
}
