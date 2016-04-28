#include "de-predictors.h"

void  deprediction1()
{
	
	char filename[] = "pre1_de.raw";
	//arithmetic decode
	arith_decode(filename,fpi);
	FILE *fp_dif;
	 if((fp_dif = fopen(filename, "r"))== NULL)    //open symbol file
     {
       printf("%s\n",filename);
       printf("open input file error\n");
  	   exit(0);
     }
     
     //fread(&T[0][0],sizeof(T[0][0]),1,fpi);
     T[0][0] = getT(image[0][0]);
    // dif[0][0] = fgetc(fp_dif);

     for(int j = 1;j < cols;j++)
     {
         dif[0][j] = fgetc(fp_dif);
         int dif_temp = intransfer(T[0][j - 1],dif[0][j],image[0][j-1]);
         image[0][j] = image[0][j - 1] + dif_temp;
         T[0][j] = getT(image[0][j]);
     }

     for(int i = 1; i < rows ; i ++)
     	for(int j = 0; j < cols ; j++)
     	{
     		dif[i][j] = fgetc(fp_dif);
     		int dif_temp = intransfer(T[i - 1][j],dif[i][j],image[i - 1][j]);
     		image[i][j] = image[i - 1][j] + dif_temp;
            T[i][j] = getT(image[i][j]);
            // if(i == 1 && j == 0)
            // {
            //   printf("dif = %x ,dif_temp = %d,T = %x,image[0][0] =%x ,image[1][0] = %x\n",dif[i][j],dif_temp,T[i - 1][j],image[0][0],image[1][0]);
            // }

     	}
}

void  deprediction2()
{
	
	char filename[] = "pre2_de.raw";
    //arithmetic decode
	arith_decode(filename,fpi);
	//
	FILE *fp_dif;
	 if((fp_dif = fopen(filename, "r"))== NULL)    //open symbol file
     {
       printf("%s\n",filename);
       printf("open input file error\n");
  	   exit(0);
     }
     
     //fread(&T[0][0],sizeof(T[0][0]),1,fpi);
     T[0][0] = getT(image[0][0]);
    // printf("image[0][0] = %x\n",image[0][0]);
    // dif[0][0] = fgetc(fp_dif);

     for(int i = 1;i < rows;i++)
     {
         dif[i][0] = fgetc(fp_dif);
         int dif_temp = intransfer(T[i - 1][0],dif[i][0],image[i - 1][0]);
         image[i][0] = image[i - 1][0] + dif_temp;
         T[i][0] = getT(image[i][0]);
         //printf("dif = %x ,dif_temp = %d,image[%d][0] = %x\n",dif[i][0],dif_temp,i,image[i][0]);
     }

     for(int i = 0; i < rows ; i ++)
     	for(int j = 1; j < cols ; j++)
     	{
     		dif[i][j] = fgetc(fp_dif);
     		int dif_temp = intransfer(T[i][j - 1],dif[i][j],image[i][j - 1]);
     		image[i][j] = image[i][j - 1] + dif_temp;
            T[i][j] = getT(image[i][j]);
            // if(i == 1 && j == 0)
            // {
            //   printf("dif = %x ,dif_temp = %d,T = %x,image[0][0] =%x ,image[1][0] = %x\n",dif[i][j],dif_temp,T[i - 1][j],image[0][0],image[1][0]);
            // }

     	}
}



void  deprediction3()
{
	
	char filename[] = "pre3_de.raw";
	//arithmetic decode
	arith_decode(filename,fpi);
	FILE *fp_dif;
	 if((fp_dif = fopen(filename, "r"))== NULL)    //open symbol file
     {
       printf("%s\n",filename);
       printf("open input file error\n");
  	   exit(0);
     }
     
     //fread(&T[0][0],sizeof(T[0][0]),1,fpi);
     T[0][0] = getT(image[0][0]);
     //printf("image[0][0] = %x\n",image[0][0]);
    // dif[0][0] = fgetc(fp_dif);
    


     for(int j = 1;j < cols;j++)
     {
         dif[0][j] = fgetc(fp_dif);
         int dif_temp = intransfer(T[0][j - 1],dif[0][j],image[0][j-1]);
         image[0][j] = image[0][j - 1] + dif_temp;
         T[0][j] = getT(image[0][j]);
     }
     


     for(int i = 1;i < rows;i++)
     {
         dif[i][0] = fgetc(fp_dif);
         int dif_temp = intransfer(T[i - 1][0],dif[i][0],image[i - 1][0]);
         image[i][0] = image[i - 1][0] + dif_temp;
         T[i][0] = getT(image[i][0]);
         //printf("dif = %x ,dif_temp = %d,image[%d][0] = %x\n",dif[i][0],dif_temp,i,image[i][0]);
     }




     for(int i = 1; i < rows ; i ++)
     	for(int j = 1; j < cols ; j++)
     	{
     		dif[i][j] = fgetc(fp_dif);
     		int dif_temp = intransfer(T[i - 1][j - 1],dif[i][j],image[i - 1][j - 1]);
     		image[i][j] = image[i - 1][j - 1] + dif_temp;
            T[i][j] = getT(image[i][j]);
            // if(i == 1 && j == 0)
            // {
            //   printf("dif = %x ,dif_temp = %d,T = %x,image[0][0] =%x ,image[1][0] = %x\n",dif[i][j],dif_temp,T[i - 1][j],image[0][0],image[1][0]);
            // }

     	}
}


