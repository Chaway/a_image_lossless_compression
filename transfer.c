#include "transfer.h"

unsigned char getT(unsigned char pixels_value)
{        
  if(pixels_value -  min > max - pixels_value)
       {
           return max - pixels_value;
       }
    else
       {
           return pixels_value - min;
       }
}


unsigned char transfer(unsigned char T_pre, int dif)
{
   unsigned char temp;
   if(dif < 0 && dif >= -T_pre)
   {
     temp = 2*(- dif) - 1; 
   }
   else if(dif >= 0 && dif <= T_pre)
   {
    temp = 2*dif;
   }
   else
   {
     temp = T_pre + abs(dif);
   }
   return temp;
}

int intransfer(unsigned char T,unsigned char dif,unsigned char pixels_value)
{

  if (dif > 2*T)
  {
      if(pixels_value > (max + min)/2)
      {
        return T - dif;
      }
      else
      {
        return dif - T;
      }
  }
  else if(dif%2 == 1)
  {
     return -(dif + 1)/2;
  }
  else
  {
     return dif/2;
  }

}