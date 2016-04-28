#include "transfer.h"

int getT(int pre_value)
{        
  if(pre_value -  min > max - pre_value)
       {
           return max - pre_value;
       }
    else
       {
           return pre_value - min;
       }
}


unsigned char transfer(int T_pre, int dif)
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

int intransfer(int T,unsigned char dif,int pre_value)
{

  if (dif > 2*T)
  {
      if(pre_value > (max + min)/2)
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