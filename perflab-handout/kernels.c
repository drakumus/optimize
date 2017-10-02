#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following student struct 
 */
student_t student = {
  "Rohan Cheeniyil",     /* Full name */
  "u0914584@utah.edu",  /* Email address */

};

/******************************************************
 * PINWHEEL KERNEL
 *
 * Your different versions of the pinwheel kernel go here
 ******************************************************/

/* 
 * naive_pinwheel - The naive baseline version of pinwheel 
 */
char naive_pinwheel_descr[] = "naive_pinwheel: baseline implementation";
void naive_pinwheel(pixel *src, pixel *dest)
{
  int qi, qj, i, j;

  /* qi & qj are column and row of quadrant
     i & j are column and row within quadrant */

  /* Loop over 4 quadrants: */
  for (qi = 0; qi < 2; qi++)
    for (qj = 0; qj < 2; qj++)
      /* Loop within quadrant: */
      for (i = 0; i < src->dim/2; i++)
        for (j = 0; j < src->dim/2; j++) {
          int s_idx = RIDX((qj * src->dim/2) + i,
                           j + (qi * src->dim/2), src->dim);
          int d_idx = RIDX((qj * src->dim/2) + src->dim/2 - 1 - j,
                           i + (qi * src->dim/2), src->dim);
          dest[d_idx].red = (src[s_idx].red
                             + src[s_idx].green
                             + src[s_idx].blue) / 3;
          dest[d_idx].green = (src[s_idx].red
                               + src[s_idx].green
                               + src[s_idx].blue) / 3;
          dest[d_idx].blue = (src[s_idx].red
                              + src[s_idx].green
                              + src[s_idx].blue) / 3;
        }
}

/* 
 * pinwheel - Your current working version of pinwheel
 * IMPORTANT: This is the version you will be graded on
 */
char pinwheel_descr[] = "pinwheel: Current working version";
void pinwheel(pixel *src, pixel *dest)
{
  unsigned int qi, qj, i, j, s_idx, d_idx;
  pixel src_load;
  int size = src->dim/2;
    /* qi & qj are column and row of quadrant
       i & j are column and row within quadrant */
  
    /* Loop over 4 quadrants: */
    for (qi = 0; qi < 2; qi++)
      for (qj = 0; qj < 2; qj++)
        /* Loop within quadrant: */
        for (i = 0; i < size; i++)
          for (j = 0; j < size; j++) {
            s_idx = RIDX((qj * size) + i,
                             j + (qi * size), src->dim);
            d_idx = RIDX((qj * size) + size - 1 - j,
                             i + (qi * size), src->dim);
            src_load = src[s_idx];//1 load on src
            dest[d_idx].red = (src_load.red
                               + src_load.green
                               + src_load.blue) / 3;
            dest[d_idx].green = (src_load.red
                                 + src_load.green
                                 + src_load.blue) / 3;
            dest[d_idx].blue = (src_load.red
                                + src_load.green
                                + src_load.blue) / 3;
          }
}

char pinwheel_descr1[] = "pinwheel: unroll1";
void pinwheelRoll1(pixel *src, pixel *dest)
{
  unsigned int qi, qj, i, j, s_idx0, s_idx1, d_idx0, d_idx1;
  pixel src_load0;
  pixel src_load1;
  int size = src->dim/2;
    /* qi & qj are column and row of quadrant
       i & j are column and row within quadrant */
  
    /* Loop over 4 quadrants: */
    for (qi = 0; qi < 2; qi++)
      for (qj = 0; qj < 2; qj++)
        /* Loop within quadrant: */
        for (i = 0; i < size; i++){
          for (j = 0; j < size; j+=2) 
          {
            s_idx0 = RIDX((qj * size) + i,
                             j + (qi * size), src->dim);
            d_idx0 = RIDX((qj * size) + size - 1 - j,
                             i + (qi * size), src->dim);
            s_idx1 = RIDX((qj * size) + i,
                             (j+1) + (qi * size), src->dim);
            d_idx1 = RIDX((qj * size) + size - 1 - (j+1),
                             i + (qi * size), src->dim);
            src_load0 = src[s_idx0];//1 load on src
            src_load1 = src[s_idx1];
            dest[d_idx0].red = (src_load0.red
                               + src_load0.green
                               + src_load0.blue) / 3;
            dest[d_idx0].green = (src_load0.red
                                 + src_load0.green
                                 + src_load0.blue) / 3;
            dest[d_idx0].blue = (src_load0.red
                                + src_load0.green
                                + src_load0.blue) / 3;
            dest[d_idx1].red = (src_load1.red
                                + src_load1.green
                                + src_load1.blue) / 3;
            dest[d_idx1].green = (src_load1.red
                                + src_load1.green
                                + src_load1.blue) / 3;
            dest[d_idx1].blue = (src_load1.red
                                + src_load1.green
                                + src_load1.blue) / 3;
             
          }
          //printf("itter: %d, size: %d, j: %d\n",i*j , size, j);
          
          for (; j < size; j++)
          {
            s_idx0 = RIDX((qj * size) + i,
                    j + (qi * size), size);
            d_idx0 = RIDX((qj * size) + size - 1 - j,
                    i + (qi * size), size);
            src_load0 = src[s_idx0];//1 load on src
            dest[d_idx0].red = (src_load0.red
                          + src_load0.green
                          + src_load0.blue) / 3;
            dest[d_idx0].green = (src_load0.red
                            + src_load0.green
                            + src_load0.blue) / 3;
            dest[d_idx0].blue = (src_load0.red
                          + src_load0.green
                          + src_load0.blue) / 3;
          }

          //printf("size: %d, j: %d", size, j);
        }
}

