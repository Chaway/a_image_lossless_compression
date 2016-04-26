#include "predictions.h"
void prediction1()
{ 
   //fwrite(&dif[0][0],1,1,fpo);
	FILE * fpo;
  int dif_temp;
  char filename[] = "pre1.raw";
 	fpo = fopen(filename,"wb");
	if(fpo == NULL)
	{
		printf("file %s open failed\n","pre1.raw");
		exit(0);
	}


    for(int i = 0; i < rows ; i ++)
      for(int j = 0; j < cols ; j++)
      {
     
          if(image[i][j] -  min > max - image[i][j])
         {
           T[i][j] = max - image[i][j];
         }
          else
         {
           T[i][j] = image[i][j] - min;
         }
       
      } 

   dif[0][0] = 0;
   //fwrite(&dif[0][0],1,1,fpo);

   for(int j = 0 ; j < cols - 1 ;j++)
   {
   	  dif_temp  = image[0][j + 1] - image[0][j];
      dif[0][j + 1] = transfer(T[0][j],dif_temp);
      fwrite(&dif[0][j + 1],1,1,fpo);
   }

   for(int i = 1 ; i < rows;i++)
   	for(int j = 0; j < cols ;j++)
   	{
   		dif_temp = image[i][j] - image[i-1][j];
      dif[i][j] = transfer(T[i - 1][j],dif_temp);
   		fwrite(&dif[i][j],1,1,fpo);
      // if(i == 1 && j == 0)
      // {
      //   printf("dif = %x ,dif_temp = %d,T = %x,image[0][0] = %x,image[1][0] = %x\n",dif[i][j],dif_temp,T[i - 1][j],image[0][0],image[1][0]);
      // }
   	}

    fclose(fpo);

    FILE * fp_code = fopen(outputname,"wb");
    if(fp_code == NULL)
    {
      printf("file %s open failed\n",outputname);
      exit(0);
    }

    unsigned char preclass = 1;
    fwrite(&preclass,sizeof(preclass),1,fp_code);
    fwrite(&image[0][0],sizeof(image[0][0]),1,fp_code);
    fwrite(&min,sizeof(min),1,fp_code);
    fwrite(&max,sizeof(max),1,fp_code);
    //fwrite(&T[0][0],sizeof(T[0][0]),1,fp_code);
    
    //printf("image[0][0] = %d\n",image[0][0]);
    printf("Pre-processing1 finished -> arithmetic coding start -> ");
    int code_length =  arith_code(filename,fp_code);
    //printf("%d\n",ftell(fp_code));
    min_code_length = code_length;
    printf("Arithmetic code stream length is %d bytes by prediction1\n",code_length);
    best_pre = 1;
    fclose(fp_code);
}


 void prediction2()
 {
   //fwrite(&dif[0][0],1,1,fpo);
 	FILE * fpo;
  char * filename = "pre2.raw";
  int dif_temp;

 	fpo = fopen(filename,"wb");
	if(fpo == NULL)
	{
		printf("file %s open failed\n","pre2.raw");
		exit(0);
	}

   dif[0][0] = 0;
   //fwrite(&dif[0][0],1,1,fpo);
   for(int i = 0 ; i < rows - 1 ;i++)
   {
      dif_temp  = image[i + 1][0] - image[i][0];
      dif[i + 1][0] = transfer(T[i][0],dif_temp);
      fwrite(&dif[i + 1][0],1,1,fpo);
     // printf("T = %x ,dif = %x ,dif_temp = %d,image[%d][0] = %x\n",T[i][0],dif[i][0],dif_temp,i + 1,image[i + 1][0]);
   }

   for(int i = 0 ; i < rows;i++)
   	for(int j = 1; j < cols ;j++)
   	{
      dif_temp = image[i][j] - image[i][j-1];
      dif[i][j] = transfer(T[i][j-1],dif_temp);
      fwrite(&dif[i][j],1,1,fpo);
   	}

   	fclose(fpo);

    FILE * fp_code = fopen("lena2.dat","wb");
    if(fp_code == NULL)
    {
      printf("file %s open failed\n","lena2.dat");
      exit(0);
    }

    unsigned char preclass = 2;
    fwrite(&preclass,sizeof(preclass),1,fp_code);
    fwrite(&image[0][0],sizeof(image[0][0]),1,fp_code);
    fwrite(&min,sizeof(min),1,fp_code);
    fwrite(&max,sizeof(max),1,fp_code);
    //fwrite(&T[0][0],sizeof(T[0][0]),1,fp_code);
    
    //printf("image[0][0] = %d\n",image[0][0]);
    printf("Pre-processing2 finished -> arithmetic coding start -> ");
    int code_length =  arith_code(filename,fp_code);
    //printf("%d\n",ftell(fp_code));
    //min_code_length = code_length;
    printf("Arithmetic code stream length is %d bytes by prediction2\n",code_length);
    if(code_length < min_code_length)
    {
      min_code_length = code_length;
      best_pre = 2;
      remove(outputname);
      //remove("./pre2.raw");
      rename("lena2.dat",outputname);
    }
    else
    {
      remove("lena2.dat");
    }

    fclose(fp_code);
 }


 void prediction3()
 {
   //fwrite(&dif[0][0],1,1,fpo);
 	FILE * fpo;
  char * filename = "pre3.raw";
 	fpo = fopen(filename,"wb");
	if(fpo == NULL)
	{
		printf("file %s open failed\n","pre3.raw");
		exit(0);
	}
   dif[0][0] = 0;
   //fwrite(&dif[0][0],1,1,fpo);
     
   for(int j = 0 ; j < cols - 1 ;j++)
   {
      fwrite(&dif[0][j + 1],1,1,fpo);
   }

   for(int i = 0 ; i < rows - 1 ;i++)
   {
      fwrite(&dif[i + 1][0],1,1,fpo);
   }

   for(int i = 1 ; i < rows;i++)
   	for(int j = 1; j < cols ;j++)
   	{
      int dif_temp  = image[i][j] - image[i-1][j-1];
      dif[i][j] = transfer(T[i-1][j-1],dif_temp);
      fwrite(&dif[i][j],1,1,fpo);
   	}

   	fclose(fpo);

    FILE * fp_code = fopen("lena3.dat","wb");
    if(fp_code == NULL)
    {
      printf("file %s open failed\n","lena3.dat");
      exit(0);
    }

    unsigned char preclass = 3;
    fwrite(&preclass,sizeof(preclass),1,fp_code);
    fwrite(&image[0][0],sizeof(image[0][0]),1,fp_code);
    fwrite(&min,sizeof(min),1,fp_code);
    fwrite(&max,sizeof(max),1,fp_code);
    //fwrite(&T[0][0],sizeof(T[0][0]),1,fp_code);
    
    //printf("image[0][0] = %d\n",image[0][0]);
     printf("Pre-processing3 finished -> arithmetic coding start -> ");
    int code_length =  arith_code(filename,fp_code);
    //printf("%d\n",ftell(fp_code));
    //min_code_length = code_length;
    printf("Arithmetic code stream length is %d bytes by prediction3\n",code_length);
    if(code_length < min_code_length)
    {
      min_code_length = code_length;
      best_pre = 3;
      remove(outputname);
      rename("lena3.dat",outputname);
    }
    else
    {
      remove("lena3.dat");
    }
    fclose(fp_code);

 }



  void prediction4()
 {
   //fwrite(&dif[0][0],1,1,fpo);
  FILE * fpo;
  char * filename = "pre4.raw";
  fpo = fopen(filename,"wb");
  if(fpo == NULL)
  {
    printf("file %s open failed\n","pre4.raw");
    exit(0);
  }

   dif[0][0] = 0;
   
   for(int j = 0 ; j < cols - 1 ;j++)
   {
      fwrite(&dif[0][j + 1],1,1,fpo);
   }

   for(int i = 0 ; i < rows - 1 ;i++)
   {
      fwrite(&dif[i + 1][0],1,1,fpo);
   }

   for(int i = 1 ; i < rows;i++)
   	for(int j = 1; j < cols ;j++)
   	{
      unsigned char pre_value = (image[i - 1][j] + image[i][j - 1])/2;
      int dif_temp  = image[i][j] - pre_value;
      dif[i][j] = transfer(getT(pre_value),dif_temp);
      fwrite(&dif[i][j],1,1,fpo);
   	}

   	fclose(fpo);

     FILE * fp_code = fopen("lena4.dat","wb");
    if(fp_code == NULL)
    {
      printf("file %s open failed\n","lena4.dat");
      exit(0);
    }

    unsigned char preclass = 4;
    fwrite(&preclass,sizeof(preclass),1,fp_code);
    fwrite(&image[0][0],sizeof(image[0][0]),1,fp_code);
    fwrite(&min,sizeof(min),1,fp_code);
    fwrite(&max,sizeof(max),1,fp_code);
    //fwrite(&T[0][0],sizeof(T[0][0]),1,fp_code);
    
    //printf("image[0][0] = %d\n",image[0][0]);
   printf("Pre-processing4 finished -> arithmetic coding start -> ");
    int code_length =  arith_code(filename,fp_code);
    //printf("%d\n",ftell(fp_code));
    //min_code_length = code_length;
    printf("Arithmetic code stream length is %d bytes by prediction4\n",code_length);
    if(code_length < min_code_length)
    {
      min_code_length = code_length;
      best_pre = 4;
      remove(outputname);
      rename("lena4.dat",outputname);
    }
    else
    {
      remove("lena4.dat");
    }

    fclose(fp_code);
 }


   void prediction5()
 {
  FILE * fpo;
  char * filename = "pre5.raw";
  fpo = fopen(filename,"wb");
  if(fpo == NULL)
  {
    printf("file %s open failed\n","pre5.raw");
    exit(0);
  }

   dif[0][0] = 0;
   
   for(int j = 0 ; j < cols - 1 ;j++)
   {
      fwrite(&dif[0][j + 1],1,1,fpo);
   }

   for(int i = 0 ; i < rows - 1 ;i++)
   {
      fwrite(&dif[i + 1][0],1,1,fpo);
   }


   for(int i = 1 ; i < rows;i++)
   	for(int j = 1; j < cols ;j++)
   	{
     
      int pre_value = image[i - 1][j] + image[i][j - 1] - image[i-1][j-1]; 
     if(pre_value > max)
      {
        pre_value = pre_value - max + min;
      }
      else if(pre_value < min)
      {
        pre_value = pre_value + max - min;
      }

        int dif_temp  = image[i][j] - pre_value;
        dif[i][j] = transfer(getT(pre_value),dif_temp);
        fwrite(&dif[i][j],1,1,fpo);     
   	}

   	fclose(fpo);


     FILE * fp_code = fopen("lena5.dat","wb");
    if(fp_code == NULL)
    {
      printf("file %s open failed\n","lena5.dat");
      exit(0);
    }

    unsigned char preclass = 5;
    fwrite(&preclass,sizeof(preclass),1,fp_code);
    fwrite(&image[0][0],sizeof(image[0][0]),1,fp_code);
    fwrite(&min,sizeof(min),1,fp_code);
    fwrite(&max,sizeof(max),1,fp_code);
    //fwrite(&T[0][0],sizeof(T[0][0]),1,fp_code);
    
    //printf("image[0][0] = %d\n",image[0][0]);
    printf("Pre-processing5 finished -> arithmetic coding start -> ");
    int code_length =  arith_code(filename,fp_code);
    //printf("%d\n",ftell(fp_code));
    //min_code_length = code_length;
    printf("Arithmetic code stream length is %d bytes by prediction5\n",code_length);
    if(code_length < min_code_length)
    {
      min_code_length = code_length;
      best_pre = 5;
      remove(outputname);
      rename("lena5.dat",outputname);
    }
    else
    {
      remove("lena5.dat");
    }
    fclose(fp_code);
 }


  void prediction6()
 {
  FILE * fpo;
  char * filename = "pre6.raw";
  fpo = fopen(filename,"wb");
  if(fpo == NULL)
  {
    printf("file %s open failed\n","pre6.raw");
    exit(0);
  }

   dif[0][0] = 0;
   
   for(int j = 0 ; j < cols - 1 ;j++)
   {
      fwrite(&dif[0][j + 1],1,1,fpo);
   }

   for(int i = 0 ; i < rows - 1 ;i++)
   {
      fwrite(&dif[i + 1][0],1,1,fpo);
   }


   for(int i = 1 ; i < rows;i++)
    for(int j = 1; j < cols ;j++)
    {
     
      int pre_value = image[i][j - 1] + (image[i - 1][j] - image[i-1][j-1])/2; 

     if(pre_value > max)
      {
        pre_value = (pre_value - max)*2 + min;
      }
      else if(pre_value < min)
      {
        pre_value = (pre_value  - min)*2 + max;
      }

        int dif_temp  = image[i][j] - pre_value;
        dif[i][j] = transfer(getT(pre_value),dif_temp);
        fwrite(&dif[i][j],1,1,fpo);     
    }

    fclose(fpo);


     FILE * fp_code = fopen("lena6.dat","wb");
    if(fp_code == NULL)
    {
      printf("file %s open failed\n","lena6.dat");
      exit(0);
    }

    unsigned char preclass = 6;
    fwrite(&preclass,sizeof(preclass),1,fp_code);
    fwrite(&image[0][0],sizeof(image[0][0]),1,fp_code);
    fwrite(&min,sizeof(min),1,fp_code);
    fwrite(&max,sizeof(max),1,fp_code);
    //fwrite(&T[0][0],sizeof(T[0][0]),1,fp_code);
    
    //printf("image[0][0] = %d\n",image[0][0]);
  printf("Pre-processing6 finished -> arithmetic coding start -> ");
    int code_length =  arith_code(filename,fp_code);
    //printf("%d\n",ftell(fp_code));
    //min_code_length = code_length;
    printf("Arithmetic code stream length is %d bytes by prediction6\n",code_length);
    if(code_length < min_code_length)
    {
      min_code_length = code_length;
      best_pre = 6;
      remove(outputname);
      rename("lena6.dat",outputname);
    }
    else
    {
      remove("lena6.dat");
    }

    fclose(fp_code);
 }



  void prediction7()
 {
  FILE * fpo;
  char * filename = "pre7.raw";
  fpo = fopen(filename,"wb");
  if(fpo == NULL)
  {
    printf("file %s open failed\n","pre7.raw");
    exit(0);
  }

   dif[0][0] = 0;
   
   for(int j = 0 ; j < cols - 1 ;j++)
   {
      fwrite(&dif[0][j + 1],1,1,fpo);
   }

   for(int i = 0 ; i < rows - 1 ;i++)
   {
      fwrite(&dif[i + 1][0],1,1,fpo);
   }


   for(int i = 1 ; i < rows;i++)
    for(int j = 1; j < cols ;j++)
    {
     
      int pre_value = image[i - 1][j] + (image[i][j - 1] - image[i-1][j-1])/2; 

      if(pre_value > max)
      {
        pre_value = (pre_value - max)*2 + min;
      }
      else if(pre_value < min)
      {
        pre_value = (pre_value  - min)*2 + max;
      }

        int dif_temp  = image[i][j] - pre_value;
        dif[i][j] = transfer(getT(pre_value),dif_temp);
        fwrite(&dif[i][j],1,1,fpo);     
    }

    fclose(fpo);

     FILE * fp_code = fopen("lena7.dat","wb");
    if(fp_code == NULL)
    {
      printf("file %s open failed\n","lena7.dat");
      exit(0);
    }

    unsigned char preclass = 7;

    fwrite(&preclass,sizeof(preclass),1,fp_code);
    fwrite(&image[0][0],sizeof(image[0][0]),1,fp_code);
    fwrite(&min,sizeof(min),1,fp_code);
    fwrite(&max,sizeof(max),1,fp_code);
    printf("Pre-processing7 finished -> arithmetic coding start -> ");
    int code_length =  arith_code(filename,fp_code);

    printf("Arithmetic code stream length is %d bytes by prediction7\n",code_length);
    if(code_length < min_code_length)
    {
      min_code_length = code_length;
      best_pre = 7;
      remove(outputname);
      rename("lena7.dat",outputname);
    }
    else
    {
      remove("lena7.dat");
    }
    fclose(fp_code);
 }
