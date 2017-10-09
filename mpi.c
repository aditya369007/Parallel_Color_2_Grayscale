/* Creates a negative image of the input bitmap file */
#include "qdbmp.h"
#include <stdio.h>
double diftime[64];

#include <mpi.h>
int main(int argc, char *argv[] )
{

   int  rank, nprocs, count, start, stop;



    BMP*    bmp;
    UCHAR   r, g, b;
    UINT    width, height;
    UINT    x, y;
MPI_Init(&argc, &argv);

 MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);



    /* Read an image file */
    bmp = BMP_ReadFile( "ajju.bmp" );

    /* Get image's dimensions */
    width = BMP_GetWidth( bmp );
    height = BMP_GetHeight( bmp );
double start_time, end_time;


count = width / nprocs;
 start = rank * count;
    stop = start + count;

start_time = MPI_Wtime();

 
    for ( x = 0  ; x <= stop ; ++x )
    {
  
        for ( y = 0 ; y < height ; ++y )
        {

                 /* Get pixel's RGB values */
            BMP_GetPixelRGB( bmp, x, y, &r, &g, &b );

            /* Invert RGB values */
            BMP_SetPixelRGB( bmp, x, y, ((0.30 *r)+(0.59 *g)+(0.11* b))/3, ((0.30 *r)+(0.59 *g)+(0.11* b))/3, ((0.30 *r)+(0.59 *g)+(0.11* b))/3);
        }
    }

end_time = MPI_Wtime();
  //   }
    /* Save result */
    BMP_WriteFile( bmp, "ajji1 out.bmp" );

diftime[rank] = diftime[rank] + (end_time - start_time);
     printf("thread[%d]  %.32g\n", rank, end_time - start_time);


    /* Free all memory allocated for the image */
    BMP_Free( bmp );
     MPI_Finalize();

    return 0;
}