char pinwheel_descr2[] = "pinwheel: unroll2";
void pinwheelRoll2(pixel *src, pixel *dest)
{
  unsigned int qi, qj, i, j, s_idx0_0, 
               s_idx0_1, s_idx1_0, s_idx1_1, 
               d_idx0_0, d_idx0_1, d_idx1_0, d_idx1_1;
  pixel src_load0_0;
  pixel src_load0_1;
  pixel src_load1_0;
  pixel src_load1_1;
  int size = src->dim/2;
    /* qi & qj are column and row of quadrant
       i & j are column and row within quadrant */
  
    /* Loop over 4 quadrants: */
    for (qi = 0; qi < 2; qi++)
      for (qj = 0; qj < 2; qj++){
        /* Loop within quadrant: */
        for (i = 0; i < size; i+=2){
          for (j = 0; j < size; j+=2) 
          {
            s_idx0_0 = RIDX((qj * size) + i,
                             j + (qi * size), src->dim);
            s_idx0_1 = RIDX((qj * size) + (i+1),
                             j + (qi * size), src->dim);
            d_idx0_0 = RIDX((qj * size) + size - 1 - j,
                             i + (qi * size), src->dim);
            d_idx0_1 = RIDX((qj * size) + size - 1 - j,
                             (i+1) + (qi * size), src->dim);
            s_idx1_0 = RIDX((qj * size) + i,
                             (j+1) + (qi * size), src->dim);
            s_idx1_1 = RIDX((qj * size) + (i+1),
                             (j+1) + (qi * size), src->dim);
            d_idx1_0 = RIDX((qj * size) + size - 1 - (j+1),
                             i + (qi * size), src->dim);
            d_idx1_1 = RIDX((qj * size) + size - 1 - (j+1),
                             (i+1) + (qi * size), src->dim);
            
            src_load0_0 = src[s_idx0_0];//1 load on src
            src_load0_1 = src[s_idx0_1];
            src_load1_0 = src[s_idx1_0];
            src_load1_1 = src[s_idx1_1];
            dest[d_idx0_0].red = (src_load0_0.red
                               + src_load0_0.green
                               + src_load0_0.blue) / 3;
            dest[d_idx0_0].green = (src_load0_0.red
                               + src_load0_0.green
                               + src_load0_0.blue) / 3;
            dest[d_idx0_0].blue = (src_load0_0.red
                               + src_load0_0.green
                               + src_load0_0.blue) / 3;
            dest[d_idx0_1].red = (src_load0_1.red
                               + src_load0_1.green
                               + src_load0_1.blue) / 3;
            dest[d_idx0_1].green = (src_load0_1.red
                               + src_load0_1.green
                               + src_load0_1.blue) / 3;
            dest[d_idx0_1].blue = (src_load0_1.red
                               + src_load0_1.green
                               + src_load0_1.blue) / 3;
            dest[d_idx1_0].red = (src_load1_0.red
                               + src_load1_0.green
                               + src_load1_0.blue) / 3;
            dest[d_idx1_0].green = (src_load1_0.red
                               + src_load1_0.green
                               + src_load1_0.blue) / 3;
            dest[d_idx1_0].blue = (src_load1_0.red
                               + src_load1_0.green
                               + src_load1_0.blue) / 3;
            dest[d_idx1_1].red = (src_load1_1.red
                               + src_load1_1.green
                               + src_load1_1.blue) / 3;
            dest[d_idx1_1].green = (src_load1_1.red
                               + src_load1_1.green
                               + src_load1_1.blue) / 3;
            dest[d_idx1_1].blue = (src_load1_1.red
                               + src_load1_1.green
                               + src_load1_1.blue) / 3;  
          }
          //printf("itter: %d, size: %d, j: %d\n",i*j , size, j);
          
          for (; j < size; j++)
          {
          s_idx0_0 = RIDX((qj * size) + i,
                  j + (qi * size), size);
          d_idx0_0 = RIDX((qj * size) + size - 1 - j,
                  i + (qi * size), size);
          src_load0_0 = src[s_idx0_0];//1 load on src
          dest[d_idx0_0].red = (src_load0_0.red
                        + src_load0_0.green
                        + src_load0_0.blue) / 3;
          dest[d_idx0_0].green = (src_load0_0.red
                          + src_load0_0.green
                          + src_load0_0.blue) / 3;
          dest[d_idx0_0].blue = (src_load0_0.red
                        + src_load0_0.green
                        + src_load0_0.blue) / 3;
          }

          //printf("size: %d, j: %d", size, j);
        }
        for (; i < size; i++)
        {
          s_idx0_0 = RIDX((qj * size) + i,
                  j + (qi * size), size);
          d_idx0_0 = RIDX((qj * size) + size - 1 - j,
                  i + (qi * size), size);
          src_load0_0 = src[s_idx0_0];//1 load on src
          dest[d_idx0_0].red = (src_load0_0.red
                        + src_load0_0.green
                        + src_load0_0.blue) / 3;
          dest[d_idx0_0].green = (src_load0_0.red
                          + src_load0_0.green
                          + src_load0_0.blue) / 3;
          dest[d_idx0_0].blue = (src_load0_0.red
                        + src_load0_0.green
                        + src_load0_0.blue) / 3;
        }
      }
}
/*********************************************************************
 * register_pinwheel_functions - Register all of your different versions
 *     of the pinwheel kernel with the driver by calling the
 *     add_pinwheel_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_pinwheel_functions() {
  add_pinwheel_function(&pinwheel, pinwheel_descr);
  add_pinwheel_function(&naive_pinwheel, naive_pinwheel_descr);
  add_pinwheel_function(&pinwheelRoll1, pinwheel_descr1);
  add_pinwheel_function(&pinwheelRoll2, pinwheel_descr2);
}


/***************************************************************
 * MOTION KERNEL
 * 
 * Starts with various typedefs and helper functions for the motion
 * function, and you may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
  int red;
  int green;
  int blue;
} pixel_sum;

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
  sum->red = sum->green = sum->blue = 0;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_weighted_sum(pixel_sum *sum, pixel p, double weight) 
{
  sum->red += (int) p.red * weight;
  sum->green += (int) p.green * weight;
  sum->blue += (int) p.blue * weight;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
  current_pixel->red = (unsigned short)sum.red;
  current_pixel->green = (unsigned short)sum.green;
  current_pixel->blue = (unsigned short)sum.blue;
}

/* 
 * weighted_combo - Returns new pixel value at (i,j) 
 */
