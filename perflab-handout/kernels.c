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

char pinwheel_descrUpperUnroll[] = "pinwheel: Upper Unroll";
void pinwheelUpper(pixel *src, pixel *dest)
{
  unsigned int i, j, size = src->dim/2;
  pixel loadPix0, loadPix1;
  pixel *destPix0;
  pixel *destPix1;
  unsigned int s_idx0, s_idx1, d_idx0, d_idx1;
  unsigned short sum0, sum1; 
  for (i = 0; i < size; i++)
    for (j = 0; j < size; j+=2) {
      s_idx0 = RIDX(i,j, src->dim);
      s_idx1 = RIDX(i,j+1, src->dim);
      d_idx0 = RIDX(size - 1 - j, i, src->dim);
      d_idx1 = RIDX(size - 1 - (j+1), i, src->dim);
      loadPix0 = src[s_idx0];
      loadPix1 = src[s_idx1];
      sum0 = (loadPix0.red
        + loadPix0.green
        + loadPix0.blue) / 3;
      sum1 = (loadPix1.red
        + loadPix1.green
        + loadPix1.blue) / 3;
      
      destPix0 = &dest[d_idx0];
      destPix0->red = sum0;
      destPix0->green = sum0;
      destPix0->blue = sum0;

      destPix1 = &dest[d_idx1];
      destPix1->red = sum1;
      destPix1->green = sum1;
      destPix1->blue = sum1;
    }
  for (i = 0; i < size; i++)
    for (j = 0; j < size; j+=2) {
      s_idx0 = RIDX((size) + i, j, src->dim);
      s_idx1 = RIDX((size) + i, j+1, src->dim);
      d_idx0 = RIDX((size) + size - 1 - j, i, src->dim);
      d_idx1 = RIDX((size) + size - 1 - (j+1), i, src->dim);
      loadPix0 = src[s_idx0];
      loadPix1 = src[s_idx1];
      sum0 = (loadPix0.red
        + loadPix0.green
        + loadPix0.blue) / 3;
      sum1 = (loadPix1.red
        + loadPix1.green
        + loadPix1.blue) / 3;
      
      destPix0 = &dest[d_idx0];
      destPix0->red = sum0;
      destPix0->green = sum0;
      destPix0->blue = sum0;

      destPix1 = &dest[d_idx1];
      destPix1->red = sum1;
      destPix1->green = sum1;
      destPix1->blue = sum1;
    }
  for (i = 0; i < size; i++)
    for (j = 0; j < size; j+=2) {
      s_idx0 = RIDX(i, j + (size), src->dim);
      s_idx1 = RIDX(i, j + 1 + (size), src->dim);
      d_idx0 = RIDX(size - 1 - j, i + (size), src->dim);
      d_idx1 = RIDX(size - 1 - (j+1), i + (size), src->dim);
      loadPix0 = src[s_idx0];
      loadPix1 = src[s_idx1];
      sum0 = (loadPix0.red
        + loadPix0.green
        + loadPix0.blue) / 3;
      sum1 = (loadPix1.red
        + loadPix1.green
        + loadPix1.blue) / 3;
      
      destPix0 = &dest[d_idx0];
      destPix0->red = sum0;
      destPix0->green = sum0;
      destPix0->blue = sum0;

      destPix1 = &dest[d_idx1];
      destPix1->red = sum1;
      destPix1->green = sum1;
      destPix1->blue = sum1;
    }
  for (i = 0; i < size; i++)
   for (j = 0; j < size; j+=2) {
      s_idx0 = RIDX((size) + i, j + (size), src->dim);
      s_idx1 = RIDX((size) + i, j + 1 + (size), src->dim);
      d_idx0 = RIDX((size) + size - 1 - j, i + (size), src->dim);
      d_idx1 = RIDX((size) + size - 1 - (j+1), i + (size), src->dim);
      loadPix0 = src[s_idx0];
      loadPix1 = src[s_idx1];
      sum0 = (loadPix0.red
        + loadPix0.green
        + loadPix0.blue) / 3;
      sum1 = (loadPix1.red
        + loadPix1.green
        + loadPix1.blue) / 3;
      
      destPix0 = &dest[d_idx0];
      destPix0->red = sum0;
      destPix0->green = sum0;
      destPix0->blue = sum0;

      destPix1 = &dest[d_idx1];
      destPix1->red = sum1;
      destPix1->green = sum1;
      destPix1->blue = sum1;
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
  unsigned short color;
  int size = size;
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
            color = (src_load.red
                    + src_load.green
                    + src_load.blue) / 3;
            dest[d_idx].red = color;
            dest[d_idx].green = color;
            dest[d_idx].blue = color;
          }
}

