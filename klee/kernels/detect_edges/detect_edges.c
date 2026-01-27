/* masks for sobel operator */

#include "klee/klee.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define SOBEL 3

short sobel_mask_0[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

short sobel_mask_1[3][3] = {{2, 1, 0}, {1, 0, -1}, {0, -1, -2}};

short sobel_mask_2[3][3] = {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}};
short sobel_mask_3[3][3] = {{0, -1, -2}, {1, 0, -1}, {2, 1, 0}};

short sobel_mask_4[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

short sobel_mask_5[3][3] = {{-2, -1, 0}, {-1, 0, 1}, {0, 1, 2}};

short sobel_mask_6[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

short sobel_mask_7[3][3] = {{0, 1, 2}, {-1, 0, 1}, {-2, -1, 0}};

short **allocate_image_array(length, width) long length, width;
{
  int i, j;

  short **the_array = (short **)malloc(length * sizeof(short *));
  for (i = 0; i < length; i++) {
    the_array[i] = (short *)malloc(width * sizeof(short));
    if (the_array[i] == NULL) {
      // printf("\n\tmalloc of the_image[%d] failed", i);
    } /* ends if */
  }   /* ends loop over i */

  for (i = 0; i < length; i++)
    for (j = 0; j < width; j++)
      the_array[i][j] = 0;

  return (the_array);
}

int setup_masks(detect_type, mask_0, mask_1, mask_2, mask_3, mask_4, mask_5,
                mask_6, mask_7) int detect_type;
short mask_0[3][3], mask_1[3][3], mask_2[3][3], mask_3[3][3], mask_4[3][3],
    mask_5[3][3], mask_6[3][3], mask_7[3][3];
{
  int i, j;

  // if(detect_type == KIRSCH){
  //     for(i=0; i<3; i++){
  //       for(j=0; j<3; j++){
  //         mask_0[i][j] = kirsch_mask_0[i][j];
  //         mask_1[i][j] = kirsch_mask_1[i][j];
  //         mask_2[i][j] = kirsch_mask_2[i][j];
  //         mask_3[i][j] = kirsch_mask_3[i][j];
  //         mask_4[i][j] = kirsch_mask_4[i][j];
  //         mask_5[i][j] = kirsch_mask_5[i][j];
  //         mask_6[i][j] = kirsch_mask_6[i][j];
  //         mask_7[i][j] = kirsch_mask_7[i][j];
  //       }
  //     }
  // }  /* ends if detect_type == KIRSCH */

  // if(detect_type == PREWITT){
  //     for(i=0; i<3; i++){
  //       for(j=0; j<3; j++){
  //         mask_0[i][j] = prewitt_mask_0[i][j];
  //         mask_1[i][j] = prewitt_mask_1[i][j];
  //         mask_2[i][j] = prewitt_mask_2[i][j];
  //         mask_3[i][j] = prewitt_mask_3[i][j];
  //         mask_4[i][j] = prewitt_mask_4[i][j];
  //         mask_5[i][j] = prewitt_mask_5[i][j];
  //         mask_6[i][j] = prewitt_mask_6[i][j];
  //         mask_7[i][j] = prewitt_mask_7[i][j];
  //       }
  //     }
  // }  /* ends if detect_type == PREWITT */

  if (detect_type == SOBEL) {
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        mask_0[i][j] = sobel_mask_0[i][j];
        mask_1[i][j] = sobel_mask_1[i][j];
        mask_2[i][j] = sobel_mask_2[i][j];
        mask_3[i][j] = sobel_mask_3[i][j];
        mask_4[i][j] = sobel_mask_4[i][j];
        mask_5[i][j] = sobel_mask_5[i][j];
        mask_6[i][j] = sobel_mask_6[i][j];
        mask_7[i][j] = sobel_mask_7[i][j];
      }
    }
  } /* ends if detect_type == SOBEL */

  return (1);
}

int perform_convolution(image, out_image, detect_type, threshold, rows, cols,
                        bits_per_pixel, high) short **image,
    **out_image;