void  deprediction4()
{
	
	char filename[] = "pre4_de.raw";
	//arithmetic decode
	arith_decode(filename,fpi);
	FILE *fp_dif;
	 if((fp_dif = fopen(filename, "r"))== NULL)    //open symbol file
     {
       printf("%s\n",filename);
       printf("open input file error\n");
  	   exit(0);
     }
     
     //fread(&T[0][0],sizeof(T[0][0]),1,fpi);
     T[0][0] = getT(image[0][0]);
   //  printf("image[0][0] = %x\n",image[0][0]);
    // dif[0][0] = fgetc(fp_dif);
    


     for(int j = 1;j < cols;j++)
     {
         dif[0][j] = fgetc(fp_dif);
         int dif_temp = intransfer(T[0][j - 1],dif[0][j],image[0][j-1]);
         image[0][j] = image[0][j - 1] + dif_temp;
         T[0][j] = getT(image[0][j]);
     }
     


     for(int i = 1;i < rows;i++)
     {
         dif[i][0] = fgetc(fp_dif);
         int dif_temp = intransfer(T[i - 1][0],dif[i][0],image[i - 1][0]);
         image[i][0] = image[i - 1][0] + dif_temp;
         T[i][0] = getT(image[i][0]);
         //printf("dif = %x ,dif_temp = %d,image[%d][0] = %x\n",dif[i][0],dif_temp,i,image[i][0]);
     }




     for(int i = 1; i < rows ; i ++)
     	for(int j = 1; j < cols ; j++)
     	{
     		dif[i][j] = fgetc(fp_dif);
     		unsigned char pre_value = (image[i - 1][j] + image[i][j-1])/2;
     		int dif_temp = intransfer(getT(pre_value),dif[i][j],pre_value);
     		image[i][j] = pre_value + dif_temp;
     	}
}


void  deprediction5()
{
	
	char filename[] = "pre5_de.raw";
	//arithmetic decode
	arith_decode(filename,fpi);
	FILE *fp_dif;
	 if((fp_dif = fopen(filename, "r"))== NULL)    //open symbol file
     {
       printf("%s\n",filename);
       printf("open input file error\n");
  	   exit(0);
     }
     
     //fread(&T[0][0],sizeof(T[0][0]),1,fpi);
     T[0][0] = getT(image[0][0]);
     //printf("image[0][0] = %x\n",image[0][0]);
    // dif[0][0] = fgetc(fp_dif);
    


     for(int j = 1;j < cols;j++)
     {
         dif[0][j] = fgetc(fp_dif);
         int dif_temp = intransfer(T[0][j - 1],dif[0][j],image[0][j-1]);
         image[0][j] = image[0][j - 1] + dif_temp;
         T[0][j] = getT(image[0][j]);
     }
     


     for(int i = 1;i < rows;i++)
     {
         dif[i][0] = fgetc(fp_dif);
         int dif_temp = intransfer(T[i - 1][0],dif[i][0],image[i - 1][0]);
         image[i][0] = image[i - 1][0] + dif_temp;
         T[i][0] = getT(image[i][0]);
         //printf("dif = %x ,dif_temp = %d,image[%d][0] = %x\n",dif[i][0],dif_temp,i,image[i][0]);
     }




     for(int i = 1; i < rows ; i ++)
     	for(int j = 1; j < cols ; j++)
     	{
     		
     	   int pre_value = image[i - 1][j] + image[i][j-1] - image[i-1][j-1];
           // if(pre_value > max)
           // {
           //   pre_value = pre_value - max + min;
           // }
           // else if(pre_value < min)
           // {
           //  pre_value = pre_value + max - min;
           // }
     		  dif[i][j] = fgetc(fp_dif);
     		  int dif_temp = intransfer(getT(pre_value),dif[i][j],pre_value);
     		  image[i][j] = pre_value + dif_temp;
        }
}

