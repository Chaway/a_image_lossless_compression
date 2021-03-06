#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//MACRO difination
//#define m 21

FILE * fp , *fpo;
static unsigned short symbol_num; // variety  number of  symbols
static char buffer;
static unsigned long int  t;
static unsigned char bits_in_buffer; //number of bits in buffer to be read into t;
static unsigned long int  mMASK ;
static unsigned long int  norMASK ;
static int m;

struct Bit
{
  unsigned char UMSB:1;  //MSB of up boundary
  unsigned char USMSB:1; //second MSB of up boundary
  unsigned char LMSB:1;  //MSB of low boundary
  unsigned char LSMSB:1; //second MSB of low boundary
  unsigned char sendbit:1;
  unsigned char empty:3;
}bit;

void rescale(unsigned long int* l ,unsigned long int* u , int index_of_sym ,int Cum_count[])
{
	///printf("rescale: ");
	///printf("Cum_count[%d] = %d   ",index_of_sym, Cum_count[index_of_sym]);
	///printf("Cum_count[%d] = %d   ",index_of_sym - 1, Cum_count[index_of_sym - 1]);
	unsigned long int ll = *(l);
	unsigned long int uu = *(u);
  *(u) = ll + ((uu - ll + 1) * (Cum_count[index_of_sym])) / Cum_count[symbol_num] - 1;
	*(l) = ll + ((uu - ll + 1) * (Cum_count[index_of_sym - 1])) / Cum_count[symbol_num];
        ///printf("(%ld , %ld)--->>>(%ld , %ld)\n", ll , uu , *(l) , *(u));
	//printf("U = %d -> U = %d\n", uu , *(u));
}

void get_bit_from_buffer()
{
 //bit.sendbit = buffer >> (m - 1);
 if(bits_in_buffer == 0)
 {
    fread(&buffer,1,1,fp);
    bits_in_buffer = 8;
 }
  bit.sendbit = buffer >> 7;
  buffer = buffer << 1;
  bits_in_buffer --;
  t = ((t << 1) + bit.sendbit) & mMASK;
  //printf("t = %d\n",t);
}



void arith_decode(char* args,FILE * fp_in)
{
 // bits_in_buffer = 0;
 // if((fp = fopen(args[1] , "rb"))== NULL)    //open binary file
 //  {
 //  	 printf("%s\n",args[1]);
 //     printf("open input file error\n");
 //  	 exit(0);
 //  }
  
  if((fpo = fopen(args , "wb"))== NULL)    //open output file
  {
     printf("%s\n",args);
     printf("open output file error\n");
     exit(0);
  }
  

  fp = fp_in;

  // if((fs = fopen("statistic.txt" , "r"))== NULL)    //open statistic file
  // {
  //    printf("open statistic-file error\n");
  //    exit(0);
  // }
  printf("arithmetic decode start ..\n");
  fread(&symbol_num,sizeof(symbol_num),1,fp); //get the number of varity od symbols
  //printf("symbol_num = %x\n" , symbol_num);

  //initialize
  unsigned char symbols[symbol_num + 1];
  int Count[symbol_num];
  for(int i = 1 ;i <= symbol_num ; ++i)
  {
     //fscanf(fs,"%d %d", &symbols[i] , &Count[i - 1]);
    fread(&symbols[i],sizeof(symbols[i]),1,fp);
   /// printf("symbols[%d] = %x\n",i ,symbols[i]);
    /// printf("number %d symbol is (ASCII value =
    fread(&Count[i-1],sizeof(Count[i-1]),1,fp);
    ///printf("Count[%d] = %x\n",i - 1,Count[i-1]);
    /// printf("number %d symbol is (ASCII value = %d) , Count[%d] = %d \n", i , symbols[i], i - 1 , Count[i - 1]);
  }

  //fclose(fs);

  int Cum_count[symbol_num + 1];
  //calculate Cum_count
  Cum_count[0] = 0;
  for (int i = 0; i < symbol_num; ++i)
  {
     Cum_count[i + 1] = Cum_count[i] + Count[i];
  }

  int num_wait_decode = Cum_count[symbol_num];
  //printf("num_wait_decode = %d\n",num_wait_decode);

  m = (int)(log(Cum_count[symbol_num])/log(2)) + 1 + 2; 
  printf("m = %d\n",m);
  mMASK = (1 << m) - 1;
  norMASK = 1 << (m-1);


  //initialize t,l,u
  for (int i = 0; i < m; i++)
  {
      get_bit_from_buffer();
  }

 
  unsigned long int l = 0;
  unsigned long int u = mMASK;
  ///printf("u = %ld ,l = %ld , t = %ld\n",u,l,t);
  while(num_wait_decode)
  {

    while(1)
    {
       bit.UMSB = (u >> (m - 1))%2;
       bit.LMSB = (l >> (m - 1))%2;

           if(bit.UMSB == bit.LMSB)
           {
            /// printf("UMSB = LMSB --------------------------------------");
            /// printf("(%ld , %ld , %ld)--->>>",l,u,t);
             /*---------------------
               shift l to left 1 bit and shift 0 into LSB;
               shift u to left 1 bit and shift 1 into LSB;
               shift t to left 1 bit and read next bit from received bistream into LSB
             ----------------------*/
             l = (l << 1) & mMASK;    //guarantee that l and u always use m bits
             u = ((u << 1) + 1) & mMASK;
              
             get_bit_from_buffer();
            /// printf("(%ld , %ld , %ld)\n",l,u,t);
            }
            else
            {
               bit.USMSB = (u>>(m -2))%2;
               bit.LSMSB = (l>>(m -2))%2;

               if(bit.USMSB == 0 && bit.LSMSB == 1)  //USMSB = 0 and LSMSB = 1  only if when u = 10... and l = 01...
               {
                 ///printf("E3 mapping:--------------------------------------");
                 /// printf("(%ld , %ld , %ld)--->>>",l,u,t);
                 l = ((l << 1) ^ norMASK) & mMASK;
                 u = (((u << 1) ^ norMASK) + 1) & mMASK;
                 get_bit_from_buffer();
                 t = t ^ norMASK;
                 ///printf("(%ld , %ld , %ld)\n",l,u,t);
               }
               else
               {
                 //rescale l and u
                 //int index_of_sym = get_current_symbol(wait_for_encode);
                 int k = 0;
                 ///printf("u = %ld ,l = %ld , t = %ld\n",u,l,t);
                 while((((t - l + 1)*Cum_count[symbol_num] - 1))/(u - l + 1) >= Cum_count[k])
                 {
                   k ++;
                 }
                 ///printf("k = %d \n" , k);
                 unsigned char symbol = symbols[k];
                 num_wait_decode -- ;
                 ///printf(" num_wait_decode = %d\n",num_wait_decode);
                 ///printf("@@@@@@the number %d is (ASCII = %x)\n",Cum_count[symbol_num] - num_wait_decode, symbol);
                  
                 fputc(symbol , fpo);
                 rescale(&l,&u, k , Cum_count);
                 break;
                 //wait_for_encode -- ;
               }

            }
       }

  }

  //fclose(fp);
  fclose(fpo);
  printf("arithmetic decode finished\n");
}
