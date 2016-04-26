#include "Video_Decode.h"

unsigned char image[rows][cols];
unsigned char dif[rows][cols];
unsigned char T[rows][cols];
FILE *fpi,*fpo_decode;
unsigned char max = 0;
unsigned char min = 255;
unsigned char best_pre = 0;
int min_code_length = 0;



void main(int argc, char *args[])
{
		// in_file, out_file
	unsigned char symbol;
	fpi = fopen(args[1],"r");
	if(fpi == NULL)
	{
		printf("file %s open failed\n",args[1]);
		exit(0);
	}

	fpo_decode = fopen(args[2],"wb");
	if(fpo_decode == NULL)
	{
		printf("file %s open failed\n",args[2]);
		exit(0);
	}
    

    printf("decode start ...\n");
    unsigned char preclass;
    fread(&preclass,sizeof(preclass),1,fpi);

    //printf("prediction class is = %d\n",preclass);
    fread(&image[0][0],sizeof(image[0][0]),1,fpi);
    fread(&min,sizeof(min),1,fpi);
   // printf("min = %x\n",min);
    fread(&max,sizeof(max),1,fpi);
    //printf("min = %x ,max = %x\n",min,max);
    
    switch(preclass)
    {
      case 1:
             printf("encode method is prediction1\n");
             deprediction1();
             break;
      case 2:
             printf("encode method is prediction2\n");
             deprediction2();
             break;
      case 3:
      		 printf("encode method is prediction3\n");
             deprediction3();
             break;
      case 4:
             printf("encode method is prediction4\n");
             deprediction4();
             break;
      case 5:
             printf("encode method is prediction5\n");
             deprediction5();
             break;
      case 6:
             printf("encode method is prediction6\n");
             deprediction6();
             break;
      case 7:
             printf("encode method is prediction7\n");
             deprediction7();
             break;
      default:
         break;
    }

    for(int i = 0; i < rows ; i ++)
       for(int j = 0; j < cols ; j++)
     	{
     		fwrite(&image[i][j],sizeof(image[i][j]),1,fpo_decode);
     		//printf("image = %x\n",image[i][j]); 
     	}

    fclose(fpi);
	fclose(fpo_decode);
	printf("decode finished\n");
}
