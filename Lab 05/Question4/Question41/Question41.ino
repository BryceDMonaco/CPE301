/*
 * Bryce Monaco
 * CPE 301
 * Lab 05 - Question 4 (Book 4.1)
 */

void MyDelay (unsigned long mSecondsApx);

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
  MyDelay (1000); //Changed brackets from {} to (), added semicolon
  *portB &= 0x7F; //Changed from 0xDF since the LED is at bit 7, changed ':' to ';'
  MyDelay (1000); //Changed brackets from [] to (), changed ',' to ';'
  
}

void MyDelay (unsigned long mSecondsApx)
{
  volatile unsigned long i;
  unsigned long endTime = 1000 * mSecondsApx;

  for (i = 0; i < endTime; i++);
  
}