int detect_type, high, threshold;
long rows, cols, bits_per_pixel;
{

  char response[80];
  int a, b, i, is_present, j, sum;

  short mask_0[3][3], mask_1[3][3], mask_2[3][3], mask_3[3][3], mask_4[3][3],
      mask_5[3][3], mask_6[3][3], mask_7[3][3], max, min, new_hi, new_low;

  setup_masks(detect_type, mask_0, mask_1, mask_2, mask_3, mask_4, mask_5,
              mask_6, mask_7);

  new_hi = 250;
  new_low = 16;
  if (bits_per_pixel == 4) {
    new_hi = 10;
    new_low = 3;
  }

  min = 0;
  max = 255;
  if (bits_per_pixel == 4)
    max = 16;

  /* clear output image array */
  for (i = 0; i < rows; i++)
    for (j = 0; j < cols; j++)
      out_image[i][j] = 0;

  // printf("\n ");

  for (i = 1; i < rows - 1; i++) {
    // if( (i%10) == 0){ printf("%4d", i); }
    for (j = 1; j < cols - 1; j++) {

      /* Convolve for all 8 directions */

      /* 0 direction */

      sum = 0;
      for (a = -1; a < 2; a++) {
        for (b = -1; b < 2; b++) {
          sum = sum + image[i + a][j + b] * mask_0[a + 1][b + 1];
          // klee_assert(sum != 4);
        }
      }
#ifdef MERGE
        klee_open_merge();
#endif      
      if (sum > max)
        sum = max;
#ifdef MERGE
        klee_close_merge();
#endif
#ifdef MERGE
        klee_open_merge();
#endif
      if (sum < 0)
        sum = 0;
#ifdef MERGE
        klee_close_merge();
#endif
      /* Correction 12-27-92
         see file header for
         details. */
#ifdef MERGE
        klee_open_merge();
#endif
      if (sum > out_image[i][j])
        out_image[i][j] = sum;
#ifdef MERGE
        klee_close_merge();
#endif

      /* 1 direction */
      sum = 0;
      for (a = -1; a < 2; a++) {
        for (b = -1; b < 2; b++) {
          sum = sum + image[i + a][j + b] * mask_1[a + 1][b + 1];
        }
      }
#ifdef MERGE
        klee_open_merge();
#endif
      if (sum > max)
        sum = max;
#ifdef MERGE
        klee_close_merge();
#endif

#ifdef MERGE
        klee_open_merge();
#endif
      if (sum < 0)
        sum = 0;
#ifdef MERGE
        klee_close_merge();
#endif
      /* Correction 12-27-92
         see file header for
         details. */
#ifdef MERGE
        klee_open_merge();
#endif
      if (sum > out_image[i][j])
        out_image[i][j] = sum;
#ifdef MERGE
        klee_close_merge();
#endif
      // klee_assert(sum != 5);

      /* 2 direction */

      sum = 0;
      for (a = -1; a < 2; a++) {
        for (b = -1; b < 2; b++) {
          sum = sum + image[i + a][j + b] * mask_2[a + 1][b + 1];
        }
      }
#ifdef MERGE
        klee_open_merge();
#endif
      if (sum > max)
        sum = max;
#ifdef MERGE
        klee_close_merge();
#endif
#ifdef MERGE
        klee_open_merge();
#endif
      if (sum < 0)
        sum = 0;
#ifdef MERGE
        klee_close_merge();
#endif
      /* Correction 12-27-92
         see file header for
         details. */
#ifdef MERGE
        klee_open_merge();
#endif
      if (sum > out_image[i][j])
        out_image[i][j] = sum;
#ifdef MERGE
        klee_close_merge();
#endif

      /* 3 direction */

      sum = 0;
      for (a = -1; a < 2; a++) {
        for (b = -1; b < 2; b++) {
          sum = sum + image[i + a][j + b] * mask_3[a + 1][b + 1];
        }
      }
#ifdef MERGE
        klee_open_merge();
#endif
      if (sum > max)
        sum = max;
#ifdef MERGE
        klee_close_merge();
#endif
#ifdef MERGE
        klee_open_merge();
#endif
      if (sum < 0)
        sum = 0;
#ifdef MERGE
        klee_close_merge();
#endif
      /* Correction 12-27-92
         see file header for
         details. */
#ifdef MERGE
        klee_open_merge();
#endif
      if (sum > out_image[i][j])
        out_image[i][j] = sum;
#ifdef MERGE
        klee_close_merge();
#endif

      /* 4 direction */

      sum = 0;
      for (a = -1; a < 2; a++) {
        for (b = -1; b < 2; b++) {
          sum = sum + image[i + a][j + b] * mask_4[a + 1][b + 1];
        }
      }
#ifdef MERGE
        klee_open_merge();
#endif
      if (sum > max)
        sum = max;
#ifdef MERGE
        klee_close_merge();
#endif
#ifdef MERGE
        klee_open_merge();
#endif
      if (sum < 0)
        sum = 0;
#ifdef MERGE
        klee_close_merge();
#endif
      /* Correction 12-27-92
         see file header for
         details. */
#ifdef MERGE
        klee_open_merge();
#endif
      if (sum > out_image[i][j])
        out_image[i][j] = sum;
#ifdef MERGE
        klee_close_merge();
#endif

      /* 5 direction */

      sum = 0;
      for (a = -1; a < 2; a++) {
        for (b = -1; b < 2; b++) {
          sum = sum + image[i + a][j + b] * mask_5[a + 1][b + 1];
        }
      }

#ifdef MERGE
        klee_open_merge();
#endif
      if (sum > max)
        sum = max;
#ifdef MERGE
         klee_close_merge();
#endif
#ifdef MERGE
        klee_open_merge();
#endif
      if (sum < 0)
        sum = 0;
#ifdef MERGE
         klee_close_merge();
#endif
      /* Correction 12-27-92
         see file header for
         details. */
#ifdef MERGE
         klee_open_merge();   
#endif
      if (sum > out_image[i][j])
        out_image[i][j] = sum;
#ifdef MERGE
         klee_close_merge();
#endif
      /* 6 direction */
      sum = 0;
      for (a = -1; a < 2; a++) {
        for (b = -1; b < 2; b++) {
          sum = sum + image[i + a][j + b] * mask_6[a + 1][b + 1];
        }
      }
#ifdef MERGE
         klee_open_merge();
#endif
      if (sum > max)
        sum = max;
#ifdef MERGE
         klee_close_merge();
#endif
#ifdef MERGE
         klee_open_merge();
#endif
      if (sum < 0)
        sum = 0;
#ifdef MERGE
         klee_close_merge();
#endif
      /* Correction 12-27-92
         see file header for
         details. */
#ifdef MERGE
         klee_open_merge();   
#endif
      if (sum > out_image[i][j])
        out_image[i][j] = sum;
#ifdef MERGE
         klee_close_merge();
#endif

      /* 7 direction */

      sum = 0;
      for (a = -1; a < 2; a++) {
        for (b = -1; b < 2; b++) {
          sum = sum + image[i + a][j + b] * mask_7[a + 1][b + 1];
        }
      }
#ifdef MERGE
         klee_open_merge();
#endif
      if (sum > max)
        sum = max;
#ifdef MERGE
         klee_close_merge();
#endif
#ifdef MERGE
         klee_open_merge();
#endif
      if (sum < 0)
        sum = 0;
#ifdef MERGE
         klee_close_merge();
#endif
      /* Correction 12-27-92
         see file header for
         details. */
#ifdef MERGE
         klee_open_merge();
#endif
      if (sum > out_image[i][j])
        out_image[i][j] = sum;
#ifdef MERGE
         klee_close_merge();
#endif

    } /* ends loop over j */
  }   /* ends loop over i */

  /* if desired, threshold the output image */
  if (threshold == 1) {
    for (i = 0; i < rows; i++) {
      for (j = 0; j < cols; j++) {
#ifdef MERGE
        klee_open_merge();
#endif
        if (out_image[i][j] > high) {
          out_image[i][j] = new_hi;
        } else {
          out_image[i][j] = new_low;
        }
#ifdef MERGE
        klee_close_merge();
#endif
      }
    }
  } /* ends if threshold == 1 */

  return (1);
} /* ends perform_convolution */