char pinwheel_descr1[] = "pinwheel: unroll1";
void pinwheelRoll1(pixel *src, pixel *dest)
{
  unsigned int qi, qj, i, j, s_idx0, s_idx1, d_idx0, d_idx1;
  pixel src_load0;
  pixel src_load1;
  unsigned short color0;
  unsigned short color1;
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
            color0 = (src_load0.red
                      + src_load0.green
                      + src_load0.blue) / 3;
            src_load1 = src[s_idx1];
            color1 = (src_load1.red
                      + src_load1.green
                      + src_load1.blue) / 3;
            dest[d_idx0].red = color0;
            dest[d_idx0].green = color0;
            dest[d_idx0].blue = color0;
            dest[d_idx1].red = color1;
            dest[d_idx1].green = color1;
            dest[d_idx1].blue = color1;
             
          }
          //printf("itter: %d, size: %d, j: %d\n",i*j , size, j);
          
          for (; j < size; j++)
          {
            s_idx0 = RIDX((qj * size) + i,
                    j + (qi * size), size);
            d_idx0 = RIDX((qj * size) + size - 1 - j,
                    i + (qi * size), size);
            src_load0 = src[s_idx0];//1 load on src
            color0 = (src_load1.red
                      + src_load1.green
                      + src_load1.blue) / 3;
            dest[d_idx0].red = color0;
            dest[d_idx0].green = color0;
            dest[d_idx0].blue = color0;
          }

          //printf("size: %d, j: %d", size, j);
        }
}