static pixel weighted_combo(int dim, int i, int j, pixel *src) 
{
  int ii, jj;
  pixel_sum sum;
  pixel current_pixel;
  double weights[3][3] = { { 0.60, 0.03, 0.00 },
                           { 0.03, 0.30, 0.03 },
                           { 0.00, 0.03, 0.10 } };

  initialize_pixel_sum(&sum);
  for (ii=0; ii < 3; ii++)
    for (jj=0; jj < 3; jj++) 
      if ((i + ii < dim) && (j + jj < dim))
        accumulate_weighted_sum(&sum,
                                src[RIDX(i+ii,j+jj,dim)],
                                weights[ii][jj]);
  
  assign_sum_to_pixel(&current_pixel, sum);

  return current_pixel;
}

/******************************************************
 * Your different versions of the motion kernel go here
 ******************************************************/

/*
 * naive_motion - The naive baseline version of motion 
 */
char naive_motion_descr[] = "naive_motion: baseline implementation";
void naive_motion(pixel *src, pixel *dst) 
{
  int i, j;
    
  for (i = 0; i < src->dim; i++)
    for (j = 0; j < src->dim; j++)
      dst[RIDX(i, j, src->dim)] = weighted_combo(src->dim, i, j, src);
}

/*
 * motion - Your current working version of motion. 
 * IMPORTANT: This is the version you will be graded on
 */
char motion_descr[] = "motion: Current working version";
void motion(pixel *src, pixel *dst) 
{
  naive_motion(src, dst);
}

/********************************************************************* 
 * register_motion_functions - Register all of your different versions
 *     of the motion kernel with the driver by calling the
 *     add_motion_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_motion_functions() {
  add_motion_function(&motion, motion_descr);
  add_motion_function(&naive_motion, naive_motion_descr);
}
