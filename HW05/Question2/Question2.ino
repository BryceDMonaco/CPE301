/*
 * Bryce Monaco
 * CS 365 (Lab Section 1102)
 * HW05 - Question 2
 * 
 */

//Clock Pointers, See Mega Datasheet PDF Chapter 17.11 for Reg Summary
volatile unsigned char* thisTCCR1A = (unsigned char *) 0x80; //Contains WGM10 (bit 0) and WGN11 (bit 1)
volatile unsigned char* thisTCCR1B = (unsigned char *) 0x81; //Contains WGM12 (bit 3) and WGN13 (bit 4)
volatile unsigned char* thisTCCR1C = (unsigned char *) 0x82; //Contains FOC1A through C (bits 5 to 7)
volatile unsigned char* thisTIMSK1 = (unsigned char *) 0x6F; //Interrupt Mask Register
volatile unsigned int*  thisTCNT1  = (unsigned  int *) 0x84; //Timer1 Counter, 16b, H byte at 0x85
volatile unsigned char* thisTIFR1  = (unsigned char *) 0x36; //Contains TOV1 (overflow flag) (bit 0)

//GPIO Pointers for Port B, See Mega Datasheet PDF Chapter 33 pg 403
volatile unsigned char *portDDRB = (unsigned char *) 0x24; 
volatile unsigned char *portB =    (unsigned char *) 0x25;

void MyDelay (unsigned long mSeconds);

void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  //*portDDRB |= 0x80; //LED is conected to PB7, used for debugging
  *portDDRB |= 0x40; //Speaker connected to PB6, pin 12

  //Set the timer to Normal mode
  *thisTCCR1A = 0;
  *thisTCCR1B = 0;
  *thisTCCR1C = 0;
  *thisTIMSK1 = 0;
    
}

//Per request of Dr. Egbert, to reduce function calling overhead the function MyDelay has been copied directly into the loop function
//...in place of regular function calls

void loop() 
{
  //T of 440 Hz tone = 1/440 = 0.00227273 s -> 2.27273 ms
  
  *portB |= 0x40;
  
  *thisTCCR1B &= 0xF8;              //Disable Timer
  *thisTCNT1 = (unsigned int) (65536 - (long) (15.625 * 20)); //The timer will count up from the value to the max 65536
  *thisTCCR1B |= 0b00000101;        //Set pre-scalar 1024 and start Timer, I'm not sure if the function should choose what pre-scalar to use
                                    //...or if it's safest to just stick to one
  
  while ((*thisTIFR1 & 0x01) == 0);    //Wait for overflow flag 
  
  *thisTCCR1B &= 0xF8;              //Disable Timer                         
  *thisTIFR1 |= 0x01;               //Reset the flag

  *portB &= 0xBF;

  *thisTCCR1B &= 0xF8;              //Disable Timer
  *thisTCNT1 = (unsigned int) (65536 - (long) (15.625 * 20)); //The timer will count up from the value to the max 65536
  *thisTCCR1B |= 0b00000101;        //Set pre-scalar 1024 and start Timer, I'm not sure if the function should choose what pre-scalar to use
                                    //...or if it's safest to just stick to one
  
  while ((*thisTIFR1 & 0x01) == 0);    //Wait for overflow flag 
  
  *thisTCCR1B &= 0xF8;              //Disable Timer                         
  *thisTIFR1 |= 0x01;               //Reset the flag
  
}

//Not directly called in this program, thought it would be good to have in though
void MyDelay (unsigned long mSeconds)
{
  *thisTCCR1B &= 0xF8;              //Disable Timer
  *thisTCNT1 = (unsigned int) (65536 - (long) (15.625 * mSeconds)); //The timer will count up from the value to the max 65536
  *thisTCCR1B |= 0b00000101;        //Set pre-scalar 1024 and start Timer, I'm not sure if the function should choose what pre-scalar to use
                                    //...or if it's safest to just stick to one
  
  while ((*thisTIFR1 & 0x01) == 0);    //Wait for overflow flag 
  
  *thisTCCR1B &= 0xF8;              //Disable Timer                         
  *thisTIFR1 |= 0x01;               //Reset the flag

  return;
  
}
