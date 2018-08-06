#include "qdbmp.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

int *number;
int count = 0;
int flag = 0; // global variables

void *image1half(void *half)
{
   count++;
    UCHAR	r, g, b;
	UINT	width, height;
	UINT	x, y;
	BMP*	bmp;   //declarations
    int typecast ;
    typecast = (int) half;
   // printf("TYPECAST %d\n",typecast );
  if(count == 1){
    bmp = BMP_ReadFile( "wiki edit.bmp" );    //INPUT
  //  printf(" count 1 entered /n");
   }
   else {
    bmp= BMP_ReadFile("wiki out.bmp");
  //  printf(" else entered ");
   }
    width = BMP_GetWidth( bmp );
	height = BMP_GetHeight( bmp );


        for ( x = 0 ; x <= width ; ++x )
        {
           for ( y = (typecast -1)*height/(*number) ; y <= (typecast *height)/(*number); ++y )
            {
                /* Get pixel's RGB values */
                BMP_GetPixelRGB( bmp, x, y, &r, &g, &b );

                /* greyscale RGB values */
                BMP_SetPixelRGB( bmp, x, y, ((0.30 *r)+(0.59 *g)+(0.11* b))/3, ((0.30 *r)+(0.59 *g)+(0.11* b))/3, ((0.30 *r)+(0.59 *g)+(0.11* b))/3) ;
            }

        }   // converting the RGB values per pixel




         BMP_WriteFile( bmp, "wiki out.bmp" );  // OUTPUT


return 0;
}


/* Creates a negative image of the input bitmap file */
int main( void )
{
    clock_t begin = clock();   ///timing code

int N = 4;
//printf("no");

number = malloc(1);
*number =N;



    pthread_t thread1[N];
    int half;

for(int i=1;i<= N;i++){
        half = i;
	if(flag==0){

	pthread_create(&thread1[i-1],NULL,image1half,(void*) half);
	}
	else {

        pthread_join(thread1[0],NULL);
    pthread_create(&thread1[i-1],NULL,image1half,(void*) half);
	}
flag++;
}
for(int j=0;j<N-1;j++){
	pthread_join(thread1[j],NULL);
}

free(number);


clock_t stop = clock();
 double elapsed = (double)(stop - begin) * 1000.0 / CLOCKS_PER_SEC;
    printf("Time elapsed in ms: %f", elapsed);

	return 0;
}
