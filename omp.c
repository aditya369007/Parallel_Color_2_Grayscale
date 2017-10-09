/* Creates a negative image of the input bitmap file */
#include "qdbmp.h"
#include <stdio.h>

double diftime[64];

#include <omp.h>
int main( )
{
    #pragma omp parallel num_threads(5)
     {

    BMP*    bmp;
    UCHAR   r, g, b;
    UINT    width, height;
    UINT    x, y;


    /* Read an image file */
    bmp = BMP_ReadFile( "wikiedit.bmp" );

    /* Get image's dimensions */
    width = BMP_GetWidth( bmp );
    height = BMP_GetHeight( bmp );

    /* Iterate through all the image's pixels */


 double start_time, end_time;
int id = omp_get_thread_num();
   start_time = omp_get_wtime();

    #pragma omp parallel for collapse(2)

   


    for ( x = 0 ; x < width ; ++x )
    {
           for ( y = 0 ; y < height ; ++y )
        {
            /* Get pixel's RGB values */
            BMP_GetPixelRGB( bmp, x, y, &r, &g, &b );

            /* Invert RGB values */
            BMP_SetPixelRGB( bmp, x, y, ((0.30 *r)+(0.59 *g)+(0.11* b))/3, ((0.30 *r)+(0.59 *g)+(0.11* b))/3, ((0.30 *r)+(0.59 *g)+(0.11* b))/3);
        }
    }
 end_time = omp_get_wtime();
diftime[id] = diftime[id] + (end_time - start_time);
     printf("thread[%d] = %.32g\n", id, end_time - start_time);

   
    /* Save result */
    BMP_WriteFile( bmp, "wiki out.bmp" );


    /* Free all memory allocated for the image */
    BMP_Free( bmp );
   }

    return 0;
}
