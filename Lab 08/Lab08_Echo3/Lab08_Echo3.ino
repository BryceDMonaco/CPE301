/*
 * Bryce Monaco
 * (Some code from Echo3C.txt originally written by Dr. Egbert)
 * CPE 301 (Lab Section 1102)
 * Lab 08 Echo 3 - Version 1.0
 * 
 */
 
#define RDA 0x80
#define TBE 0x20  
volatile unsigned char *myUCSR0A = (unsigned char *) 0xC0;
volatile unsigned char *myUCSR0B = (unsigned char *) 0xC1;
volatile unsigned char *myUCSR0C = (unsigned char *) 0xC2;
volatile unsigned int  *myUBRR0  = (unsigned int *)  0xC4;
volatile unsigned char *myUDR0   = (unsigned char *) 0xC6;

void U0init (int rate);
unsigned char U0kbhit ();
unsigned char U0getchar ();
void U0putchar (unsigned char U0pdata);

void setup()
{
  // initialize the serial port on USART0:
  U0init(9600);
  
}

void loop()
{
  unsigned char cs1;
  while (U0kbhit()==0); // wait for RDA = true
  cs1 = U0getchar();    // read character
  U0putchar(cs1);     // echo character
  
}

void U0init(int U0baud)
{
  unsigned long FCPU = 16000000;
  unsigned int tbaud;
  tbaud = (FCPU / 16 / U0baud - 1);
  *myUCSR0A = 0x20;
  *myUCSR0B = 0x18;
  *myUCSR0C = 0x06;
  *myUBRR0  = tbaud;
 
}

unsigned char U0kbhit()
{
  return (*myUCSR0A >> 7); //Shifted to the 0th bit

}

unsigned char U0getchar()
{
  return *myUDR0;
  
}

void U0putchar(unsigned char U0pdata)
{  
  //*myUDR0 = U0pdata;
  while ((*myUCSR0A & 0x20) != 0x20); //Wait for data register to be empty
  *myUDR0 = '0';
  while ((*myUCSR0A & 0x20) != 0x20); //Wait for data register to be empty
  *myUDR0 = 'x';

  while ((*myUCSR0A & 0x20) != 0x20); //Wait for data register to be empty

  unsigned tempCharH = GetHigh4Bits (U0pdata);

  if (tempCharH > 0x09)
  {
    *myUDR0 =  tempCharH + 0x41 - 0x0A;
    
  } else
  {
    *myUDR0 =  tempCharH + 0x30;
    
  }
  
  //*myUDR0 = GetHigh4Bits (U0pdata) + 0x30;

  while ((*myUCSR0A & 0x20) != 0x20); //Wait for data register to be empty
  
  unsigned tempCharL = GetLow4Bits (U0pdata);

  if (tempCharL > 0x09)
  {
    *myUDR0 =  tempCharL + 0x41 - 0x0A;
    
  } else
  {
    *myUDR0 =  tempCharL + 0x30;
    
  }

  while ((*myUCSR0A & 0x20) != 0x20); //Wait for data register to be empty
  
  *myUDR0 = ' ';
  
  //*myUDR0 = U0pdata;

  return;
  
}

unsigned char GetHigh4Bits (unsigned char sentChar)
{
  sentChar >>= 4; //Shift the value four bits to the right, ex 0100 1010 -> 0000 0100

  return sentChar;
  
}

unsigned char GetLow4Bits (unsigned char sentChar)
{
  sentChar &= 0x0F; //Mask out the high 4 bits, ex 0100 1010 & 0000 1111 -> 0000 1010

  return sentChar;
  
}