char pinwheel_descr1_1[] = "pinwheel: unroll1_1";
void pinwheelRoll1_1(pixel *src, pixel *dest)
{
  unsigned int qi, qj, i, j, s_idx0, s_idx1, s_idx2, s_idx3, d_idx0, d_idx1, d_idx2, d_idx3;
  pixel src_load0;
  pixel src_load1;
  pixel src_load2;
  pixel src_load3;
  unsigned short color0;
  unsigned short color1;
  unsigned short color2;
  unsigned short color3;
  int size = src->dim/2;
  
    /* qi & qj are column and row of quadrant
       i & j are column and row within quadrant */
  
    /* Loop over 4 quadrants: */
    for (qi = 0; qi < 2; qi++)
      for (qj = 0; qj < 2; qj++)
        /* Loop within quadrant: */
        for (i = 0; i < size; i++){
          for (j = 0; j < size; j+=4) 
          {
            s_idx0 = RIDX((qj * size) + i,
                             j + (qi * size), src->dim);
            d_idx0 = RIDX((qj * size) + size - 1 - j,
                             i + (qi * size), src->dim);
            s_idx1 = RIDX((qj * size) + i,
                             (j+1) + (qi * size), src->dim);
            d_idx1 = RIDX((qj * size) + size - 1 - (j+1),
                             i + (qi * size), src->dim);
            s_idx2 = RIDX((qj * size) + i,
                             (j+2) + (qi * size), src->dim);
            d_idx2 = RIDX((qj * size) + size - 1 - (j+2),
                             i + (qi * size), src->dim);
            s_idx3 = RIDX((qj * size) + i,
                             (j+3) + (qi * size), src->dim);
            d_idx3 = RIDX((qj * size) + size - 1 - (j+3),
                             i + (qi * size), src->dim);
            src_load0 = src[s_idx0];//1 load on src
            src_load1 = src[s_idx1];
            src_load2 = src[s_idx2];
            src_load3 = src[s_idx3];
            color0 = (src_load0.red
                    + src_load0.green
                    + src_load0.blue) / 3;
            color1 = (src_load1.red
                    + src_load1.green
                    + src_load1.blue) / 3;
            color2 = (src_load2.red
                    + src_load2.green
                    + src_load2.blue) / 3;
            color3 = (src_load3.red
                    + src_load3.green
                    + src_load3.blue) / 3;                    
            dest[d_idx0].red = color0;
            dest[d_idx0].green = color0;
            dest[d_idx0].blue = color0;
            dest[d_idx1].red = color1;
            dest[d_idx1].green = color1;
            dest[d_idx1].blue = color1;
            dest[d_idx2].red = color2;
            dest[d_idx2].green = color2;
            dest[d_idx2].blue = color2;
            dest[d_idx3].red = color3;
            dest[d_idx3].green = color3;
            dest[d_idx3].blue = color3;
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
  unsigned short color0_0;
  unsigned short color0_1;
  unsigned short color1_0;
  unsigned short color1_1;
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
            s_idx0_0 = RIDX((qj * size) + i, j + (qi * size), src->dim);
            s_idx0_1 = RIDX((qj * size) + (i+1), j + (qi * size), src->dim);
            d_idx0_0 = RIDX((qj * size) + size - 1 - j, i + (qi * size), src->dim);
            d_idx0_1 = RIDX((qj * size) + size - 1 - j, (i+1) + (qi * size), src->dim);
            s_idx1_0 = RIDX((qj * size) + i, (j+1) + (qi * size), src->dim);
            s_idx1_1 = RIDX((qj * size) + (i+1), (j+1) + (qi * size), src->dim);
            d_idx1_0 = RIDX((qj * size) + size - 1 - (j+1), i + (qi * size), src->dim);
            d_idx1_1 = RIDX((qj * size) + size - 1 - (j+1), (i+1) + (qi * size), src->dim);
            
            src_load0_0 = src[s_idx0_0];//1 load on src
            src_load0_1 = src[s_idx0_1];
            src_load1_0 = src[s_idx1_0];
            src_load1_1 = src[s_idx1_1];

            color0_0 = (src_load0_0.red
                      + src_load0_0.green
                      + src_load0_0.blue) / 3;
            color0_1 = (src_load0_1.red
                      + src_load0_1.green
                      + src_load0_1.blue) / 3;
            color1_0 = (src_load1_0.red
                      + src_load1_0.green
                      + src_load1_0.blue) / 3;
            color1_1 = (src_load1_1.red
                      + src_load1_1.green
                      + src_load1_1.blue) / 3;
            dest[d_idx0_0].red = color0_0;
            dest[d_idx0_0].green = color0_0;
            dest[d_idx0_0].blue = color0_0;
            dest[d_idx0_1].red = color0_1;
            dest[d_idx0_1].green = color0_1;
            dest[d_idx0_1].blue =  color0_1;
            dest[d_idx1_0].red =  color1_0;
            dest[d_idx1_0].green =  color1_0;
            dest[d_idx1_0].blue = color1_0;
            dest[d_idx1_1].red = color1_1;
            dest[d_idx1_1].green = color1_1;
            dest[d_idx1_1].blue = color1_1;  
          }
          //printf("itter: %d, size: %d, j: %d\n",i*j , size, j);
          
          for (; j < size; j++)
          {
          s_idx0_0 = RIDX((qj * size) + i,
                  j + (qi * size), size);
          d_idx0_0 = RIDX((qj * size) + size - 1 - j,
                  i + (qi * size), size);
          src_load0_0 = src[s_idx0_0];//1 load on src
          color0_0 = (src_load0_0.red
                    + src_load0_0.green
                    + src_load0_0.blue) / 3;
          dest[d_idx0_0].red = color0_0;
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
          color0_0 = (src_load0_0.red
                    + src_load0_0.green
                    + src_load0_0.blue) / 3;;
          dest[d_idx0_0].red = color0_0;
          dest[d_idx0_0].green = color0_0;
          dest[d_idx0_0].blue = color0_0;
        }
      }
}
char pinwheel_descr22[] = "pinwheel: unroll22";
void pinwheelRoll22(pixel *src, pixel *dest)
{
  unsigned int qi, qj, i, j, s_idx0_0, 
               s_idx0_1, s_idx1_0, s_idx1_1, 
               d_idx0_0, d_idx0_1, d_idx1_0, d_idx1_1;
  pixel src_load0_0;
  pixel src_load0_1;
  pixel src_load1_0;
  pixel src_load1_1;
  unsigned short color0_0, color0_1, color1_0, color1_1, size = src->dim/2, qi_size = 0, qj_size = 0;
    /* qi & qj are column and row of quadrant
       i & j are column and row within quadrant */
  
    /* Loop over 4 quadrants: */
  unsigned int s_qj_size_i;
  unsigned int s_qi_size_j;
  unsigned int d_qj_size_i;
  unsigned int d_qj_size_j;

  for (qi = 0; qi < 2; qi++){
    qi_size = qi*size;
    for (qj = 0; qj < 2; qj++){
      qj_size = qj*size;
      /* Loop within quadrant: */
      for (i = 0; i < size; i+=2){
        for (j = 0; j < size; j+=2) 
        {    
          //printf("%d\t%d\n", qj*size, qj_size);
          s_qj_size_i = qj_size+i;
          s_qi_size_j = j + qi_size;
          d_qj_size_i = qj_size + size - j - 1;
          d_qj_size_j = i+ qi_size;

          s_idx0_0 = RIDX(s_qj_size_i, s_qi_size_j, src->dim);
          s_idx0_1 = RIDX(s_qj_size_i+1, s_qi_size_j, src->dim);
          d_idx0_0 = RIDX(d_qj_size_i, d_qj_size_j, src->dim);
          d_idx0_1 = RIDX(d_qj_size_i, d_qj_size_j+1, src->dim);
          s_idx1_0 = RIDX(s_qj_size_i, s_qi_size_j+1, src->dim);
          s_idx1_1 = RIDX(s_qj_size_i+1, s_qi_size_j+1, src->dim);
          d_idx1_0 = RIDX(d_qj_size_i-1, d_qj_size_j, src->dim);
          d_idx1_1 = RIDX(d_qj_size_i-1, d_qj_size_j+1, src->dim);
          
          src_load0_0 = src[s_idx0_0];//1 load on src
          src_load0_1 = src[s_idx0_1];
          src_load1_0 = src[s_idx1_0];
          src_load1_1 = src[s_idx1_1];
          color0_0 = (src_load0_0.red
                    + src_load0_0.green
                    + src_load0_0.blue) / 3;
          color0_1 = (src_load0_1.red
                    + src_load0_1.green
                    + src_load0_1.blue) / 3;
          color1_0 = (src_load1_0.red
                    + src_load1_0.green
                    + src_load1_0.blue) / 3;
          color1_1 = (src_load1_1.red
                    + src_load1_1.green
                    + src_load1_1.blue) / 3;
          dest[d_idx0_0].red = color0_0;
          dest[d_idx0_0].green = color0_0;
          dest[d_idx0_0].blue = color0_0;
          dest[d_idx0_1].red = color0_1;
          dest[d_idx0_1].green = color0_1;
          dest[d_idx0_1].blue =  color0_1;
          dest[d_idx1_0].red =  color1_0;
          dest[d_idx1_0].green =  color1_0;
          dest[d_idx1_0].blue = color1_0;
          dest[d_idx1_1].red = color1_1;
          dest[d_idx1_1].green = color1_1;
          dest[d_idx1_1].blue = color1_1;  
        }
        //printf("itter: %d, size: %d, j: %d\n",i*j , size, j);
        
        for (; j < size; j++)
        {
        s_idx0_0 = RIDX((qj * size) + i,
                j + (qi * size), size);
        d_idx0_0 = RIDX((qj * size) + size - 1 - j,
                i + (qi * size), size);
        src_load0_0 = src[s_idx0_0];//1 load on src
        color0_0 = (src_load0_0.red
                  + src_load0_0.green
                  + src_load0_0.blue) / 3;
        dest[d_idx0_0].red = color0_0;
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
        color0_0 = (src_load0_0.red
                  + src_load0_0.green
                  + src_load0_0.blue) / 3;;
        dest[d_idx0_0].red = color0_0;
        dest[d_idx0_0].green = color0_0;
        dest[d_idx0_0].blue = color0_0;
      }
    }
  }
}

char pinwheel_descr21[] = "pinwheel: unroll21";
void pinwheelRoll21(pixel *src, pixel *dest)
{
  unsigned int qi, qj, i, j, s_idx0_0, 
               s_idx0_1, s_idx1_0, s_idx1_1, 
               d_idx0_0, d_idx0_1, d_idx1_0, d_idx1_1;
  pixel src_load0_0;
  pixel src_load0_1;
  pixel src_load1_0;
  pixel src_load1_1;

  pixel *dest0_0;
  pixel *dest0_1;
  pixel *dest1_0;
  pixel *dest1_1;

  unsigned short color0_0, color0_1, color1_0, color1_1, size = src->dim/2, qi_size = 0, qj_size = 0;
    /* qi & qj are column and row of quadrant
       i & j are column and row within quadrant */
  
    /* Loop over 4 quadrants: */
  for (qi = 0; qi < 2; qi++){
    qi_size = qi*size;
    for (qj = 0; qj < 2; qj++){
      qj_size = qj*size;
      /* Loop within quadrant: */
      for (i = 0; i < size; i+=2){
        for (j = 0; j < size; j+=2) 
        {    
          //printf("%d\t%d\n", qj*size, qj_size);
          s_idx0_0 = RIDX(qj_size + i, j + qi_size, src->dim);
          s_idx0_1 = RIDX(qj_size + (i+1), j + qi_size, src->dim);
          d_idx0_0 = RIDX(qj_size + size - 1 - j, i + qi_size, src->dim);
          d_idx0_1 = RIDX(qj_size + size - 1 - j, (i+1) + qi_size, src->dim);
          s_idx1_0 = RIDX(qj_size + i, (j+1) + qi_size, src->dim);
          s_idx1_1 = RIDX(qj_size + (i+1), (j+1) + qi_size, src->dim);
          d_idx1_0 = RIDX(qj_size + size - 1 - (j+1), i + qi_size, src->dim);
          d_idx1_1 = RIDX(qj_size + size - 1 - (j+1), (i+1) + qi_size, src->dim);
          
          src_load0_0 = src[s_idx0_0];//1 load on src
          src_load0_1 = src[s_idx0_1];
          src_load1_0 = src[s_idx1_0];
          src_load1_1 = src[s_idx1_1];

          unsigned int src_color0_0 = (src_load0_0.red
            + src_load0_0.green
            + src_load0_0.blue);
          unsigned int src_color0_1 = (src_load0_1.red
            + src_load0_1.green
            + src_load0_1.blue);
          unsigned int src_color1_0 = (src_load1_0.red
            + src_load1_0.green
            + src_load1_0.blue);
          unsigned int src_color1_1 = (src_load1_1.red
            + src_load1_1.green
            + src_load1_1.blue);
          
          color0_0 = src_color0_0/3;
          color0_1 = src_color0_1/3;
          color1_0 = src_color1_0/3;
          color1_1 = src_color1_1/3;

          dest0_0 = &dest[d_idx0_0];
          dest0_1 = &dest[d_idx0_1];
          dest1_0 = &dest[d_idx1_0];
          dest1_1 = &dest[d_idx1_1];

          dest0_0->red = color0_0;
          dest0_0->green = color0_0;
          dest0_0->blue = color0_0;
          dest0_1->red = color0_1;
          dest0_1->green = color0_1;
          dest0_1->blue =  color0_1;
          dest1_0->red =  color1_0;
          dest1_0->green =  color1_0;
          dest1_0->blue = color1_0;
          dest1_1->red = color1_1;
          dest1_1->green = color1_1;
          dest1_1->blue = color1_1;  
        }
        
        for (; j < size; j++)
        {
        s_idx0_0 = RIDX((qj * size) + i,
                j + (qi * size), size);
        d_idx0_0 = RIDX((qj * size) + size - 1 - j,
                i + (qi * size), size);
        src_load0_0 = src[s_idx0_0];//1 load on src
        color0_0 = (src_load0_0.red
                  + src_load0_0.green
                  + src_load0_0.blue) / 3;
        dest[d_idx0_0].red = color0_0;
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
        color0_0 = (src_load0_0.red
                  + src_load0_0.green
                  + src_load0_0.blue) / 3;;
        dest[d_idx0_0].red = color0_0;
        dest[d_idx0_0].green = color0_0;
        dest[d_idx0_0].blue = color0_0;
      }
    }
  }
}

char pinwheel_descr211[] = "pinwheel: unroll2.1.1";
void pinwheelRoll211(pixel *src, pixel *dest)
{
  unsigned int i, j, s_idx0_0, 
               s_idx0_1, s_idx1_0, s_idx1_1, 
               d_idx0_0, d_idx0_1, d_idx1_0, d_idx1_1;
  pixel src_load0_0;
  pixel src_load0_1;
  pixel src_load1_0;
  pixel src_load1_1;

  pixel *dest0_0;
  pixel *dest0_1;
  pixel *dest1_0;
  pixel *dest1_1;

  unsigned short color0_0, color0_1, color1_0, color1_1, size = src->dim/2, qi_size = 0, qj_size = 0;
  unsigned int src_color0_0, src_color0_1, src_color1_0, src_color1_1;

  //0
  for (i = 0; i < size; i+=2){
    for (j = 0; j < size; j+=2) 
    {    
      //printf("%d\t%d\n", qj*size, qj_size);
      s_idx0_0 = RIDX(i, j, src->dim);
      s_idx0_1 = RIDX((i+1), j, src->dim);
      d_idx0_0 = RIDX(size - 1 - j, i, src->dim);
      d_idx0_1 = RIDX(size - 1 - j, (i+1), src->dim);
      s_idx1_0 = RIDX(i, (j+1), src->dim);
      s_idx1_1 = RIDX((i+1), (j+1), src->dim);
      d_idx1_0 = RIDX(size - 1 - (j+1), i, src->dim);
      d_idx1_1 = RIDX(size - 1 - (j+1), (i+1), src->dim);
      
      src_load0_0 = src[s_idx0_0];//1 load on src
      src_load0_1 = src[s_idx0_1];
      src_load1_0 = src[s_idx1_0];
      src_load1_1 = src[s_idx1_1];
      src_color0_0 = (src_load0_0.red
        + src_load0_0.green
        + src_load0_0.blue);
      src_color0_1 = (src_load0_1.red
        + src_load0_1.green
        + src_load0_1.blue);
      src_color1_0 = (src_load1_0.red
        + src_load1_0.green
        + src_load1_0.blue);
      src_color1_1 = (src_load1_1.red
        + src_load1_1.green
        + src_load1_1.blue);
      
      color0_0 = src_color0_0/3;
      color0_1 = src_color0_1/3;
      color1_0 = src_color1_0/3;
      color1_1 = src_color1_1/3;

      dest0_0 = &dest[d_idx0_0];
      dest0_1 = &dest[d_idx0_1];
      dest1_0 = &dest[d_idx1_0];
      dest1_1 = &dest[d_idx1_1];

      dest0_0->red = color0_0;
      dest0_0->green = color0_0;
      dest0_0->blue = color0_0;
      dest0_1->red = color0_1;
      dest0_1->green = color0_1;
      dest0_1->blue =  color0_1;
      dest1_0->red =  color1_0;
      dest1_0->green =  color1_0;
      dest1_0->blue = color1_0;
      dest1_1->red = color1_1;
      dest1_1->green = color1_1;
      dest1_1->blue = color1_1;  
    }
  }
  //1
  qi_size = 0;
  qj_size = size;
  for (i = 0; i < size; i+=2){
    for (j = 0; j < size; j+=2) 
    {    
      //printf("%d\t%d\n", qj*size, qj_size);
      s_idx0_0 = RIDX(qj_size + i, j, src->dim);
      s_idx0_1 = RIDX(qj_size + (i+1), j, src->dim);
      d_idx0_0 = RIDX(qj_size + size - 1 - j, i, src->dim);
      d_idx0_1 = RIDX(qj_size + size - 1 - j, (i+1), src->dim);
      s_idx1_0 = RIDX(qj_size + i, (j+1), src->dim);
      s_idx1_1 = RIDX(qj_size + (i+1), (j+1), src->dim);
      d_idx1_0 = RIDX(qj_size + size - 1 - (j+1), i, src->dim);
      d_idx1_1 = RIDX(qj_size + size - 1 - (j+1), (i+1), src->dim);
      
      src_load0_0 = src[s_idx0_0];//1 load on src
      src_load0_1 = src[s_idx0_1];
      src_load1_0 = src[s_idx1_0];
      src_load1_1 = src[s_idx1_1];
      src_color0_0 = (src_load0_0.red
        + src_load0_0.green
        + src_load0_0.blue);
      src_color0_1 = (src_load0_1.red
        + src_load0_1.green
        + src_load0_1.blue);
      src_color1_0 = (src_load1_0.red
        + src_load1_0.green
        + src_load1_0.blue);
      src_color1_1 = (src_load1_1.red
        + src_load1_1.green
        + src_load1_1.blue);
      
      color0_0 = src_color0_0/3;
      color0_1 = src_color0_1/3;
      color1_0 = src_color1_0/3;
      color1_1 = src_color1_1/3;
      dest0_0 = &dest[d_idx0_0];
      dest0_1 = &dest[d_idx0_1];
      dest1_0 = &dest[d_idx1_0];
      dest1_1 = &dest[d_idx1_1];
      dest0_0->red = color0_0;
      dest0_0->green = color0_0;
      dest0_0->blue = color0_0;
      dest0_1->red = color0_1;
      dest0_1->green = color0_1;
      dest0_1->blue =  color0_1;
      dest1_0->red =  color1_0;
      dest1_0->green =  color1_0;
      dest1_0->blue = color1_0;
      dest1_1->red = color1_1;
      dest1_1->green = color1_1;
      dest1_1->blue = color1_1;  
    }
  }
  //2
  qi_size = size;
  qj_size = 0;
  for (i = 0; i < size; i+=2){
    for (j = 0; j < size; j+=2) 
    {    
      //printf("%d\t%d\n", qj*size, qj_size);
      s_idx0_0 = RIDX(i, j + qi_size, src->dim);
      s_idx0_1 = RIDX((i+1), j + qi_size, src->dim);
      d_idx0_0 = RIDX(size - 1 - j, i + qi_size, src->dim);
      d_idx0_1 = RIDX(size - 1 - j, (i+1) + qi_size, src->dim);
      s_idx1_0 = RIDX(i, (j+1) + qi_size, src->dim);
      s_idx1_1 = RIDX((i+1), (j+1) + qi_size, src->dim);
      d_idx1_0 = RIDX(size - 1 - (j+1), i + qi_size, src->dim);
      d_idx1_1 = RIDX(size - 1 - (j+1), (i+1) + qi_size, src->dim);
      
      src_load0_0 = src[s_idx0_0];//1 load on src
      src_load0_1 = src[s_idx0_1];
      src_load1_0 = src[s_idx1_0];
      src_load1_1 = src[s_idx1_1];
      src_color0_0 = (src_load0_0.red
        + src_load0_0.green
        + src_load0_0.blue);
      src_color0_1 = (src_load0_1.red
        + src_load0_1.green
        + src_load0_1.blue);
      src_color1_0 = (src_load1_0.red
        + src_load1_0.green
        + src_load1_0.blue);
      src_color1_1 = (src_load1_1.red
        + src_load1_1.green
        + src_load1_1.blue);
      
      color0_0 = src_color0_0/3;
      color0_1 = src_color0_1/3;
      color1_0 = src_color1_0/3;
      color1_1 = src_color1_1/3;
      dest0_0 = &dest[d_idx0_0];
      dest0_1 = &dest[d_idx0_1];
      dest1_0 = &dest[d_idx1_0];
      dest1_1 = &dest[d_idx1_1];
      dest0_0->red = color0_0;
      dest0_0->green = color0_0;
      dest0_0->blue = color0_0;
      dest0_1->red = color0_1;
      dest0_1->green = color0_1;
      dest0_1->blue =  color0_1;
      dest1_0->red =  color1_0;
      dest1_0->green =  color1_0;
      dest1_0->blue = color1_0;
      dest1_1->red = color1_1;
      dest1_1->green = color1_1;
      dest1_1->blue = color1_1;  
    }
  }
  //3
  qi_size = size;
  qj_size = size;
  for (i = 0; i < size; i+=2){
    for (j = 0; j < size; j+=2) 
    {    
      //printf("%d\t%d\n", qj*size, qj_size);
      s_idx0_0 = RIDX(qj_size + i, j + qi_size, src->dim);
      s_idx0_1 = RIDX(qj_size + (i+1), j + qi_size, src->dim);
      d_idx0_0 = RIDX(qj_size + size - 1 - j, i + qi_size, src->dim);
      d_idx0_1 = RIDX(qj_size + size - 1 - j, (i+1) + qi_size, src->dim);
      s_idx1_0 = RIDX(qj_size + i, (j+1) + qi_size, src->dim);
      s_idx1_1 = RIDX(qj_size + (i+1), (j+1) + qi_size, src->dim);
      d_idx1_0 = RIDX(qj_size + size - 1 - (j+1), i + qi_size, src->dim);
      d_idx1_1 = RIDX(qj_size + size - 1 - (j+1), (i+1) + qi_size, src->dim);
      
      src_load0_0 = src[s_idx0_0];//1 load on src
      src_load0_1 = src[s_idx0_1];
      src_load1_0 = src[s_idx1_0];
      src_load1_1 = src[s_idx1_1];
      src_color0_0 = (src_load0_0.red
        + src_load0_0.green
        + src_load0_0.blue);
      src_color0_1 = (src_load0_1.red
        + src_load0_1.green
        + src_load0_1.blue);
      src_color1_0 = (src_load1_0.red
        + src_load1_0.green
        + src_load1_0.blue);
      src_color1_1 = (src_load1_1.red
        + src_load1_1.green
        + src_load1_1.blue);
      
      color0_0 = src_color0_0/3;
      color0_1 = src_color0_1/3;
      color1_0 = src_color1_0/3;
      color1_1 = src_color1_1/3;
      dest0_0 = &dest[d_idx0_0];
      dest0_1 = &dest[d_idx0_1];
      dest1_0 = &dest[d_idx1_0];
      dest1_1 = &dest[d_idx1_1];
      dest0_0->red = color0_0;
      dest0_0->green = color0_0;
      dest0_0->blue = color0_0;
      dest0_1->red = color0_1;
      dest0_1->green = color0_1;
      dest0_1->blue =  color0_1;
      dest1_0->red =  color1_0;
      dest1_0->green =  color1_0;
      dest1_0->blue = color1_0;
      dest1_1->red = color1_1;
      dest1_1->green = color1_1;
      dest1_1->blue = color1_1;  
    }
  }
}

char pinwheel_descrSpicy[] = "pinwheel: unrollSpicy";
void pinwheelRollSpicy(pixel *src, pixel *dest)
{
  unsigned int qi, qj, i, j, 
  s_idx0_0_0, s_idx0_1_0, s_idx1_0_0, s_idx1_1_0,
  s_idx0_0_1, s_idx0_1_1, s_idx1_0_1, s_idx1_1_1,
  d_idx0_0_0, d_idx0_1_0, d_idx1_0_0, d_idx1_1_0,
  d_idx0_0_1, d_idx0_1_1, d_idx1_0_1, d_idx1_1_1;
  pixel src_load0_0_0;
  pixel src_load0_1_0;
  pixel src_load0_0_1;
  pixel src_load0_1_1;
  pixel src_load1_0_0;
  pixel src_load1_1_0;
  pixel src_load1_0_1;
  pixel src_load1_1_1;
  unsigned short color0_0_0;
  unsigned short color0_1_0;
  unsigned short color0_0_1;
  unsigned short color0_1_1;
  unsigned short color1_0_0;
  unsigned short color1_1_0;
  unsigned short color1_0_1;
  unsigned short color1_1_1;
  int size = src->dim/2;
    /* qi & qj are column and row of quadrant
       i & j are column and row within quadrant */
  
    /* Loop over 4 quadrants: */
    for (qi = 0; qi < 2; qi++){
      for (qj = 0; qj < 2; qj+=2){
        /* Loop within quadrant: */
        for (i = 0; i < size; i+=2){
          for (j = 0; j < size; j+=2) 
          {
            s_idx0_0_0 = RIDX((qj * size) + i, j + (qi * size), src->dim);
            s_idx0_1_0 = RIDX((qj * size) + (i+1), j + (qi * size), src->dim);
            d_idx0_0_0 = RIDX((qj * size) + size - 1 - j, i + (qi * size), src->dim);
            d_idx0_1_0 = RIDX((qj * size) + size - 1 - j, (i+1) + (qi * size), src->dim);
            s_idx0_0_1 = RIDX(((qj+1) * size) + i, j + (qi * size), src->dim);
            s_idx0_1_1 = RIDX(((qj+1) * size) + (i+1), j + (qi * size), src->dim);
            d_idx0_0_1 = RIDX(((qj+1) * size) + size - 1 - j, i + (qi * size), src->dim);
            d_idx0_1_1 = RIDX(((qj+1) * size) + size - 1 - j, (i+1) + (qi * size), src->dim);

            s_idx1_0_0 = RIDX((qj * size) + i, (j+1) + (qi * size), src->dim);
            s_idx1_1_0 = RIDX((qj * size) + (i+1), (j+1) + (qi * size), src->dim);
            d_idx1_0_0 = RIDX((qj * size) + size - 1 - (j+1), i + (qi * size), src->dim);
            d_idx1_1_0 = RIDX((qj * size) + size - 1 - (j+1), (i+1) + (qi * size), src->dim);
            s_idx1_0_1 = RIDX(((qj+1) * size) + i, (j+1) + (qi * size), src->dim);
            s_idx1_1_1 = RIDX(((qj+1) * size) + (i+1), (j+1) + (qi * size), src->dim);
            d_idx1_0_1 = RIDX(((qj+1) * size) + size - 1 - (j+1), i + (qi * size), src->dim);
            d_idx1_1_1 = RIDX(((qj+1) * size) + size - 1 - (j+1), (i+1) + (qi * size), src->dim);
            

            src_load0_0_0 = src[s_idx0_0_0];//1 load on src
            src_load0_1_0 = src[s_idx0_1_0];
            src_load0_0_1 = src[s_idx0_0_1];//1 load on src
            src_load0_1_1 = src[s_idx0_1_1];

            src_load1_0_0 = src[s_idx1_0_0];
            src_load1_1_0 = src[s_idx1_1_0];
            src_load1_0_1 = src[s_idx1_0_1];
            src_load1_1_1 = src[s_idx1_1_1];

            color0_0_0 = (src_load0_0_0.red
                      + src_load0_0_0.green
                      + src_load0_0_0.blue) / 3;
            color0_1_0 = (src_load0_1_0.red
                      + src_load0_1_0.green
                      + src_load0_1_0.blue) / 3;
            color0_0_1 = (src_load0_0_1.red
                      + src_load0_0_1.green
                      + src_load0_0_1.blue) / 3;
            color0_1_1 = (src_load0_1_1.red
                      + src_load0_1_1.green
                      + src_load0_1_1.blue) / 3;
            color1_0_0 = (src_load1_0_0.red
                      + src_load1_0_0.green
                      + src_load1_0_0.blue) / 3;
            color1_1_0 = (src_load1_1_0.red
                      + src_load1_1_0.green
                      + src_load1_1_0.blue) / 3;
            color1_0_1 = (src_load1_0_1.red
                      + src_load1_0_1.green
                      + src_load1_0_1.blue) / 3;
            color1_1_1 = (src_load1_1_1.red
                      + src_load1_1_1.green
                      + src_load1_1_1.blue) / 3;
    
            dest[d_idx0_0_0].red = color0_0_0;
            dest[d_idx0_0_0].green = color0_0_0;
            dest[d_idx0_0_0].blue = color0_0_0;

            dest[d_idx0_1_0].red = color0_1_0;
            dest[d_idx0_1_0].green = color0_1_0;
            dest[d_idx0_1_0].blue =  color0_1_0;
            
            dest[d_idx0_0_1].red = color0_0_1;
            dest[d_idx0_0_1].green = color0_0_1;
            dest[d_idx0_0_1].blue = color0_0_1;

            dest[d_idx0_1_1].red = color0_1_1;
            dest[d_idx0_1_1].green = color0_1_1;
            dest[d_idx0_1_1].blue =  color0_1_1;
            
            dest[d_idx1_0_0].red =  color1_0_0;
            dest[d_idx1_0_0].green =  color1_0_0;
            dest[d_idx1_0_0].blue = color1_0_0;
            
            dest[d_idx1_1_0].red = color1_1_0;
            dest[d_idx1_1_0].green = color1_1_0;
            dest[d_idx1_1_0].blue = color1_1_0;  

            dest[d_idx1_0_1].red =  color1_0_1;
            dest[d_idx1_0_1].green =  color1_0_1;
            dest[d_idx1_0_1].blue = color1_0_1;
            
            dest[d_idx1_1_1].red = color1_1_1;
            dest[d_idx1_1_1].green = color1_1_1;
            dest[d_idx1_1_1].blue = color1_1_1;
          }
          //printf("itter: %d, size: %d, j: %d\n",i*j , size, j);
          
          for (; j < size; j++)
          {
          s_idx0_0_0 = RIDX((qj * size) + i,
                  j + (qi * size), size);
          d_idx0_0_0 = RIDX((qj * size) + size - 1 - j,
                  i + (qi * size), size);
          src_load0_0_0 = src[s_idx0_0_0];//1 load on src
          color0_0_0 = (src_load0_0_0.red
                    + src_load0_0_0.green
                    + src_load0_0_0.blue) / 3;
          dest[d_idx0_0_0].red = color0_0_0;
          }

          //printf("size: %d, j: %d", size, j);
        }
        for (; i < size; i++)
        {
          s_idx0_0_0 = RIDX((qj * size) + i,
                  j + (qi * size), size);
          d_idx0_0_0 = RIDX((qj * size) + size - 1 - j,
                  i + (qi * size), size);
          src_load0_0_0 = src[s_idx0_0_0];//1 load on src
          color0_0_0 = (src_load0_0_0.red
                    + src_load0_0_0.green
                    + src_load0_0_0.blue) / 3;;
          dest[d_idx0_0_0].red = color0_0_0;
          dest[d_idx0_0_0].green = color0_0_0;
          dest[d_idx0_0_0].blue = color0_0_0;
        }
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
  //add_pinwheel_function(&pinwheel, pinwheel_descr);
  //add_pinwheel_function(&naive_pinwheel, naive_pinwheel_descr);
  //add_pinwheel_function(&pinwheelUpper, pinwheel_descrUpperUnroll);
  //add_pinwheel_function(&pinwheelRoll1, pinwheel_descr1);
  //add_pinwheel_function(&pinwheelRoll1_1, pinwheel_descr1_1);
  //add_pinwheel_function(&pinwheelRoll2, pinwheel_descr2);
  add_pinwheel_function(&pinwheelRoll21, pinwheel_descr21);
  add_pinwheel_function(&pinwheelRoll211, pinwheel_descr211);
  //add_pinwheel_function(&pinwheelRoll22, pinwheel_descr22);
  //add_pinwheel_function(&pinwheelRollSpicy, pinwheel_descrSpicy);
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
  //add_motion_function(&motion, motion_descr);
  //add_motion_function(&naive_motion, naive_motion_descr);
}