int detect_edges(the_image, out_image, detect_type, threshold, high, rows, cols,
                 bits_per_pixel) int detect_type,
    high, threshold;
long rows, cols, bits_per_pixel;
short **the_image, **out_image;

{
  perform_convolution(the_image, out_image, detect_type, threshold, rows, cols,
                      bits_per_pixel, high);
  // fix_edges(out_image, 1, rows, cols);
  return (1);
}

int main() {

  int detect_type = SOBEL;
  int threshold;
  int high;
  int bits_per_pixel;
  long length = SIZE;
  long width = SIZE;

  short **the_image;
  short **out_image;

  // klee_make_symbolic(&length, sizeof(long), "length");
  // klee_make_symbolic(&width, sizeof(long), "width");

  // klee_assume(0 < length);
  // klee_assume(length < 10);

  // klee_assume(0 < width);
  // klee_assume(width < 10);
  assert(0 < length && length < 10);
  assert(0 < width && width < 10);

  the_image = allocate_image_array(length, width);
  out_image = allocate_image_array(length, width);

  for (int i = 0; i < length; i++) {
    klee_make_symbolic(the_image[i], width * sizeof(short), "the_image");
  }

  klee_make_symbolic(&high, sizeof(high), "high");
  klee_make_symbolic(&bits_per_pixel, sizeof(bits_per_pixel), "bits_per_pixel");
  klee_make_symbolic(&threshold, sizeof(threshold), "threshold");

  detect_edges(the_image, out_image, detect_type, threshold, high, length,
               width, bits_per_pixel);

   // FIXME : check some condition on out_image
   /*for (int i = 0; i < length; i++) {*/
      /*for (int j = 0; j < width; j++) {*/
         /*printf("i = %d, j = %d\n", i, j);*/
         /*klee_assert(out_image[i][j] > 128);*/
      /*}*/
   /*}*/

  return 0;
}
