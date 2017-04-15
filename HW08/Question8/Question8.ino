/*
 * Bryce Monaco
 * CPE 301 (Lab Section 1102)
 * HW08 - Question 8 - Version 1.0
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

//Status Register
volatile unsigned char *thisSREG = (unsigned char *) 0x5F;

void MyDelay (unsigned long mSeconds);

void setup() 
{  
  // initialize digital pin LED_BUILTIN as an output.
  *portDDRB |= 0x80; //LED is conected to PB7, used for debugging
  *portB = 0x00; //Start with the LED off

  //Set the timer to Normal mode
  *thisTCCR1A = 0;
  *thisTCCR1B = 0;
  *thisTCCR1C = 0;
  *thisTIMSK1 = 0x01; //Enable interrupt

  *thisSREG |= 0x80; //Enable global interrupts

  //Run the timer for the first time to start the cycle
 InitializeTimer();
    
}

void loop() 
{
    
}

/*
 * Note number of ticks (160) was found with the following equation:
 *          ((1/x)/(6.25*10^-8))
 * Where x is the frequncy (in this case 100,000) and 6.25*10^-8 is the period of the CPU (1/16 MHz).
 * 
 */

void InitializeTimer ()
{
  *thisTCCR1B &= 0xF8;              //Disable Timer
  *thisTCNT1 = (unsigned int) (65536 - 160); //The timer will count up from the value to the max 65536
  *thisTCCR1B |= 0b00000001; //Run the timer at PS1

  return;
  
}

ISR(TIMER1_OVF_vect)
{  
  if ((*portB & 0x80) == 0x80) //LED is on
  {
    *portB &= 0x7F; //Disable the LED
    
  } else
  {
    *portB |= 0x80; //Enable the LED
     
  }
  
  *thisTCCR1B &= 0xF8;              //Disable Timer
  *thisTCNT1 = (unsigned int) (65536 - 160); //The timer will count up from the value to the max 65536
  *thisTCCR1B |= 0b00000001; //Run the timer at PS1
  
}