void  deprediction6()
{
	
	char filename[] = "pre6_de.raw";
	//arithmetic decode
	arith_decode(filename,fpi);
	FILE *fp_dif;
	 if((fp_dif = fopen(filename, "r"))== NULL)    //open symbol file
     {
       printf("%s\n",filename);
       printf("open input file error\n");
  	   exit(0);
     }
     
     //fread(&T[0][0],sizeof(T[0][0]),1,fpi);
     T[0][0] = getT(image[0][0]);
     //printf("image[0][0] = %x\n",image[0][0]);
    // dif[0][0] = fgetc(fp_dif);
    


     for(int j = 1;j < cols;j++)
     {
         dif[0][j] = fgetc(fp_dif);
         int dif_temp = intransfer(T[0][j - 1],dif[0][j],image[0][j-1]);
         image[0][j] = image[0][j - 1] + dif_temp;
         T[0][j] = getT(image[0][j]);
     }
     


     for(int i = 1;i < rows;i++)
     {
         dif[i][0] = fgetc(fp_dif);
         int dif_temp = intransfer(T[i - 1][0],dif[i][0],image[i - 1][0]);
         image[i][0] = image[i - 1][0] + dif_temp;
         T[i][0] = getT(image[i][0]);
         //printf("dif = %x ,dif_temp = %d,image[%d][0] = %x\n",dif[i][0],dif_temp,i,image[i][0]);
     }




     for(int i = 1; i < rows ; i ++)
     	for(int j = 1; j < cols ; j++)
     	{
     		
     	   int pre_value = image[i][j - 1] + (image[i - 1][j] - image[i-1][j-1])/2;
          // if(pre_value > max)
          // {
          //   pre_value = (pre_value - max)*2 + min;
          // }
          // else if(pre_value < min)
          // {
          //   pre_value = (pre_value  - min)*2 + max;
          // }

     		  dif[i][j] = fgetc(fp_dif);
     		  int dif_temp = intransfer(getT(pre_value),dif[i][j],pre_value);
     		  image[i][j] = pre_value + dif_temp;
        }
}


void  deprediction7()
{
	
	char filename[] = "pre7_de.raw";
	//arithmetic decode
	arith_decode(filename,fpi);
	FILE *fp_dif;
	 if((fp_dif = fopen(filename, "r"))== NULL)    //open symbol file
     {
       printf("%s\n",filename);
       printf("open input file error\n");
  	   exit(0);
     }
     
     //fread(&T[0][0],sizeof(T[0][0]),1,fpi);
     T[0][0] = getT(image[0][0]);
     //printf("image[0][0] = %x\n",image[0][0]);
    // dif[0][0] = fgetc(fp_dif);
    


     for(int j = 1;j < cols;j++)
     {
         dif[0][j] = fgetc(fp_dif);
         int dif_temp = intransfer(T[0][j - 1],dif[0][j],image[0][j-1]);
         image[0][j] = image[0][j - 1] + dif_temp;
         T[0][j] = getT(image[0][j]);
     }
     


     for(int i = 1;i < rows;i++)
     {
         dif[i][0] = fgetc(fp_dif);
         int dif_temp = intransfer(T[i - 1][0],dif[i][0],image[i - 1][0]);
         image[i][0] = image[i - 1][0] + dif_temp;
         T[i][0] = getT(image[i][0]);
         //printf("dif = %x ,dif_temp = %d,image[%d][0] = %x\n",dif[i][0],dif_temp,i,image[i][0]);
     }




     for(int i = 1; i < rows ; i ++)
     	for(int j = 1; j < cols ; j++)
     	{
     		
     	   int pre_value = image[i - 1][j] + (image[i][j-1] - image[i-1][j-1])/2;
          // if(pre_value > max)
          // {
          //   pre_value = (pre_value - max)*2 + min;
          // }
          // else if(pre_value < min)
          // {
          //   pre_value = (pre_value  - min)*2 + max;
          // }
     		  dif[i][j] = fgetc(fp_dif);
     		  int dif_temp = intransfer(getT(pre_value),dif[i][j],pre_value);
     		  image[i][j] = pre_value + dif_temp;
        }
}