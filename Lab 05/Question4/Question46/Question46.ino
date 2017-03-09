/*
 * Bryce Monaco
 * CPE 301
 * Lab 05 - Question 4 (Book 4.6)
 */

void NewDelay (unsigned long mSecondsApx); 

void setup ()
{
  unsigned char* portDDRB;
  portDDRB = (unsigned char*) 0x24;

  *portDDRB |= 0x80; //Changed from 0x20 since the Mega has the LED at bit 7
  
}

void loop ()
{
  unsigned char* portB;

  portB = (unsigned char*) 0x25;

  *portB |= 0x80;
  NewDelay (100); 
  *portB &= 0x7F; //Changed from 0xDF since the LED is at bit 7
  NewDelay (100); 
  
}

void NewDelay (unsigned long mSecondsApx) 
{
  volatile unsigned long i;
  unsigned char j = 0;
  unsigned long endTime = 100 * mSecondsApx;

  i = 0;
  while (j == 0) //Changed '=' to '=='
  {
    i++;

    if (i == endTime) //Changed '=' to '=='
    {
      j = 1;
      
    }
  }  
}
