/* Creates a negative image of the input bitmap file */
#include "qdbmp.h"
#include <stdio.h>
#include <time.h>

int main( )
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

   
     //{
   clock_t begin = clock();

  
   


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
 clock_t stop = clock();
 double elapsed = (double)(stop - begin) * 1000.0 / CLOCKS_PER_SEC;
    printf("Time elapsed in ms: %f", elapsed);

  //   }
    /* Save result */
    BMP_WriteFile( bmp, "wiki out.bmp" );


    /* Free all memory allocated for the image */
    BMP_Free( bmp );
   

    return 0;
}
