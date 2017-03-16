/*
 * Bryce Monaco
 * CPE 301 (Lab Section 1102)
 * Lab 06 - Version 1.0
 * 
 */

//GPIO Pointers for Port B, See Mega Datasheet PDF Chapter 33 pg 403
volatile unsigned char *portDDRB = (unsigned char *) 0x24; 
volatile unsigned char *portB =    (unsigned char *) 0x25;
volatile unsigned char *pinB =     (unsigned char *) 0x23;

volatile unsigned char *portDDRK = (unsigned char *) 0x107;
volatile unsigned char *portK =    (unsigned char *) 0x108;

void setup() 
{
  *portDDRB = 0x80; //Set LED (p7) to output and p0 as input
  *portB = 0x0F; //Set p0-p3 as pullup input

  *portDDRK = 0xFF; //Make all pins output, bit 7/PK7 doesn't get used
  *portK = 0x00; //Make LED blank/clear the buffer

}

//These values print their index number in hexidecimal on the display, for example at [2] is 0x5B which displays a '2' on the display
unsigned char values[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

void loop() 
{
 
  /*
  //Input testing on PB0
  if ((*pinB & 0x01) == 1)
  {
    *portB |= 0x80;
    
  } else
  {
    *portB &= 0x7F;
    
  }
*/
/*
  for (int i = 0; i < 16; i++)
  {
    *portK = values[i];

    delay(500);
    
  }
*/ 

  *portK = values[(*pinB & 0x0F)];  //Take the input from the switches, mask out bits 4-7, and use it as an array index (see values[] comment)
                                    //...and output it to Port K 
  
}
