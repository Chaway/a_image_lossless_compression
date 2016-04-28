#include "Video_Code.h"

unsigned char image[rows][cols];
unsigned char dif[rows][cols];
unsigned char T[rows][cols];
FILE *fpi;
unsigned char max = 0;
unsigned char min = 255;
unsigned char best_pre = 0;
int min_code_length = 0;
char * outputname;

void main(int argc, char *args[])
{
		// in_file, out_file
	unsigned char symbol ;

	fpi = fopen(args[1],"r");
	if(fpi == NULL)
	{
		printf("file %s open failed\n",args[1]);
		exit(0);
	}

  outputname = args[2];
	// if(fpo_code==NULL)
	// {
	// 	printf("file %s open failed\n",args[2]);
	// 	exit(0);
	// }
    
     for(int i = 0; i < rows ; i ++)
     	for(int j = 0; j < cols ; j++)
     	{
     		image[i][j] = fgetc(fpi);
	        if(image[i][j] > max)
       		 {
         	 max = image[i][j];
        	}

        	if(image[i][j] < min)
        	{
       		   min = image[i][j];
        	}
     		//printf("image = %x\n",image[i][j]); 
     	}
    fclose(fpi);
    printf("Size of origin file is %d bytes\n",num_pixels);
    printf("encode start ...\n");
    prediction1();
    prediction2();
    prediction3();
    prediction4();
    prediction5();
    prediction6();
    prediction7();

    printf("encode finished ,best prediction is number %d\n\n", best_pre);
	
	//fclose(fpo_code);

}


